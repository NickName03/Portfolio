// oop.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <random>
#include <string.h>
#include <Windows.h>
using namespace std;

// определение функции проверки на то, пустая ли указанная клетка
bool is_Empty(vector<string> field, int x, int y);

class Creature abstract {
protected:
	int x;
	int y;
	double hungry;

public:
	Creature() {
		RandCoords();
		hungry = 5;
	}
	Creature(vector<string> field) {
		RandCoords(field);
		hungry = 5;
	}
	virtual ~Creature() { }
	int GetX() { return x; }
	int GetY() { return y; }
	bool GetL() { if (hungry > 0) return 1; else return 0; }
	double GetH() { return hungry; }
	void SetX(int _x) { x = _x; }
	void SetY(int _y) { y = _y; }
	void RandCoords() {
		x = rand() % 10;
		y = rand() % 10;
	}
	// генерация случайных координат с проверкой на то, свободна ли сгенерированная позиция
	void RandCoords(vector<string> field) { 
		mark:
		x = rand() % 10;
		y = rand() % 10;
		if (!is_Empty(field, x, y)) goto mark;
	}
	void Eat() { hungry += 0.2; }
	void Move(vector<string> field) {
	mark:
		// выбор направления
		int a = rand() % 5 + 1;
		// проверка есть ли возможность сместиться в сгенерированном направлении
		switch (a) {
		case 1: if (y <= 0 || !(is_Empty(field, x ,y - 1))) { goto mark; } // если нет, то новая генерация
			  else { y -= 1; } // смещение
			  break;
		case 2: if (x >= 9 || !(is_Empty(field, x + 1, y))) { goto mark; }
			  else { x += 1; }
			  break;
		case 3: if (y >= 9 || !(is_Empty(field, x, y + 1))) { goto mark; }
			  else { y += 1; }
			  break;
		case 4: if (x <= 0 || !(is_Empty(field, x - 1, y))) { goto mark; }
			  else { x -= 1; }
			  break;
		case 5: // остается на том же месте с небольшим штрафом
			  hungry += 0.1; // плюс, потому что ниже отнимется в любом случае
			  break;
		}
		hungry -= 0.2;
	}
};

class Plant : public Creature {
public:
	Plant() : Creature() {}
	Plant(vector<string> field): Creature(field) { }
	~Plant() {}
	void Dead() { this->~Plant(); }
	void Move(vector<string> field) { hungry -= 1; }
};

class Herbivore : public Creature {
public:
	Herbivore() : Creature() { hungry = 1; }
	Herbivore(vector<string> field) : Creature(field) { hungry = 1; }
	~Herbivore() {}
	void Dead() { this->~Herbivore(); }
	// функции, которые нужны для другого класса, но так как я использую шаблоны, нужны и тут. Костыль, получается
	bool Reproduction() { return 1; }
	void Not_Reproduct() { }
};

class Predator : public Creature {
	bool reproduction; // новое поле - показатель того, может ли родиться потомство
public:
	Predator() : Creature() {
		hungry = 1;
		reproduction = 1;
	}
	Predator(vector<string> field): Creature(field) {
		hungry = 1;
		reproduction = 1;
	}
	~Predator() {}
	void Dead() { this->~Predator(); }

	bool Reproduction() { return reproduction; }
	void Not_Reproduct() { reproduction = 0; }
};

// функция, определенная в самом начале
bool is_Empty(vector<string> field, int x, int y) {
	if (field[x][y] == '-') return 1;
	else return 0;
}

// создание нового обхекта и запись его в вектор
template <typename T>
void new_creature(vector<T>& creature) {
	T n;
	creature.push_back(n);
}

// запись в поле местоположение всех действующих существ
template <typename T>
void printCreature(vector<T> creature, vector<string>& field, char c) {
	int x, y = 0;
	for (int i = 0; i < creature.size(); i++) {
		x = creature[i].GetX();
		y = creature[i].GetY();
		field[x][y] = c;
	}
}

void PrintField(vector<Plant> &carrot, vector<Herbivore> &rabbit, vector<Predator> &wolf, vector<string> &field) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) 
			field[i][j] = '-';
	}
	printCreature(carrot, field, '*');
	printCreature(rabbit, field, 'r');
	printCreature(wolf, field, 'w');
	for (int i = 0; i < 10; i++) 
		cout << "\t\t" << field[i] << endl;
}

// создание нескольких объектов и запись их в поле
template <typename T>
void pos(vector<T> &creature, char c, vector<string> &field, int count) {
	T buf = T(field);
	int x, y = 0;
	for (int i = 0; i < count; i++) {
		creature.push_back(buf);
		x = buf.GetX();
		y = buf.GetY();
		field[x][y] = c;
		buf = T(field);
	}
}

template <typename T>
void Move(vector<T>& creature, vector<string>& field) {
	for (int i = 0; i < creature.size(); i++) {
		creature[i].Move(field);
		if (!(creature[i].GetL())) {
			creature[i].Dead();
			creature.erase(creature.begin() + i);
		}
	}
}

// генерация новых существ при определенных условиях
template<typename T>
void check_new_creature(vector<T>& creature, vector<string>& field) {
	int x, y = 0;
	T n;
	string clas = typeid(n).name();
	// по условию на поле должно быть как минимум 5 волков. если их меньше, новые появляются на границе поля
	if (clas == "class Predator") {
		while (creature.size() < 5) {
			// генерация координат на границе поля
		mark:
			x = rand() % 10;
			if (x == 0 || x == 9) y = rand() % 10;
			else {
				if (rand() % 2 == 1) y = 9;
				else y = 0;
			}
			if (!is_Empty(field, x, y)) goto mark;
			// само создание в приемлемых координатах
			new_creature(creature);
			creature.back().SetX(x);
			creature.back().SetY(y);
		}
	}
	// раз в несколько жизненных циклов появляется новое растение
	if (clas == "class Plant" && (rand() % 3) == 1) new_creature(creature);
	// также было добавлено условие, по которому, если все травоядные умерли, появляются ещё трое
	if (clas == "class Herbivore" && creature.size() == 0) pos(creature, 'r', field, 3);
}
// тот, кого едят        тот, кто ест    т.е передается растение и травоядное или травоядное и хищник
template <typename T, typename T2>
void Eat(vector<T>& eaten, vector<T2>& eating, vector<string> &field) {
	string clas = typeid(eating[0]).name();
	int xr, yr, xw, yw, x, y, ate = 0;
	// проверяем каждого едока
	for (int i = 0; i < eating.size(); i++) {
		ate = 0;
		xw = eating[i].GetX();
		yw = eating[i].GetY();
		// может ли он съест какую-нибудь добычу
		for (int j = 0; j < eaten.size(); j++) {
			xr = eaten[j].GetX();
			yr = eaten[j].GetY();
			x = xw - xr;
			y = yw - yr;
			// если добыча находится в клетках, куда едок может пойти
			if ((x == -1 && y == 0) || (x == 0 && y == 1) || (x == 1 && y == 0) || (x == 0 && y == -1)) {
				// он ест и занимает её место
				eating[i].SetX(xr);
				eating[i].SetY(yr);
				eating[i].Eat();
				eaten[j].Dead();
				eaten.erase(eaten.cbegin() + j);
				// флаг для того, чтобы понять, выполнилось ли это условие
				ate = 1;
				if (clas == "class Predator") {
					// может ли хищник совершить второй ход, если он всё ещё голоден (по заданному условию)
					if (eating[i].GetH() < 0.5) i--;
					else { 
						// и если он не голоден и может дать потомство, то он размножается
						if (eating[i].GetH() > 1 && eating[i].Reproduction()) {
							T2 n;
							n.SetX(xw);
							n.SetY(yw);
							n.Move(field);
							eating.push_back(n);
							eating[i].Not_Reproduct(); // по условию он может размножится только один раз
						}
					}
				} // досрочный выход, так как если ктото съел другого это уже действие и ход определенного существа закончен
				break;
			}
		}
		// если едок не поел, он просто перемещается
		if (!ate) {
			eating[i].Move(field);
			// если он умирает в процессе, то, т.к размер вектора уменьшится, нужно остатся на текущей позиции
			if (!(eating[i].GetL())) {
				eating[i].Dead();
				eating.erase(eating.cbegin() + i);
				i--;
			} // если это хищник, то снова проверка на то, может он сходить второй раз или нет
			else if (clas == "class Predator" && eating[i].GetH() < 0.5) i--;
		}
	}
	// по условию кроли размножается с вероятностью 25%
	if (clas == "class Herbivore" && (rand() % 4) == 1) {
		T2 n;
		// чтобы появился рядом с "родителем"
		n.SetX(xw);
		n.SetY(yw);
		n.Move(field);
		eating.push_back(n);
	}
}

void game() {
	vector<Plant> carrot; vector<Herbivore> rabbit; vector<Predator> wolf;
	vector<string> field(10, "----------");
	// генерация начальной конфигурации со случайным количество растений и травоядных, а также с 5 хищниками
	int random = rand() % 9 + 1;
	pos(carrot, '*', field, random);
	random = rand() % 9 + 1;
	pos(rabbit, 'r', field, random);
	pos(wolf, 'w', field, 5);
	while (true) {
		system("cls");
		PrintField(carrot, rabbit, wolf, field);
		Move(carrot, field); 
		Eat(carrot, rabbit, field);
		Eat(rabbit, wolf, field);
		check_new_creature(carrot, field);
		check_new_creature(rabbit, field);
		check_new_creature(wolf, field);
		cout << endl;
		system("pause");
	}
}

int main()
{
	srand(time(NULL));
	game();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
