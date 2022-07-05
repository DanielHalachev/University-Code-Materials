using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Threading;
using System.Runtime.Serialization;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

namespace FractalRenderer
{
    public class Generic2DFractal : GenericFractal
    {
        public Generic2DFractal()
        {
            fractalParameters.SetValue("X", 0.0);
            fractalParameters.SetValue("Y", 0.0);
            fractalParameters.SetValue("XC", 0.0);
            fractalParameters.SetValue("YC", 0.0);
            fractalParameters.SetValue("W", 1.0);
            fractalParameters.SetValue("H", 1.0);
            fractalParameters.SetValue("WIDTH", 640);
            fractalParameters.SetValue("HEIGHT", 480);
            fractalParameters.SetValue("VERSION", "1.0.0");
            fractalParameters.AddValue("ITERATIONS", 64);
            fractalParameters.AddValue("ZOOMABLE", 1);
            fractalParameters.AddValue("SCROLLABLE", 1);
            fractalParameters.AddValue("NUM_THREADS", Environment.ProcessorCount);
            fractalParameters.AddValue("APPLY_BILINEAR_FILTER", 0);            
        }

        virtual public void SetOrigin(double dx, double dy)
        {
             
            double CurWpix = (int)fractalParameters.GetValue("WIDTH");
            double CurHpix = (int)fractalParameters.GetValue("HEIGHT");
            double FracWidth = (double)fractalParameters.GetValue("W");
            double FracHeight = (double)fractalParameters.GetValue("H");
            double FracX = (double)fractalParameters.GetValue("X");
            double FracY = (double)fractalParameters.GetValue("Y");

            FracX -= dx * FracWidth / CurWpix;
            FracY -= dy * FracHeight / CurHpix;

            fractalParameters.SetValue("X", FracX);
            fractalParameters.SetValue("Y", FracY);
        }

        virtual public void SetControlParameter(double dx, double dy)
        {
            double CurWpix = (int)fractalParameters.GetValue("WIDTH");
            double CurHpix = (int)fractalParameters.GetValue("HEIGHT");
            double FracWidth = (double)fractalParameters.GetValue("W");
            double FracHeight = (double)fractalParameters.GetValue("H");
            double FracX = (double)fractalParameters.GetValue("XC");
            double FracY = (double)fractalParameters.GetValue("YC");

            FracX -= dx * FracWidth / CurWpix;
            FracY -= dy * FracHeight / CurHpix;

            fractalParameters.SetValue("XC", FracX);
            fractalParameters.SetValue("YC", FracY);
        }

        override protected void RenderFunction(object o)
        {
            object[] P = (object[])o;
            RenderResult.RenderComplete clbk = (RenderResult.RenderComplete)P[0];
            RenderResult.RenderStatus status_clbk = (RenderResult.RenderStatus)P[1];

            try
            {
                Random r = new Random();

                int width = (int)fractalParameters.GetValue("WIDTH");
                int heigth = (int)fractalParameters.GetValue("HEIGHT");
                int iterations = (int)fractalParameters.GetValue("ITERATIONS") - 1;
                int[] Palette = (int[])fractalParameters.GetValue("PALETTE");
                int NumThreads = (int)fractalParameters.GetValue("NUM_THREADS", 2);
                int BilinearFilter = (int)fractalParameters.GetValue("APPLY_BILINEAR_FILTER",0);  

                int[] colrTable = new int[width * heigth];
                
                WaitHandle[] handles = new WaitHandle[NumThreads];
                Thread[] threads = new Thread[NumThreads];

                linesRendered = 0;

                for (int i = 0; i < NumThreads; i++)
                {
                    handles[i] = new AutoResetEvent(false);
                    threads[i] = new Thread(new ParameterizedThreadStart(PartialRender));
                    threads[i].Start((object)(new object[] { i * heigth / NumThreads, 
                                                             heigth / NumThreads, 
                                                             colrTable, 
                                                             status_clbk, handles[i] }));
                }
 
                while (true)
                {
                    if (WaitHandle.WaitAll(handles, 100, false) == true)
                    {
                        break;
                    }
                    else if (interrupt.WaitOne(100, false) == true)
                    {
                        try
                        {
                            for (int i = 0; i < NumThreads; i++)
                            {
                                threads[i].Abort();
                            }
                        }
                        catch { }

                        clbk(null, -2);

                        return;
                    }
                }
                
                if (BilinearFilter == 1)
                {
                    int [] filteredColorTable =  new int[(width * heigth)];
                    int idxs11 = 0,idxs12 = 0,idxs21 = 0,idxs22 = 0;

                    for (int y = 0; y < heigth-1; y++)
                    {
                        idxs11 = y * (width);
                        idxs12 = idxs11 + 1;
                        idxs21 = idxs11 + width;
                        idxs22 = idxs21 + 1;

                        for (int x = 0; x < width-1; x++)
                        {                            
                            int colf1 = Utils.InterpolateColors(colrTable[idxs11], colrTable[idxs12], 127);
                            int colf2 = Utils.InterpolateColors(colrTable[idxs21], colrTable[idxs22], 127);
                            
                            filteredColorTable[idxs11] = Utils.InterpolateColors(colf1, colf2, 128);
                            
                            idxs11++;
                            idxs12++;
                            idxs21++;
                            idxs22++;
                        }
                    }
                   
                    colrTable = filteredColorTable;
                }

                Bitmap bmp = new Bitmap(width, heigth, PixelFormat.Format32bppPArgb);
                BitmapData pdate = bmp.LockBits(new Rectangle(0, 0, width, heigth),
                                                ImageLockMode.ReadWrite,
                                                PixelFormat.Format32bppPArgb);

                IntPtr pscan0 = pdate.Scan0;
               
                Marshal.Copy(colrTable, 0, pscan0, width * heigth);
 
                bmp.UnlockBits(pdate);

                renderResult.IsCompleted = true;

                ((AutoResetEvent)(renderResult.AsyncWaitHandle)).Set();
                
                clbk(bmp, 0);
            }
            catch
            {
                clbk(null, -1);
            }
        }

        virtual protected void PartialRender(object P)
        {

        }
    }

}
