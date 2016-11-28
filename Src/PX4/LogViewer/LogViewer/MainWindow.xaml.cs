using LogViewer.Controls;
using LogViewer.Model;
using LogViewer.Utilities;
using Microsoft.Maps.MapControl.WPF;
using Microsoft.Networking.Mavlink;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Xml.Linq;

namespace LogViewer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        const double MaxChartHeight = 400;
        ProgressUtility progress;
        List<IDataLog> logs = new List<IDataLog>();
        ObservableCollection<Flight> allFlights = new ObservableCollection<Flight>();
        DelayedActions delayedActions = new DelayedActions();
        Quaternion initialAttitude;
        MapPolyline currentFlight;
        MavlinkLog currentFlightLog;

        public MainWindow()
        {
            InitializeComponent();

            UiDispatcher.Initialize();

            this.progress = new ProgressUtility(MyProgress);
            MyProgress.Visibility = Visibility.Collapsed;
            UpdateButtons();
            FlightView.ItemsSource = allFlights;
            ConnectionPanel.DownloadCompleted += OnLogDownloadComplete;
            ConnectionPanel.Connected += OnChannelConnected;
            ConnectionPanel.Disconnected += OnChannelDisconnected;
            this.Visibility = Visibility.Hidden;
            RestoreSettings();
            this.SizeChanged += OnWindowSizeChanged;
            this.LocationChanged += OnWindowLocationChanged;
            ChartStack.Visibility = Visibility.Collapsed;
            initialAttitude = ModelViewer.ModelAttitude;
            CameraPanel.Visibility = Visibility.Collapsed;
        }

        private void OnWindowLocationChanged(object sender, EventArgs e)
        {
            delayedActions.StartDelayedAction("SaveWindowLocation", SavePosition, TimeSpan.FromMilliseconds(1000));
        }

        private void OnWindowSizeChanged(object sender, SizeChangedEventArgs e)
        {
            delayedActions.StartDelayedAction("SaveWindowLocation", SavePosition, TimeSpan.FromMilliseconds(1000));
        }

        private async void RestoreSettings()
        {
            Settings settings = await ((App)App.Current).LoadSettings();
            if (settings.WindowLocation.X != 0 && settings.WindowSize.Width != 0 && settings.WindowSize.Height != 0)
            {
                // make sure it is visible on the user's current screen configuration.
                var bounds = new System.Drawing.Rectangle(
                    XamlExtensions.ConvertFromDeviceIndependentPixels(settings.WindowLocation.X),
                    XamlExtensions.ConvertFromDeviceIndependentPixels(settings.WindowLocation.Y),
                    XamlExtensions.ConvertFromDeviceIndependentPixels(settings.WindowSize.Width),
                    XamlExtensions.ConvertFromDeviceIndependentPixels(settings.WindowSize.Height));
                var screen = System.Windows.Forms.Screen.FromRectangle(bounds);
                bounds.Intersect(screen.WorkingArea);

                this.Left = XamlExtensions.ConvertToDeviceIndependentPixels(bounds.X);
                this.Top = XamlExtensions.ConvertToDeviceIndependentPixels(bounds.Y);
                this.Width = XamlExtensions.ConvertToDeviceIndependentPixels(bounds.Width);
                this.Height = XamlExtensions.ConvertToDeviceIndependentPixels(bounds.Height);
            }
            ConnectionPanel.DefaultUdpPort = settings.Port;
            this.Visibility = Visibility.Visible;
        }

        async void SavePosition()
        {
            var bounds = this.RestoreBounds;

            Settings settings = await ((App)App.Current).LoadSettings();
            settings.WindowLocation = bounds.TopLeft;
            settings.WindowSize = bounds.Size;
            await settings.SaveAsync();
        }

        private async void OnChannelConnected(object sender, EventArgs e)
        {
            ConnectorControl.Connected = true;

            QuadButton.IsChecked = true;

            var channel = ConnectionPanel.Channel;
            channel.MessageReceived += OnMavlinkMessageReceived;

            channel.SendMessage(new MavLinkMessage()
            {
                ComponentId = (byte)MAVLink.MAV_COMPONENT.MAV_COMP_ID_MISSIONPLANNER,
                SystemId = 255,
                MsgId = MAVLink.MAVLINK_MSG_ID.COMMAND_LONG,
                TypedPayload = new MAVLink.mavlink_command_long_t()
                {
                    command = (ushort)MAVLink.MAV_CMD.SET_MESSAGE_INTERVAL,
                    param1 = (float)MAVLink.MAVLINK_MSG_ID.ATTITUDE_QUATERNION,
                    param2 = 50000
                }
            });

            Settings settings = await ((App)App.Current).LoadSettings();
            settings.Port = ConnectionPanel.DefaultUdpPort;
            await settings.SaveAsync();

        }

        private void OnMavlinkMessageReceived(object sender, MavLinkMessage e)
        {
            if (currentFlightLog != null && !pauseRecording)
            {
                currentFlightLog.AddMessage(e);
            }

            switch (e.MsgId)
            {
                case MAVLink.MAVLINK_MSG_ID.ATTITUDE_QUATERNION:
                    {
                        var payload = (MAVLink.mavlink_attitude_quaternion_t)e.TypedPayload;
                        var q = new System.Windows.Media.Media3D.Quaternion(payload.q1, payload.q2, payload.q3, payload.q4);
                        UiDispatcher.RunOnUIThread(() =>
                        {
                            ModelViewer.ModelAttitude = initialAttitude * q;
                        });
                        break;
                    }

                case MAVLink.MAVLINK_MSG_ID.ATTITUDE:
                    {
                        var payload = (MAVLink.mavlink_attitude_t)e.TypedPayload;
                        Quaternion y = new Quaternion(new Vector3D(0, 0, 1), -payload.yaw * 180 / Math.PI);
                        Quaternion x = new Quaternion(new Vector3D(1, 0, 0), payload.pitch * 180 / Math.PI);
                        Quaternion z = new Quaternion(new Vector3D(0, 1, 0), payload.roll * 180 / Math.PI);
                        UiDispatcher.RunOnUIThread(() =>
                        {
                            ModelViewer.ModelAttitude = initialAttitude * (y * x * z);
                        });
                        break;
                    }
                case MAVLink.MAVLINK_MSG_ID.HIL_STATE_QUATERNION:
                    {
                        var payload = (MAVLink.mavlink_hil_state_quaternion_t)e.TypedPayload;
                        Quaternion q = new Quaternion(payload.attitude_quaternion[0],
                            payload.attitude_quaternion[1],
                            payload.attitude_quaternion[2],
                            payload.attitude_quaternion[3]);
                        UiDispatcher.RunOnUIThread(() =>
                        {
                            ModelViewer.ModelAttitude = initialAttitude * q;
                        });
                        break;
                    }
                case MAVLink.MAVLINK_MSG_ID.GLOBAL_POSITION_INT:
                    {
                        var payload = (MAVLink.mavlink_global_position_int_t)e.TypedPayload;
                        UiDispatcher.RunOnUIThread(() =>
                        {
                            MapLocation((double)payload.lat / 1e7, (double)payload.lon / 1e7);
                        });
                        break;
                    }
                case MAVLink.MAVLINK_MSG_ID.DATA_TRANSMISSION_HANDSHAKE:
                    if (showImageStream) {
                        var p = (MAVLink.mavlink_data_transmission_handshake_t)e.TypedPayload;
                        incoming_image.size = p.size;
                        incoming_image.packets = p.packets;
                        incoming_image.payload = p.payload;
                        incoming_image.quality = p.jpg_quality;
                        incoming_image.type = p.type;
                        incoming_image.width = p.width;
                        incoming_image.height = p.height;
                        incoming_image.start = Environment.TickCount;
                        incoming_image.packetsArrived = 0;
                        incoming_image.data = new byte[incoming_image.size];
                    }
                    break;
                case MAVLink.MAVLINK_MSG_ID.ENCAPSULATED_DATA:
                    if (showImageStream)
                    {
                        var img = (MAVLink.mavlink_encapsulated_data_t)e.TypedPayload;
                        
                        int seq = img.seqnr;
                        uint pos = (uint)seq * (uint)incoming_image.payload;

                        // Check if we have a valid transaction
                        if (incoming_image.packets == 0 || incoming_image.size == 0)
                        {
                            // not expecting an image?
                            incoming_image.packetsArrived = 0;
                            break;
                        }

                        uint available = (uint)incoming_image.payload;
                        if (pos + available > incoming_image.size)
                        {
                            available = incoming_image.size - pos;
                        }
                        Array.Copy(img.data, 0, incoming_image.data, pos, available);

                        progress.ShowProgress(0, incoming_image.size, pos + available);

                        ++incoming_image.packetsArrived;
                        //Debug.WriteLine("packet {0} of {1}, position {2} of {3}", incoming_image.packetsArrived, incoming_image.packets,
                        //    pos + available, incoming_image.size);

                        // emit signal if all packets arrived
                        if (pos + available >= incoming_image.size)
                        {
                            // Restart state machine
                            incoming_image.packets = 0;
                            incoming_image.packetsArrived = 0;
                            byte[] saved = incoming_image.data;
                            incoming_image.data = null;

                            UiDispatcher.RunOnUIThread(() =>
                            {
                                progress.ShowProgress(0, 0, 0);
                                ShowImage(saved);
                            });
                        }
                    }
                    break;
            }
        }
        

        private void ShowImage(byte[] image)
        {
            try
            {
                MemoryStream ms = new MemoryStream(image);
                BitmapDecoder decoder = null;
                MAVLink.MAVLINK_DATA_STREAM_TYPE type = (MAVLink.MAVLINK_DATA_STREAM_TYPE)incoming_image.type;
                switch (type)
                {
                    case MAVLink.MAVLINK_DATA_STREAM_TYPE.MAVLINK_DATA_STREAM_IMG_JPEG:
                        decoder = JpegBitmapDecoder.Create(ms, BitmapCreateOptions.IgnoreImageCache, BitmapCacheOption.None);
                        break;
                    case MAVLink.MAVLINK_DATA_STREAM_TYPE.MAVLINK_DATA_STREAM_IMG_BMP:
                        decoder = BitmapDecoder.Create(ms, BitmapCreateOptions.IgnoreImageCache, BitmapCacheOption.None);
                        break;
                    case MAVLink.MAVLINK_DATA_STREAM_TYPE.MAVLINK_DATA_STREAM_IMG_RAW8U:
                        var raw = Raw8UBitmapDecoder.Create(image, incoming_image.width, incoming_image.height);
                        BitmapFrame frame = raw.Frames[0];
                        ImageViewer.Source = frame;
                        break;
                    case MAVLink.MAVLINK_DATA_STREAM_TYPE.MAVLINK_DATA_STREAM_IMG_RAW32U:
                        //decoder = Raw8UBitmapDecoder.Create(ms, incoming_image.width, incoming_image.height);
                        break;
                    case MAVLink.MAVLINK_DATA_STREAM_TYPE.MAVLINK_DATA_STREAM_IMG_PGM:
                        //decoder = PgmBitmapDecoder.Create(ms, BitmapCreateOptions.IgnoreImageCache, BitmapCacheOption.None);
                        break;
                    case MAVLink.MAVLINK_DATA_STREAM_TYPE.MAVLINK_DATA_STREAM_IMG_PNG:
                        decoder = PngBitmapDecoder.Create(ms, BitmapCreateOptions.IgnoreImageCache, BitmapCacheOption.None);
                        break;
                }
                if (decoder != null && decoder.Frames.Count > 0)
                {
                    BitmapFrame frame = decoder.Frames[0];
                    ImageViewer.Source = frame;
                }
            }
            catch
            {

            }
        }

        private void OnChannelDisconnected(object sender, EventArgs e)
        {
            ConnectorControl.Connected = false;
        }

        private void OnLogDownloadComplete(object sender, string fileName)
        {
            ConnectionPanel.Visibility = Visibility.Collapsed;
            Task.Run(async () => { await LoadBinaryFile(fileName); });
        }

        private async void OnOpenFile(object sender, RoutedEventArgs e)
        {
            OpenButton.IsEnabled = false;

            Microsoft.Win32.OpenFileDialog fo = new Microsoft.Win32.OpenFileDialog();
            fo.Filter = "PX4 Log Files (*.px4log)|*.px4log|CSV Files (*.csv)|*.csv|bin files (*.bin)|*.bin|mavlink files (*.mavlink)|*.mavlink";
            fo.CheckFileExists = true;
            fo.Multiselect = true;
            if (fo.ShowDialog() == true)
            {
                foreach (var file in fo.FileNames)
                {
                    switch (System.IO.Path.GetExtension(file).ToLowerInvariant())
                    {
                        case ".csv":
                            await Task.Run(async () => { await LoadCsvFile(file); });
                            break;
                        case ".bin":
                        case ".px4log":
                            await Task.Run(async () => { await LoadBinaryFile(file); });
                            break;
                        case ".mavlink":
                            await Task.Run(async () => { await LoadMavlinkFile(file); });
                            break;
                        default:
                            MessageBox.Show("Do not know how to read files of type : " + System.IO.Path.GetExtension(file),
                                "Unsupported file extension", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                            break;
                    }
                }
            }
            OpenButton.IsEnabled = true;
        }

        private async Task LoadBinaryFile(string file)
        {
            try
            {
                AppendMessage("Loading " + file);
                ShowStatus("Loading " + file);

                Px4DataLog data = new Px4DataLog();
                await data.Load(file, progress);

                logs.Add(data);
                ShowSchema();

                Debug.WriteLine(data.StartTime.ToString());

                UiDispatcher.RunOnUIThread(() =>
                {
                    // add flight for 
                    Flight entireLog = new Flight()
                    {
                        Name = "Log " + logs.Count,
                        StartTime = data.StartTime,
                        Duration = data.Duration
                    };
                    allFlights.Add(entireLog);

                    foreach (var flight in data.GetFlights())
                    {
                        flight.Name = "Flight " + allFlights.Count;
                        allFlights.Add(flight);
                        AppendMessage("Motor started at {0} and ran for {1} ", flight.StartTime, flight.Duration);
                    }

                    if (myMap.Visibility == Visibility.Visible)
                    {
                        ShowMap();
                    }
                });

                // remember successfully loaded log file.
                Settings settings = await ((App)App.Current).LoadSettings();
                settings.LastLogFile = file;
                await settings.SaveAsync();
            }
            catch (Exception ex)
            {
                AppendMessage("### Error loading log: " + ex.Message);
            }
            ShowStatus("Done Loading " + file);
            UpdateButtons();
        }

        private async Task LoadMavlinkFile(string file)
        {
            try
            {
                AppendMessage("Loading " + file);
                ShowStatus("Loading " + file);

                MavlinkLog data = new MavlinkLog();
                await data.Load(file, progress);

                logs.Add(data);
                ShowSchema();

                Debug.WriteLine(data.StartTime.ToString());

                UiDispatcher.RunOnUIThread(() =>
                {
                    foreach (var flight in data.GetFlights())
                    {
                        flight.Name = "Flight " + allFlights.Count;
                        allFlights.Add(flight);
                        AppendMessage("Motor started at {0} and ran for {1} ", flight.StartTime, flight.Duration);
                    }

                    if (myMap.Visibility == Visibility.Visible)
                    {
                        ShowMap();
                    }
                });

                // remember successfully loaded log file.
                Settings settings = await ((App)App.Current).LoadSettings();
                settings.LastLogFile = file;
                await settings.SaveAsync();
            }
            catch (Exception ex)
            {
                AppendMessage("### Error loading log: " + ex.Message);
            }
            ShowStatus("Done Loading " + file);
            UpdateButtons();
        }

        private void AppendMessage(string fmt, params object[] args)
        {
            UiDispatcher.RunOnUIThread(() =>
            {
                string msg = fmt;
                if (args != null && args.Length > 0)
                {
                    msg = string.Format(fmt, args);
                }
                var doc = Messages.Document;
                Paragraph p = new Paragraph(new Run(msg));
                p.Inlines.Add(new LineBreak());
                doc.Blocks.Add(p);
                Debug.WriteLine(msg);
            });
        }

        private async Task LoadCsvFile(string file)
        {
            try
            {
                ShowStatus("Loading " + file);

                CsvDataLog log = new CsvDataLog();
                await log.Load(file, progress);

                FlightView.ItemsSource = new List<Flight>();
                logs.Add(log);

                ShowSchema();

            }
            catch (Exception ex)
            {
                ShowStatus(ex.Message);
            }
            ShowStatus("Done");
        }

        private void ShowSchema()
        {
            UiDispatcher.RunOnUIThread(() =>
            {
                LogItemSchema schema = null;

                // todo: compute combined schema for selected logs, but for now just show the first one.
                if (this.currentFlightLog != null)
                {
                    schema = currentFlightLog.Schema;
                }
                else if (this.logs.Count > 0)
                {
                    schema = this.logs[0].Schema;
                }
                if (schema == null)
                { 
                    CategoryList.ItemsSource = null;
                }
                else
                {
                    // todo: compute combined schema for selected logs, but for now just show the first one.
                    List<LogItemSchema> list = new List<Model.LogItemSchema>(schema.ChildItems);
                    list.Sort((a, b) => { return string.Compare(a.Name, b.Name, StringComparison.OrdinalIgnoreCase); });
                    CategoryList.ItemsSource = list;
                }
            });
        }
        
        private void ShowStatus(string message)
        {
            UiDispatcher.RunOnUIThread(() =>
            {
                StatusText.Text = message;
            });
        }

        private void OnListItemSelected(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems != null && e.AddedItems.Count > 0)
            {
                LogItemSchema item = (LogItemSchema)e.AddedItems[0];
                if (sender == CategoryList && item.ChildItems != null)
                {
                    ListViewItem listItem = CategoryList.ItemContainerGenerator.ContainerFromItem(item) as ListViewItem;
                    if (listItem != null)
                    {
                        // make sure expander is toggled.
                        Expander expander = listItem.FindDescendantsOfType<Expander>().FirstOrDefault();
                        expander.IsExpanded = true;
                    }
                }
                else if (item.ChildItems == null || item.ChildItems.Count == 0)
                {
                    if (item.Parent == null)
                    {
                        GraphItem(item);
                    }
                }
            }

            if (e.RemovedItems != null && e.RemovedItems.Count > 0)
            {
                LogItemSchema item = (LogItemSchema)e.RemovedItems[0];
                if (sender == CategoryList && item.ChildItems != null)
                {
                    ListViewItem listItem = CategoryList.ItemContainerGenerator.ContainerFromItem(item) as ListViewItem;
                    if (listItem != null)
                    {
                        Expander expander = listItem.FindDescendantsOfType<Expander>().FirstOrDefault();
                        expander.IsExpanded = false;
                    }
                }

            }
        }

        private void OnShowMap(object sender, RoutedEventArgs e)
        {
            ShowMap();
        }

        private void OnHideMap(object sender, RoutedEventArgs e)
        {
            myMap.Visibility = Visibility.Collapsed;
            if (QuadButton.IsChecked == true)
            {
                ModelViewer.Visibility = Visibility.Visible;
            }
            else
            {
                ChartStack.Visibility = Visibility.Visible;
            }
        }

        List<Flight> GetSelectedFlights()
        {
            List<Flight> selected = new List<Model.Flight>();
            foreach (Flight f in FlightView.SelectedItems)
            {
                selected.Add(f);
            }
            return selected;
        }

        double lastLat = 0;
        double lastLon = 0;

        private void MapLocation(double latitude, double longitude)
        {
            if (Math.Round(lastLat, 5) == Math.Round(latitude) && Math.Round(lastLon, 5) == Math.Round(longitude, 5))
            {
                // hasn't moved far enough yet...
                return;
            }
            lastLat = latitude;
            lastLon = longitude;
            bool first = false;
            if (currentFlight == null)
            {
                first = true;
                currentFlight = new MapPolyline();
                currentFlight.StrokeThickness = 4;
                currentFlight.Stroke = new SolidColorBrush(Colors.Magenta);
                currentFlight.Locations = new LocationCollection();
                myMap.Children.Add(currentFlight);
            }
            currentFlight.Locations.Add(new Location() { Latitude = latitude, Longitude = longitude });
            // make sure it's on top.
            if (myMap.Children.IndexOf(currentFlight) < 0)
            {
                myMap.Children.Add(currentFlight);
            }
            else if (myMap.Children.IndexOf(currentFlight) != myMap.Children.Count - 1)
            {
                myMap.Children.Remove(currentFlight);
                myMap.Children.Add(currentFlight);
            }
            if (currentFlight.Locations.Count > 1000)
            {
                // remove the older points.
                currentFlight.Locations.RemoveAt(0);
            }
            if (first && myMap.Visibility == Visibility.Visible)
            {
                myMap.SetView(currentFlight.Locations, new Thickness(20.0), 0);
            }
        }

        void ShowMap()
        {
            myMap.Children.Clear();

            List<Flight> selected = GetSelectedFlights();
            if (selected.Count == 0)
            {
                // show everything.
                selected.Add(new Flight() { StartTime = DateTime.MinValue, Duration = TimeSpan.MaxValue });
            }
            var glitchIcon = XamlExtensions.LoadImageResource("Assets.GpsGlitchIcon.png");
            var imageLayer = new MapLayer();
            myMap.Children.Add(imageLayer);
            MapPolyline last = currentFlight;
            foreach (IDataLog log in this.logs)
            {
                if (log != null)
                {
                    bool gpsIsBad = false;
                    foreach (var flight in selected)
                    {
                        if (flight.Log == null || flight.Log == log)
                        {
                            MapPolyline line = new MapPolyline();
                            line.StrokeThickness = 4;
                            line.Stroke = new SolidColorBrush(HlsColor.GetRandomColor());
                            LocationCollection points = new LocationCollection();

                            Debug.WriteLine("time,\t\tlat,\t\tlong,\t\t\tnsat,\talt,\thdop,\tfix");
                            foreach (var row in log.GetRows("GPS", flight.StartTime, flight.Duration))
                            {
                                LogEntryGPS gps = new LogEntryGPS(row);
                                //Debug.WriteLine("{0},\t{1},\t{2},\t{3},\t\t{4:F2},\t{5},\t{6}", gps.TimeMS,  gps.Lat, gps.Lng, gps.NSats, gps.Alt, gps.HDop, gps.Fix);
                                if (!(gps.Lat == 0 && gps.Lon == 0))
                                {
                                    var pos = new Location() { Altitude = gps.Alt, Latitude = gps.Lat, Longitude = gps.Lon };
                                    points.Add(pos);
                                    ulong time = (ulong)gps.GPSTime;
                                    if (time != 0)
                                    {
                                        if ((gps.nSat < 5 || gps.EPH > 20))
                                        {
                                            if (!gpsIsBad)
                                            {
                                                gpsIsBad = true;
                                                Debug.WriteLine("{0},\t{1},\t{2},\t{3},\t\t{4:F2},\t{5},\t{6}", gps.GPSTime, gps.Lat, gps.Lon, gps.nSat, gps.Alt, gps.EPH, gps.Fix);
                                                Image img = new Image();
                                                img.Width = 30;
                                                img.Height = 30;
                                                img.Source = glitchIcon;
                                                img.Stretch = Stretch.None;
                                                img.ToolTip = "GPS Glitch!";
                                                imageLayer.AddChild(img, pos, PositionOrigin.Center);
                                            }
                                        }
                                        else
                                        {
                                            gpsIsBad = false;
                                        }
                                    }
                                }
                            }
                            if (points.Count > 0)
                            {
                                line.Locations = points;
                                myMap.Children.Add(line);
                                last = line;
                            }
                        }
                    }
                }
            }

            ModelViewer.Visibility = Visibility.Collapsed;
            Messages.Visibility = Visibility.Collapsed;
            ChartStack.Visibility = Visibility.Collapsed;
            TextButton.IsChecked = false;
            myMap.Visibility = Visibility.Visible;
            myMap.UpdateLayout();

            if (last != null)
            {
                try
                {
                    myMap.SetView(last.Locations, new Thickness(20.0), 0);
                }
                catch (Exception ex)
                {
                    ShowStatus(ex.Message);
                }
            }

        }


        private void UpdateButtons()
        {
            UiDispatcher.RunOnUIThread(() =>
            {
                ShowMapButton.Visibility = Visibility.Visible;
            });
        }

        private void OnShowMessages(object sender, RoutedEventArgs e)
        {
            Messages.Visibility = Visibility.Visible;
            Messages.Focus();
        }

        private void OnHideMessages(object sender, RoutedEventArgs e)
        {
            Messages.Visibility = Visibility.Collapsed;
        }

        HashSet<ListView> childLists = new HashSet<ListView>();

        private void OnChildListItemSelected(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems != null && e.AddedItems.Count > 0 && e.OriginalSource == sender)
            {
                childLists.Add((ListView)sender);
                LogItemSchema item = (LogItemSchema)e.AddedItems[0];
                GraphItem(item);
            }
        }

        IEnumerable<DataValue> GetSelectedDataValues(LogItemSchema schema)
        {
            List<DataValue> combined = new List<DataValue>();

            List<Flight> selected = GetSelectedFlights();
            if (selected.Count == 0)
            {
                // show everything.
                selected.Add(new Flight() { StartTime = DateTime.MinValue, Duration = TimeSpan.MaxValue });
            }

            foreach (IDataLog log in this.logs)
            {
                if (log != null)
                {
                    foreach (var flight in selected)
                    {
                        if (flight.Log == null || flight.Log == log)
                        {
                            combined.AddRange(log.GetDataValues(schema, flight.StartTime, flight.Duration));
                        }
                    }
                }
            }

            return combined;
        }

        Thickness defaultChartMargin = new Thickness(0, 10, 0, 10);

        private void GraphItem(LogItemSchema schema)
        {
            if (schema.IsNumeric)
            {
                ChartStack.Visibility = Visibility.Visible;
                ChartStack.UpdateLayout();
                SimpleLineChart chart = new SimpleLineChart();
                chart.Margin = defaultChartMargin;
                chart.Focusable = false;
                chart.Closed += OnChartClosed;
                chart.LineColor = HlsColor.GetRandomColor();
                chart.StrokeThickness = 1;
                chart.Tag = schema;

                if (currentFlightLog != null && schema.Root == currentFlightLog.Schema)
                {
                    List<DataValue> values = new List<DataValue>(currentFlightLog.GetDataValues(schema, DateTime.MinValue, TimeSpan.MaxValue)); 
                    InitializeChartData(schema, chart, values);

                    // now turn on live scrolling...
                    chart.LiveScrolling = true;

                    // now start watching the live update for new values that need to be added to this chart.
                    Task.Run(() =>
                    {
                        LiveUpdate(chart, currentFlightLog, schema);
                    });

                }
                else
                {
                    List<DataValue> values = new List<DataValue>(GetSelectedDataValues(schema));
                    InitializeChartData(schema, chart, values);
                }

                if (chartGroup != null)
                {
                    SimpleLineChart last = null;
                    if (chartGroup.Children.Count > 0)
                    {
                        last = chartGroup.Children[chartGroup.Children.Count - 1] as SimpleLineChart;
                    }
                    chartGroup.Children.Add(chart);
                    if (chartGroup.Parent == null)
                    {
                        ChartStack.AddChart(chartGroup);
                    }
                    if (last != null)
                    {
                        last.Next = chart;
                    }
                }
                else
                {
                    ChartStack.AddChart(chart);
                }
                LayoutCharts();

                Messages.Visibility = Visibility.Collapsed;
            }
            else
            {
                Paragraph p = new Paragraph();
                foreach (var value in GetSelectedDataValues(schema))
                {
                    p.Inlines.Add(new Run(value.Label));
                    p.Inlines.Add(new LineBreak());
                }
                var doc = Messages.Document;
                doc.Blocks.Add(p);

                Messages.Visibility = Visibility.Visible;
                Messages.Focus();
            }
        }

        // bugbug: should concatenate data from selected logs - then sort by X...
        // bugbug: give them unique X values that are smooth over time.  Alternatively we could
        // give the entry Timestamp, but that seems to bunch up the values, so timeclock is not
        // updating smoothly for some reason...

        private void InitializeChartData(LogItemSchema schema, SimpleLineChart chart, List<DataValue> values)
        {
            int x = 0;
            foreach (var d in values)
            {
                d.X = x++;
            }
            chart.SetData(new Model.DataSeries()
            {
                Name = schema.Name,
                Values = values
            });
        }

        private void LiveUpdate(SimpleLineChart chart, MavlinkLog currentFlightLog, LogItemSchema schema)
        {
            // this method is running on a background task and it's job is to read an infinite stream of
            // data values from the log and show them in the live scrolling chart.

            CancellationTokenSource canceller = new CancellationTokenSource();

            chart.Closed += (s,e) =>
            {
                canceller.Cancel();
            };

            var query = currentFlightLog.LiveQuery(schema, canceller.Token);
            foreach (DataValue item in query)
            {
                if (item == null)
                {
                    return;
                }
                chart.SetCurrentValue(item);
            }
        }

        private void LayoutCharts()
        {
            // layout charts to fill the space available.
            double height = ChartStack.ActualHeight;
            double count = ChartStack.ChartCount;
            height -= (count * (defaultChartMargin.Top + defaultChartMargin.Bottom)); // remove margins
            double chartHeight = Math.Min(MaxChartHeight, height / count);
            bool found = false;
            foreach (FrameworkElement c in ChartStack.Charts)
            {
                found = true;
                c.Height = chartHeight;
            }
            if (!found)
            {
                ChartStack.Visibility = Visibility.Collapsed;
            }
        }

        private void OnChartClosed(object sender, EventArgs e)
        {
            FrameworkElement chart = (FrameworkElement)sender;
            ChartStack.RemoveChart(chart);
            LayoutCharts();

            LogItemSchema item = (chart.Tag as LogItemSchema);
            if (item != null)
            {
                UnselectCategory(item);
            }

        }

        private void UnselectCategory(LogItemSchema item)
        {
            if (CategoryList.SelectedItems.Contains(item))
            {
                CategoryList.SelectedItems.Remove(item);
            }
            else
            {
                // might be a child category item...
                foreach (var childList in childLists)
                {
                    if (childList.SelectedItems.Contains(item))
                    {
                        childList.SelectedItems.Remove(item);
                    }
                }
            }
        }

        private void OnClear(object sender, RoutedEventArgs e)
        {
            ChartStack.ClearCharts();
            logs.Clear();
            ShowSchema();
            CategoryList.SelectedItem = null;
            allFlights.Clear();
            if (currentFlightLog != null)
            {
                currentFlightLog.Clear();
                logs.Add(currentFlightLog);
            }
            if (currentFlight != null)
            {
                currentFlight.Locations = new LocationCollection();
            }
            myMap.Children.Clear();
            ImageViewer.Source = null;
        }

        private void OnFlightSelected(object sender, SelectionChangedEventArgs e)
        {
            UiDispatcher.RunOnUIThread(() =>
            {
                if (myMap.Visibility == Visibility.Visible)
                {
                    ShowMap();
                }
                else
                {
                    // todo: show sensor data pruned to this flight time...
                    foreach (LogItemSchema item in CategoryList.SelectedItems)
                    {
                        if (item.ChildItems == null || item.ChildItems.Count == 0)
                        {
                            GraphItem(item);
                        }
                    }
                }
            });
        }

        //private void OnMapPointerMoved(object sender, PointerRoutedEventArgs e)
        //{
        //    Point mapPos = e.GetCurrentPoint(myMap).Position;
        //    Geopoint location;
        //    myMap.GetLocationFromOffset(mapPos, out location);
        //    StatusText.Text = location.Position.Latitude + ", " + location.Position.Longitude;
        //}

        private void OnFlightViewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Delete)
            {
                // remove this flight.
            }
        }

        private void OnItemExpanded(object sender, RoutedEventArgs e)
        {
            Expander expander = (Expander)sender;
            ListView childView = expander.Content as ListView;
            if (childView != null)
            {
                LogItemSchema item = (LogItemSchema)expander.DataContext;
                childView.ItemsSource = item.ChildItems;
            }
        }

        private void OnItemCollapsed(object sender, RoutedEventArgs e)
        {
            Expander expander = (Expander)sender;
            Expander source = e.OriginalSource as Expander;
            if (source != null && source != expander)
            {
                // bugbug: for some reason WPF also sends collapse event to all the parents
                // but we want to ignore those.
                return;
            }
            ListView childView = expander.Content as ListView;
            if (childView != null)
            {
                childView.ItemsSource = null;
            }
            // todo: remove the graphs...
        }

        Grid chartGroup;

        private void OnGroupChecked(object sender, RoutedEventArgs e)
        {
            chartGroup = new Grid() { HorizontalAlignment = HorizontalAlignment.Stretch, VerticalAlignment = VerticalAlignment.Stretch };
        }

        private void OnGroupUnchecked(object sender, RoutedEventArgs e)
        {
            chartGroup = null;
        }

        private void OnClearZoom(object sender, RoutedEventArgs e)
        {
            ChartStack.ResetZoom();
        }

        private void OnConnectorClick(object sender, MouseButtonEventArgs e)
        {
            ConnectionPanel.Start();
            TranslateTransform transform = new TranslateTransform(300, 0);
            ConnectionPanel.RenderTransform = transform;
            transform.BeginAnimation(TranslateTransform.XProperty,
                new DoubleAnimation(0, new Duration(TimeSpan.FromSeconds(0.2)))
                {
                    EasingFunction = new ExponentialEase() { EasingMode = EasingMode.EaseOut }
                });
        }

        private void OnOpenFileCommand(object sender, ExecutedRoutedEventArgs e)
        {
            OnOpenFile(sender, e);
        }

        private void OnShowQuad(object sender, RoutedEventArgs e)
        {
            ModelViewer.Visibility = Visibility.Visible;
        }

        private void OnHideQuad(object sender, RoutedEventArgs e)
        {
            ModelViewer.Visibility = Visibility.Collapsed;
        }

        private void OnRecord(object sender, RoutedEventArgs e)
        {
            Button button = (Button)sender;
            if (button.Tag != null)
            {
                // paused
                button.Content = button.Tag;
                button.Tag = null;
                StopRecording();
            }
            else
            {
                // start recording.
                button.Tag = button.Content;
                button.Content = "\ue15b";
                StartRecording();
            }
        }

        void StartRecording()
        {
            if (currentFlightLog == null)
            {
                currentFlightLog = new MavlinkLog();
                currentFlightLog.SchemaChanged += (s, args) =>
                {
                    ShowSchema();
                };
            }
            pauseRecording = false;
        }

        bool pauseRecording;

        void StopRecording()
        {
            pauseRecording = true;
        }

        private void OnShowCamera(object sender, RoutedEventArgs e)
        {
            CameraPanel.Visibility = Visibility.Visible;
            showImageStream = true;
        }

        private void OnHideCamera(object sender, RoutedEventArgs e)
        {
            showImageStream = false;
            CameraPanel.Visibility = Visibility.Collapsed;
        }
        private void ShowImageStream()
        {
            // show encapsulated data
        }

        bool showImageStream;

        struct IncomingImage
        {
            public uint size;              // Image size being transmitted (bytes)
            public int packets;           // Number of data packets being sent for this image
            public int packetsArrived;    // Number of data packets received
            public int payload;           // Payload size per transmitted packet (bytes). Standard is 254, and decreases when image resolution increases.
            public int quality;           // Quality of the transmitted image (percentage)
            public int type;              // Type of the transmitted image (BMP, PNG, JPEG, RAW 8 bit, RAW 32 bit)
            public int width;             // Width of the image stream
            public int height;            // Width of the image stream
            public byte[] data;           // Buffer for the incoming bytestream
            public long start;            // Time when we started recieving data
        };

        IncomingImage incoming_image = new IncomingImage();
        
    }
}

