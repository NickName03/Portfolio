#include <iostream>
#include <sys\stat.h>
#include <cmath>
#include <locale.h>
#include <windows.h>
#include <vector>
#include <iomanip>

using namespace std;
typedef unsigned char byte;
typedef const char* text;

void insertSort(vector<unsigned char>& symbols, double* P, int n)
{
    for (int i = 1; i < n; i++)
    {
        double temp = P[i];
        char tempData = symbols[i];
        int j = i - 1;
        while ((j >= 0) && (temp > P[j]))
        {
            P[j + 1] = P[j];
            symbols[j + 1] = symbols[j];
            j = j - 1;
        }
        P[j + 1] = temp;
        symbols[j + 1] = tempData;
    }
}

unsigned char* loadFile(int* size, const char* name)
{
    FILE* file;
    fopen_s(&file, name, "rb");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    struct stat Stat;
    int error = fstat(_fileno(file), &Stat);
    if (error != 0)
    {
        printf("Ошибка считывания stat файла: %d\n", error);
        exit(1);
    }
    *size = Stat.st_size;
    unsigned char* data = new unsigned char[*size];
    fread(data, *size, 1, file);
    fclose(file);
    return data;
}

void getP(unsigned char* data, double* P, vector<unsigned char>& symbols, int size, int* pp)
{
    for (int i = 0; i < symbols.size(); i++)
    {
        int frequency = 0;
        for (int j = 0; j < size; j++)
            if (data[j] == symbols[i])
                frequency++;

        pp[i] = frequency;
        P[i] = (double)frequency / size;
    }
}

bool isInside(vector<unsigned char>& array, int element)
{
    if (array.size() == 0)
        return false;

    for (int i = 0; i < array.size(); i++)
    {
        if (array[i] == element)
            return true;
    }
    return false;
}

double sumP(double* P, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += P[i];
    return sum;
}

double getEntropy(double* P, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += P[i] * log2f(P[i]);
    }

    return sum * (-1);
}

double getAverageLength(double* P, int* L, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += P[i] * L[i];
    return sum;
}

int createArithmeticCode(byte* block, vector<byte>a, double* Q, char* code, int size)
{
    double l = 0, h = 1, r = 1;
    int m;
    cout << "Блок: [ ";
    for (int i = 0; i < size; i++)
        cout << block[i] << " ";
    cout << "\b]" << endl << endl;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < a.size(); j++)
        {
            if (block[i] == a[j])
                m = j;
        }

        h = l + r * Q[m + 1];
        l = l + r * Q[m];
        r = h - l;

        cout << "После просмотра " << block[i] << ": [" << l << ", " << h << ")" << endl;
    }

    // double res = (l + h) / 2;
    double res = l;
    int d = -floor(log2(r)) + 1;

    for (int i = 0; i < d; i++)
    {
        // res = res << 1;
        res *= 2;
        code[i] = res >= 1 ? '1' : '0';
        if (res >= 1)
            res -= 1;
    }

    cout << endl;

    return d;
}

void getQ(double* Q, double* P, int n)
{
    Q[0] = 0;
    for (int i = 0; i < n; i++)
        Q[i + 1] = Q[i] + P[i];
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int size = -1;
    char code[256];
    int blockLength = 7;
    byte* block = new byte[blockLength];
    int pp[256];
    int low = 0, high = 1;

    byte* data = loadFile(&size, "ex1.txt");
    cout << "Размер файла: " << size << " байт" << endl;

    vector<byte> uniqSymbols;
    for (int i = 0; i < size; i++)
    {
        if (!isInside(uniqSymbols, data[i]))
            uniqSymbols.push_back(data[i]);
    }
    int n = uniqSymbols.size();

    double* P = new double[n];
    getP(data, P, uniqSymbols, size, pp);
    // insertSort(uniqSymbols, P, n);
    double* Q = new double[n + 1];
    getQ(Q, P, n);

    for (int i = 0; i < size; i += 7)
    {
        for (int j = 0; j < 7; j++)
            block[j] = data[i + j];

        int length = createArithmeticCode(block, uniqSymbols, Q, code, blockLength);
        cout << "Кодовое слово: ";
        for (int j = 0; j < length; j++)
            cout << code[j] << " ";
        cout << endl << endl;

        for (int j = 0; j < length; j++)
            code[j] = '0';
    }

    return 0;
}