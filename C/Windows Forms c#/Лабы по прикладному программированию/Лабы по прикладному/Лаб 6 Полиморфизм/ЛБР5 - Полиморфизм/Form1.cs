using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ЛБР5___Полиморфизм
{

    public partial class Form1 : Form
    {
        // создаём листы под каждый класс
        List<Kadr> Spisok1 = new List<Kadr>();
        List<WORK> Spisok2 = new List<WORK>();
        List<Manager> Spisok3 = new List<Manager>();
        List<Engineer> Spisok4 = new List<Engineer>();
        List<WORK> PREOBR = new List<WORK>();
        public Form1()
        {
            InitializeComponent();
        }
        abstract public class Kadr
        {
            protected string FIO; // ФИО
            protected DateTime Date_work; // Дата приёма на работу
            // объявляем абстрактную функцию 
            public abstract string PrintKadr();
            // конструктор с параметрами
            public Kadr(string F, DateTime DW)
            {
                FIO = F;
                Date_work = DW;
            }
            // геттеры
            public string Get_FIO()
            {
                return FIO;
            }
            public DateTime GetDate_Work()
            {
                return Date_work;
            }
            public Kadr() { }
        }

        // класс "Рабочий". Делаем его абстрактным, чтобы объявить одну абстрактную функцию
        abstract class WORK : Kadr
        {
            protected string SPEC; // Специальность
            // та самая абстрактная функция
            public abstract string PrintWORK();
            // переопредленная функция из класса-родителя
            public override string PrintKadr()
            {
                return FIO + " " + Date_work +  " " + SPEC;
            }
            // конструктор с параметрами
            public WORK(string F, DateTime DW, string S) : base(F, DW)
            {
                SPEC = S;
            }
            // геттеры
            public string Get_SPEC()
            {
                return SPEC;
            }
            public WORK() { }
        }

        // управляющий
         class Manager : Kadr
        {
            protected string DOLZH; // Должность
            protected string PODRazd; // Подразделение
            
            // переопределнный метод родительского класса
            public override string PrintKadr()
            {
                return FIO + " " + Date_work + " " + DOLZH + " " + PODRazd;
            }
            // конструктор с параметрами
            public Manager(string F, DateTime DW, string DL, string PDR) : base(F, DW)
            {
                DOLZH = DL;
                PODRazd = PDR;
            }
          
            public Manager() { }
        }

        class Engineer : WORK
        {

            protected string QUALIF; //Квалификация
            protected string PodRazd2; // Подразделение
            public override string PrintWORK()
            {
                return FIO + " " + Date_work + " " + SPEC + " " + QUALIF + " " + PodRazd2;
            }

            // контруктор с параметрами
            public Engineer(string F, DateTime DW, string S, string Qua, string PDR2) : base(F, DW, S)
            {
                QUALIF = Qua;
                PodRazd2 = PDR2;
            }
            // геттеры
            public string Get_QUALIF()
            {
                return QUALIF;
            }
            public string Get_PDR2()
            {
                return PodRazd2;
            }
            public Engineer() { }
            // преобразование 
            public void Fron_Work(WORK ob)
            {
                // присваиваем полям этого объекта значения полей объекта, который передали в функцию
                this.FIO = ob.Get_FIO();
                this.Date_work = Convert.ToDateTime(ob.GetDate_Work());
                this.SPEC = ob.Get_SPEC();
                QUALIF = "-";
                PodRazd2 = "-";
            }
        }
        // очищение всех текстбоксов
        public void Clear()
        {
            textBox1.Clear(); textBox2.Text = "01.01.2021"; textBox3.Clear(); ; textBox4.Clear();
            textBox5.Clear(); textBox6.Clear(); textBox7.Clear();
        }
        
        // добавить Рабочего
        private void button2_Click(object sender, EventArgs e)
        {
            // добавляем в лист данные 
            Spisok2.Add(new Engineer(textBox1.Text, Convert.ToDateTime(textBox2.Text), textBox3.Text, "", ""));
            // очищаем таблицу
            dataGridView2.Rows.Clear();
            // заполняем список 
            for (int i = 0; i < Spisok2.Count; i++)
            {
                // создаём строковую переменную в которую передаем данные
                string str = Spisok2[i].PrintKadr();
                // создаём массив строковых элементов, в которые заносим подстроки, которые разбили из строки
                string[] Str = str.Split(' ');
                // добавляем эти подстроки в таблицу
                dataGridView2.Rows.Add(Str[0], Str[1], Str[3]);
                
            }
            // добавляем в комбобокс специальность 
            comboBox1.Items.Add(textBox3.Text);
            // очищаем 
            Clear();
        }

        // Добавить управляющего 
        private void button3_Click(object sender, EventArgs e)
        {
            // делаем тоже самое, что и для других добавлений
            Spisok3.Add(new Manager(textBox1.Text, Convert.ToDateTime(textBox2.Text), textBox4.Text, textBox5.Text));
            dataGridView3.Rows.Clear();
            for (int i = 0; i < Spisok3.Count; i++)
            {
                string str = Spisok3[i].PrintKadr();
                string[] Str = str.Split(' ');
                dataGridView3.Rows.Add(Str[0], Str[1], Str[3], Str[4]);
            }
            Clear();
        }

        // добавить инженера
        private void button4_Click(object sender, EventArgs e)
        {
            // тоже самое
            Spisok4.Add(new Engineer(textBox1.Text, Convert.ToDateTime(textBox2.Text), textBox3.Text, textBox6.Text, textBox7.Text));
            dataGridView4.Rows.Clear();
            for (int i = 0; i < Spisok4.Count; i++) {
                string str = Spisok4[i].PrintWORK();
                string[] Str = str.Split(' ');
                dataGridView4.Rows.Add(Str[0], Str[1], Str[3], Str[4], Str[5]);
            }
            Clear();
        }

        // преобразовать
        private void button5_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < Spisok2.Count; i++)
            {
                if (comboBox1.Text.Equals(Spisok2[i].Get_SPEC()))
                {
                    // создаем переменную класса Инженер
                    Engineer temp = new Engineer();
                    // преобразовываем в новую переменную данные из i-того элемента 
                    temp.Fron_Work(Spisok2[i]);
                    // добавляем в лист 4 новую переменную
                    Spisok4.Add(temp);
                    // удаляем из списка 2 этот i-тый элемент
                    Spisok2.RemoveAt(i);
                    // добавляем в таблицу 4 новый элемент
                    dataGridView4.Rows.Add(Spisok4[Spisok4.Count - 1].Get_FIO(), Spisok4[Spisok4.Count - 1].GetDate_Work().ToShortDateString(), Spisok4[Spisok4.Count - 1].Get_SPEC(), Spisok4[Spisok4.Count - 1].Get_QUALIF(), Spisok4[Spisok4.Count - 1].Get_PDR2());
                    // удаляем из комбобокса i-тый элемент
                    comboBox1.Items.RemoveAt(i);
                    // очищаем таблицу 2
                    dataGridView2.Rows.Clear();
                }
                for (int j = 0; j < Spisok2.Count; j++)
                {
                    string str = Spisok2[j].PrintKadr();
                    string[] Str = str.Split(' ');
                    dataGridView2.Rows.Add(Str[0], Str[1], Str[3]);
                }
            }
        }
    }
}

