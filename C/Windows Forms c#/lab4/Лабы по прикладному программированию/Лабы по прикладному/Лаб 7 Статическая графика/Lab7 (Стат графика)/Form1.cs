using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab7__Стат_графика_
{
    public partial class Form1 : Form
    {
        // Рандомайзер для генерации случайных чисел, чтобы потом сгенерировать из них случайный цвет
        private Random rnd = new Random();
        public Form1()
        {
            InitializeComponent();
        }
        // создаем переменную под холст
        Graphics g;
        // создаем переменную типа Point, чтобы сохранить туда 
        // координаты клика мыши
        Point click;
        // создаем перо красного цвета
        Pen p = new Pen(Color.Red);



        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            // дедаем холст из всей формы
            g = CreateGraphics();
            // очищаем ее установленым цветом 
            g.Clear(Color.Azure);
        }

        // активируется только по нажатию кнопки мыши по форме
        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            // устанавливаем перу случайный цвет, генерируя случайные числа в диапазоне от 0 до 255
            // и из них генерируем цвет в системe RGB
            p.Color = Color.FromArgb(rnd.Next(256), rnd.Next(256), rnd.Next(256));
            // присваиваем переменной click координаты мыши, т.к
            // у нас в саму функцию передаётся MouseEventArgs
            click = e.Location;
            // рисуем элипс исходя из текущих координат мыши размером в 100
            if (radioButton1.Checked == true)
            {
                // так как функция DrawEllipse принимает (перо, координату по х, координату по у 
                // ( х и у обозначают, откуда начинается рисунок), и размер. Так как нам нужен круг
                // то устанавливаем одинаковый размер.
                g.DrawEllipse(p, click.X - 43, click.Y - 55, 100, 100);
            }
            // рисуем квадрат исходя из текущих координат мыши размером в 100
            if (radioButton2.Checked == true)
            {
                // в принципе, в эту функцию передаются те же самые параметры, что и присовании эллипса
                g.DrawRectangle(p, click.X - 43, click.Y - 55, 100, 100);
            }
            if (radioButton3.Checked == true)
            {
                // создаем массив координат для рисования треугольника
                Point[] points = new Point[]
                {
                    new Point(click.X-10, click.Y-10),
                    new Point(click.X+25, click.Y+25),
                    new Point(click.X+25, click.Y-50)
                };
                g.DrawPolygon(p, points);
            }
        }

        // очистка холста
        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            g = CreateGraphics();
            g.Clear(Color.Azure);
        }

    }
}
