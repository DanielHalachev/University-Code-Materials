using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Threading;
using System.Runtime.Serialization;

namespace FractalRenderer
{
  
  
    public class TestFractal : GenericFractal 
    {                          
        public TestFractal()
        {
            fractalParameters.SetValue("NAME", "Render Test");                     
        }        

        override protected void RenderFunction(object o)
        {
            object[] P = (object[])o;
            RenderResult.RenderComplete clbk = (RenderResult.RenderComplete)P[0];
            RenderResult.RenderStatus status_clbk = (RenderResult.RenderStatus)P[1];

            try
            {                               
                int width = (int)fractalParameters.GetValue("WIDTH");
                int heigth = (int)fractalParameters.GetValue("HEIGHT");

                Bitmap bitmapImage = new Bitmap(width, heigth, System.Drawing.Imaging.PixelFormat.Format32bppPArgb);

                using (Graphics g = Graphics.FromImage(bitmapImage))
                {
                    Random r = new Random();
                    for (int i = 0; i < 10000; i++)
                    {
                        int x = r.Next(0, width);
                        int y = r.Next(0, heigth);
                        int w = r.Next(1, width - x);
                        int h = r.Next(1, heigth - y);
                        int col = r.Next(0, 255);
                        using (SolidBrush brush = new SolidBrush(Color.FromArgb(col, col, col)))
                        {
                            g.FillRectangle(brush, new Rectangle(x, y, w, h));
                        }
                        status_clbk(((float)i) / 100.0f);
                    }
                }

                renderResult.IsCompleted = true;
                ((AutoResetEvent)(renderResult.AsyncWaitHandle)).Set();
                clbk(bitmapImage, 0);
            }
            catch
            {
                clbk(null, -1);
            }
        } 
                 
    }
}
