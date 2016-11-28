//using NavigationDemo.Mavlink;
using System;
using System.Diagnostics;
using System.Threading.Tasks;
using Windows.Devices.Geolocation;
using Windows.Foundation;
using Windows.Storage;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Maps;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Navigation;
//using Microsoft.VisualStudio.DgmlTestModeling;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace NavigationDemo
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        const int initialZoomLevel = 18;
        //MavlinkChannel channel;

        public MainPage()
        {
            this.InitializeComponent();

            myMap.IsHitTestVisible = true;
            myMap.MapTapped += OnMapTapped;

            Window.Current.CoreWindow.Closed += CoreWindow_Closed;
        }

        private void OnLogEvent(object sender, string e)
        {
            Debug.WriteLine(e);
        }

        MapIcon MissionPin;
        MapIcon HomePin;

        private async void OnMapTapped(MapControl sender, MapInputEventArgs args)
        {
            Geopoint location = args.Location;
            
            if (MissionPin == null)
            {
                MissionPin = new MapIcon();
                StorageFolder installDir = Windows.ApplicationModel.Package.Current.InstalledLocation;
                StorageFile icon = await installDir.GetFileAsync(@"Assets\pin.png");
                MissionPin.Image = icon;
                myMap.MapElements.Add(MissionPin);
                MissionPin.NormalizedAnchorPoint = new Point(7/36, 32/36);
                MissionPin.Title = "";
            }
            ShowError(location.Position.Latitude + "," + location.Position.Longitude);
            MissionPin.Location = location;
//            locationSet = true;

            if (HomeTapped(args))
            {
                //simulation.RaiseEvent(SimulationMachine.P_MACHINE_GpsSensor, SimulationEvent.P_EVENT_GPS_HOME, null);
            }

        }

        private bool HomeTapped(MapInputEventArgs args)
        {
            if (HomePin != null)
            {
                Point pt = args.Position;
                Point homePos;
                double dx = 36 / 2;
                double dy = 36 / 2;
                myMap.GetOffsetFromLocation(HomePin.Location, out homePos);
                if (Math.Abs(homePos.X - pt.X) < dx && Math.Abs(homePos.Y - pt.Y) < dy)
                {
                    return true;
                }
            }
            return false;
        }

        private async void SetHome()
        {
            if (HomePin == null)
            {
                HomePin = new MapIcon();
                StorageFolder installDir = Windows.ApplicationModel.Package.Current.InstalledLocation;
                StorageFile icon = await installDir.GetFileAsync(@"Assets\home.png");
                HomePin.Image = icon;
                myMap.MapElements.Add(HomePin);
            }
            HomePin.Location = MissionPin.Location;
        }
        
        //bool locationSet;

        private void OnButtonChecked(object sender, RoutedEventArgs e)
        {
            ShowError("");
            Button button = (Button)sender;
            //Tuple<SimulationMachine, SimulationEvent> data = ParseTag((string)button.Tag, "");
            //if (data.Item2 == SimulationEvent.P_EVENT_SET_HOME_POS)
            //{
            //    if (!locationSet)
            //    {
            //        ShowError("Please click on the map to define the home position then click Set Home again");
            //        return;
            //    }
            //    SetHome();
            //}
            //simulation.RaiseEvent(data.Item1, data.Item2, null);
        }


        private void ShowError(string v)
        {
            var nowait = Dispatcher.RunAsync(CoreDispatcherPriority.Normal, new DispatchedHandler(() =>
            {
                Status.Text = v;
            }));
        }

        private void OnToggleButtonUnchecked(object sender, RoutedEventArgs e)
        {
            ShowError("");
            ToggleButton button = (ToggleButton)sender;
            //Tuple<SimulationMachine, SimulationEvent> data = ParseTag((string)button.Tag, "_OFF");
            //simulation.RaiseEvent(data.Item1, data.Item2, null);
        }

        private void OnToggleButtonChecked(object sender, RoutedEventArgs e)
        {
            ShowError("");
            ToggleButton button = (ToggleButton)sender;
            //Tuple<SimulationMachine, SimulationEvent> data = ParseTag((string)button.Tag, "_ON");
            //simulation.RaiseEvent(data.Item1, data.Item2, null);
        }

        //Tuple<SimulationMachine, SimulationEvent> ParseTag(string tag, string eventSuffix)
        //{
        //    string[] parts = tag.Split(',');
        //    if (parts.Length != 2)
        //    {
        //        ShowError("### Error: tag should contain 'machine,event'");
        //        return null;
        //    }
        //    return new Tuple<SimulationMachine, SimulationEvent>(GetMachineByName(parts[0]), GetEventByName(parts[1] + eventSuffix));
        //}

        //SimulationMachine GetMachineByName(string name)
        //{
        //    SimulationMachine result = SimulationMachine.P_MACHINE_FlightController;
        //    if (!Enum.TryParse<SimulationMachine>(name, out result))
        //    {
        //        Debug.WriteLine("### Error: could not find machine named " + name);
        //    }
        //    return result;
        //}

        //SimulationEvent GetEventByName(string name)
        //{
        //    SimulationEvent result = SimulationEvent._P_EVENT_NULL;
        //    if (!Enum.TryParse<SimulationEvent>(name, out result))
        //    {
        //        Debug.WriteLine("### Error: could not find event named " + name);
        //    }
        //    return result;
        //}

        private void CoreWindow_Closed(Windows.UI.Core.CoreWindow sender, Windows.UI.Core.CoreWindowEventArgs args)
        {
            //simulation.Stop();
        }

        protected async override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);

            TrySetView(new Geopoint(new BasicGeoposition() { Latitude = 47.64217, Longitude = -122.142097 }));
            //simulation.Start();

            try
            {
                ShowError("connecting...");

                //this.channel = new Mavlink.MavlinkChannel();
                //this.channel.MessageReceived += OnMessageReceived;
                //this.channel.Start(port);

                ShowError("connected");
            }
            catch (Exception ex)
            {
                ShowError(ex.Message);
            }
        }

        //private void OnMessageReceived(object sender, Message e)
        //{
        //    Debug.WriteLine(e.MsgId + " " + (e.TypedPayload != null ? e.TypedPayload.GetType().Name : ""));
        //}

        async void TrySetView(Geopoint location)
        {
            int retries = 5;
            while (retries-- > 0)
            {
                if (await myMap.TrySetViewAsync(location, initialZoomLevel, null, null, MapAnimationKind.None))
                {
                    break;
                }
                await Task.Delay(1000);
            }
            return;
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            //simulation.Stop();
            base.OnNavigatedFrom(e);
        }

        private void OnAltitudeChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            //simulation.RaiseEvent(SimulationMachine.P_MACHINE_Altimeter, SimulationEvent.P_EVENT_SET_ALTITUDE, (int)e.NewValue);
        }

        private void OnShowSettings(object sender, RoutedEventArgs e)
        {

        }

        private void OnEditMission(object sender, RoutedEventArgs e)
        {

        }

        private void OnFly(object sender, RoutedEventArgs e)
        {

        }
    }
}
