using Microsoft.Networking;
using Microsoft.Networking.Mavlink;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace MavlinkTest
{
    class Program
    {
        IPort port;
        IPEndPoint udpAddress;
        const int DefaultUdpPort = 14550;
        string comPortName;
        IPEndPoint proxyAddress;
        UdpPort  proxyPort;
        const int DefaultComBaudRate = 115200;
        private MavlinkChannel proxyChannel;

        static void Main(string[] args)
        {
            Program p = new MavlinkTest.Program();
            if (!p.ParseCommandLine(args))
            {
                PrintUsage();
                return;
            }
            else
            {
                p.Run();
            }
            ManualResetEvent forever = new ManualResetEvent(false);
            forever.WaitOne();
        }

        static void PrintUsage()
        {
            Console.WriteLine("Usage: MavlinkTest [-udp [localIp][:port]] [-com name] [-proxy [ip][:port]]");
            Console.WriteLine("Dumps mavlink messages received from the specified channel and optionally relays to given proxy");
            Console.WriteLine("Options:");
            Console.WriteLine("-udp [localIp][:port]      Listen to UDP on local IP and port (default 14550)");
            Console.WriteLine("-com name                  List to COM port");
            Console.WriteLine("-proxy [ip][:port]         Act as a proxy and relay all messages to given ip & port");
        }

        bool ParseCommandLine(string[] args)
        {
            for (int i = 0; i < args.Length; i++)
            {
                string arg = args[i];
                if (arg[0] == '-' || arg[0] == '/')
                {
                    switch (arg.Substring(1).ToLowerInvariant())
                    {
                        case "udp":
                            if (i + 1 < args.Length)
                            {                                 
                                string ip = args[++i];
                                udpAddress = ParseIPEndPoint(ip, DefaultUdpPort);
                                if (udpAddress == null)
                                {
                                    return false;
                                }
                            }
                            else
                            {
                                Console.WriteLine("### Error: please also provide the ip address, e.g. 192.168.1.20:14550");
                                return false;
                            }
                            break;
                        case "proxy":
                            if (i + 1 < args.Length)
                            {
                                string ip = args[++i];
                                proxyAddress = ParseIPEndPoint(ip, DefaultUdpPort);
                            }
                            else
                            {
                                Console.WriteLine("### Error: please also provide the port number, e.g. localhost:14555");
                                return false;
                            }
                            break;
                        case "com":
                            if (i + 1 < args.Length)
                            {
                                comPortName = args[++i];
                            }
                            else
                            {
                                Console.WriteLine("### Error: please also provide the com port name, e.g. 'COM4'");
                                return false;
                            }
                            break;
                        case "h":
                        case "?":
                        case "help":
                            return false;
                        default:
                            Console.WriteLine("### Error: unknown argument: '{0}'", arg);
                            return false;
                    }
                }
                else
                {
                    Console.WriteLine("### Error: unknown argument: '{0}'", arg);
                    return false;
                }
            }
            if (udpAddress == null && comPortName == null)
            {
                Console.WriteLine("### Error: missing port type argument");
                return false;
            }
            return true;
        }

        static IPEndPoint ParseIPEndPoint(string addr, int defaultPort)
        {
            int i = addr.IndexOf(':');
            if (i > 0)
            {
                string number = addr.Substring(i + 1);
                if (!int.TryParse(number, out defaultPort))
                {
                    Console.WriteLine("Invalid port number: " + number);
                    return null;
                }
                addr = addr.Substring(0, i);
            }
            IPAddress address = null;
            if (!IPAddress.TryParse(addr, out address))
            {
                Console.WriteLine("Invalid ip address: " + addr);
                return null;            
            }
            return new IPEndPoint(address, defaultPort);
        }

        void Run()
        {
            if (udpAddress != null)
            {
                UdpPort udp = new UdpPort();
                udp.Connect(udpAddress);

                IPEndPoint remote = udp.WaitForOneMessage(TimeSpan.FromSeconds(10));
                if (remote == null)
                {
                    Console.WriteLine("### Error: not getting any messages from " + udpAddress);
                    return;
                }
                port = udp;
            }
            else if (comPortName != null)
            {
                SerialPort serial = new SerialPort();
                serial.Connect(comPortName, DefaultComBaudRate);
                port = serial;
            }
            if (proxyAddress != null)
            {
                proxyPort = new UdpPort();
                proxyPort.Connect(new IPEndPoint(udpAddress.Address, 0), proxyAddress);
                proxyChannel = new MavlinkChannel();
                proxyChannel.MessageReceived += OnProxyMessageReceived;
                proxyChannel.Start(proxyPort);
            }
            
            MavlinkChannel channel = new MavlinkChannel();
            channel.MessageReceived += OnMessageReceived;
            channel.Start(port);
        }

        private void OnProxyMessageReceived(object sender, MavLinkMessage e)
        {
            // message from the proxy has to go back the other way.
            byte[] packed = e.Pack();
            port.Write(packed, packed.Length);
        }

        private void OnMessageReceived(object sender, MavLinkMessage e)
        {
            if (proxyAddress != null)
            {
                // send it to the proxy...
                byte[] packed = e.Pack();
                proxyPort.Write(packed, packed.Length);
            }
            if (e.SystemId != 1  && e.SystemId != 10)
            {
                
            }
            Console.Write(e.TypedPayload.GetType().Name);
        
            if (e.TypedPayload is MAVLink.mavlink_statustext_t)
            {
                MAVLink.mavlink_statustext_t s = (MAVLink.mavlink_statustext_t)e.TypedPayload;
                string msg = BytesToString(s.text);
                Console.WriteLine(":  severity=" + s.severity + ", text=" + msg);
            }
            else if (e.TypedPayload is MAVLink.mavlink_named_value_int_t)
            {
                MAVLink.mavlink_named_value_int_t nv = (MAVLink.mavlink_named_value_int_t)e.TypedPayload;
                string name = BytesToString(nv.name);
                Console.WriteLine(":  " + nv.name + "=" + nv.value);
            }
            else if (e.TypedPayload is MAVLink.mavlink_named_value_float_t)
            {
                MAVLink.mavlink_named_value_float_t nv = (MAVLink.mavlink_named_value_float_t)e.TypedPayload;
                string name = BytesToString(nv.name);
                Console.WriteLine(":  " + nv.name + "=" + nv.value);
            }
            else if (e.TypedPayload != null)
            {
                Console.WriteLine(":  " + e.ToString());
            }
            else
            {
                Console.WriteLine("UnknownMessageType:  " + e.ToString());
            }
        }
        
        static string BytesToString(byte[] b)
        {
            if (b == null || b.Length == 0) return "";
            int n = b.Length;
            for (int i = 0; i < n; i++)
            {
                if (b[i] == '\0')
                {
                    n = i;
                    break;
                }
            }
            return Encoding.UTF8.GetString(b, 0, n);
        }
    }
}
