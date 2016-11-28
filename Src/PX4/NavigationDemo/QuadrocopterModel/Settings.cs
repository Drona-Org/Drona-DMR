using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Media.Media3D;
using System.Xml.Serialization;

namespace MeshViewer
{
    public class Settings
    {
        public Settings()
        {
        }

        // X,Y,Z,W is the quaternion rotation
        public double RotationX { get; set; }

        public double RotationY { get; set; }

        public double RotationZ { get; set; }

        public double RotationW { get; set; }

        // position of the camera
        public double CameraX { get; set; }

        public double CameraY { get; set; }

        public double CameraZ { get; set; }

        public static Settings Load()
        {
            try
            {
                XmlSerializer s = new XmlSerializer(typeof(Settings));
                using (FileStream fs = new FileStream(GetFilePath(), FileMode.Open))
                {
                    return (Settings)s.Deserialize(fs);
                }
            }
            catch
            {
                return new Settings();
            }
        }

        public void Save()
        {
            try
            {
                XmlSerializer s = new XmlSerializer(typeof(Settings));
                using (FileStream fs = new FileStream(GetFilePath(), FileMode.Create))
                {
                    s.Serialize(fs, this);
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Settings.Save failed: " + ex.Message);
            }
        }

        const string FileName = "Settings.xml";

        public static string GetFilePath()
        {
            string appdata = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
            string path = System.IO.Path.Combine(appdata, "QuadrocopterModel");
            System.IO.Directory.CreateDirectory(path);
            return System.IO.Path.Combine(path, FileName);
        }
    }
}
