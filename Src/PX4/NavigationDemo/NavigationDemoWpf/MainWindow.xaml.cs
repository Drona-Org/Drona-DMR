using Microsoft.Maps.MapControl.WPF;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using FlightController;
using System.Windows.Controls.Primitives;
using System.Diagnostics;

namespace NavigationDemoWpf
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        FlightController.Simulation simulation;
        Pushpin MissionPin;
        Pushpin HomePin;

        public MainWindow()
        {
            InitializeComponent();
            
            simulation = new FlightController.Simulation();
            simulation.LogEvent += OnLogEvent;
            myMap.IsHitTestVisible = true;
            myMap.MouseLeftButtonDown += OnMapMouseDown;

            this.Closed += OnMainWindowClosed;
            this.Loaded += OnMainWindowLoaded;

            foreach (UIElement child in RootGrid.Children)
            {
                ToggleButton togglebutton = child as ToggleButton;
                if (togglebutton != null)
                {
                    togglebutton.Checked += OnToggleButtonChecked;
                    togglebutton.Unchecked += OnToggleButtonUnchecked;
                }
                else {
                    Button button = child as Button;
                    if (button != null)
                    {
                        button.Click += OnButtonChecked;
                    }
                }
            }
        }

        private void OnLogEvent(object sender, string e)
        {
            Debug.WriteLine(e);
        }

        private void OnMapMouseDown(object sender, MouseButtonEventArgs e)
        {
            Location location;
            if (myMap.TryViewportPointToLocation(e.GetPosition(myMap), out location))
            {
                OnMapTapped(location);
            }
        }

        private void OnMainWindowLoaded(object sender, RoutedEventArgs e)
        {
            SetView(new Location(47.64217, -122.142097));
            simulation.Start();
        }


        private void OnMapTapped(Location location)
        {
            if (MissionPin == null)
            {
                MissionPin = new Pushpin();
                MissionPin.Background = Brushes.Blue;
                myMap.Children.Add(MissionPin);
            }
            ShowError(location.Latitude + "," + location.Longitude);
            MissionPin.Location = location;
            locationSet = true;


        }

        private void OnHomePinMouseDown(object sender, MouseButtonEventArgs e)
        {
            MissionPin.Location = HomePin.Location;
            simulation.RaiseEvent(SimulationMachine.P_MACHINE_GpsSensor, SimulationEvent.P_EVENT_GPS_HOME, null);
        }

        private void SetHome()
        {
            if (HomePin == null)
            {
                HomePin = new Pushpin();
                HomePin.Background = Brushes.Green;
                HomePin.MouseLeftButtonDown += OnHomePinMouseDown;
                myMap.Children.Add(HomePin);
            }
            HomePin.Location = MissionPin.Location;
        }

        bool locationSet;

        private void OnButtonChecked(object sender, RoutedEventArgs e)
        {
            ShowError("");
            Button button = (Button)sender;
            Tuple<SimulationMachine, SimulationEvent> data = ParseTag((string)button.Tag, "");
            if (data.Item2 == SimulationEvent.P_EVENT_SET_HOME_POS)
            {
                if (!locationSet)
                {
                    ShowError("Please click on the map to define the home position then click Set Home again");
                    return;
                }
                SetHome();
            }
            simulation.RaiseEvent(data.Item1, data.Item2, null);
        }


        private void ShowError(string v)
        {
            Dispatcher.Invoke(() => 
            {
                Status.Text = v;
            }, System.Windows.Threading.DispatcherPriority.Normal);
        }

        private void OnToggleButtonUnchecked(object sender, RoutedEventArgs e)
        {
            ShowError("");
            ToggleButton button = (ToggleButton)sender;
            Tuple<SimulationMachine, SimulationEvent> data = ParseTag((string)button.Tag, "_OFF");
            simulation.RaiseEvent(data.Item1, data.Item2, null);
        }

        private void OnToggleButtonChecked(object sender, RoutedEventArgs e)
        {
            ShowError("");
            ToggleButton button = (ToggleButton)sender;
            Tuple<SimulationMachine, SimulationEvent> data = ParseTag((string)button.Tag, "_ON");
            simulation.RaiseEvent(data.Item1, data.Item2, null);
        }

        Tuple<SimulationMachine, SimulationEvent> ParseTag(string tag, string eventSuffix)
        {
            string[] parts = tag.Split(',');
            if (parts.Length != 2)
            {
                ShowError("### Error: tag should contain 'machine,event'");
                return null;
            }
            return new Tuple<SimulationMachine, SimulationEvent>(GetMachineByName(parts[0]), GetEventByName(parts[1] + eventSuffix));
        }

        SimulationMachine GetMachineByName(string name)
        {
            SimulationMachine result = SimulationMachine.P_MACHINE_FlightController;
            if (!Enum.TryParse<SimulationMachine>(name, out result))
            {
                Debug.WriteLine("### Error: could not find machine named " + name);
            }
            return result;
        }

        SimulationEvent GetEventByName(string name)
        {
            SimulationEvent result = SimulationEvent._P_EVENT_NULL;
            if (!Enum.TryParse<SimulationEvent>(name, out result))
            {
                Debug.WriteLine("### Error: could not find event named " + name);
            }
            return result;
        }

        private void OnMainWindowClosed(object sender, EventArgs e)
        {
            simulation.Stop();
        }

        void SetView(Location location)
        {
            myMap.SetView(location, 17);
        }

        private void OnAltitudeChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            simulation.RaiseEvent(SimulationMachine.P_MACHINE_Altimeter, SimulationEvent.P_EVENT_SET_ALTITUDE, (int)e.NewValue);
        }
    }
}
