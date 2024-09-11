#include <iostream>
#include <sys\stat.h>
#include <cmath>
#include <locale.h>
#include <windows.h>
#include <vector>
#include <iomanip>

using namespace std;

void createShannonCode(double* P, double* Q, int* L, int n)
{
    Q[0] = 0;
    for (int i = 0; i < n; i++)
    {
        Q[i + 1] = Q[i] + P[i];
        L[i] = -floor(log2f(P[i]));
    }
}

unsigned char** calculation(double* Q, int* L, int n)
{
    unsigned char** C = new unsigned char* [n];
    for (int i = 0; i < n; i++) {
        int Li = L[i];
        unsigned char* str = C[i] = new unsigned char[Li + 1];
        str[Li] = 0;
        for (int j = 0; j < Li; j++) {
            Q[i] *= 2;
            str[j] = Q[i] >= 1 ? '1' : '0';
            if (Q[i] >= 1) Q[i]--;
        }
        //printf("%10.5g   %s\n", P[i], str);
    }
    return C;
}

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

void getP(unsigned char* data, double* P, vector<unsigned char>& symbols, int size)
{
    for (int i = 0; i < symbols.size(); i++)
    {
        int frequency = 0;
        for (int j = 0; j < size; j++)
            if (data[j] == symbols[i])
                frequency++;

        P[i] = (double)frequency / size;
    }
}

unsigned char* loadFile(int* size, const char* name)
{
    FILE* file;
    fopen_s(&file, name, "rb");
    if (file == NULL)
    {
        printf("Нет такого файла.\n");
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

int FanoMed(int L, int R, double* P) {
    double SL = 0, SR = P[R];
    for (int i = L; i < R; i++) SL += P[i];
    int m = R;
    while (SL >= SR) {
        m--;
        SL -= P[m];
        SR += P[m];
    }
    //if (m == R) m--;
    return m;
}
void FanoRecurs(int L, int R, int k, double* P, unsigned char** C, int* Len) {
    if (L >= R) return;
    int m = FanoMed(L, R, P);
    for (int i = L; i <= R; i++) {
        C[i][k] = i <= m ? '0' : '1';
        Len[i]++;
        //printf("[%u %u] = %c\n", i, k, C[i][k]);
    }
    k++;
    FanoRecurs(L, m, k, P, C, Len);
    FanoRecurs(m + 1, R, k, P, C, Len);
}
unsigned char** createFanoCode(int n, double* P, int* Len) {
    unsigned char** C = new unsigned char* [n];
    for (int i = 0; i < n; i++) C[i] = new unsigned char[257], Len[i] = 0;
    FanoRecurs(0, n - 1, 0, P, C, Len);
    for (int i = 0; i < n; i++) C[i][Len[i]] = 0;
    return C;
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

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int size = -1;

    unsigned char* data = loadFile(&size, "ex.txt");
    cout << "Размер файла: " << size << " байт" << endl;

    vector<unsigned char> uniqSymbols;
    for (int i = 0; i < size; i++)
    {
        if (!isInside(uniqSymbols, data[i]))
        {
            uniqSymbols.push_back(data[i]);
        }
    }
    int n = uniqSymbols.size();
    double* P = new double[n];
    getP(data, P, uniqSymbols, size);
    insertSort(uniqSymbols, P, n);
    double* Q = new double[n + 1];
    int* LShannon = new int[n];

    createShannonCode(P, Q, LShannon, n);
    unsigned char** C = calculation(Q, LShannon, n);

    cout << endl << endl << "Код Шеннона: " << endl;

    cout.precision(3);
    cout << "Символ\tВероятность\tКод.слово\t\tДлина код.слова" << endl;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        cout << uniqSymbols[i] << "\t";
        cout << setw(10) << P[i] << "\t";
        for (int j = 0; j < LShannon[i]; j++)
            cout << C[i][j];
        cout << "\t\t\t";
        cout << LShannon[i] << endl;
    }

    cout << endl << endl << "Код Фано: " << endl;

    int* LFano = new int[n];
    unsigned char** newC = createFanoCode(n, P, LFano);
    cout << "Символ\tВероятность\tКод.слово\t\tДлина код.слова" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << uniqSymbols[i] << "\t";
        cout << setw(10) << P[i] << "\t";
        for (int j = 0; j < LShannon[i]; j++)
            cout << C[i][j];
        cout << "\t\t\t";
        cout << LShannon[i] << endl;
    }

    cout << endl << endl;

    cout << "Энтропия\tСр.длина (Шеннон)\tСр.длина (Фано)\tИзбыточность (Шеннон)\tИзбыточность (Фано)" << endl;
    double entropy = getEntropy(P, n);
    printf("%.5f\t\t", entropy);
    cout << getAverageLength(P, LShannon, n) << "\t\t\t";
    cout << getAverageLength(P, LFano, n) << "\t\t";
    cout << getAverageLength(P, LShannon, n) - entropy << "\t\t\t";
    cout << getAverageLength(P, LFano, n) - entropy;
    return 0;
}