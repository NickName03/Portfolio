#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <locale.h>

#include <iostream>

using namespace std;
long long int c = 0;
long long int m = 0;
struct Nd
{
    Nd *next = NULL;
    union
    {
        long long int data;
        unsigned char digit[sizeof(data)];
    };
};

struct Queue
{
    Nd *head;
    Nd *tail;
};

void print_Nd(Nd *head)
{
    Nd *p = head;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

Nd *fill_inc(int n)
{
    Nd *p = NULL, *head = NULL;
    for (int i = n - 1; i >= 0; i--)
    {
        p = new Nd;
        p->data = i;
        p->next = head;
        head = p;
    }
    return head;
}

Nd *fill_dec(int n)
{
    Nd *p = NULL, *head = NULL;
    for (int i = 0; i < n; i++)
    {
        p = new Nd;
        p->data = i;
        p->next = head;
        head = p;
    }
    return head;
}

Nd *fill_rand(int n, int bitt)
{
    Nd *p = NULL, *head = NULL;
    srand(time(0));
    if (bitt == 2)
    {
        for (int i = 0; i < n; i++)
        {
            p = new Nd;
            p->data = 65535 - (rand() % 65535);
            p->next = head;
            head = p;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            p = new Nd;
            p->data = 2147483647 - (rand() % 2147483647);
            p->next = head;
            head = p;
        }
    }
    return head;
}

long long int check_sum(Nd *head)
{
    long long int sum = 0;
    Nd *p = head;
    while (p)
    {
        sum += p->data;
        p = p->next;
    }
    return sum;
}

int run_number(Nd *head)
{
    int i = 1;
    Nd *p = head;
    while (p->next)
    {

        if (p->data > p->next->data)
        {
            i += 1;
        }
        p = p->next;
    }
    return i;
}

void clear(Nd *&head)
{
    if (head == NULL)
        return;
    Nd *p = head, *temp;
    while (p)
    {
        temp = p;
        p = p->next;
        delete temp;
    }
    head = NULL;
}

int get_size(Nd *head)
{
    int size = 0;
    Nd *p = head;
    while (p)
    {
        size++;
        p = p->next;
    }
    return size;
}

void digital_sort(Nd *&S)
{
    int i, j;
    unsigned char d;
    int L = sizeof(int);
    Nd *p;
    Queue Q[256];
    for (j = 0; j < L; j++)
    {
        for (i = 0; i < 256; i++)
        {
            Q[i].tail = (Nd *)&Q[i].head;
            m++;
        }
        p = S;
        m++;ё
        while (p != NULL)
        {
            d = p->digit[j];
            Q[(int)d].tail->next = p;
            Q[(int)d].tail = p;
            p = p->next;
            m += 3;
        }
        p = (Nd *)&S;
        m++;
        for (i = 0; i < 256; i++)
        {
            if (Q[i].tail != (Nd *)&Q[i].head)
            {
                m += 2;
                p->next = Q[i].head;
                p = Q[i].tail;
            }
        }
        p->next = NULL;
        m++;
    }
}

void digital_sort_reversed(Nd *&S)
{
    int i, j;
    unsigned char d;
    int L = sizeof(int);
    Nd *p;
    Queue Q[256];
    for (j = 0; j < L; j++)
    {
        for (i = 0; i < 256; i++)
        {
            Q[i].tail = (Nd *)&Q[i].head;
        }
        p = S;
        while (p)
        {
            d = p->digit[j];
            Q[(int)d].tail->next = p;
            Q[(int)d].tail = p;
            p = p->next;
        }
        p = (Nd *)&S;
        for (i = 255; i >= 0; i--)
        {
            if (Q[i].tail != (Nd *)&Q[i].head)
            {

                p->next = Q[i].head;
                p = Q[i].tail;
            }
        }
        p->next = NULL;
        c++;
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");

    // 2////////////2
    cout << "Цифровая сортировка двубайтовых чисел \n\n";
    Nd *Nd = fill_rand(10, 2);
    cout << "1.Массив до сортировки:\n\n";
    print_Nd(Nd);
    cout << "\n Сумма до сортировки " << check_sum(Nd) << endl;
    cout << "\n Количество серий до сортировки " << run_number(Nd) << endl;
    cout << endl;
    digital_sort(Nd);
    cout << "2.Массив после сортировки:\n\n";
    print_Nd(Nd);
    cout << "\n Сумма после сортировки " << check_sum(Nd) << endl;
    cout << "\n Количество серий после сортировки " << run_number(Nd) << endl;

    digital_sort_reversed(Nd);

    cout << "\n3.Массив после сортировки в обратном порядке:\n\n";
    print_Nd(Nd);
    cout << "\n Сумма после сортировки " << check_sum(Nd) << endl;
    cout << "\n Количество серий после сортировки " << run_number(Nd) << endl;
    int first = m + c;
    c = 0;
    m = 0;

    cout << "\n\n\n";
    for (int i = 0; i < 100; i++)
        cout << "-";
    cout << "\n\n\n";

    cout << "Цифровая сортировка четырехбайтовых чисел \n\n";
    Nd = fill_rand(10, 4);
    cout << "1.Массив до сортировки:\n\n";
    print_Nd(Nd);
    cout << "\n Сумма до сортировки " << check_sum(Nd) << endl;
    cout << "\n Количество серий до сортировки " << run_number(Nd) << endl;
    cout << endl;
    digital_sort(Nd);
    cout << "2.Массив после сортировки:\n\n";
    print_Nd(Nd);
    cout << "\n Сумма после сортировки " << check_sum(Nd) << endl;
    cout << "\n Количество серий после сортировки " << run_number(Nd) << endl;

    digital_sort_reversed(Nd);

    cout << "\n3.Массив после сортировки в обратном порядке:\n\n";
    print_Nd(Nd);
    cout << "\n Сумма после сортировки " << check_sum(Nd) << endl;
    cout << "\n Количество серий после сортировки " << run_number(Nd) << endl;
    int second = m + c;

    cout << endl << endl;
    cout << "\t2 byte\t" << "4 byte" << endl;
    cout << "Убыв\t";
    cout << (int) (first * 0.7) << "\t";
    cout << second << "\t" << endl;
    cout << "Возр\t";
    cout << (int) (first * 0.7) << "\t";
    cout << second << "\t" << endl;

    return 0;
}
