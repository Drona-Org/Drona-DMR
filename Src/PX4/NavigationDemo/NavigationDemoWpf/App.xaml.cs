using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using Foundation = Windows.Foundation;

namespace NavigationDemoWpf
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            WinRT.Initialize();
            base.OnStartup(e);
        }
    }

    class WinRT
    {
        public static void Initialize()
        {
            foreach (var profile in Windows.Networking.Connectivity.NetworkInformation.GetConnectionProfiles())
            {
                if (profile.IsWlanConnectionProfile)
                {
                    Debug.WriteLine(profile.ProfileName);
                }
            }
        }
    }
}
