using LogViewer.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Threading;
using LogViewer.Model;
// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236

namespace LogViewer.Controls
{
    public sealed partial class SimpleLineChart : UserControl
    {
        private DataSeries series;
        private DispatcherTimer _updateTimer;
        DataValue currentValue;
        bool liveScrolling;

        /// <summary>
        /// Set this property to add the chart to a group of charts.  The group will share the same "scale" information across the 
        /// combined chart group so that the charts line up under each other if they are arranged in a stack.
        /// </summary>
        public SimpleLineChart Next { get; set; }

        public SimpleLineChart()
        {
            this.InitializeComponent();
            this.Background = new SolidColorBrush(Colors.Transparent); // ensure we get manipulation events no matter where user presses.
            this.SizeChanged += SimpleLineChart_SizeChanged;
        }

        void SimpleLineChart_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            UpdateChart();
        }

        /// <summary>
        /// Call this method when you turn on LiveScrolling.
        /// </summary>
        public void SetCurrentValue(DataValue value)
        {
            System.Threading.Interlocked.Exchange<DataValue>(ref currentValue, value);
        }

        /// <summary>
        /// Set this to true to start the graph scrolling showing live values provided by thread safe
        /// SetCurrentValue method.
        /// </summary>
        public bool LiveScrolling
        {
            get { return liveScrolling; }
            set
            {
                liveScrolling = value;
                if (value)
                {
                    StartUpdateTimer();
                }
                else
                {
                    StopUpdateTimer();
                }
            }
        }

        private void StartUpdateTimer()
        {
            if (_updateTimer == null)
            {
                _updateTimer = new DispatcherTimer();
                _updateTimer.Interval = TimeSpan.FromMilliseconds(30);
                _updateTimer.Tick += OnUpdateTimerTick;
            }
            _updateTimer.Start();
        }

        private void StopUpdateTimer()
        {
            if (_updateTimer != null)
            {
                _updateTimer.Tick -= OnUpdateTimerTick;
                _updateTimer.Stop();
                _updateTimer = null;
            }
        }

        void OnUpdateTimerTick(object sender, object e)
        {
            if (liveScrolling && currentValue != null)
            {
                SmoothScroll(currentValue);
            }
            else
            {
                UpdateChart();
            }
        }

        MatrixTransform zoomTransform = new MatrixTransform();
        MatrixTransform scaleTransform = new MatrixTransform();

        internal void ZoomTo(double x, double width)
        {
            ComputeScaleSelf();

            // figure out where this is given existing transform.
            Matrix mp = zoomTransform.Matrix;
            mp.OffsetX -= x;
            mp.Scale(this.ActualWidth / width, 1);
            zoomTransform.Matrix = mp;

            UpdateChart();
        }

        internal void ResetZoom()
        {
            zoomTransform = new MatrixTransform();
            UpdateChart();
        }


        public void SetData(DataSeries series)
        {
            this.dirty = true;
            this.series = series;

            this.UpdateLayout();
            if (this.ActualWidth != 0)
            {
                UpdateChart();
            }
        }

        bool dirty;
        int scaleIndex; // for incremental scale calculation.
        double xScale;
        double yScale;
        double minY;
        double maxY;
        double minX;
        double maxX;

        /// <summary>
        /// Returns true if the scale just changed.
        /// </summary>
        bool ComputeScale()
        {
            bool changed = false;
            if (this.Next != null)
            {
                double maxYScale = double.MinValue;
                double maxXScale = double.MinValue;

                double previousYScale = 0;
                double previouXScale = 0;
                for (var ptr = this; ptr != null; ptr = ptr.Next)
                {
                    previousYScale = ptr.yScale;
                    previouXScale = ptr.xScale;
                }

                // make sure they are all up to date.
                for (var ptr = this; ptr != null; ptr = ptr.Next)
                {
                    ptr.ComputeScaleSelf();
                    maxYScale = Math.Max(maxYScale, ptr.yScale);
                    maxXScale = Math.Max(maxXScale, ptr.xScale);
                }

                for (var ptr = this; ptr != null; ptr = ptr.Next)
                {
                    if (ptr.yScale != maxYScale)
                    {
                        ptr.yScale = maxYScale;
                        if (previousYScale != maxYScale)
                        {
                            changed = true;
                        }
                    }
                    if (ptr.xScale != maxXScale)
                    {
                        ptr.xScale = maxXScale;
                        if (previouXScale != maxXScale)
                        {
                            changed = true;
                        }
                    }
                }
            }
            else
            {
                changed = ComputeScaleSelf();
            }
            return changed;
        }



        bool ComputeScaleSelf()
        {
            if (!dirty)
            {
                return false;
            }

            if (scaleIndex == 0)
            {
                minY = double.MaxValue;
                maxY = double.MinValue;
                minX = double.MaxValue;
                maxX = double.MinValue;
            }

            if (series == null)
            {
                return false;
            }
            double actualHeight = this.ActualHeight;
            double actualWidth = this.ActualWidth;
            bool changed = false;
            int len = series.Values.Count;
            for (int i = scaleIndex; i < len; i++)
            {
                if (i < 0 || i >= len)
                {
                    continue;
                }
                DataValue d = series.Values[i];
                double x = d.X;
                double y = d.Y;
                double newMinY = Math.Min(y, minY);
                if (newMinY != minY)
                {
                    minY = newMinY;
                    changed = true;
                }
                double newMaxY = Math.Max(y, maxY);
                if (newMaxY != maxY)
                {
                    maxY = newMaxY;
                    changed = true;
                }

                double newMinX = Math.Min(x, minX);
                if (newMinX != minX)
                {
                    minX = newMinX;
                }

                double newMaxX = Math.Max(x, maxX);
                if (newMaxX != maxX)
                {
                    maxX = newMaxX;
                }
            }
            scaleIndex = len;
            double newyScale = actualHeight / (maxY - minY);
            if (newyScale == 0)
            {
                newyScale = 1;
            }
            if (newyScale != yScale)
            {
                yScale = newyScale;
                changed = true;
            }

            if (!LiveScrolling)
            {
                double newxScale = actualWidth / (maxX - minX);
                if (newxScale == 0)
                {
                    newxScale = 1;
                }
                if (newxScale != xScale)
                {
                    xScale = newxScale;
                    changed = true;
                }
            }
            else
            {
                xScale = 1;
            }

            Matrix m = new Matrix();
            m.Scale(xScale, yScale);
            m.OffsetX = -minX * xScale;
            m.OffsetY = -minY * yScale;
            scaleTransform = new MatrixTransform(m);
            return changed;
        }

        int updateIndex;
        int startIndex;

        private void SmoothScroll(DataValue newValue)
        {
            if (this.series == null)
            {
                this.series = new DataSeries() { Name = "", Values = new List<DataValue>() };
            }

            // we do not use the data value x coordinates right now because they are timestamp values
            // and they bunch up and are not smooth...due to random network noise, so until we figure
            // out something better the graph is smoothing out the x values.
            double x = 0;
            if (this.series.Values.Count > 0)
            {
                x = this.series.Values[this.series.Values.Count - 1].X + 1;
            }

            DataValue copy = new Model.DataValue()
            {
                X = x,
                Y = newValue.Y
            };

            this.series.Values.Add(copy);

            PathGeometry g = Graph.Data as PathGeometry;
            if (g == null)
            {
                UpdateChart();
                return;
            }
            PathFigure f = g.Figures[0];

            if (ComputeScale() || g.Bounds.Width > 2 * this.ActualWidth)
            {
                // can't do incremental, have to reset scaled values.
                if (this.series != null && this.series.Values.Count > 2 * this.ActualWidth)
                {
                    // purge history since this is an infinite scrolling stream...
                    this.series.Values.RemoveRange(0, this.series.Values.Count - (int)this.ActualWidth);
                    System.Diagnostics.Debug.WriteLine("Trimming data series {0} back to {1} values", this.series.Name, this.series.Values.Count);
                }
                UpdateChart();
            }
            else
            {
                AddScaledValues(f, updateIndex, series.Values.Count);
                Graph.UpdateLayout();
                if (g.Bounds.Width >= this.ActualWidth)
                {
                    Canvas.SetLeft(Graph, Canvas.GetLeft(Graph) - 1);
                }
                updateIndex = series.Values.Count;
            }
        }


        void UpdateChart()
        {
            Canvas.SetLeft(Graph, 0);
            scaleIndex = 0;
            updateIndex = 0;

            if (series.Values == null || series.Values.Count == 0)
            {
                Graph.Data = null;
                MinLabel.Text = "";
                MaxLabel.Text = "";
                return;
            }
            if (liveScrolling && series.Values.Count > this.ActualWidth)
            {
                // just show the tail that fits on screen, since the scaling will not happen on x-axis in this case.
                updateIndex = series.Values.Count - (int)this.ActualWidth;
                scaleIndex = updateIndex;
                startIndex = updateIndex;
                minY = double.MaxValue;
                maxY = double.MinValue;
                minX = double.MaxValue;
                maxX = double.MinValue;
            }

            ComputeScale();

            double count = series.Values.Count;
            PathGeometry g = new PathGeometry();
            PathFigure f = new PathFigure();
            g.Figures.Add(f);

            AddScaledValues(f, updateIndex, series.Values.Count);
            updateIndex = series.Values.Count;

            //MinLabel.Text = minY.ToString("N2");
            //MaxLabel.Text = maxY.ToString("N2");

            Graph.Data = g;
            Graph.Stroke = this.Stroke;
            Graph.StrokeThickness = this.StrokeThickness;

        }

        private void AddScaledValues(PathFigure figure, int start, int end)
        {
            double height = this.ActualHeight;
            double availableHeight = height;
            double width = this.ActualWidth;

            int len = series.Values.Count;
            
            bool started = (figure.Segments.Count > 0);
            for (int i = start; i < end; i++)
            {
                DataValue d = series.Values[i];

                // add graph segment
                Point point = scaleTransform.Transform(new Point(d.X, d.Y));
                point = zoomTransform.Transform(point);
                double y = availableHeight - point.Y;
                double x = point.X;

                Point pt = new Point(x, y);
                if (!started)
                {
                    figure.StartPoint = pt;
                    started = true;
                }
                else
                {
                    figure.Segments.Add(new LineSegment() { Point = pt });
                }
            }
        }

        public Brush Stroke
        {
            get { return (Brush)GetValue(StrokeProperty); }
            set { SetValue(StrokeProperty, value); }
        }

        // Using a DependencyProperty as the backing store for Stroke.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty StrokeProperty =
            DependencyProperty.Register("Stroke", typeof(Brush), typeof(SimpleLineChart), new PropertyMetadata(new SolidColorBrush(Colors.White)));



        public double StrokeThickness
        {
            get { return (double)GetValue(StrokeThicknessProperty); }
            set { SetValue(StrokeThicknessProperty, value); }
        }

        // Using a DependencyProperty as the backing store for StrokeThickness.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty StrokeThicknessProperty =
            DependencyProperty.Register("StrokeThickness", typeof(double), typeof(SimpleLineChart), new PropertyMetadata(1.0));

        private void CloseBoxClick(object sender, RoutedEventArgs e)
        {
            if (Closed != null)
            {
                Closed(this, EventArgs.Empty);
            }
        }

        public event EventHandler Closed;


        internal void HandleMouseMove(MouseEventArgs e)
        {
            Point pos = e.GetPosition(this.Graph);
            UpdatePointer(pos);
        }

        internal void HandleMouseLeave()
        {
            HidePointer();
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            HandleMouseMove(e);
            base.OnMouseMove(e);
        }

        protected override void OnMouseLeave(MouseEventArgs e)
        {
            HandleMouseLeave();
            base.OnMouseLeave(e);
        }

        public Color LineColor
        {
            get
            {
                var brush = this.Stroke as SolidColorBrush;
                if (brush != null)
                {
                    return brush.Color;
                }

                return Colors.Black;
            }
            set
            {
                this.Stroke = new SolidColorBrush(value);

                HlsColor darker = new HlsColor(value);
                darker.Darken(0.33f);
                PointerBorder.BorderBrush = Pointer.Fill = PointerLabel.Foreground = new SolidColorBrush(darker.Color);

            }
        }

        const double TooltipThreshold = 20;

        void UpdatePointer(Point pos)
        {
            if (series.Values != null && series.Values.Count > 0)
            {

                // add graph segment
                double height = this.ActualHeight;
                double availableHeight = height;
                double width = this.ActualWidth;

                double minDistance = double.MaxValue;
                DataValue found = null;

                // find the closed data value.

                for (int i = 0; i < series.Values.Count; i++)
                {
                    DataValue d = series.Values[i];

                    Point scaled = scaleTransform.Transform(new Point(d.X, d.Y));
                    scaled = zoomTransform.Transform(scaled);
                    double x = scaled.X;
                    double y = availableHeight - scaled.Y;
                    double dx = (x - pos.X);
                    double dy = y - pos.Y;
                    double distance = Math.Sqrt((dx * dx) + (dy * dy));
                    if (distance < TooltipThreshold)
                    {
                        if (distance < minDistance)
                        {
                            minDistance = distance;
                            found = d;
                        }
                    }
                }
                if (found != null)
                {
                    PointerLabel.Text = series.Name + " = " + (!string.IsNullOrEmpty(found.Label) ? found.Label : found.Y.ToString("N3"));
                    PointerBorder.UpdateLayout();

                    double tipPositionX = pos.X;
                    if (tipPositionX + PointerBorder.ActualWidth > this.ActualWidth)
                    {
                        tipPositionX = this.ActualWidth - PointerBorder.ActualWidth;
                    }
                    double tipPositionY = pos.Y - PointerLabel.ActualHeight - 4;
                    if (tipPositionY < 0)
                    {
                        tipPositionY = 0;
                    }
                    PointerBorder.Margin = new Thickness(tipPositionX, tipPositionY, 0, 0);
                    PointerBorder.Visibility = System.Windows.Visibility.Visible;

                    double value = found.Y;
                    Point scaled = scaleTransform.Transform(new Point(found.X, found.Y));
                    scaled = zoomTransform.Transform(scaled);
                    double x = scaled.X;
                    double y = availableHeight - scaled.Y;
                    Point pointerPosition = new Point(x, y);
                    Pointer.RenderTransform = new TranslateTransform(pointerPosition.X, pointerPosition.Y);
                    Pointer.Visibility = System.Windows.Visibility.Visible;
                }
                else
                {
                    PointerBorder.Visibility = System.Windows.Visibility.Hidden;
                    Pointer.Visibility = System.Windows.Visibility.Hidden;
                }

            }
        }

        void HidePointer()
        {
            Pointer.Visibility = Visibility.Collapsed;
        }

    }

}
