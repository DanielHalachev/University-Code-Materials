using System;
using System.Drawing;
using System.IO;
using System.Text;
using System.Threading;
using System.Xml;

namespace FractalRenderer
{
    public class GenericFractal : IFractal
    {
        protected RenderResult renderResult = null;
        protected IFractalParameters fractalParameters = new ParameterList();
        protected AutoResetEvent interrupt = new AutoResetEvent(false);
        protected int linesRendered = 0;

        public GenericFractal()
        {
            // basic fractalParameters that any fractal should use:
            // name of the fractal
            fractalParameters.AddValue("NAME", "GenericFractal");
            // output width and height
            fractalParameters.AddValue("WIDTH", 800);
            fractalParameters.AddValue("HEIGHT", 600);
            // version of the fractal render engine 
            fractalParameters.AddValue("VERSION", "1.0.0");

            // generate the palette
            int numberOfColors = 256;
            int[] palette = new int[numberOfColors];
            for (int i = 0; i < numberOfColors; i++)
            {
                int g = (int)(255.0 * (double)i / (double)numberOfColors);
                palette[i] = Color.FromArgb(g, g, g).ToArgb();
            }
            palette[numberOfColors - 1] = palette[0];
            fractalParameters.AddValue("PALETTE", palette);
        }

        public void ReadFromXml(Stream inputStream)
        {
            try
            {

                XmlDocument xmldoc = new XmlDocument();
                xmldoc.Load(inputStream);
                XmlNodeList nodes = xmldoc.GetElementsByTagName("frac");
                if (nodes.Count == 1)
                {
                    nodes = xmldoc.GetElementsByTagName("parameter");
                    foreach (XmlNode n in nodes)
                    {
                        string type = n.Attributes["type"].Value;
                        string name = n.Attributes["name"].Value;
                        string value = n.InnerXml;

                        if (type == "System.Int32[]")
                        {
                            string[] vals = value.Split(new char[] { ',' });
                            int Count = vals.Length;
                            int[] values = new Int32[Count];
                            for (int i = 0; i < Count; i++)
                            {
                                values[i] = Convert.ToInt32(vals[i]);
                            }
                            fractalParameters.SetValue(name, values);
                        }
                        else if (type == "System.Int32")
                        {
                            fractalParameters.SetValue(name, Convert.ToInt32(value));
                        }
                        else if (type == "System.Double")
                        {
                            fractalParameters.SetValue(name, Convert.ToDouble(value));
                        }
                        else if (type == "System.String")
                        {
                            fractalParameters.SetValue(name, value);
                        }
                        else
                        {
                            throw new ApplicationException("unsupported parameter type:" + type);
                        }
                    }
                }
                else
                {
                    throw new IOException("Illegal file format!");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception caught: " + ex.Message);
            }
        }

        virtual public void ReadFromXml(string filename)
        {
            try
            {
                FileStream f = new FileStream(filename, FileMode.Open);
                ReadFromXml(f);
            }
            catch
            {

            }
        }

        virtual public void WriteToXml(string filename)
        {
            try
            {
                Stream stream = File.Open(filename, FileMode.Create);

                string name = (String)this.fractalParameters.GetValue("NAME");

                TextWriter w = new StreamWriter(stream, Encoding.UTF8);
                w.WriteLine("<?xml version='1.0' encoding='utf-8' ?>");
                w.WriteLine("<frac name='" + name + "' type='" + this.GetType().ToString() + "'>");

                foreach (Parameter p in Parameters)
                {
                    string pname = p.Name;
                    string type = p.Type.ToString();

                    if (type == "System.Int32[]")
                    {
                        Int32[] pal = (Int32[])p.Value;
                        String palette = String.Empty;

                        for (int i = 0; i < pal.Length; i++)
                        {
                            // TODO : format to hex
                            if (i < pal.Length - 1) palette += "" + pal[i] + ",";
                            else palette += "" + pal[i];
                        }

                        w.WriteLine("<parameter name='" + pname + "' type='" + type + "' >" + palette + "</parameter>");
                    }
                    else if (type == "System.Int32" ||
                             type == "System.String" ||
                             type == "System.Double" ||
                             type == "System.Float")
                    {
                        String value = p.Value.ToString();
                        w.WriteLine("<parameter name='" + pname + "' type='" + type + "' >" + value + "</parameter>");
                    }
                    else
                    {
                        throw new ApplicationException("unsupported parameter type:" + type);
                    }
                }

                w.WriteLine("</frac>");
                w.Flush();
                w.Close();
            }
            catch
            {
            }
        }



        public IFractalParameters Parameters
        {
            get
            {
                return fractalParameters;
            }
            set
            {
                fractalParameters = value;
            }
        }

        public IAsyncResult BeginRender(Delegate completed, Delegate status)
        {
            if (renderResult == null)
            {
                renderResult = new RenderResult();
                interrupt.Reset();
                Thread d = new Thread(new ParameterizedThreadStart(RenderFunction));
                d.Start(new object[] { completed, status });
                renderResult.AsyncState = d;
                return renderResult;
            }
            else
            {
                throw new ApplicationException("BeginRender already called");
            }
        }

        public void EndRender(IAsyncResult Res)
        {
            interrupt.Set();
            renderResult = null;
        }

        virtual protected void RenderFunction(object o)
        {
            throw new ApplicationException("Virtual function not overridden!");
        }

        virtual public void Configure()
        {
            FractalSettingsDialog dia = new FractalSettingsDialog();
            dia.Parameters = (IFractalParameters)this.Parameters.Clone();
            if (dia.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                this.Parameters = dia.Parameters;
            }
        }
    }

}
