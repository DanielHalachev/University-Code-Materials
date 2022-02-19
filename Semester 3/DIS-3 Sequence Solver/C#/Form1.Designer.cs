namespace SequenceSolver
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textBoxA1 = new System.Windows.Forms.TextBox();
            this.textBoxA2 = new System.Windows.Forms.TextBox();
            this.textBoxA3 = new System.Windows.Forms.TextBox();
            this.textBoxA4 = new System.Windows.Forms.TextBox();
            this.textBoxA5 = new System.Windows.Forms.TextBox();
            this.textBoxA6 = new System.Windows.Forms.TextBox();
            this.textBoxLambda = new System.Windows.Forms.TextBox();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.buttonCalculate = new System.Windows.Forms.Button();
            this.buttonClear = new System.Windows.Forms.Button();
            this.buttonClose = new System.Windows.Forms.Button();
            this.richTextBoxIndexes = new System.Windows.Forms.RichTextBox();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // textBoxA1
            // 
            this.textBoxA1.Location = new System.Drawing.Point(13, 13);
            this.textBoxA1.Name = "textBoxA1";
            this.textBoxA1.Size = new System.Drawing.Size(100, 20);
            this.textBoxA1.TabIndex = 0;
            // 
            // textBoxA2
            // 
            this.textBoxA2.Location = new System.Drawing.Point(13, 39);
            this.textBoxA2.Name = "textBoxA2";
            this.textBoxA2.Size = new System.Drawing.Size(100, 20);
            this.textBoxA2.TabIndex = 1;
            // 
            // textBoxA3
            // 
            this.textBoxA3.Location = new System.Drawing.Point(13, 65);
            this.textBoxA3.Name = "textBoxA3";
            this.textBoxA3.Size = new System.Drawing.Size(100, 20);
            this.textBoxA3.TabIndex = 2;
            // 
            // textBoxA4
            // 
            this.textBoxA4.Location = new System.Drawing.Point(13, 91);
            this.textBoxA4.Name = "textBoxA4";
            this.textBoxA4.Size = new System.Drawing.Size(100, 20);
            this.textBoxA4.TabIndex = 3;
            // 
            // textBoxA5
            // 
            this.textBoxA5.Location = new System.Drawing.Point(13, 117);
            this.textBoxA5.Name = "textBoxA5";
            this.textBoxA5.Size = new System.Drawing.Size(100, 20);
            this.textBoxA5.TabIndex = 4;
            // 
            // textBoxA6
            // 
            this.textBoxA6.Location = new System.Drawing.Point(13, 143);
            this.textBoxA6.Name = "textBoxA6";
            this.textBoxA6.Size = new System.Drawing.Size(100, 20);
            this.textBoxA6.TabIndex = 5;
            // 
            // textBoxLambda
            // 
            this.textBoxLambda.Location = new System.Drawing.Point(13, 169);
            this.textBoxLambda.Name = "textBoxLambda";
            this.textBoxLambda.Size = new System.Drawing.Size(100, 20);
            this.textBoxLambda.TabIndex = 6;
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(479, 270);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.Size = new System.Drawing.Size(240, 150);
            this.dataGridView1.TabIndex = 11;
            // 
            // buttonCalculate
            // 
            this.buttonCalculate.Location = new System.Drawing.Point(108, 270);
            this.buttonCalculate.Name = "buttonCalculate";
            this.buttonCalculate.Size = new System.Drawing.Size(75, 23);
            this.buttonCalculate.TabIndex = 8;
            this.buttonCalculate.Text = "button1";
            this.buttonCalculate.UseVisualStyleBackColor = true;
            this.buttonCalculate.Click += new System.EventHandler(this.buttonCalculate_Click);
            // 
            // buttonClear
            // 
            this.buttonClear.Location = new System.Drawing.Point(108, 317);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(75, 23);
            this.buttonClear.TabIndex = 9;
            this.buttonClear.Text = "button1";
            this.buttonClear.UseVisualStyleBackColor = true;
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // buttonClose
            // 
            this.buttonClose.Location = new System.Drawing.Point(108, 361);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(75, 23);
            this.buttonClose.TabIndex = 10;
            this.buttonClose.Text = "button1";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // richTextBoxIndexes
            // 
            this.richTextBoxIndexes.Location = new System.Drawing.Point(163, 30);
            this.richTextBoxIndexes.Name = "richTextBoxIndexes";
            this.richTextBoxIndexes.Size = new System.Drawing.Size(100, 96);
            this.richTextBoxIndexes.TabIndex = 7;
            this.richTextBoxIndexes.Text = "";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.richTextBoxIndexes);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.buttonClear);
            this.Controls.Add(this.buttonCalculate);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.textBoxLambda);
            this.Controls.Add(this.textBoxA6);
            this.Controls.Add(this.textBoxA5);
            this.Controls.Add(this.textBoxA4);
            this.Controls.Add(this.textBoxA3);
            this.Controls.Add(this.textBoxA2);
            this.Controls.Add(this.textBoxA1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxA1;
        private System.Windows.Forms.TextBox textBoxA2;
        private System.Windows.Forms.TextBox textBoxA3;
        private System.Windows.Forms.TextBox textBoxA4;
        private System.Windows.Forms.TextBox textBoxA5;
        private System.Windows.Forms.TextBox textBoxA6;
        private System.Windows.Forms.TextBox textBoxLambda;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button buttonCalculate;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.RichTextBox richTextBoxIndexes;
    }
}

