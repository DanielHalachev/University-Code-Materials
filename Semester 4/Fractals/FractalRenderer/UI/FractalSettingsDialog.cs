using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace FractalRenderer
{
    public partial class FractalSettingsDialog : Form
    {
        IFractalParameters pars = null;
        public FractalSettingsDialog()
        {
            InitializeComponent();
        }

        public IFractalParameters Parameters
        {
            set
            {
                pars = value;
                ApplyParameters();
            }
            get
            {
                return pars;
            }
        }

        private void ApplyParameters()
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new MethodInvoker(ApplyParameters));
            }
            else
            {
                foreach (Parameter p in pars)
                {
                    this.ParameterGridView.Rows.Add(new object[] { p.Name, p.Type.ToString(), p.Value });
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;           
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}