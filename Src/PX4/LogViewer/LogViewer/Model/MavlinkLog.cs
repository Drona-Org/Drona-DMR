using LogViewer.Utilities;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using System.Reflection;
using Microsoft.Networking.Mavlink;
using LogViewer.Controls;
using System.Collections;
using System.Threading;

namespace LogViewer.Model
{
    class MavlinkLog : IDataLog
    {
        string file;
        DateTime startTime;
        TimeSpan duration;
        List<Message> data;
        LogItemSchema schema = new LogItemSchema() { Name = "MavlinkLog", Type = "Root" };
        Dictionary<Type, LogItemSchema> schemaCache = new Dictionary<Type, LogItemSchema>();

        internal class Message
        {
            public MavLinkMessage Msg;
            public ulong Ticks;
            public DateTime Timestamp;
            public object TypedValue;
        }

        public MavlinkLog()
        {
            MaxSize = 1000000;
        }

        public LogItemSchema Schema
        {
            get { return this.schema; }
        }

        public DateTime StartTime
        {
            get { return startTime; }
        }
        public TimeSpan Duration
        {
            get { return duration; }
        }

        public IEnumerable<DataValue> GetDataValues(LogItemSchema schema, DateTime startTime, TimeSpan duration)
        {
            if (schema != null)
            {
                foreach (var msg in GetMessages(startTime, duration))
                {
                    DataValue value = GetDataValue(schema, msg);
                    if (value != null)
                    {
                        yield return value;
                    }
                }
            }
        }

        internal DataValue GetDataValue(LogItemSchema schema, Message msg)
        {
            // we support 3 levels of nesting, so schema could be the row, the column or an array item.
            LogItemSchema rowSchema = schema;
            LogItemSchema columnSchema = schema;
            LogItemSchema arraySchema = schema;
            if (rowSchema.Parent != this.schema)
            {
                rowSchema = rowSchema.Parent;
            }
            if (rowSchema.Parent != this.schema)
            {
                columnSchema = rowSchema;
                rowSchema = rowSchema.Parent;
            }

            StringBuilder textBuilder = new StringBuilder();
            var row = msg.TypedValue;
            if (row != null && row.GetType().Name == rowSchema.Name)
            {
                // get a time value for this message.
                FieldInfo fi = row.GetType().GetField(columnSchema.Name, BindingFlags.Public | BindingFlags.Instance);
                if (fi != null)
                {
                    object value = fi.GetValue(row);
                    DataValue data = new DataValue() { X = msg.Ticks };
                    // byte array is special (we treat this like text).
                    if (value is byte[])
                    {
                        textBuilder.Length = 0;
                        byte[] text = (byte[])value;
                        bool binary = false;
                        // see if this is binary or text.
                        for (int i = 0, n = text.Length; i < n; i++)
                        {
                            byte b = text[i];
                            if (b != 0 && b < 0x20 || b > 0x80)
                            {
                                binary = true;
                            }
                        }

                        for (int i = 0, n = text.Length; i < n; i++)
                        {
                            byte b = text[i];
                            if (b != 0)
                            {
                                if (binary)
                                {
                                    textBuilder.Append(b.ToString("x2"));
                                    textBuilder.Append(" ");
                                }
                                else
                                {
                                    char ch = Convert.ToChar(b);
                                    textBuilder.Append(ch);
                                }
                            }
                        }

                        data.Label = textBuilder.ToString();
                    }
                    else if (value is string)
                    {
                        data.Label = (string)value;
                    }
                    else
                    {
                        if (fi.FieldType.IsArray)
                        {
                            // then we are expecting an array selector as well...
                            Array a = (Array)value;
                            int index = 0;
                            int.TryParse(arraySchema.Name, out index);
                            if (a.Length > index)
                            {
                                value = a.GetValue(index);
                            }
                        }

                        data.Y = ConvertToNumeric(value);
                    };
                    return data;
                }
            }
            return null;
        }

        public IEnumerable<DataValue> LiveQuery(LogItemSchema schema, CancellationToken token)
        {
            return new MavlinkQuery(this, schema, token);
        }

        internal void AddQuery(MavlinkQueryEnumerator q)
        {
            lock (queryEnumerators)
            {
                queryEnumerators.Add(q);
            }
        }
        internal void RemoveQuery(MavlinkQueryEnumerator q)
        {
            lock (queryEnumerators)
            {
                queryEnumerators.Remove(q);
            }
        }

        /// <summary>
        /// This implements a nice little reactive stream over the DataValues.
        /// </summary>
        internal class MavlinkQuery : IEnumerable<DataValue>
        {
            private MavlinkLog log;
            private LogItemSchema schema;
            private CancellationToken token;

            internal MavlinkQuery(MavlinkLog log, LogItemSchema schema, CancellationToken token)
            {
                this.log = log;
                this.schema = schema;
                this.token = token;
            }

            public IEnumerator<DataValue> GetEnumerator()
            {
                return new MavlinkQueryEnumerator(this.log, this.schema, this.token);
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return new MavlinkQueryEnumerator(this.log, this.schema, this.token);
            }

        }

        internal class MavlinkQueryEnumerator : IEnumerator<DataValue>
        {
            private MavlinkLog log;
            private LogItemSchema schema;
            private DataValue current;
            private DataValue next;
            private CancellationToken token;
            private bool disposed;
            private bool waiting;
            private System.Threading.Semaphore available = new System.Threading.Semaphore(0, 1);

            internal MavlinkQueryEnumerator(MavlinkLog log, LogItemSchema schema, CancellationToken token)
            {
                this.log = log;
                this.schema = schema;
                this.token = token;
                this.log.AddQuery(this);
            }

            internal void Add(Message msg)
            {
                DataValue d = this.log.GetDataValue(schema, msg);
                if (d != null)
                {
                    next = d;
                    if (waiting)
                    {
                        available.Release();
                    }
                }
            }

            public DataValue Current
            {
                get { return current; }
            }

            object IEnumerator.Current
            {
                get { return current; }
            }

            public void Dispose()
            {
                disposed = true;
                this.log.RemoveQuery(this);
            }

            public bool MoveNext()
            {
                if (disposed || token.IsCancellationRequested)
                {
                    return false;
                }

                if (next == null)
                {
                    waiting = true;
                    WaitHandle.WaitAny(new[] { available, token.WaitHandle });
                    waiting = false;
                }
                current = next;

                return true;
            }

            public void Reset()
            {
                // this is a forward only infinite stream.
                throw new NotSupportedException();
            }
        }



        IEnumerable<Message> GetMessages(DateTime startTime, TimeSpan duration)
        {
            bool allValues = (startTime == DateTime.MinValue && duration == TimeSpan.MaxValue);
            DateTime endTime = allValues ? DateTime.MaxValue : startTime + duration;

            lock (data)
            {
                foreach (Message message in data)
                {
                    var timestamp = message.Timestamp;
                    bool include = allValues;
                    if (!include)
                    {
                        include = (timestamp >= startTime && timestamp <= endTime);
                    }
                    if (include)
                    {
                        yield return message;
                    }
                }
            }
        }

        public IEnumerable<LogEntry> GetRows(string typeName, DateTime startTime, TimeSpan duration)
        {
            foreach (var msg in GetMessages(startTime, duration))
            {
                object typedValue = msg.TypedValue;

                if (typedValue != null)
                {
                    if (typeName == "GPS" )
                    {
                        // do auto-conversion from MAVLink.mavlink_global_position_int_t
                        if (typedValue is MAVLink.mavlink_global_position_int_t)
                        {
                            MAVLink.mavlink_global_position_int_t gps = (MAVLink.mavlink_global_position_int_t)typedValue;
                            LogEntry e = new LogEntry();
                            e.SetField("GPSTime", (ulong)gps.time_boot_ms);
                            e.SetField("Lat", (float)gps.lat);
                            e.SetField("Lon", (float)gps.lon);
                            e.SetField("Alt", (float)((double)gps.alt / 1000));
                            e.SetField("nSat", 9); // fake values so the map works
                            e.SetField("EPH", 1);
                            yield return e;
                        }
                    }
                }
            }
        }

        List<MavlinkQueryEnumerator> queryEnumerators = new List<MavlinkQueryEnumerator>();

        internal Message AddMessage(MavLinkMessage e)
        {
            if (this.data == null)
            {
                this.data = new List<Message>();
            }

            DateTime time = epoch.AddMilliseconds(e.Time / 1000);

            Message msg = new Model.MavlinkLog.Message()
            {
                Msg = e,
                Timestamp = time,
                Ticks = e.Time
            };

            if (e.TypedPayload == null) {
                Type msgType = MAVLink.MAVLINK_MESSAGE_INFO[(int)e.MsgId];
                if (msgType != null)
                {
                    byte[] msgBuf = new byte[256];
                    GCHandle handle = GCHandle.Alloc(msgBuf, GCHandleType.Pinned);
                    IntPtr ptr = handle.AddrOfPinnedObject();

                    // convert to proper mavlink structure.
                    msg.TypedValue = Marshal.PtrToStructure(ptr, msgType);

                    handle.Free();
                }
            }
            else
            {
                msg.TypedValue = e.TypedPayload;
            }

            lock (data)
            {
                this.data.Add(msg);
                if (this.data.Count > MaxSize)
                {
                    this.data.RemoveAt(0);
                }
            }
            if (msg.TypedValue != null)
            {
                CreateSchema(msg.TypedValue);
            }

            lock (queryEnumerators)
            {
                foreach (var q in queryEnumerators)
                {
                    q.Add(msg);
                }
            }
            return msg;
        }

        public int MaxSize { get; set; }

        public DateTime GetTime(ulong timeMs)
        {
            return startTime.AddMilliseconds(timeMs);
        }


        private double ConvertToNumeric(object value)
        {
            if (value == null) return 0;
            if (value is Array)
            {
                Array a = (Array)value;
                if (a.Length > 0)
                {
                    // todo: need a way for user to retrieve specific indexes from this array...
                    object x = a.GetValue(0);
                    return Convert.ToDouble(x);
                }
                return 0;
            }
            return Convert.ToDouble(value);
        }

        List<Flight> flights;

        public IEnumerable<Flight> GetFlights()
        {
            if (flights == null)
            {
                flights = new List<Model.Flight>();
                int min = int.MaxValue;
                int max = int.MinValue;
                // compute the min/max servo settings.
                foreach (var msg in this.data)
                {
                    if (msg.TypedValue is MAVLink.mavlink_servo_output_raw_t)
                    {
                        MAVLink.mavlink_servo_output_raw_t servo = (MAVLink.mavlink_servo_output_raw_t)msg.TypedValue;
                        if (servo.servo1_raw != 0)
                        {
                            min = Math.Min(min, servo.servo1_raw);
                            max = Math.Max(max, servo.servo1_raw);
                        }
                    }
                }

                // find flights
                DateTime start = this.startTime;
                DateTime endTime = start;
                Flight current = null;
                int offCount = 0;
                // compute the min/max servo settings.
                foreach (var msg in this.data)
                {
                    if (msg.TypedValue is MAVLink.mavlink_servo_output_raw_t)
                    {
                        MAVLink.mavlink_servo_output_raw_t servo = (MAVLink.mavlink_servo_output_raw_t)msg.TypedValue;
                        endTime = start.AddMilliseconds(servo.time_usec / 1000);
                        if (servo.servo1_raw > min)
                        {
                            if (current == null)
                            {
                                current = new Flight()
                                {
                                    Log = this,
                                    StartTime = start.AddMilliseconds(servo.time_usec / 1000)
                                };
                                flights.Add(current);
                                offCount = 0;
                            }
                        }
                        else if (servo.servo1_raw == min && offCount++ > 10)
                        {
                            if (current != null)
                            {
                                current.Duration = endTime - current.StartTime;
                                current = null;
                            }
                        }
                    }
                }
                if (current != null)
                {
                    current.Duration = endTime - current.StartTime;
                }

            }

            return flights;
        }

        static DateTime epoch = new DateTime(1970, 1, 1);

        public async Task Load(string file, ProgressUtility progress)
        {
            this.file = file;
            this.startTime = DateTime.MinValue;
            this.duration = TimeSpan.Zero;
            bool first = true;
            // QT time is milliseconds from the following epoch.
            byte[] msgBuf = new byte[256];
            GCHandle handle = GCHandle.Alloc(msgBuf, GCHandleType.Pinned);
            IntPtr ptr = handle.AddrOfPinnedObject();
            
            DateTime lastTime = DateTime.MinValue;

            await Task.Run(() =>
            {
                // MAVLINK_MSG_ID
                using (Stream s = File.OpenRead(file))
                {
                    BinaryReader reader = new BinaryReader(s);
                    while (s.Position < s.Length)
                    {
                        progress.ShowProgress(0, s.Length, s.Position);

                        try
                        {
                            MavLinkMessage header = new MavLinkMessage();
                            header.ReadHeader(reader);

                            while (!header.IsValid())
                            {
                                // hmm. looks like a bad record, so now what?
                                header.ShiftHeader(reader);
                            }

                            int read = s.Read(msgBuf, 0, header.Length);
                            if (read == header.Length)
                            {
                                header.Crc = reader.ReadUInt16();

                                if (!header.IsValidCrc(msgBuf, read))
                                {
                                    continue;
                                }

                                Type msgType = MAVLink.MAVLINK_MESSAGE_INFO[(int)header.MsgId];
                                if (msgType != null)
                                {
                                    // convert to proper mavlink structure.
                                    header.TypedPayload = Marshal.PtrToStructure(ptr, msgType);
                                }

                                Message message = AddMessage(header);
                                if (first)
                                {
                                    startTime = message.Timestamp; 
                                    first = false;
                                }
                            }
                        }
                        catch
                        {
                            // try and continue...
                        }
                    }
                }
                handle.Free();
            });
            this.duration = lastTime - startTime;
        }

        private void CreateSchema(object message)
        {
            Type t = message.GetType();
            if (schemaCache.ContainsKey(t))
            {
                return;
            }

            LogItemSchema item = new LogItemSchema() { Name = t.Name, Type = t.Name, ChildItems = new List<LogItemSchema>(), Parent = this.schema };

            foreach (FieldInfo fi in t.GetFields(BindingFlags.Public | BindingFlags.Instance))
            {
                var field = new LogItemSchema() { Name = fi.Name, Type = fi.FieldType.Name, Parent = item };
                item.ChildItems.Add(field);

                object value = fi.GetValue(message);
                // byte[] array is special, we return that as binhex encoded binary data.
                if (fi.FieldType.IsArray && fi.FieldType != typeof(byte[]))
                {
                    field.ChildItems = new List<Model.LogItemSchema>();
                    Type itemType = fi.FieldType.GetElementType();
                    Array a = (Array)value;
                    for (int i = 0, n = a.Length; i < n; i++)
                    {
                        field.ChildItems.Add(new LogItemSchema() { Name = i.ToString(), Type = itemType.Name, Parent = field });
                    }
                }
            }
            schemaCache[t] = item;

            if (schema.ChildItems == null)
            {
                schema.ChildItems = new List<LogItemSchema>();
            }
            schema.ChildItems.Add(item);

            if (SchemaChanged != null)
            {
                SchemaChanged(this, EventArgs.Empty);
            }
        }

        public event EventHandler SchemaChanged;

        internal void Clear()
        {
            this.data = new List<Message>();
            LogItemSchema schema = new LogItemSchema() { Name = "MavlinkLog", Type = "Root" };
            Dictionary<Type, LogItemSchema> schemaCache = new Dictionary<Type, LogItemSchema>();

        }
    }
}
