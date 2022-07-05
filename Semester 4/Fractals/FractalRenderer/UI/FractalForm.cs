using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace FractalRenderer
{
    public partial class FractalForm : Form
    {
        #region MEMBERS
        IAsyncResult renderResult = null;
        IFractal frac = null;
        string caption = String.Empty;
        float CalculationProgress = 0;
        Bitmap LastFractalImage = null;
        int LastErrorCode = 0;
        Point dragStart = Point.Empty;
        Point dragEnd = Point.Empty;
        Rectangle r = new Rectangle();
        bool isDragging = false;
        bool isZooming = false;
        bool isRendering = false;
        DateTime renderStart = DateTime.MinValue;
        TimeSpan renderTime = new TimeSpan();
        #endregion

        /// <summary>
        /// Get or set fractal associated with  this form
        /// </summary>
        public IFractal Fractal
        {
            get { return frac; }
            set { frac = value; }
        }

        public FractalForm()
        {            
            InitializeComponent();
            pictureBox2.MouseMove += new MouseEventHandler(pictureBox2_MouseMove);
            pictureBox2.MouseDown += new MouseEventHandler(pictureBox2_MouseDown);
            pictureBox2.MouseUp += new MouseEventHandler(pictureBox2_MouseUp);
            splitContainer2.Panel1.SizeChanged += new System.EventHandler(this.splitContainer2_Panel1_SizeChanged);           
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            if (isRendering && renderResult != null)
            {
                frac.EndRender(renderResult);
            }
            base.OnClosing(e);
        }

        private void splitContainer2_Panel1_SizeChanged(object sender, EventArgs e)
        {
            UpdatePictureBox();
        }

        
        void UpdatePictureBox()
        {
            if (InvokeRequired)
            {
                this.Invoke(new MethodInvoker(UpdatePictureBox));
            }
            else
            {
                if (LastFractalImage != null)
                {
                    pictureBox2.Width = LastFractalImage.Width + 20;
                    pictureBox2.Height = LastFractalImage.Height + 20;

                    Point location = pictureBox2.Location;

                    if (pictureBox2.Width < splitContainer2.Panel1.Width)
                    {
                        location.X = (splitContainer2.Panel1.Width - pictureBox2.Width) / 2;
                    }
                    else
                    {
                        location.X = -splitContainer2.Panel1.HorizontalScroll.Value;
                    }

                    if (pictureBox2.Height < splitContainer2.Panel1.Height)
                    {
                        location.Y = (splitContainer2.Panel1.Height - pictureBox2.Height) / 2;
                    }
                    else
                    {
                        location.Y = -splitContainer2.Panel1.VerticalScroll.Value;
                    }

                    pictureBox2.Location = location;
                }
            }
        }

        void OnImageOriginDragged(int dx, int dy)
        {
            ((Generic2DFractal)frac).SetOrigin(dx, dy);          

            RenderFractal();
        }

        void OnControlPointDragged(int dx, int dy)
        {
            ((Generic2DFractal)frac).SetControlParameter(dx, dy);

            RenderFractal();

        }
        bool ScreenToFractal(double X, double Y, out double XF, out double YF)
        {
            if (pictureBox2.Image != null)
            {
                int off_x = pictureBox2.Width - pictureBox2.Image.Width;
                int off_y = pictureBox2.Height - pictureBox2.Image.Height;

                off_x /= 2;
                off_y /= 2;

                if (X > off_x && X < (off_x + pictureBox2.Image.Width) &&
                    Y > off_y && Y < (off_y + pictureBox2.Image.Height))
                {
                    X -= off_x;
                    Y -= off_y;
                    IFractalParameters pars = frac.Parameters;

                    double FracX = (double)pars.GetValue("X");
                    double FracY = (double)pars.GetValue("Y");
                    double FracWidth = (double)pars.GetValue("W");
                    double FracHeight = (double)pars.GetValue("H");
                    double FracX1 = FracX - 0.5 * FracWidth;
                    double FracY1 = FracY - 0.5 * FracHeight;
                   
                    // PicW : X = FracWidth : dxf
                    // pictureBox2.Image.Width : X = FracWidth : dxf
                    double dxf = FracWidth * X / pictureBox2.Image.Width;
                    double dyf = FracHeight * Y / pictureBox2.Image.Height;
                    XF = FracX1 + dxf;
                    YF = FracY1 + dyf;
                    return true;
                }
            }
            XF = 0;
            YF = 0;
            return false;
        }

        void OnImageZoomed(Point p1, Point p2)
        {
            IFractalParameters pars = frac.Parameters;
            
            double x1f,y1f;
            double x2f, y2f;

            ScreenToFractal(p1.X, p1.Y, out x1f, out y1f);
            ScreenToFractal(p2.X, p2.Y, out x2f, out y2f);

            double XN = (x2f + x1f) / 2.0;
            double YN = (y2f + y1f) / 2.0;
            double WFN = (x2f - x1f);
            double HFN = (y2f - y1f);
            pars.SetValue("X", XN);
            pars.SetValue("Y", YN);
            pars.SetValue("W", WFN);
            pars.SetValue("H", HFN);
            RenderFractal();
        }

        void pictureBox2_MouseUp(object sender, MouseEventArgs e)
        {
            if (IsMouseOverImage(e.X, e.Y) && 
                dragStart != Point.Empty && 
                e.Button == MouseButtons.Right)
            {
                // begin drag
                dragEnd = new Point(e.X, e.Y);
                OnImageOriginDragged(dragEnd.X - dragStart.X, dragEnd.Y - dragStart.Y);
            }
            else if (IsMouseOverImage(e.X, e.Y) &&
                     dragStart != Point.Empty &&
                     e.Button == MouseButtons.Middle)
            {
                // begin drag
                dragEnd = new Point(e.X, e.Y);
                OnControlPointDragged(dragEnd.X - dragStart.X, dragEnd.Y - dragStart.Y);
            }
            else if (IsMouseOverImage(e.X, e.Y) && dragStart != Point.Empty && e.Button == MouseButtons.Left)
            {
                double ar = 1.0;

                if (pictureBox2.Image != null)
                {
                    ar = (double)pictureBox2.Image.Width / (double)pictureBox2.Image.Height;
                }

                double drw = e.X - dragStart.X;
                double drh = e.Y - dragStart.Y;

                if (drw > drh)  drh = drw / ar;                 
                else            drw = drh * ar;

                dragEnd = new Point((int)(dragStart.X + drw), (int)(dragStart.Y + drh));                 
                OnImageZoomed( dragStart , dragEnd );
            }

            isZooming = false;
            isDragging = false;
            dragStart = Point.Empty;
            dragEnd = Point.Empty;         
            this.Cursor = Cursors.Default;
        }

        void pictureBox2_MouseDown(object sender, MouseEventArgs e)
        {
            if (IsMouseOverImage(e.X, e.Y) && 
                dragStart == Point.Empty && 
                e.Button == MouseButtons.Right &&
                !isRendering)
            {
                // begin drag
                dragStart = new Point(e.X, e.Y);
                Cursor = Cursors.SizeAll;
                isDragging = true;
            }
            else if (IsMouseOverImage(e.X, e.Y) &&
            dragStart == Point.Empty &&
            e.Button == MouseButtons.Middle &&
            !isRendering)
            {
                // begin drag
                dragStart = new Point(e.X, e.Y);
                Cursor = Cursors.Cross;
                isDragging = true;
            }
            else if (IsMouseOverImage(e.X, e.Y) && 
                     dragStart == Point.Empty && 
                     e.Button == MouseButtons.Left &&
                     !isRendering)
            {
                dragStart = new Point(e.X, e.Y);
                Cursor = Cursors.IBeam;
                isZooming = true;
                // begin zoom
                Point startPoint = pictureBox2.PointToScreen(new Point(e.X, e.Y));
                r = new Rectangle(startPoint.X, startPoint.Y, 0, 0);              
            }
            else
            {
                dragStart = Point.Empty;
                dragEnd = Point.Empty;
                Cursor = Cursors.Default;
            }
        }

        void pictureBox2_MouseMove(object sender, MouseEventArgs e)
        {
            
            if (!isDragging && !isZooming && !isRendering)
            {
                if (IsMouseOverImage(e.X, e.Y))
                {                     
                    this.Cursor = Cursors.Hand;                     
                }
                else
                {
                    this.Cursor = Cursors.Default;
                }
            }           
            else if (isZooming && !isRendering)
            {                 
                ControlPaint.DrawReversibleFrame(r, this.BackColor, FrameStyle.Dashed);

                Point endPoint = pictureBox2.PointToScreen(new Point(e.X, e.Y));
                Point startPoint = pictureBox2.PointToScreen(dragStart);
                double ar = 1.0;

                if (pictureBox2.Image != null)
                {
                    ar = (double)pictureBox2.Image.Width / (double)pictureBox2.Image.Height;
                }

                double drw = endPoint.X - startPoint.X;
                double drh = endPoint.Y - startPoint.Y;

                if (drw > drh)      drh = drw / ar;
                else                drw = drh * ar;

                r = new Rectangle(startPoint.X, startPoint.Y, (int)drw, (int)drh);               
                
                ControlPaint.DrawReversibleFrame(r, this.BackColor, FrameStyle.Dashed);               
            }
        }

        bool IsMouseOverImage(int X, int Y)
        {
            if (pictureBox2.Image != null)
            {
                int off_x = pictureBox2.Width - pictureBox2.Image.Width;
                int off_y = pictureBox2.Height - pictureBox2.Image.Height;

                off_x /= 2;
                off_y /= 2;

                if (X > off_x && X < (off_x + pictureBox2.Image.Width) &&
                     Y > off_y && Y < (off_y + pictureBox2.Image.Height))
                {
                    return true;
                }
            }
            return false;
        }

        private void OnChangefractalSettings(object sender, EventArgs e)
        {
            try
            {
                frac.Configure();
                 
            }
            catch { }
        }
       
        private void UpdateFormContent()
        {
            if (InvokeRequired)
            {
                this.Invoke(new MethodInvoker(UpdateFormContent));
            }
            else
            {
                try
                {
                    this.Text = caption;
                    if (LastFractalImage == null)
                    {
                        toolStripStatusLabel1.Visible = true;
                        toolStripStatusLabel1.Text = "Отказано";
                        toolStripProgressBar1.Visible = false;
                        // LastErrorCode = 1;
                    }
                    else
                    {
                        toolStripStatusLabel1.Visible = true;
                        toolStripStatusLabel1.Text= "Генерирано:  " + renderTime.TotalSeconds + "s";
                        toolStripProgressBar1.Visible = false;
                    }
                    stopToolStripMenuItem.Enabled = false;
                    renderToolStripMenuItem.Enabled = true;
                    editToolStripMenuItem.Enabled = true;
                    if (LastErrorCode == 0)
                    {
                        pictureBox2.Image = LastFractalImage;
                        pictureBox2.SizeMode = PictureBoxSizeMode.CenterImage;
                        UpdatePictureBox();                       
                    }
                    
                }
                catch { }
            }
        }

        private void UpdateFormCaption()
        {
            if (InvokeRequired)
            {
                this.Invoke(new MethodInvoker(UpdateFormCaption));
            }
            else
            {
                int Pcnt = (int)CalculationProgress;
                this.Text = caption + "[" + Pcnt + "%]";
                this.toolStripProgressBar1.Value = Pcnt;
            }
        }

        private void RenderComplete(Bitmap bmp, int ErrorCode)
        {
            try
            {
                if (renderResult != null)
                {                   
                    renderTime = DateTime.Now - renderStart;
                    LastErrorCode = ErrorCode;
                    
                    frac.EndRender(renderResult);
                    LastFractalImage = bmp;
                   
                    UpdateFormContent();
                    
                    renderResult = null;
                    isRendering = false;
                }                
            }
            catch { }             
        }

        private void RenderStatusUpdated(float pcnt)
        {
            try
            {
                CalculationProgress = pcnt;
                UpdateFormCaption();
            }
            catch { }
        }
                
        private void InterruptRender()
        {
            if (renderResult != null)
            {
                frac.EndRender(renderResult);               
            }

            renderToolStripMenuItem.Enabled = true;
            stopToolStripMenuItem.Enabled = false;
        }

        private void RenderFractal()
        {
            if (renderResult == null)
            {
                caption = this.Text;
                isRendering = true;

                renderStart = DateTime.Now;
                renderResult = frac.BeginRender(new RenderResult.RenderComplete(RenderComplete),
                                                  new RenderResult.RenderStatus(RenderStatusUpdated));

                renderToolStripMenuItem.Enabled = false;
                editToolStripMenuItem.Enabled = false;
                stopToolStripMenuItem.Enabled = true;
                toolStripStatusLabel1.Visible = false;
                toolStripProgressBar1.Visible = true;
            }
        }

        private void OnrenderToolStripMenuItemClicked(object sender, EventArgs e)
        {
            RenderFractal();
            stopToolStripMenuItem.Enabled = false;
        }

        private void OnstopToolStripMenuItemClicked(object sender, EventArgs e)
        {
            InterruptRender();
           
        }

        private void EditToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void RenderToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            RenderFractal();
        }

        
        private void CancelToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            InterruptRender();
        }

        private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }
    }
}