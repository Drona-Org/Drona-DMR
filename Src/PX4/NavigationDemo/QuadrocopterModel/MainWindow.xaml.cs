using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Media3D;
using System.Windows.Media.Media3D.Converters;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Windows.Media.Animation;
using System.IO;
using MeshViewer.Gestures;
using MeshViewer.Sensor;

namespace MeshViewer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ModelVisual3D model;
        RotateGesture3D gesture;
        Settings settings;
        Rect3D modelBounds;
        double modelRadius;
        Point3D lookAt;

        public MainWindow()
        {
            InitializeComponent();
            this.Loaded += OnWindowLoaded;
            gesture = new RotateGesture3D(this);
            gesture.Changed += OnGestureChanged;
            settings = Settings.Load();

            this.Closing += OnWindowClosing;
        }

        private void OnWindowClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            PerspectiveCamera camera = (PerspectiveCamera)MainViewPort.Camera;
            Vector3D position = (Vector3D)camera.Position;

            settings.CameraX = position.X;
            settings.CameraY = position.Y;
            settings.CameraZ = position.Z;

            if (this.model != null)
            {
                RotateTransform3D transform = (RotateTransform3D)model.Transform;
                QuaternionRotation3D rotation = (QuaternionRotation3D)transform.Rotation;
                Quaternion quat = rotation.Quaternion;
                settings.RotationX = quat.X;
                settings.RotationY = quat.Y;
                settings.RotationZ = quat.Z;
                settings.RotationW = quat.W;
            }

            settings.Save();
        }

        private void OnGestureChanged(object sender, EventArgs e)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                UpdateRotation();
            }));
        }

        private void OnWindowLoaded(object sender, RoutedEventArgs e)
        {
            LoadModel();

            PerspectiveCamera camera = (PerspectiveCamera)MainViewPort.Camera;
            Vector3D position = (Vector3D)camera.Position;
            position.X = settings.CameraX;
            position.Y = settings.CameraY;
            position.Z = settings.CameraZ;
            camera.Position = (Point3D)position;

            if (this.model != null)
            {
                this.modelBounds = this.model.Content.Bounds;
                double radius = Math.Max(modelBounds.Size.X, Math.Max(modelBounds.Size.Y, modelBounds.Size.Z));
                this.modelRadius = radius;
                Point3D center = new Point3D(modelBounds.X + (modelBounds.SizeX / 2), modelBounds.Y + (modelBounds.SizeY / 2), modelBounds.Z + (modelBounds.SizeZ / 2));
                this.lookAt = center;

                if (camera.Position.X == 0 && camera.Position.Y == 0 && camera.Position.Z == 0)
                {
                    position.X = this.modelBounds.X + this.modelBounds.SizeX;
                    position.Y = this.modelBounds.Y + (this.modelBounds.SizeY / 2);
                    position.Z = this.modelBounds.Z + this.modelBounds.SizeZ;
                    position.Normalize();
                    position *= (radius * 3);
                    camera.Position = (Point3D)position;
                }

                camera.LookDirection = this.lookAt - camera.Position;

                camera.FarPlaneDistance = radius * 10;

                Quaternion rotation  = new Quaternion(settings.RotationX, settings.RotationY, settings.RotationZ, settings.RotationW);
                QuaternionRotation3D quaternionRotation = new QuaternionRotation3D(rotation);
                RotateTransform3D myRotateTransform = new RotateTransform3D(quaternionRotation);
                model.Transform = myRotateTransform;
                gesture.Rotation = rotation;
            }

        }

        private void UpdateConnectIcon(bool state)
        {
            ConnectIcon.Visibility = (state) ? Visibility.Collapsed : Visibility.Visible;
            DisconnectIcon.Visibility = (state) ? Visibility.Visible : Visibility.Collapsed;
        }

        static DiffuseMaterial material = new DiffuseMaterial(new LinearGradientBrush(Colors.BlueViolet, Colors.Violet, 45));
        static DiffuseMaterial backMaterial = new DiffuseMaterial(new LinearGradientBrush(Colors.DarkGreen, Colors.Green, 45));


        private void LoadModel()
        {
            MeshGeometry3D mymesh = new MeshGeometry3D();

            using (var stream = this.GetType().Assembly.GetManifestResourceStream("MeshViewer.Mesh.txt"))
            {
                using (var reader = new StreamReader(stream))
                {
                    string line = null;
                    do
                    {
                        line = reader.ReadLine();
                        if (line != null)
                        {
                            int i = line.IndexOf(',');
                            string a = line.Substring(0, i);
                            int j = line.IndexOf(',', i + 1);
                            string b = line.Substring(i + 1, j - i - 1);
                            string c = line.Substring(j + 1);

                            double x = double.Parse(a);
                            double y = double.Parse(b);
                            double z = double.Parse(c);

                            mymesh.Positions.Add(new Point3D(x, y, z));
                        }
                    }
                    while (line != null);
                }
            }

            
            GeometryModel3D geometry = new GeometryModel3D(mymesh, material);
            geometry.BackMaterial = backMaterial;

            Model3DGroup group = new Model3DGroup();
            group.Children.Add(geometry);

            this.model = new ModelVisual3D();
            this.model.Content = group;

            this.MainViewPort.Children.Add(this.model);
        }


        private void UpdateRotation()
        {
            Quaternion totalRotation = gesture.Rotation;
            QuaternionRotation3D rotation = new QuaternionRotation3D(totalRotation);
            RotateTransform3D myRotateTransform = new RotateTransform3D(rotation);
            model.Transform = myRotateTransform;
            
            PerspectiveCamera camera = (PerspectiveCamera)MainViewPort.Camera;
            Vector3D position = (Vector3D)camera.Position;
            Vector3D lookDirection = this.lookAt - camera.Position;
            double length = lookDirection.Length;
            length += (gesture.Zoom * this.modelRadius / 10); // 10 clicks to travel size of model
            if (length <= 0.1)
            {
                length = 0.1;
            }
            lookDirection.Normalize();
            lookDirection *= length;
            gesture.Zoom = 0;

            camera.Position = this.lookAt - lookDirection;

        }


    }
}
