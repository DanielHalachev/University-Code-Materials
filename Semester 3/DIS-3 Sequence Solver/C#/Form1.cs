using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Windows.Forms;

namespace SequenceSolver
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            textBoxLambda.Focus();
            dataGridView1.RowHeadersVisible = false;
        }

        private double calculateDenominator(int b1, int b2, int b3, double previous)
        {
            return (b1 * previous * previous + b2 * previous + b3);
        }
        private double calculateMember(int a1, int a2, int a3, double denominator, double previous)
        {
            return (a1 * previous * previous + a2 * previous + a3) / denominator;
        }
        private void buttonCalculate_Click(object sender, EventArgs e)
        {
            int a1 = 0, a2 = 0, a3 = 0, b1 = 0, b2 = 0, b3 = 1;
            double lambda = 0;
            try
            {
                dataGridView1.Visible = true;
                a1 = int.Parse(textBoxA1.Text);
                a2 = int.Parse(textBoxA2.Text);
                a3 = int.Parse(textBoxA3.Text);
                b1 = int.Parse(textBoxA4.Text);
                b2 = int.Parse(textBoxA5.Text);
                b3 = int.Parse(textBoxA6.Text);
                lambda = double.Parse(textBoxLambda.Text);
            }
            catch (FormatException ex)
            {
                MessageBox.Show("Нещо се обърка. Моля проверете входните данни!\n" + ex.Message);
                return;
            }
            if (b1 * lambda * lambda + b2 * lambda + b3 == 0)
            {
                MessageBox.Show("Знаменателят не може да е нула! Въведете нова начална стойност!");
                textBoxLambda.Clear();
                textBoxLambda.Focus();
                dataGridView1.Visible = false;
                return;
            }
            List<int> indexes = new List<int>();
            string[] indexStrings = richTextBoxIndexes.Text.Split(',');
            try
            {
                if (indexStrings.Length == 0)
                {
                    throw new Exception("Не сте въвели индекси за изчисление!");
                }
                for (int i = 0; i < indexStrings.Length; i++)
                {
                    int temporary = int.Parse(indexStrings[i]);
                    if (temporary < 1)
                    {
                        dataGridView1.Visible = false;
                        throw new Exception("Невалиден отрицателен индекс за изчисление");
                    }
                    if (!indexes.Contains(temporary))
                    {
                        indexes.Add(temporary);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                richTextBoxIndexes.Clear();
                richTextBoxIndexes.Focus();
                dataGridView1.Visible = false;
                return;
            }
            indexes.Sort();
            Dictionary<int, double> results = new Dictionary<int, double>();
            double temp = lambda;
            int nextInIndexes = 0;
            double denominator;
            for (int i = 1; i <= indexes.Last(); i++)
            {
                denominator = calculateDenominator(b1, b2, b3, temp);
                if (denominator == 0)
                {
                    MessageBox.Show("Член номер {0} не съществува, защото знаменателят е нула. Изчисляването прекратено.", i.ToString());
                    break;
                }
                temp = calculateMember(a1, a2, a3, denominator, temp);
                if (i == indexes[nextInIndexes])
                {
                    results.Add(i, temp);
                    nextInIndexes++;
                }
            }
            dataGridView1.Visible = true;
            var indexValueArray = from row in results select new { Номер = row.Key, Стойност = row.Value };
            dataGridView1.DataSource = indexValueArray.ToArray();
            dataGridView1.Columns[0].AutoSizeMode = DataGridViewAutoSizeColumnMode.DisplayedCells;
            dataGridView1.Columns[1].AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;

            dataGridView1.Refresh();
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            textBoxLambda.Clear();
            richTextBoxIndexes.Clear();
            dataGridView1.Visible = false;
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
