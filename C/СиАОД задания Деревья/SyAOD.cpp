#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <locale.h>
#include <vector>
#include <algorithm>
#include <locale>
#include <iostream>

using namespace std;
long long int c = 0;
long long int m = 0;
struct Nd
{
    Nd* next = NULL;
    union
    {
        char data[5];
        unsigned char digit[sizeof(data)];
    };
    union
    {
        char aut[5];
        unsigned char digit2[sizeof(aut)];
    };
};

struct Queue
{
    Nd* head;
    Nd* tail;
};

void print_Nd(Nd* head)
{
    Nd* p = head;
    while (p != NULL)
    {
        for (int i = 0; i < 5; i++) {
            cout << p->data[i];
        }
        cout << " ";
        for (int i = 0; i < 5; i++) {
            cout << p->aut[i];
        }
        cout << endl;
        p = p->next;
    }
    cout << endl;
}

Nd* fill_rand(int n, int bitt)
{
    Nd* p = NULL, * head = NULL;
    srand(time(0));
    string str = "абвгдежзик";
    int a;
    for (int i = 0; i < n; i++)
    {
        p = new Nd;
        for (int i = 0; i < 5; i++) {
            a = rand() % 5;
            p->data[i] = str[a];
            a = rand() % 5;
            p->aut[i] = str[a + 1];
        }
        p->next = head;
        head = p;
    }
    return head;
}

void FreeQueue(Nd* p) {
    Nd* q;
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
    p = NULL;
}

int compare(Nd& laut, Nd& raut)
{
    return strncmp(laut.aut, raut.aut, 5);
}

void digital_sort(Nd*& S, int flag)
{
    int i, j;
    unsigned char d;
    int L = sizeof(int);
    Nd* p;
    vector<Queue> Q(256);
    vector<Nd> buf;
    vector<Queue> b(1);
    for (j = 3; j >= 0; j--)
    {
        for (i = 0; i < 256; i++)
        {
            Q[i].tail = (Nd*)&Q[i].head;
        }
        p = S;
        while (p != NULL)
        {
            if (flag) d = p->data[j];
            else d = p->aut[j];
            Q[(int)d].tail->next = p;
            Q[(int)d].tail = p;
            p = p->next;
        }
        p = (Nd*)&S;
        for (i = 0; i < 256; i++)
        {
            if (Q[i].tail != (Nd*)&Q[i].head)
            {
                if (j != 0) {
                    p->next = Q[i].head;
                    p = Q[i].tail;
                }
                else {
                    p->next = Q[i].head;
                    p = Q[i].tail;
                }
            }
        }
        p->next = NULL;
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");

    Nd* Nd = fill_rand(10, 2);
    cout << "1.Массив до сортировки:\n\n";
    print_Nd(Nd);
    cout << endl << endl;
    digital_sort(Nd, 1);
    cout << "1.Массив после сортировки:\n\n";
    //print_Nd(Nd);
    return 0;
}