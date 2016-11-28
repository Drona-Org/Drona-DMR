using System;
using System.Collections.Generic;
using System.Linq;
using System.Management;
using System.Text;
using System.Threading.Tasks;

namespace MeshViewer.Sensor
{
    static class SerialPortExtensions
    {

        internal static async Task<string> GetFriendlyName(string portName)
        {
            string result = portName;

            await Task.Run(() =>
            {
                try
                {
                    string upper = portName.ToUpper();
                    ObjectQuery query = new ObjectQuery("SELECT * FROM Win32_SerialPort");                // Win32_USBControllerDevice
                    using (ManagementObjectSearcher searcher = new ManagementObjectSearcher(query))
                    {
                        foreach (ManagementObject obj2 in searcher.Get())
                        {
                            //DeviceID                     
                            if (obj2.Properties["DeviceID"].Value.ToString().ToUpper() == upper)
                            {
                                result = obj2.Properties["Name"].Value.ToString();
                                break;
                            }
                        }
                    }
                }
                catch { }
            });

            return result;
        }
    }
}
