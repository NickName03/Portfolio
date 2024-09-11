using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        // класс родитель "Растение"
        class Plant
        {
            protected string title;
            protected string type;

            internal Plant(string t, string ty)
            {
                title = t;
                type = ty;
            }

            internal string gett()
            { return title; }
            internal string getty()
            { return type; }
        }

        // класс наследник "Цветы", который также будет являться родительским для следующего класса
        class Flowers: Plant
        {
            protected double lenght;

            internal Flowers(string t, string ty, string l): base(t, ty)
            {
                title = t;
                type = ty;
                lenght = Convert.ToDouble(l);
            }
    
            internal string getl()
            { return lenght.ToString(); } 
        }

        // класс наследник "Роза", наследует поля и методы от класса-родителя "Цветы"
        class Rose: Flowers
        {
            protected string color;

            internal Rose(string t, string ty, string l, string c): base(t, ty, l)
            {
                title = t;
                type = ty;
                lenght = Convert.ToDouble(l);
                color = c;
            }

            internal string getc()
            { return color; }
        }

        // класс "Дерево"
        class Tree: Plant
        {
            protected double age;
            protected string sheet;

            internal Tree(string t, string ty, string a, string s): base(t, ty)
            {
                title = t;
                type = ty;
                age = Convert.ToDouble(a);
                sheet = s;
            }
        }

        // функция очищения текстбоксов
        internal void clear_box()
        {
            textBox1.Clear(); textBox2.Clear(); textBox3.Clear(); textBox4.Clear(); 
            textBox6.Clear(); textBox7.Clear(); textBox8.Clear(); textBox9.Clear();
        }
        // функция заполнения ДатаГрид
        internal void Fill_DataGrid()
        {
            // очищаем таблицу от прошлых данных
            dataGridView1.Rows.Clear();
            /* Для чего в счетчика нужно было -1? Допустим такую ситуацию: пользователь не вводил 
             * Растения и Розы, просто ввел какой-нибудь Цветок. Если бы не следующие проверки,
             * то в DataGrid пришлось бы записать нулевые объекты (например данные p[0]).
             * А что в таком случае было записано в p[0]? Правильно, ничего, и это была бы ошибка.
             * Поэтому счечик -1 нужен, чтобы вывод данных был нормальным, во */
            if (count_p > -1)
            {
                // для первых объктов каждого класса в первую колонку записывается тип, в остальных пустота 
                for (int i = 0; i < count_p; i++)
                {
                    if (i == 0)
                        dataGridView1.Rows.Add("Растение", p[i].gett(), p[i].getty(), "-", "-");
                    else
                        dataGridView1.Rows.Add("", p[i].gett(), p[i].getty(), "-", "-");
                }  
            }
            if (count_f > -1)
            {
                for (int i = 0; i < count_f; i++)
                {
                    if (i == 0)
                        dataGridView1.Rows.Add("Цветы", f[i].gett(), f[i].getty(), f[i].getl(), "-");
                    else
                        dataGridView1.Rows.Add("", f[i].gett(), f[i].getty(), f[i].getl(), "-");
                }
            }
            if (count_r > -1)
            {
                for (int i = 0; i < count_r; i++)
                {
                    if (i == 0)
                        dataGridView1.Rows.Add("Розы", r[i].gett(), r[i].getty(), r[i].getl(), r[i].getc());
                    else
                        dataGridView1.Rows.Add("", r[i].gett(), r[i].getty(), r[i].getl(), r[i].getc());
                }
            }
        }

        // глобавльно объявляем массивы под объекты каждого класса и счетчики для них
        // у счетчиков изначально значение -1. Это нужно для проверки в функции Fill_DataGrid
        int count_p = -1, count_f = -1, count_r = -1, count_t = 0;
        Plant[] p = new Plant[100];
        Flowers[] f = new Flowers[100];
        Rose[] r = new Rose[100];
        Tree[] t = new Tree[100];

        // кнопка "В розу"
        private void button2_Click(object sender, EventArgs e)
        {
            int n = Convert.ToInt32(comboBox2.SelectedItem) - 1;
            // создаем новую "Розу", используя данные, которые ввел пользователь
            r[count_r] = new Rose(textBox1.Text, textBox2.Text, textBox3.Text, textBox4.Text);
            // удаляем объект из "Цветов"
            for (int i = n; i <= count_f; i++)
            {
                f[i] = f[i + 1];
            }
            count_r++;
            count_f--;
            comboBox2.Items.Clear();
            for (int i = 0; i < count_f; i++)
            {
                comboBox2.Items.Add(i + 1);
            }
            Fill_DataGrid();
            clear_box();
        }

        // при выборе любого элемента будет показвать данные по выбранному цветку
        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            int n = Convert.ToInt32(comboBox2.SelectedItem) - 1;
            textBox1.Text = f[n].gett();
            textBox2.Text = f[n].getty();
            textBox3.Text = f[n].getl();
            textBox4.Text = "";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            t[count_t] = new Tree(textBox6.Text, textBox7.Text, textBox8.Text, textBox9.Text);
            count_t++;
            dataGridView2.Rows.Add(textBox6.Text, textBox7.Text, textBox8.Text, textBox9.Text);
            clear_box();
        }

        // кнопка "добавить"
        private void button1_Click(object sender, EventArgs e)
        {
            if (comboBox1.SelectedItem.ToString() == "Растение")
            {
                if (count_p == -1)
                    count_p = 0;
                p[count_p] = new Plant(textBox1.Text, textBox2.Text);
                count_p++;
            }
            if (comboBox1.SelectedItem.ToString() == "Цветок")
            {
                if (count_f == -1)
                    count_f = 0;
                f[count_f] = new Flowers(textBox1.Text, textBox2.Text, textBox3.Text);
                comboBox2.Items.Add(count_f + 1);
                count_f++;
            }
            if (comboBox1.SelectedItem.ToString() == "Роза")
            {
                if (count_r == -1)
                    count_r = 0;
                r[count_r] = new Rose(textBox1.Text, textBox2.Text, textBox3.Text, textBox4.Text);
                count_r++;
            }
            // перезаписываем таблицу с обновленными данными
            Fill_DataGrid();
            clear_box();
        }

        // при смене типа появляются или исчезают определенные компоненты
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedItem.ToString() == "Растение")
            {
                label4.Visible = false;
                label5.Visible = false;
                label6.Visible = false;
                textBox3.Visible = false;
                textBox4.Visible = false;
                comboBox2.Visible = false;
                button2.Visible = false;
            }
            if (comboBox1.SelectedItem.ToString() == "Цветок")
            {
                label4.Visible = true;
                label5.Visible = false;
                label6.Visible = false;
                textBox3.Visible = true;
                textBox4.Visible = false;
                comboBox2.Visible = false;
                button2.Visible = false;
            }
            if (comboBox1.SelectedItem.ToString() == "Роза")
            {
                label4.Visible = true;
                label5.Visible = true;
                label6.Visible = true;
                textBox3.Visible = true;
                textBox4.Visible = true;
                comboBox2.Visible = true;
                button2.Visible = true;
            }
        }
    }
}
