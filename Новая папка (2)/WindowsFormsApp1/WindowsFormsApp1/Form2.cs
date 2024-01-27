using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form2 : Form
    {
        int N;
        Graphics g;
        public Form2(int Num)
        {
            N = Num;
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        void Rec(int x, int y, int Lenth, int N, int Count) 
        {
            if (Count > N)
                return;
            Pen pn = new Pen(Color.FromArgb(255, 57, 31));
            if(Count%2 == 0)
                pn = new Pen(Color.FromArgb(255, 57, 31));
            else
                pn = new Pen(Color.FromArgb(0, 255, 0));
            for (int i = 0; i < 3; i++)
            {
                g.DrawLine(pn, new Point(x, y), new Point(x-Lenth/2 + i*Lenth/2,y + 40));
                Rec(x - Lenth / 2 + i * Lenth / 2, y + 40, Lenth/3, N, Count+1);
            }           
        }

        private void Form2_Paint(object sender, PaintEventArgs e)
        {
            g = CreateGraphics();
            g.Clear(Color.Black);
            if (N >= 1) {
                for (int i = 0; i < 4; i++)
                {
                    g.DrawLine(Pens.White, new Point(this.Width/2, 10), new Point(150 + i*this.Width/5, 50));
                    if (N >= 2) {
                        Rec(150 + i * this.Width / 5, 50, this.Width/8, N, 2);
                    }
                }
            }
        }
    }
}
