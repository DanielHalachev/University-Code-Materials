using System;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace FractalRenderer
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }
        private void MainForm_Load(object sender, EventArgs e)
        {
            Controls.OfType<MdiClient>().FirstOrDefault().BackColor = Color.White;
            this.BackColor = Color.White;
        }

        #region FractalGeneration
        private void MandelbrotFractalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FractalForm frmchild = new FractalForm();
            frmchild.MdiParent = this;
            frmchild.Fractal = new MandelbrotFractal();
            frmchild.Show();
            frmchild.Text = "Фрактал на Манделброт";
        }

        private void NewtonFractalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FractalForm frmchild = new FractalForm();
            frmchild.MdiParent = this;
            frmchild.Fractal = new NewtonFractalByIterationsRequired();
            frmchild.Show();
            frmchild.Text = "Фрактал на Нютон чрез итерации";
        }
        #endregion

        #region Layout
        private void CascadedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.Cascade);
        }

        private void TileHorizontalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileHorizontal);
        }

        private void TileVerticalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LayoutMdi(MdiLayout.TileVertical);
        }
        #endregion

        private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}