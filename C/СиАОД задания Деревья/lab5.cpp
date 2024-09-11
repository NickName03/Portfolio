#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

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

AVLVertex *findVertex(AVLVertex *root, int number)
{
    vector<AVLVertex *> queue;
    queue.push_back(root);

    int count = 1;

    while (queue.size() > 0)
    {
        AVLVertex *currentNode = queue[0];
        queue.erase(queue.begin());
        if (currentNode->number == number)
            return currentNode;
        
        if (currentNode->left != NULL)
            queue.push_back(currentNode->left);
        if (currentNode->right != NULL)
            queue.push_back(currentNode->right);
    }
    return root;
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

void newLeftLeftTurn(AVLVertex *&vertex, bool &isDecrease)
{
    AVLVertex *q = vertex->left;
    if (q->balance == 0)
    {
        q->balance = 1;
        vertex->balance = -1;
        isDecrease = false;
    }
    else
    {
        q->balance = 0;
        vertex->balance = 0;
    }

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

void newRightRightTurn(AVLVertex *&vertex, bool &isDecrease)
{
    AVLVertex *q = vertex->right;
    if (q->balance == 0)
    {
        q->balance = -1;
        vertex->balance = 1;
        isDecrease = false;
    }
    else
    {
        q->balance = 0;
        vertex->balance = 0;
    }

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

void balanceLeft(AVLVertex *&vertex, bool &isDecrease)
{
    if (vertex->balance == -1)
    {
        vertex->balance = 0;
    }
    else if (vertex->balance == 0)
    {
        vertex->balance = 1;
        isDecrease = false;
    }
    else if (vertex->balance == 1)
    {
        if (vertex->right->balance >= 0)
        {
            newRightRightTurn(vertex, isDecrease);
        }
        else
        {
            rightLeftTurn(vertex);
        }
    }
}

void balanceRight(AVLVertex *&vertex, bool &isDecrease)
{
    if (vertex->balance == 1)
    {
        vertex->balance = 0;
    }
    else if (vertex->balance == 0)
    {
        vertex->balance = -1;
        isDecrease = false;
    }
    else if (vertex->balance == -1)
    {
        if (vertex->left->balance <= 0)
        {
            newLeftLeftTurn(vertex, isDecrease);
        }
        else
        {
            leftRightTurn(vertex);
        }
    }
}

void del(AVLVertex *&q, AVLVertex *&r, bool &isDecrease)
{
    if (r->right != NULL)
    {
        del(q, r->right, isDecrease);
        if (isDecrease)
            balanceRight(r, isDecrease);
    }
    else
    {
        q->value = r->value;
        q = r;
        r = r->left;
        isDecrease = true;
    }
}

void deleteVertex(AVLVertex *&vertex, int x, bool &isDecrease)
{
    if (vertex == NULL)
        return;

    if (x < vertex->value)
    {
        deleteVertex(vertex->left, x, isDecrease);
        if (isDecrease)
            balanceLeft(vertex, isDecrease);
    }
    else if (x > vertex->value)
    {
        deleteVertex(vertex->right, x, isDecrease);
        if (isDecrease)
            balanceRight(vertex, isDecrease);
    }
    else
    {
        AVLVertex *q = vertex;
        if (q->left == NULL)
        {
            vertex = q->right;
            isDecrease = true;
        }
        else if (q->right == NULL)
        {
            vertex = q->left;
            isDecrease = true;
        }
        else
        {
            del(q, q->left, isDecrease);
            if (isDecrease)
                balanceLeft(vertex, isDecrease);
        }
        delete q;
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
    int size = 20;  // Кол-во вершин
    int array[size];
    fillRand(array, size);

    bool isIncrease = false;
    bool isDecrease = false;
    AVLVertex *AVLTree = NULL;
    
    for (int i = 0; i < size; i++)
        addToAVL(AVLTree, array[i], isIncrease);

    fillNumbers(AVLTree);
    cout << "Обход АВЛ дерева слева направо: " << endl;
    printLeftToRight(AVLTree);
    cout << "\b\b  " << endl << endl;
    printTree(AVLTree, nullptr, false);
    cout << endl << endl;

    for (int i = 0; i < 10; i++)
    {
        int number = 0;
        while (true)
        {
            string strNumber;
            cout << "(" << i + 1 << ") Введите номер вершины: ";
            getline(cin, strNumber);
            number = stoi(strNumber);
            if (number < 1 || number > size)
                cout << "Вершины с таким номером не существует." << endl;
            else
                break;
        }
        AVLVertex *vertex = findVertex(AVLTree, number);
        deleteVertex(AVLTree, vertex->value, isDecrease);

        if (AVLTree == NULL)
        {
            cout << "Дерево пустое. " << endl;
            break;
        }

        fillNumbers(AVLTree);
        printLeftToRight(AVLTree);
        cout << "\b\b  " << endl << endl;
    }
    return 0;
}