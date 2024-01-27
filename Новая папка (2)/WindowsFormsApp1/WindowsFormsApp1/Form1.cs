using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        Graphics g;
        const float Rad = 100;
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
           
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Start(object sender, EventArgs e) // Кнопка Start - начало событий
        {
            int N = comboBox1.SelectedIndex;
            int x = this.Width/8,  y = this.Height/8;

            g = CreateGraphics();
            g.Clear(Color.Black);

            TreeFractal tree = new TreeFractal(N, g, this.Width, this.Height);

            tree.MainFunTree(1200, 500, 500);

            for (int i = 0, count = 0; i < 3; i++) 
            {
                
                for(int j = 0;j < 3; j++, count++) 
                {
                    if (count <= N)
                    {
                        CircleFractal frac = new CircleFractal(count, g, this.Width, this.Height, Rad);
                        frac.StartToDraw(i * 300+100, j * 300+100);
                    }
                }
            }
            
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }

    public class CircleFractal
    {
        public int N, Width, Height;
        public float Rad;
        Graphics g;
        public CircleFractal(int Num, Graphics graphic, int XWidth, int YHeight, float Radius)
        {
            N = Num;
            g = graphic;
            Width = XWidth;
            Height = YHeight;
            Rad = Radius;
        }
        void RecCircle(int N, int count, int x, int y, float R, int Rot)
        {
            if (count > N)
                return;
            if (Rot != 3)
            {
                RecCircle(N, count + 1, x - (int)R / 2, y + (int)R / 4, R / 2, 1);
                DrawCircleWithFourColour(x - (int)R / 2, y + (int)R / 4, R / 2);
            }
            if (Rot != 4)
            {
                RecCircle(N, count + 1, x + (int)R / 4, y - (int)R / 2, R / 2, 2);
                DrawCircleWithFourColour(x + (int)R / 4, y - (int)R / 2, R / 2);
            }
            if (Rot != 1)
            {
                RecCircle(N, count + 1, x + (int)R, y + (int)R / 4, R / 2, 3);
                DrawCircleWithFourColour(x + (int)R, y + (int)R / 4, R / 2);
            }
            if (Rot != 2)
            {
                RecCircle(N, count + 1, x + (int)R / 4, y + (int)R, R / 2, 4);
                DrawCircleWithFourColour(x + (int)R / 4, y + (int)R, R / 2);
            }
        }

        void DrawCircleWithFourColour(int x, int y, float R)
        {   // Открисовка круга с 4 цветами
            var brushRed = new SolidBrush(Color.FromArgb(255, 57, 3)); // Создание цветов заливки
            var brushOrange = new SolidBrush(Color.Orange);
            var brushYelGr = new SolidBrush(Color.FromArgb(255, 241, 0));
            var brushYel = new SolidBrush(Color.Yellow);

            g.FillEllipse(brushRed, x, y, R, R);
            g.FillEllipse(brushOrange, x + (float)0.025 * R, y + (float)0.025 * R,
                         (float)0.95 * R, (float)0.95 * R); // 95% от основного радиуса
            g.FillEllipse(brushYelGr, x + (float)0.1 * R, y + (float)0.1 * R,
                         (float)0.8 * R, (float)0.8 * R); // 80% 
            g.FillEllipse(brushYel, x + (float)0.2 * R, y + (float)0.2 * R,
                         (float)0.6 * R, (float)0.6 * R); // 60%
        }
        public void StartToDraw(int x, int y) {
            DrawCircleWithFourColour(x, y, Rad);

            if (N >= 1)
            {
                DrawCircleWithFourColour(x - (int)Rad / 2, y + (int)Rad / 4, Rad / 2); // 1
                DrawCircleWithFourColour(x + (int)Rad / 4, y - (int)Rad / 2, Rad / 2); // 2
                DrawCircleWithFourColour(x + (int)Rad, y + (int)Rad / 4, Rad / 2); // 3
                DrawCircleWithFourColour(x + (int)Rad / 4, y + (int)Rad, Rad / 2); //4
            }

            if (N >= 2)
            {
                RecCircle(N, 2, x - (int)Rad / 2, y + (int)Rad / 4, Rad / 2, 1);
                RecCircle(N, 2, x + (int)Rad / 4, y - (int)Rad / 2, Rad / 2, 2);
                RecCircle(N, 2, x + (int)Rad, y + (int)Rad / 4, Rad / 2, 3);
                RecCircle(N, 2, x + (int)Rad / 4, y + (int)Rad, Rad / 2, 4);
            }
        }
    }

    public class TreeFractal
    {
        int N, Width, Height;
        Graphics g;
        public TreeFractal(int Num, Graphics graphic, int XWidth, int YHeight)
        {
            N = Num;
            g = graphic;
            Width = XWidth;
            Height = YHeight;
        }
        void Rec(int x, int y, int Lenth, int N, int Count)
        {
            if (Count > N)
                return;
            Pen pn = new Pen(Color.FromArgb(255, 57, 31));
            if (Count % 2 == 0)
                pn = new Pen(Color.FromArgb(255, 57, 31));
            else
                pn = new Pen(Color.FromArgb(0, 255, 0));
            for (int i = 0; i < 3; i++)
            {
                g.DrawLine(pn, new Point(x, y), new Point(x - Lenth / 2 + i * Lenth / 2, y + 40));
                Rec(x - Lenth / 2 + i * Lenth / 2, y + 40, Lenth / 3, N, Count + 1);
            }
        }
        public void MainFunTree(int x ,int y, int len)
        {
            if (N >= 1)
            {
                for (int i = 0; i < 4; i++)
                {
                    g.DrawLine(Pens.White, new Point(x, y), new Point(x - len/2 + i * len/4, y + 30));
                    if (N >= 2)
                    {
                        Rec(x - len / 2 + i * len / 4, y + 30, 80, N, 2);
                    }
                }
            }
        }

    }
}
