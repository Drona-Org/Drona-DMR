﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Microsoft.Networking.Mavlink
{
    public class MavLinkMessage
    {
        public byte Magic { get; set; }
        public MAVLink.MAVLINK_MSG_ID MsgId { get; set; }
        public byte Length { get; set; }
        public byte ComponentId { get; set; }
        public byte SystemId { get; set; }
        public byte SequenceNumber { get; set; }
        public ushort Crc { get; set; }
        public UInt64 Time { get; set; }
        public byte[] Payload { get; set; }
        public object TypedPayload { get; set; }

        public override string ToString()
        {
            return Newtonsoft.Json.JsonConvert.SerializeObject(this);
        }

        public byte[] Pack()
        {
            const byte MAVLINK_STX = 254;
            Serialize();
            int length = Payload.Length;
            if (length + 7 > 255)
            {
                throw new Exception("Message is too long.  Must be less than 248 bytes");
            }
            byte[] fullMessage = new byte[length + 8];
            fullMessage[0] = MAVLINK_STX; // magic marker
            fullMessage[1] = (byte)length;
            fullMessage[2] = this.SequenceNumber;
            fullMessage[3] = this.SystemId;
            fullMessage[4] = this.ComponentId;
            fullMessage[5] = (byte)this.MsgId;
            Array.Copy(Payload, 0, fullMessage, 6, length);
            this.Crc = crc_calculate();
            fullMessage[6 + length] = (byte)(this.Crc);
            fullMessage[6 + length + 1] = (byte)(this.Crc >> 8);
            return fullMessage;
        }

        public void ReadHeader(BinaryReader reader)
        {
            Time = ConvertBigEndian(reader.ReadUInt64());
            Magic = reader.ReadByte();
            Length = reader.ReadByte();
            SequenceNumber = reader.ReadByte();
            SystemId = reader.ReadByte();
            ComponentId = reader.ReadByte();
            MsgId = (MAVLink.MAVLINK_MSG_ID)reader.ReadByte();
        }

        private ulong ConvertBigEndian(ulong v)
        {
            ulong result = 0;
            ulong shift = v;
            for (int i = 0; i < 8; i++)
            {
                ulong low = (shift & 0xff);
                result = (result << 8) + low;
                shift >>= 8;
            }
            return result;
        }

        public bool IsValid()
        {
            return Magic == 254 && Length <= 255 && SystemId < 10 && ComponentId < 10;
        }

        /// <summary>
        /// Read 1 byte and shift left the whole structure until we find something that looks like a valid header.
        /// </summary>
        /// <param name="reader"></param>
        public void ShiftHeader(BinaryReader reader)
        {
            Time = (Time << 8) + (ulong)(Crc << 8);
            Crc = (UInt16)((Crc << 8) + Magic);
            Magic = Length;
            Length = SequenceNumber;
            SequenceNumber = SystemId;
            SystemId = ComponentId;
            ComponentId = (byte)MsgId;
            MsgId = (MAVLink.MAVLINK_MSG_ID)reader.ReadByte();
        }

        public bool IsValidCrc(byte[] msg, int len)
        {
            ushort crc = crc_calculate(msg, len);
            return crc == this.Crc;
        }

        public ushort crc_calculate()
        {
            return crc_calculate(this.Payload, this.Payload.Length);
        }

        private ushort crc_calculate(byte[] buffer, int len)
        {
            byte crc_extra = MAVLink.MAVLINK_MESSAGE_CRCS[(int)this.MsgId];
            ushort crcTmp = 0xffff; // X25_INIT_CRC;
            // Start with the MAVLINK_CORE_HEADER_LEN bytes.
            crcTmp = crc_accumulate((byte)this.Length, crcTmp);
            crcTmp = crc_accumulate((byte)this.SequenceNumber, crcTmp);
            crcTmp = crc_accumulate((byte)this.SystemId, crcTmp);
            crcTmp = crc_accumulate((byte)this.ComponentId, crcTmp);
            crcTmp = crc_accumulate((byte)this.MsgId, crcTmp);
            crcTmp = crc_accumulate(buffer, len, crcTmp);
            return crc_accumulate(crc_extra, crcTmp);
        }

        static ushort crc_accumulate(byte[] msg, int len, ushort crcTmp)
        {
            for (int i = 0; i < len; i++)
            {
                crcTmp = crc_accumulate(msg[i], crcTmp);
            }
            return crcTmp;
        }

        static ushort crc_accumulate(byte data, ushort crcAccum)
        {
            /*Accumulate one byte of data into the CRC*/
            byte tmp;
            tmp = (byte)(data ^ (byte)(crcAccum & 0xff));
            tmp ^= (byte)(tmp << 4);
            return (ushort)((crcAccum >> 8) ^ (tmp << 8) ^ (tmp << 3) ^ (tmp >> 4));
        }

        public void Deserialize()
        {
            GCHandle handle = GCHandle.Alloc(this.Payload, GCHandleType.Pinned);
            IntPtr ptr = handle.AddrOfPinnedObject();
            Type msgType = MAVLink.MAVLINK_MESSAGE_INFO[(int)this.MsgId];
            if (msgType != null)
            {
                object typed = Marshal.PtrToStructure(ptr, msgType);

                this.TypedPayload = typed;

                if (typed != null && typed.GetType() == typeof(MAVLink.mavlink_statustext_t))
                {
                    // convert the byte[] text to something readable.
                    MAVLink.mavlink_statustext_t s = (MAVLink.mavlink_statustext_t)typed;
                    mavlink_statustext_t2 t2 = new mavlink_statustext_t2()
                    {
                        severity = s.severity,
                    };
                    if (s.text != null)
                    {
                        int i = 0;
                        int n = s.text.Length;
                        for (i = 0; i < n; i++)
                        {
                            if (s.text[i] == 0)
                            {
                                break;
                            }
                        }
                        t2.text = Encoding.UTF8.GetString(s.text, 0, i);
                    }
                    this.TypedPayload = t2;
                }
            }
        }

        internal void Serialize()
        {
            if (this.TypedPayload != null && this.Payload == null)
            {
                int size = Marshal.SizeOf(this.TypedPayload);
                IntPtr ptr = Marshal.AllocCoTaskMem(size);
                Marshal.StructureToPtr(this.TypedPayload, ptr, false);
                byte[] block = new byte[size];
                Marshal.Copy(ptr, block, 0, size);
                Marshal.FreeCoTaskMem(ptr);
                this.Payload = block;
                this.Length = (byte)block.Length;
            }
        }
    }

    public class MavlinkChannel
    {
        IPort port;
        byte seqno;

        public void Start(IPort port)
        {
            this.port = port;

            Task.Run(() => ReceiveThread());
        }

        public void Stop()
        {
            IPort p = this.port;
            if (p != null)
            {
                this.port = null;
                p.Close();
            }
        }

        public void SendMessage(MavLinkMessage msg)
        {
            msg.SequenceNumber = seqno++;
            byte[] buffer = msg.Pack();
            if (this.port == null)
            {
                throw new Exception("Please call Start to provide the mavlink Port we are using");
            }
            this.port.Write(buffer, buffer.Length);
        }

        public event EventHandler<MavLinkMessage> MessageReceived;

        void ReceiveThread()
        {
            byte[] buffer = new byte[1];

            MavLinkMessage msg = null;
            ReadState state = ReadState.Init;
            int payloadPos = 0;
            ushort crc = 0;

            try
            {

                while (this.port != null)
                {
                    int len = this.port.Read(buffer, 1);
                    if (len == 1)
                    {
                        byte b = buffer[0];
                        switch (state)
                        {
                            case ReadState.Init:
                                if (b == MagicMarker)
                                {
                                    state = ReadState.GotMagic;
                                    msg = new MavLinkMessage();
                                    msg.Time = (ulong)Environment.TickCount;
                                    msg.Magic = MagicMarker;
                                    payloadPos = 0;
                                    crc = 0;
                                }
                                break;
                            case ReadState.GotMagic:
                                msg.Length = b;
                                msg.Payload = new byte[msg.Length];
                                state = ReadState.GotLength;
                                break;
                            case ReadState.GotLength:
                                msg.SequenceNumber = b;
                                state = ReadState.GotSequenceNumber;
                                break;
                            case ReadState.GotSequenceNumber:
                                msg.SystemId = b;
                                state = ReadState.GotSystemId;
                                break;
                            case ReadState.GotSystemId:
                                msg.ComponentId = b;
                                state = ReadState.GotComponentId;
                                break;
                            case ReadState.GotComponentId:
                                msg.MsgId = (MAVLink.MAVLINK_MSG_ID)b;
                                if (msg.Length == 0)
                                {
                                    // done!
                                    state = ReadState.GotPayload;
                                }
                                else
                                {
                                    state = ReadState.GotMessageId;
                                }
                                break;

                            case ReadState.GotMessageId:
                                // read in the payload.
                                msg.Payload[payloadPos++] = b;
                                if (payloadPos == msg.Length)
                                {
                                    state = ReadState.GotPayload;
                                }
                                break;
                            case ReadState.GotPayload:
                                crc = b;
                                state = ReadState.GotCrc1;
                                break;
                            case ReadState.GotCrc1:
                                crc = (ushort)((b << 8) + crc);
                                // ok, let's see if it's good.
                                msg.Crc = crc;
                                ushort found = msg.crc_calculate();
                                if (found != crc)
                                {
                                    // bad crc!!
                                }
                                else
                                {
                                    // try and deserialize the payload.
                                    msg.Deserialize();
                                    if (MessageReceived != null)
                                    {
                                        MessageReceived(this, msg);
                                    }
                                }
                                state = ReadState.Init;
                                break;
                        }
                    }

                }

            }
            catch (Exception)
            {
                // port was closed
            }
        }

        enum ReadState
        {
            Init,
            GotMagic,
            GotLength,
            GotSequenceNumber,
            GotSystemId,
            GotComponentId,
            GotMessageId,
            GotPayload,
            GotCrc1
        }

        const int MagicMarker = 254;

    }


    public struct mavlink_statustext_t2
    {
        /// <summary> Severity of status. Relies on the definitions within RFC-5424. See enum MAV_SEVERITY. </summary>
        public byte severity;
        /// <summary> Status text message, without null termination character </summary>            
        public string text;

    };


}
