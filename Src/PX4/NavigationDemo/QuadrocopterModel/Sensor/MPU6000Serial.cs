using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MeshViewer.Sensor
{
    class MPU6000Serial
    {
        SerialPort port;
        bool opened;

        public MPU6000Serial()
        {

        }

        public async Task ConnectAsync()
        {
            await Task.Run(async () =>
            {
                foreach (string name in SerialPort.GetPortNames())
                {
                    try {
                        string fullName = await SerialPortExtensions.GetFriendlyName(name);
                        if (fullName.Contains("USB Serial Port"))
                        {
                            port = new SerialPort(name, 115200);
                            port.Open();
                            opened = true;
                            port.Close();
                        }
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine(ex.Message);
                    }
                }
            });
        }
    }
}

