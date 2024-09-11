
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <vector>

#define YES true
#define NO false
using namespace std;


struct vertex
{
	int data;
	int h;
	int w;
	vertex* left;
	vertex* right;
};

vertex* root;
vertex* root2;
vertex* root3;

int const N = 100;

int c = 0, c1 = 0, c2 = 0;
int* mas, * W;
int* h;
int AW[N + 1][N + 1];
int AP[N + 1][N + 1], AR[N + 1][N + 1];


void AW_count() {
	for (int i = 0; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			AW[i][j] = AW[i][j - 1] + W[j - 1];
}

void AP_AR_count() {
	int min, m, x, j;
	for (int i = 0; i < N; i++) {
		j = i + 1;
		AP[i][j] = AW[i][j];
		AR[i][j] = j;
	}
	for (int H = 2; H <= N; H++) {
		for (int i = 0; i <= N - H; i++) {
			j = i + H;
			m = AR[i][j - 1];
			min = AP[i][m - 1] + AP[m][j];
			for (int k = m + 1; k <= AR[i + 1][j]; k++) {
				x = AP[i][k - 1] + AP[k][j];
				if (x < min) {
					m = k;
					min = x;
				}
			}
			AP[i][j] = min + AW[i][j];
			AR[i][j] = m;
		}
	}
}

void add(vertex*& p, int x, int w) {
	if (p == NULL)
	{
		p = new vertex;
		p->data = mas[x - 1];
		p->w = w;
		p->left = NULL;
		p->right = NULL;
		//cout << p->data << " ";
	}
	else
		if (x < p->data) {
			add(p->left, x, w);
		}
		else
			if (x >= p->data) {
				add(p->right, x, w);
			}
}

void create_tree(int L, int R) {
	int k;

	if (L < R) {
		k = AR[L][R];
		//cout << k << " ";
		add(root, k, W[k - 1]);
		create_tree(L, k - 1);
		create_tree(k, R);
	}
}

void LRprint(vertex*& x) {//Îáõîä ñëåâà íàïðàâî
	if (x == NULL) return;
	LRprint(x->left);
	cout << x->data << ' ' << x->w << " " << x->h << endl;
	LRprint(x->right);
}

int size(vertex* p) // Âû÷èñëÿåò ðàçìåð äåðåâà
{
	if (p == NULL)
		return 0;
	return 1 + size(p->left) + size(p->right);
}

long summ(vertex* p) // Âû÷èñëÿåò êîíòðîëüíóþ ñóììó äàííûõ â âåðøèíàõ äåðåâà
{
	if (p == NULL)
		return 0;
	return p->data + summ(p->left) + summ(p->right);
}

void seth(vertex* p)
{
	if (p) {
		if (p->left) {
			p->left->h = p->h + 1;
		}
		if (p->right) {
			p->right->h = p->h + 1;
		}
		seth(p->left);
		seth(p->right);
	}
}

void midh(vertex* p, int& c)
{
	if (p) {
		c += p->w * p->h;
		midh(p->left, c);
		midh(p->right, c);
	}
}

int height(vertex* x, int data) {
	if (x == NULL) {
		return 0;
	}
	else {
		if (x->data < data) {
			return 1 + height(x->left, data);
		}
		else if (x->data > data) {
			return 1 + height(x->right, data);
		}
		else if (x->data == data) {
			return 1;
		}
	}
}

void A1(int* D, int n, vertex*& root) {
	vector <int> mas(D, D + n);
	std::sort(mas.begin(), mas.end(), comp2);
	for (int i = 0; i < n; i++) {
		add(root, i, mas[i]);
	}
}

void A2(int L, int R, int* D, vertex*& root) {
	int wes = 0, sum = 0;
	int i = 0;
	if (L <= R) {
		for (i = L; i < R; i++) {
			wes += D[i];
		}
		for (i = L; i < R; i++) {
			if (sum < wes / 2 && sum + D[i] > wes / 2)
				break;
			sum += D[i];
		}
		add(root, i, D[i]);
		A2(L, i - 1, D, root);
		A2(i + 1, R, D, root);
	}
}

int main() {
	srand(time(0));
	mas = new int[N];
	for (int i = 0; i < N; i++) {
		mas[i] = rand() % 999 + 1;
	}

	W = new int[N];
	for (int i = 0; i < N; i++) {
		W[i] = i + 1;
	}

	AW_count();


	AP_AR_count();

	create_tree(0, N);

	int WW = AW[0][N];

	cout << endl;
	A1(W, N, root1);
	A2(0, R, W, root2);
	root->h = 1;
	seth(root);
	midh(root, c);
	root1->h = 1;
	seth(root1);
	midh(root1, c1);
	root2->h = 1;
	seth(root2);
	midh(root2, c2);
	// LRprint(root);

	cout << endl << (double)AP[0][N] / AW[0][N] << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "| n=100 |  Size    | Summ. Data   | Average Weight    |" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "|  DOP  |" << setw(10) << size(root) << "|" << setw(14) << summ(root) << "|" << setw(21) << c / (double)WW << "|" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "|  A1   |" << setw(10) << size(root1) << "|" << setw(14) << summ(root1) << "|" << setw(21) << c1 / (double)WW << "|" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "|  A2   |" << setw(10) << size(root2) << "|" << setw(14) << summ(root2) << "|" << setw(21) << c2 / (double)WW << "|" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;

	delete[] mas;
	delete[] W;

	return 0;
}