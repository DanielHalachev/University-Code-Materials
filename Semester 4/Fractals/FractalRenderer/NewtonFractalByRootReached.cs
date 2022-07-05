using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Threading;
using System.Runtime.Serialization;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;
using ComplexMath;

namespace FracMaster
{
    public class NewtonFractalByRootReached : Generic2DFractal
    {
        public NewtonFractalByRootReached()
        {
            pars.SetValue("NAME", "Newton Fractal by root reached");
            pars.SetValue("X", 0.0);
            pars.SetValue("Y", 0.0);
            pars.SetValue("W", 8.0);
            pars.SetValue("H", 8.0);
            pars.SetValue("A", 1.0);
            pars.SetValue("WIDTH", 512);
            pars.SetValue("HEIGHT", 512);
            pars.SetValue("VERSION", "1.0.0");
            pars.SetValue("ITERATIONS", 64);
            pars.SetValue("NUM_THREADS", Environment.ProcessorCount);
        }

        public override void Configure()
        {
            MandelbrotFractalSettings dia = new MandelbrotFractalSettings();
            dia.JuliaFractal = true;
            dia.Parameters = (IFractalParameters)this.Parameters.Clone();

            if (dia.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                this.Parameters = dia.Parameters;
            }
        }

        override protected void PartialRender(object P)
        {
            PartialRenderRootReached(P);
        }

       
        // which root reached after how many steps
        protected void PartialRenderRootReached(object P)
        {

            object[] o = (object[])P;
            int offset = (int)o[0];
            int lines = (int)o[1];
            int[] dst = (int[])o[2];
              RenderResult.RenderStatus status_clbk = (RenderResult.RenderStatus)o[3];
            AutoResetEvent completed = (AutoResetEvent)o[4];

            int width = (int)pars.GetValue("WIDTH");
            int heigth = (int)pars.GetValue("HEIGHT");
            int iterations = (int)pars.GetValue("ITERATIONS") - 1;
            Int32[] Palette = (Int32[])pars.GetValue("PALETTE");

            double W = (double)pars.GetValue("W");
            double H = (double)pars.GetValue("H");
            double X = (double)pars.GetValue("X");
            double Y = (double)pars.GetValue("Y");

            int iter = 0;
            int idx = 0;
            double xs = (X - W / 2.0);
            double ys = (Y - H / 2.0);
            double xd = W / (double)width;
            double yd = H / (double)heigth;
            double y1 = ys + yd * offset;
            double a = 1.0;

            Complex Att1 = new Complex(1.25992, 0);
            Complex Att2 = new Complex(-0.629961, -1.09112);
            Complex Att3 = new Complex(-0.629961, 1.09112);

            for (int y = offset; y < offset + lines; y++)
            {
                idx = y * width;
                double x1 = xs;

                for (int x = 0; x < width; x++)
                {
                    iter = 0;

                    // newton fractal formula:
                    // zn+1 = zn - a* p(zn)/p'(zn)
                    // were p(z): 
                    //              z^3-1   a: 1,0 ..... 0,5

                    Complex zn = new Complex(x1, y1);
                    Complex pz = new Complex(1, 0);
                    Complex pzd = new Complex(1, 0);
                   
                    if (x1 == 0 && y1 == 0)
                    {
                        iter = 0;
                    }
                    else
                    {
                        while ((iter < iterations) && pz.GetModulusSquared() > 0.00000001)
                        {
                            pz = Complex.Pow(zn, 3) - 2;
                            pzd = 3 * Complex.Pow(zn, 2);
                            zn = (zn - a * pz / pzd);
                            iter++;                           
                        }
                    }

                    Att1 = Att1 - zn;
                    Att2 = Att2 - zn;
                    Att3 = Att3 - zn;
                    int palidx = iter;

                    if (Att1.GetModulusSquared() < 0.0001)
                    {
                        palidx = iter;
                    }
                    else if (Att2.GetModulusSquared() < 0.0001)
                    {
                        palidx = iter + 32;
                    }
                    else if (Att3.GetModulusSquared() < 0.0001)
                    {
                        palidx = iter + 64;
                    }

                    palidx = palidx % Palette.Length;
                    dst[idx++] = Palette[palidx];
                    x1 += xd;
                }
                y1 += yd;
                lines_rendered++;
                if (lines_rendered % 40 == 0)
                {
                    status_clbk(100.0f * ((float)lines_rendered) / heigth);
                }
            }
            completed.Set();
        }

    }
}
