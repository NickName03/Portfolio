#include <iostream>
#include <cmath>
#include <locale.h>
#include <windows.h>
#include <vector>
#include <iomanip>

using namespace std;
typedef unsigned char byte;
typedef const char *text;

text fixedVariable(int len, int num, char *code)
{
    if (num == 0)
    {
        for (int i = 0; i < len; i++)
            code[i] = '0';
        code[len] = 0;
        return code;
    }
    int d = (int)floor(log2(num)) + 1, pos = 0;
    if (d >= 1 << len)
        return "Не кодируется";
    for (int i = 1; i <= len; i++)
        code[pos++] = d >> (len - i) & 1 ? '1' : '0';
    code[pos++] = ' ';
    for (int i = 1; i < d; i++)
        code[pos++] = num >> (d - i - 1) & 1 ? '1' : '0';
    code[pos] = 0;
    return code;
}

text gammaElias(int num, char *code)
{
    if (num == 0)
        return "Не кодируется";
    if (num == 1)
        return "1";
    int d = (int)floor(log2(num)) + 1, pos = 0;
    for (int i = 1; i < d; i++)
        code[pos++] = '0';
    code[pos++] = '1';
    code[pos++] = ' ';
    for (int i = 1; i < d; i++)
        code[pos++] = num >> (d - i - 1) & 1 ? '1' : '0';
    code[pos] = 0;
    return code;
}

void omegaRecurs(int num, char *code, int *pos)
{
    int d = (int)floor(log2(num)) + 1;

    if (d >= 3)
        omegaRecurs(d - 1, code, pos);

    for (int i = 0; i < d; i++)
        code[(*pos)++] = num >> (d - i - 1) & 1 ? '1' : '0';
    code[(*pos)++] = ' ';
}

text omegaElias(int num, char *code)
{
    text first[] = {"Не кодируется", "0", "10 0", "11 0"};
    if (num < 4)
        return first[num];
    int d = (int)floor(log2(num)) + 1, pos = 0;

    omegaRecurs(d - 1, code, &pos);

    for (int i = 0; i < d; i++)
        code[pos++] = num >> (d - i - 1) & 1 ? '1' : '0';
    code[pos++] = ' ';
    code[pos++] = '0';
    code[pos] = 0;
    return code;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char code[256], code2[256], code3[256];
    cout << setw(3) << "Число" << setw(30) << "Fixed + Variable" << setw(30) << "Gamma-Elias" << setw(30) << "Omega-Elias" << endl;
    for (int i = 0; i < 256; i++)
        cout << setw(3) << i << setw(32) << fixedVariable(4, i, code) << setw(31) << gammaElias(i, code2) << setw(30) << omegaElias(i, code3) << endl;

    return 0;
}