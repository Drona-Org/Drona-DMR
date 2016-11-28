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

namespace LogViewer.Controls
{
    /// <summary>
    /// Interaction logic for SelectionOverlay.xaml
    /// </summary>
    public partial class ChartStack : Grid
    {
        public ChartStack()
        {
            InitializeComponent();
        }
        private bool selecting;
        private Point mouseDownPos;

        public void AddChart(FrameworkElement chart)
        {
            theStack.Children.Add(chart);
        }
        public void RemoveChart(FrameworkElement chart)
        {
            if (chart.Parent == theStack)
            {
                theStack.Children.Remove(chart);
            }
            else if (chart.Parent is Grid)
            {
                // it's a chart group then.
                Grid group = (Grid)chart.Parent;
                group.Children.Remove(chart);
                if (group.Children.Count == 0)
                {
                    theStack.Children.Remove(group);
                }
            }
        }

        public void ClearCharts()
        {
            theStack.Children.Clear();
        }

        public int ChartCount {  get { return theStack.Children.Count; } }

        public UIElementCollection Charts {  get { return theStack.Children; } }


        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            selecting = true;
            Point pos = mouseDownPos = e.GetPosition(this);
            Selection.Visibility = Visibility.Visible;
            Selection.Width = 1;
            Selection.Height = this.ActualHeight;
            Selection.Margin = new Thickness(pos.X, 0, 0, 0);
            this.CaptureMouse();
            base.OnMouseLeftButtonDown(e);
        }

        protected override void OnMouseLeftButtonUp(MouseButtonEventArgs e)
        {
            if (selecting)
            {
                Point pos = e.GetPosition(this);

                double x = Math.Min(pos.X, mouseDownPos.X);
                double width = Math.Abs(pos.X - mouseDownPos.X);

                ZoomTo(x, width);

                selecting = false;
                Selection.Visibility = Visibility.Collapsed;

            }
            this.ReleaseMouseCapture();
            base.OnMouseLeftButtonUp(e);
        }

        IEnumerable<SimpleLineChart> FindCharts()
        {
            foreach (UIElement e in theStack.Children)
            {
                SimpleLineChart chart = e as SimpleLineChart;
                if (chart != null)
                {
                    yield return chart;
                }
                Grid group = e as Grid;
                if (group != null)
                {
                    foreach (UIElement f in group.Children)
                    {
                        chart = f as SimpleLineChart;
                        if (chart != null)
                        {
                            yield return chart;
                        }
                    }
                }
            }
        }

        private void ZoomTo(double x, double width)
        {
            foreach (SimpleLineChart chart in FindCharts())
            {
                chart.ZoomTo(x, width);
            }
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            Point pos = e.GetPosition(this);
            if (selecting)
            {
                double x = Math.Min(pos.X, mouseDownPos.X);
                Selection.Width = Math.Abs(pos.X - mouseDownPos.X);
                Selection.Margin = new Thickness(x, 0, 0, 0);
            }
            else
            {
                foreach (SimpleLineChart chart in FindCharts())
                {
                    chart.HandleMouseMove(e);
                }
                e.Handled = false;
            }
            base.OnMouseMove(e);
        }

        protected override void OnMouseLeave(MouseEventArgs e)
        {
            foreach (SimpleLineChart chart in FindCharts())
            {
                chart.HandleMouseLeave();
            }
            base.OnMouseLeave(e);
        }

        protected override void OnLostMouseCapture(MouseEventArgs e)
        {
            selecting = false;
            Selection.Visibility = Visibility.Collapsed;
            base.OnLostMouseCapture(e);
        }

        internal void ResetZoom()
        {
            foreach (SimpleLineChart chart in FindCharts())
            {
                chart.ResetZoom();
            }
        }
    }
}
