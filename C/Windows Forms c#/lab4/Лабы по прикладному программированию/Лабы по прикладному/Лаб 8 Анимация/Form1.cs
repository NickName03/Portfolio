using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab8
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            // задаём интервал в 1 мс
            timer1.Interval = 1;
            // создаём холст из формы
            g = CreateGraphics();
            // будущая размерность массива точек. Умножаем количество "колец" (iNumRevs) на два и полученное умножаем на сумму длины формы и ширины
            iNumPoints = iNumRevs * 2 * (this.Width+this.Height);
            // объявляем массив точек с уже найденой размерностью
            points = new PointF[iNumPoints];
            // угол
            fAngle = 0;
            // масштаб
            fScale = 1 ;

            // вычисляем координаты начала
            points[0].X = (float)(this.Width / 2 * (1 + fScale * Math.Cos(fAngle)));
            points[0].Y = (float)(this.Height / 2 * (1 + fScale * Math.Sin(fAngle)));
        }
        // переменная под холст
        Graphics g;
        // количество "колец"
        const int iNumRevs = 3;
        // переменная под размерность
        int iNumPoints;
        // переменная под массив точек
        PointF[] points;
        // переменные под угол и масштаб
        float fAngle, fScale;

        private void Form1_Click(object sender, EventArgs e)
        {
            // запускаем таймер по нажатию мыши по форме
            timer1.Start();
        }
        // переменная счётчик, начинается с 1, т.к 0 уже занят
        int i = 1;

        private void timer1_Tick(object sender, EventArgs e)
        {
            // рисуется пока все элементы массива точек не будут использованы
            if (i >= iNumPoints)
                // если использованы, то таймер останавливается
                timer1.Stop();
            // в противном случае
            else
            {
                // вычисляем угол исходя из текущей "позиции"
                fAngle = (float)(i * 2 * Math.PI / (iNumPoints / iNumRevs));
                // тоже самое с масштабом
                fScale = 1 - (float)i / iNumPoints;

                // вычисляем координаты
                points[i].X = (float)(this.Width / 2 * (1 + fScale * Math.Cos(fAngle)));
                points[i].Y = (float)(this.Height / 2 * (1 + fScale * Math.Sin(fAngle)));
                // рисуем с помощью пера синего цвета, толщиной в 4. Используем предыдущую точку, чтобы
                // рисунок закруглялся
                g.DrawLine(new Pen(Color.Blue, 4), points[i - 1], points[i]);
                // увеличиваем счётчик
                i++;
            }
        }
    }
}
