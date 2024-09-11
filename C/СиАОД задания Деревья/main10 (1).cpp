#include <iostream>
#include <sys/stat.h>
#include <cmath>
#include <locale.h>
#include <vector>
#include <iomanip>

using namespace std;

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
    for (int i = 0; i < n; i++)
    {
        int Li = L[i];
        unsigned char* str = C[i] = new unsigned char[Li + 1];
        str[Li] = 0;
        for (int j = 0; j < Li; j++)
        {
            Q[i] *= 2;
            str[j] = Q[i] >= 1 ? '1' : '0';
            if (Q[i] >= 1)
                Q[i]--;
        }
    }
    return C;
}

void createGilbertMooreCode(double* P, double* Q, int* L, int n)
{
    double pSum = 0;
    for (int i = 0; i < n; i++)
    {
        Q[i] = pSum + P[i] / 2;
        pSum += P[i];
        L[i] = -floor(log2f(P[i])) + 1;
    }
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

    int size = -1;

    unsigned char* data = loadFile(&size, "ex.txt");


    vector<unsigned char> uniqSymbols;
    for (int i = 0; i < size; i++)
    {
        if (!isInside(uniqSymbols, data[i]))
            uniqSymbols.push_back(data[i]);
    }
    int n = uniqSymbols.size();

    double* P = new double[n];
    getP(data, P, uniqSymbols, size);
    insertSort(uniqSymbols, P, n);
    double* Q = new double[n + 1];
    int* LHuffman = new int[n];

    unsigned char** C = createHuffmanCode(n, P, LHuffman);

    cout << "Код Хаффмана: " << endl;

    cout.precision(3);
    cout << "Символ\tВероятность\tКод. слово\t\t\tДлина код. слова" << endl;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        cout << uniqSymbols[i];
        cout << setw(15) << P[i];
        string string;
        for (int j = 0; j < LHuffman[i]; j++)
            string.push_back(C[i][j]);
        cout << setw(17) << string;
        cout << setw(22) << LHuffman[i] << endl;
    }

    cout << endl
        << endl
        << "Код Гилберта-Мура: " << endl;

    int* LGilbertMoore = new int[n];
    createGilbertMooreCode(P, Q, LGilbertMoore, n);
    unsigned char** newC = calculation(Q, LGilbertMoore, n);
    cout << "Символ\tВероятность\tКод. слово\t\t\tДлина код. слова" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << uniqSymbols[i];
        cout << setw(15) << P[i];
        string string;
        for (int j = 0; j < LGilbertMoore[i]; j++)
            string.push_back(newC[i][j]);
        cout << setw(17) << string;
        cout << setw(22) << LGilbertMoore[i] << endl;
    }

    cout << endl
        << endl;

    cout << "H\tL(avg) Хаффман\tL(avg) Гилберт-Мур\tИзбыточность Хаффман\tИзбыточность Гилберт-Мур" << endl;
    double entropy = getEntropy(P, n);
    printf("%.5f\t", entropy);
    cout << getAverageLength(P, LHuffman, n) << "\t\t\t";
    cout << getAverageLength(P, LGilbertMoore, n) << "\t\t\t";
    cout << getAverageLength(P, LHuffman, n) - entropy << "\t\t\t";
    cout << getAverageLength(P, LGilbertMoore, n) - entropy;
    cout << "\nРазмер файла: " << size << " bytes" << endl;
    return 0;
}
