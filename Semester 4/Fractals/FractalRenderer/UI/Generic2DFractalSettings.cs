using System;
using System.Drawing;
using System.Windows.Forms;

namespace FractalRenderer
{
    public partial class Generic2DFractalSettings : Form
    {
        IFractalParameters parameters = null;
        Bitmap preview = null;
        string fractalType = "FractalRenderer.MandelbrotFractal";

        public IFractalParameters Parameters
        {
            set
            {
                parameters = value;
                ParametersToDialog();
                CalcPreview();
            }
            get
            {
                return parameters;
            }
        }

        public string FractalType
        {
            set
            {
                fractalType = value;
            }
        }

        public Generic2DFractalSettings()
        {
            InitializeComponent();
        }

        private void ParametersToDialog()
        {
            if (InvokeRequired)
            {
                this.Invoke(new MethodInvoker(ParametersToDialog));
            }
            else
            {
                this.tb_X.Text = ((double)parameters.GetValue("X")).ToString();
                this.tb_Y.Text = ((double)parameters.GetValue("Y")).ToString();
                this.tb_Iterations.Text = ((int)parameters.GetValue("ITERATIONS")).ToString();

            }
        }

        private bool DialogValuesToParameters()
        {
            try
            {
                double x = Convert.ToDouble(tb_X.Text);
                parameters.SetValue("X", x);

                double y = Convert.ToDouble(tb_Y.Text);
                parameters.SetValue("Y", y);

                int iterations = Convert.ToInt32(tb_Iterations.Text);
                parameters.SetValue("ITERATIONS", iterations);
                return true;
            }
            catch { }

            return false;

        }

        private void RenderComplete(Bitmap bitmap, int errorCode)
        {
            if (errorCode == 0)
            {
                preview = bitmap;
            }
            UpdatePreview();

        }

        private void UpdatePreview()
        {
            if (InvokeRequired)
            {
                this.Invoke(new MethodInvoker(UpdatePreview));
            }
            else
            {
                this.pictureBox.Image = preview;
                button1.Enabled = true;
            }
        }

        private void RenderStatusUpdated(float pcnt)
        {

        }

        private void CalcPreview()
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new MethodInvoker(CalcPreview));
            }
            else
            {
                if (fractalType == "FractalRenderer.NewtonFractal" ||
                         fractalType == "FractalRenderer.NewtonFractalByIterationsRequired")
                {
                    NewtonFractalByIterationsRequired f = new NewtonFractalByIterationsRequired();
                    f.Parameters = (IFractalParameters)parameters.Clone();
                    f.Parameters.SetValue("WIDTH", 128);
                    f.Parameters.SetValue("HEIGHT", 128);
                    f.BeginRender(new RenderResult.RenderComplete(RenderComplete),
                                  new RenderResult.RenderStatus(RenderStatusUpdated));
                }
                else
                {
                    MandelbrotFractal f = new MandelbrotFractal();
                    f.Parameters = (IFractalParameters)parameters.Clone();
                    f.Parameters.SetValue("WIDTH", 128);
                    f.Parameters.SetValue("HEIGHT", 128);
                    f.BeginRender(new RenderResult.RenderComplete(RenderComplete),
                                  new RenderResult.RenderStatus(RenderStatusUpdated));
                }
                button1.Enabled = false;
            }
        }

        private void OnButtonPreviewClick(object sender, EventArgs e)
        {
            if (DialogValuesToParameters() == true)
            {
                pictureBox.Visible = true;
                CalcPreview();
            }
        }

        private void OnButtonOkClick(object sender, EventArgs e)
        {
            if (DialogValuesToParameters() == true)
            {
                DialogResult = DialogResult.OK;
                this.Close();
            }
        }

        private void OnButtonCancelClick(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}