#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

struct DOPVertex
{
    int value;
    int number;
    int weight;
    DOPVertex *left;
    DOPVertex *right;
};

bool isInside(int *array, int size, int element)
{
    if (size == 0)
        return false;

    for (int i = 0; i < size; i++)
    {
        if (array[i] == element)
            return true;
    }
    return false;
}

int getRandomInteger(int start, int end)
{
    return rand() % (end - start + 1) + start;
}

void fillRand(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        int value = getRandomInteger(10, 999);
        while (isInside(array, i, value))
            value = getRandomInteger(10, 999);

        array[i] = value;
    }
}

void insertSort(DOPVertex **vertexArray, int size, int type)
{
    if (type == 1)
    {
        for (int i = 1; i < size; i++)
        {
            DOPVertex *temp = vertexArray[i];
            int j = i - 1;
            while ((j >= 0) && (temp->weight > vertexArray[j]->weight))
            {
                vertexArray[j + 1] = vertexArray[j];
                j = j - 1;
            }
            vertexArray[j + 1] = temp;
        }
    }
    else if (type == 2)
    {
        for (int i = 1; i < size; i++)
        {
            DOPVertex *temp = vertexArray[i];
            int j = i - 1;
            while ((j >= 0) && (temp->value < vertexArray[j]->value))
            {
                vertexArray[j + 1] = vertexArray[j];
                j = j - 1;
            }
            vertexArray[j + 1] = temp;
        }
    }
}

void printLeftToRight(DOPVertex *vertex)
{
    DOPVertex *current = vertex;

    if (current != NULL)
    {
        printLeftToRight(current->left);
        cout << current->value << " (" << current->weight << "), ";
        printLeftToRight(current->right);
    }
}

void treeCollector(DOPVertex *vertex, int height, int &size, int &sum, int &mid_wh, int &sum_w) 
{
	size++;
	sum += vertex->value;
	mid_wh += vertex->weight * height;
	sum_w += vertex->weight;
	height++;
	if (vertex->left != NULL) 
        treeCollector(vertex->left, height, size, sum, mid_wh, sum_w);
	if (vertex->right != NULL) 
        treeCollector(vertex->right, height, size, sum, mid_wh, sum_w);
}

void calculation(DOPVertex **vertexArray, int **AR, int size)
{
    int n = size - 1;
    int **AW = new int *[size];
    int **AP = new int *[size];
    for (int i = 0; i < size; i++)
        AW[i] = new int[size];

    for (int i = 0; i < size; i++)
        AP[i] = new int[size];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            AW[i][j] = AP[i][j] = AR[i][j] = 0;

    // Вычисление AW-матрицы весов
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            AW[i][j] = AW[i][j - 1] + vertexArray[j - 1]->weight;
        }
    }


    // Вычисление матриц AP и AR
    for (int i = 0; i < n; i++) // h = 1
    {
        for (int j = i + 1; j < size; j++)
        {
            AP[i][j] = AW[i][j];
            AR[i][j] = i + 1;
        }
    }

    for (int h = 2; h < size; h++) // h > 1
    {
        for (int i = 0; i < size - h; i++)
        {
            int j = i + h;
            int m = AR[i][j - 1];
            int min = AP[i][m - 1] + AP[m][j];

            for (int k = m + 1; k <= AR[i + 1][j]; k++)
            {
                int x = AP[i][k - 1] + AP[k][j];
                if (x < min)
                {
                    m = k;
                    min = x;
                }
            }

            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
}

DOPVertex *newDOP(int value, int weight)
{
    DOPVertex *element = new DOPVertex;
    element->left = NULL;
    element->right = NULL;
    element->value = value;
    element->weight = weight;
    return element;
}

void addVertex(DOPVertex *&vertex, DOPVertex *element)
{
    if (vertex == NULL)
    {
        vertex = element;
    }
    else if (element->value < vertex->value)
    {
        addVertex(vertex->left, element);
    }
    else if (element->value > vertex->value)
    {
        addVertex(vertex->right, element);
    }
    else
    {
        cout << "Ошибка! Такая вершина уже есть." << endl;
        return;
    }
}

void createTree(DOPVertex *&root, DOPVertex **vertexArray, int **AR, int left, int right)
{
    if (left < right)
    {
        int k = AR[left][right] - 1;
        addVertex(root, vertexArray[k]);
        createTree(root, vertexArray, AR, left, k);
        createTree(root, vertexArray, AR, k + 1, right);
    }
}

void createA2(DOPVertex *&root, DOPVertex **vertexArray, int left, int right)
{
    int weight = 0, sum = 0;
    if (left <= right)
    {
        for (int i = left; i <= right; i++)
            weight += vertexArray[i]->weight;

        int i = left;
        for (i; i <= right; i++)
        {
            if ((sum < (weight / 2)) && (sum + vertexArray[i]->weight > (weight / 2)))
                break;
            sum += vertexArray[i]->weight;
        }

        if (i > right)
            i = right;
        
        addVertex(root, vertexArray[i]);
        createA2(root, vertexArray, left, i - 1);
        createA2(root, vertexArray, i + 1, right);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");
    int n = 100;
    int size = n + 1;
    int* array = new int[n];
    int* weightArray = new int[n];
    fillRand(weightArray, n);
    fillRand(array, n);

    DOPVertex *exactTree = NULL;
    DOPVertex *A1Tree = NULL;
    DOPVertex *A2Tree = NULL;
    DOPVertex *exactVertexArray[n];
    DOPVertex *A1VertexArray[n];
    DOPVertex *A2VertexArray[n];
    for (int i = 0; i < n; i++)
    {
        exactVertexArray[i] = newDOP(array[i], weightArray[i]);
        A1VertexArray[i] = newDOP(array[i], weightArray[i]);
        A2VertexArray[i] = newDOP(array[i], weightArray[i]);
    }

    insertSort(exactVertexArray, n, 2);

    int **AR = new int *[size];
    for (int i = 0; i < size; i++)
        AR[i] = new int[size];
    calculation(exactVertexArray, AR, size);
    createTree(exactTree, exactVertexArray, AR, 0, n);
    // printLeftToRight(exactTree);
    // cout << "\b\b  " << endl << endl;

    // Добавление в А1

    insertSort(A1VertexArray, n, 1); // Сортировка по убыванию весов
    for (int i = 0; i < n; i++)
        addVertex(A1Tree, A1VertexArray[i]);

    cout << "Обход А1 слева направо: " << endl;
    printLeftToRight(A1Tree);
    cout << "\b\b  " << endl << endl;

    // Добавление в А2

    insertSort(A2VertexArray, n, 2); // Сортировка по ключу
    createA2(A2Tree, A2VertexArray, 0, n - 1);
    cout << "Обход А2 слева направо: " << endl;
    printLeftToRight(A2Tree);
    cout << "\b\b  " << endl << endl;

    cout.precision(3);
    int treeSize, sum, mid_wh, sum_w;
    cout << "n = 100\t\tРазмер\t\tКонтр.сумма\t\tСрдн.взв.высота" << endl;
    cout << "ДОП\t\t";
    treeSize = 0, sum = 0, mid_wh = 0, sum_w = 0;
	treeCollector(exactTree, 1, treeSize, sum, mid_wh, sum_w);
    cout << treeSize << "\t\t";
    cout << sum << "\t\t\t";
    cout << (double) mid_wh / sum_w << "\t\t" << endl;

    cout << "А1\t\t";
    treeSize = 0, sum = 0, mid_wh = 0, sum_w = 0;
	treeCollector(A1Tree, 1, treeSize, sum, mid_wh, sum_w);
    cout << treeSize << "\t\t";
    cout << sum << "\t\t\t";
    cout << (double) mid_wh / sum_w << "\t\t" << endl;

    cout << "А2\t\t";
    treeSize = 0, sum = 0, mid_wh = 0, sum_w = 0;
	treeCollector(A2Tree, 1, treeSize, sum, mid_wh, sum_w);
    cout << treeSize << "\t\t";
    cout << sum << "\t\t\t";
    cout << (double) mid_wh / sum_w << "\t\t" << endl;
    return 0;
}