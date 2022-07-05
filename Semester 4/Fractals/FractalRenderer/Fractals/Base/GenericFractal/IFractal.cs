using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Runtime.Serialization;
using System.IO;

namespace FractalRenderer
{
   
    public interface IFractal 
    {                 
        /// <summary>
        /// begin rendering of fractal
        /// </summary>
        /// <param name="RenderComplete"></param>
        /// <param name="StatusUpdate"></param>
        /// <returns></returns>
        IAsyncResult BeginRender(Delegate RenderComplete, Delegate StatusUpdate);
        
        /// <summary>
        /// end (or interrupt rendering)
        /// </summary>
        /// <param name="Res"></param>
        void EndRender(IAsyncResult Res);

        IFractalParameters Parameters { get; set;}

        void Configure();

        void WriteToXml(string filename);

        void ReadFromXml(string filename);

        void ReadFromXml(Stream xmlstream);       

    }
}
