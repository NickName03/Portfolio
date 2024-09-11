using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Лаб1
{
    public partial class Form1 : Form
    {
        // объявляем переменную Person как массив объектов класса Klient_Banka
        Klient_Bankа[] Person;
        // счётчик
        int count = 0;
        // переменные-запоминалки, нужны для перегрузки
         int a, b;
        public Form1()
        {
            InitializeComponent();
            // "устанавливаем" размер массива объектов Person
            // теперь он может вместить 100 объектов класса
            Person = new Klient_Bankа[100];
        }
        // сам класс 
        class Klient_Bankа
        {
            // поля класса
            string FIO; // ФИО
            int N_Score; // Номер счёта
            double Sum_Score; // Сумма на счёте
            DateTime Date_Chang; // Дата последнего изменения
            // конструктор по умолчанию - при его вызове у того объекта
            // который его вызвал, все поля станут равны самому минимальному значению.
            public Klient_Bankа()
            {

            }
            // сеттеры. Принимают в качестве параметра одну переменную
            // значение которой будет присвоено определенному полю объекта класса
            public void Set_FIO(string F)
            {
                FIO = F;
            }
            public void Set_Score(int S)
            {
                N_Score = S;
            }
            public void Set_SumScore(double Sum)
            {
                Sum_Score = Sum;
            }
            public void Set_DateChang(DateTime D)
            {
                Date_Chang = D;
            }

            // геттеры. Возращают значение определенного поля объекта класса
            public string Get_FIO()
            {
                return FIO;
            }
            public int Get_Score()
            {
                return N_Score;
            }
            public double Get_SumScore()
            {
                return Sum_Score;
            }
            public DateTime Get_DateChang()
            {
                return Date_Chang;
            }
            // перегрузка оператора +
            public static Klient_Bankа operator +(Klient_Bankа a1, Klient_Bankа a2)
            {
                // возвращаем совершенно новый объект класса, в котором складывается сумма из двух объектов класса
                // остальным полям присваиваются значения того объекта, который передали в перегрузку первой
                 return new Klient_Bankа { FIO = a1.FIO, N_Score = a1.N_Score, Date_Chang = a1.Date_Chang, Sum_Score = a1.Sum_Score + a2.Sum_Score };
            }
            // перегрузка знака ">"
            public static bool operator >(Klient_Bankа c1, Klient_Bankа c2)
            {
                // возвращается результат сравнения номеров счёта.
                // так как мы указали тип возвращаемого значения bool
                // то и возвращаться будут только true или false
                return c1.N_Score > c2.N_Score;
            }
            // перегрузка знака "<". В принципе, она нигде не используется, но нужна
            // для того, чтобы работала перегрузка выше
            public static bool operator <(Klient_Bankа c1, Klient_Bankа c2)
            {
                return c1.Sum_Score < c2.Sum_Score;
            }
        }
        //Добавление записи
        private void button1_Click(object sender, EventArgs e)
        {
            // создаем конструктор по умолчанию count-му объекту класса
            Person[count] = new Klient_Bankа();
            // устанавливаем каждому полю соответствующие данные из текстбоксов
            // попутно конвертируя их в нужный тип, чтобы не проихошло конфликтов с данными
            Person[count].Set_FIO(textBox1.Text);
            Person[count].Set_Score(Convert.ToInt32(textBox2.Text));
            Person[count].Set_SumScore(Convert.ToInt32(textBox3.Text));
            Person[count].Set_DateChang(Convert.ToDateTime(textBox4.Text));
            // добавляем в комбобокс1 то, что записывалось как "ФИО", для возможности
            // вывода остальных полей по данному полю. То есть выбираем в комбобоксе какое-то ФИО
            // и нам выдаёт остальные поля объекта класса
            comboBox1.Items.Add(textBox1.Text);
            // заносим в комбобокс 2-3 то, что дожно быть "сумма на счету"
            // для возможности перегрузки 
            comboBox2.Items.Add(textBox3.Text);
            comboBox3.Items.Add(textBox3.Text);
            // прибавляем счётчик, чтобы не объекты класса не перезаписывали друг друга
            count++;
            // очищаем поля первых трех текстбоксов, чтобы в 4 текстбоксе
            // оставался пример того, как нужно вводить данные
            textBox1.Text = "";
            textBox2.Text = "";
            textBox3.Text = "";
        }
        //Вывод записей
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            // через цикл прогоняем каждый объект класса
            for (int i = 0; i < count; i++)
            {
                // если выбранное значение в комбобоксе равно ФИО i-того объекта
                // то вывод остальных значений полей объекта в текстбоксы 
                if (comboBox1.Text.Equals(Person[i].Get_FIO()))
                {
                    textBox1.Text = Convert.ToString(Person[i].Get_FIO());
                    textBox2.Text = Convert.ToString(Person[i].Get_Score());
                    textBox3.Text = Convert.ToString(Person[i].Get_SumScore());
                    textBox4.Text = Convert.ToString(Person[i].Get_DateChang());
                }
            }
        }
        
        // Перегрузка операторов 
        private void button4_Click(object sender, EventArgs e)
        {
            // создаём новую переменную для объекта (уже одного, так как это не массив) класса
            Klient_Bankа temp = new Klient_Bankа();
            // через цикл прогоняем каждый объект класса
            for (int i = 0; i < count; i++)
            {
                // пока не найдем совпадение с выбранным значением в комбобоксе
                if (comboBox2.Text.Equals(Person[i].Get_SumScore().ToString()))
                {
                    // запоминаем номер этого объекта
                    a = i;
                }
            }
            // делаем тоже самое с другим комбобоксом
            for (int j = 0; j < count; j++)
            {
                if (comboBox3.Text.Equals(Person[j].Get_SumScore().ToString()))
                {
                    b = j;
                }
            }
            // в новой переменной выполняем перегрузку "+"
            temp = Person[a] + Person[b];
            // выводим получившиеся поля в текстбоксы
            textBox1.Text = temp.Get_FIO();
            textBox2.Text = temp.Get_Score().ToString();
            textBox3.Text = temp.Get_SumScore().ToString();
            textBox4.Text = temp.Get_DateChang().ToString();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            // делаем тоже самое, что было описано в перегрузке "+"
            Klient_Bankа temp = new Klient_Bankа();
            for (int i = 0; i < count; i++)
            {
                if (comboBox2.Text.Equals(Person[i].Get_SumScore().ToString()))
                {
                    a = i;
                }
            }
            for (int j = 0; j < count; j++)
            {
                if (comboBox3.Text.Equals(Person[j].Get_SumScore().ToString()))
                {
                    b = j;
                }
            }
            // в зависимости от того, какой результат выдаст перегрузка ">"
            // выводим определенные надписи
            if (Person[a] > Person[b])
            {
                label5.Text = "Первый объект больше второго";
                
            }else
            {
                label5.Text = "Второй обьект больше первого";
            }  
        }
    }
}
