#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string.h>
#include <conio.h>
#include <string>
using namespace std;

int start();
int menu();
void original_digit(int* mas, int pos); // генерация числа с оригинальными цифрами
int diapazon(int input); // проверка на правильность
void split_mas(int input, int* chislo); // разделение числа по цифрам в массив
int cmp(int* chislo, int* hidden); // сравнение чисел

int cmp(int* chislo, int* hidden) {
	int povt = 0, mest = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (hidden[i] == chislo[j]) {
				povt++;
				break;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		if (hidden[i] == chislo[i]) {
			mest++;
		}
	}
	cout << "Угаданных цифр: " << povt << "\nЦифр на своих местах: " << mest << endl;
	if (povt == 4 && mest == 4) {
		cout << "Вы угадали!\n";
		return 0;
	}
	return 1;
}

int diapazon(int input) {
	while (input < 1000 || input > 9999) {
		cout << "Число не подходит, нужно ввести четырехзначное число!\n";
		cout << "Вы вводите: ";
		cin >> input;
	}
	return input;
}

void split_mas(int input, int* chislo) {
	for (int i = 3; i >= 0; i--) {
		chislo[i] = input % 10;
		input /= 10;
	}
}

int start() {
	int hidden[4];
	int chislo[4];
	string str;
	int input = -1;
	int flag = 0;
	while (1) {
		if (flag == 0) {
			cout << "Компьютер загадал число!\n";
			for (int i = 0; i < 4; i++) {
				original_digit(hidden, i);
			}
			flag = 1;
		}
		else {
			cout << "\nДля выхода введите -1!\n";
			cout << "Вы вводите: ";
			cin >> str;
			if (str == "-1") {
				return 2;
			}
			input = atoi(str.c_str());
			while (input == 0) {
				cout << "Некорректный ввод, нужно число!\nВы вводите: ";
				cin >> str;
				input = atoi(str.c_str());
			}
			input = diapazon(input);
			split_mas(input, chislo);
			flag = cmp(chislo, hidden);
		}
	}
	return 0;
}

int menu() {
	cout << "\t\t\t\t\tДобро пожаловать в игру Быки и Коровы!\n\t\t\t\t"
		"Вам нужно угадать загаданное число из 4 цифр!\n\t\t\t"
		"В качестве подсказок после каждого введенного варианта будут показываться:\n\t\t\t\t"
		"- Количество угаданных цифр\n\t\t\t\t"
		"- Количество цифр, которые стоят на своём месте\n\t\t\t\t\t";
	while (1) {
		cout << "Для начала игры нажмите - 1. Для выхода - 2\n\nВаше действие:\n";
		int act = _getch();
		while (act != 49 && act != 50) {
			cout << "Некоректный ввод!\nДля начала игры нажмите - 1. Для выхода - 2\nВаше действие:\n";
			act = _getch();
		}
		if (act == 50) {
			cout << "Вы решили выйти! Спасибо за посещение!\n";
			return 2;
		}
		start();
	}
	return 0;
}

void original_digit(int* mas, int pos) {
	int povt = 0;
	int dig;
	while (1) {
		povt = 0;
		dig = rand() % 10;
		for (int i = 0; i < pos; i++) {
			if (mas[i] == dig) {
				povt++;
			}
		}
		if (povt == 0) {
			mas[pos] = dig;
			break;
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	menu();
	return 0;
}