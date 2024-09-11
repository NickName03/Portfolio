#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

struct RandomVertex
{
    int value;
    int number;
    int frequency;
    RandomVertex *left;
    RandomVertex *right;
};

struct AVLVertex
{
    int value;
    int number;
    int balance;
    AVLVertex *left;
    AVLVertex *right;
};

struct Trunk
{
    Trunk *prev;
    string str;
 
    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
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

void printLeftToRight(RandomVertex *vertex)
{
    RandomVertex *current = vertex;

    if (current != NULL)
    {
        printLeftToRight(current->left);
        cout << current->number << " (" << current->value << "), ";
        printLeftToRight(current->right);
    }
}

int getTreeSize(RandomVertex *vertex)
{
    if (vertex == NULL)
        return 0;
    return 1 + getTreeSize(vertex->left) + getTreeSize(vertex->right);
}

int getCheckSum(RandomVertex *vertex)
{
    if (vertex == NULL)
        return 0;
    return vertex->value + getCheckSum(vertex->left) + getCheckSum(vertex->right);
}

int getTreeHeight(RandomVertex *vertex)
{
    if (vertex == NULL)
        return 0;
    return 1 + max(getTreeHeight(vertex->left), getTreeHeight(vertex->right));
}

int getSumOfLengths(RandomVertex *vertex, int level)
{
    if (vertex == NULL)
        return 0;                          
    return level + getSumOfLengths(vertex->left, level + 1) + getSumOfLengths(vertex->right, level + 1);
}

void fillNumbers(RandomVertex *vertex)
{
    vector<RandomVertex *> queue;
    queue.push_back(vertex);

    int count = 1;

    while (queue.size() > 0)
    {
        RandomVertex *currentNode = queue[0];
        queue.erase(queue.begin());
        currentNode->number = count++;
        
        if (currentNode->left != NULL)
            queue.push_back(currentNode->left);
        if (currentNode->right != NULL)
            queue.push_back(currentNode->right);
    }
}

void addRecursivelyToTree(RandomVertex *&vertex, int element)
{
    if (vertex == NULL)
    {
        vertex = new RandomVertex;
        vertex->value = element;
        vertex->left = NULL;
        vertex->right = NULL;
        vertex->frequency = 1;
    }
    else if (element < vertex->value)
    {
        addRecursivelyToTree(vertex->left, element);
    }
    else if (element > vertex->value)
    {
        addRecursivelyToTree(vertex->right, element);
    }
    else
    {
        vertex->frequency++;
    }
}

void printLeftToRight(AVLVertex *vertex)
{
    AVLVertex *current = vertex;

    if (current != NULL)
    {
        printLeftToRight(current->left);
        cout << current->number << " (" << current->value << "), ";
        printLeftToRight(current->right);
    }
}

int getTreeSize(AVLVertex *vertex)
{
    if (vertex == NULL)
        return 0;
    return 1 + getTreeSize(vertex->left) + getTreeSize(vertex->right);
}

int getCheckSum(AVLVertex *vertex)
{
    if (vertex == NULL)
        return 0;
    return vertex->value + getCheckSum(vertex->left) + getCheckSum(vertex->right);
}

int getTreeHeight(AVLVertex *vertex)
{
    if (vertex == NULL)
        return 0;
    return 1 + max(getTreeHeight(vertex->left), getTreeHeight(vertex->right));
}

int getSumOfLengths(AVLVertex *vertex, int level)
{
    if (vertex == NULL)
        return 0;                          
    return level + getSumOfLengths(vertex->left, level + 1) + getSumOfLengths(vertex->right, level + 1);
}

void fillNumbers(AVLVertex *vertex)
{
    vector<AVLVertex *> queue;
    queue.push_back(vertex);

    int count = 1;

    while (queue.size() > 0)
    {
        AVLVertex *currentNode = queue[0];
        queue.erase(queue.begin());
        currentNode->number = count++;
        
        if (currentNode->left != NULL)
            queue.push_back(currentNode->left);
        if (currentNode->right != NULL)
            queue.push_back(currentNode->right);
    }
}

void leftLeftTurn(AVLVertex *&vertex)
{
    AVLVertex *q = vertex->left;
    vertex->balance = 0;
    q->balance = 0;
    vertex->left = q->right;
    q->right = vertex;
    vertex = q;
}

void rightRightTurn(AVLVertex *&vertex)
{
    AVLVertex *q = vertex->right;
    vertex->balance = 0;
    q->balance = 0;
    vertex->right = q->left;
    q->left = vertex;
    vertex = q;
}

void leftRightTurn(AVLVertex *&vertex)
{
    AVLVertex *q = vertex->left;
    AVLVertex *r = q->right;
    
    if (r->balance < 0)
        vertex->balance = 1;
    else
        vertex->balance = 0;

    if (r->balance > 0)
        q->balance = -1;
    else
        q->balance = 0;

    r->balance = 0;
    q->right = r->left;
    vertex->left = r->right;
    r->left = q;
    r->right = vertex;
    vertex = r;
}

void rightLeftTurn(AVLVertex *&vertex)
{
    AVLVertex *q = vertex->right;
    AVLVertex *r = q->left;
    
    if (r->balance > 0)
        vertex->balance = -1; // here
    else
        vertex->balance = 0;

    if (r->balance < 0)
        q->balance = 1;
    else
        q->balance = 0;

    r->balance = 0;
    q->left = r->right;
    vertex->right = r->left;
    r->right = q;
    r->left = vertex;
    vertex = r;
}

void addToAVL(AVLVertex *&vertex, int value, bool &isIncrease)
{
    if (vertex == NULL)
    {
        vertex = new AVLVertex;
        vertex->value = value;
        vertex->balance = 0;
        vertex->left = NULL;
        vertex->right = NULL;
        isIncrease = true;
    }
    else if (vertex->value > value)
    {
        addToAVL(vertex->left, value, isIncrease);
        if (isIncrease)
        {
            if (vertex->balance > 0)
            {
                vertex->balance = 0;
                isIncrease = false;
            }
            else if (vertex->balance == 0)
            {
                vertex->balance = -1;
                isIncrease = true;
            }
            else
            {
                if (vertex->left->balance < 0)
                {
                    leftLeftTurn(vertex);
                    isIncrease = false;
                }
                else
                {
                    leftRightTurn(vertex);
                    isIncrease = false;
                }
            }
        }
    }
    else if (vertex->value < value)
    {
        addToAVL(vertex->right, value, isIncrease);
        if (isIncrease)
        {
            if (vertex->balance < 0)
            {
                vertex->balance = 0;
                isIncrease = false;
            }
            else if (vertex->balance == 0)
            {
                vertex->balance = 1;
                isIncrease = true;
            }
            else
            {
                if (vertex->right->balance > 0)
                {
                    rightRightTurn(vertex);
                    isIncrease = false;
                }
                else
                {
                    rightLeftTurn(vertex);
                    isIncrease = false;
                }
            }
        }
    }
}

// Вспомогательная функция для печати ветвей бинарного дерева
void showTrunks(Trunk *p)
{
    if (p == nullptr) {
        return;
    }
 
    showTrunks(p->prev);
    cout << p->str;
}
 
void printTree(AVLVertex* root, Trunk *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }
 
    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);
 
    printTree(root->right, trunk, true);
 
    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else {
        trunk->str = "`———";
        prev->str = prev_str;
    }
 
    showTrunks(trunk);
    cout << " " << root->value << endl;
 
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
 
    printTree(root->left, trunk, false);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");
    int size = 100;
    int array[size];
    fillRand(array, size);
    RandomVertex *randTree = NULL;

    for (int i = 0; i < size; i++)
        addRecursivelyToTree(randTree, array[i]);

    fillNumbers(randTree);
    cout << "Обход СДП слева направо: " << endl;
    printLeftToRight(randTree);
    cout << "\b\b  " << endl << endl;

    bool isIncrease = false;
    AVLVertex *AVLTree = NULL;
    
    for (int i = 0; i < size; i++)
        addToAVL(AVLTree, array[i], isIncrease);

    fillNumbers(AVLTree);
    cout << "Обход АВЛ дерева слева направо: " << endl;
    printLeftToRight(AVLTree);
    cout << "\b\b  " << endl << endl;

    cout << "n = 100\t\tРазмер\t\tКонтр.сумма\t\tВысота\t\tСр.высота" << endl;
    cout << "СДП\t\t" << getTreeSize(randTree) << "\t\t";
    cout << getCheckSum(randTree) << "\t\t\t";
    cout << getTreeHeight(randTree) << "\t\t";
    cout << (double) getSumOfLengths(randTree, 1) / getTreeSize(randTree) << "\t\t" << endl;

    cout << "АВЛ\t\t" << getTreeSize(AVLTree) << "\t\t";
    cout << getCheckSum(AVLTree) << "\t\t\t";
    cout << getTreeHeight(AVLTree) << "\t\t";
    cout << (double) getSumOfLengths(AVLTree, 1) / getTreeSize(AVLTree) << "\t\t" << endl;
    return 0;
}