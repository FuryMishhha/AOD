#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <clocale>
#include <Windows.h>
using namespace std;

struct Letter { //Создание структуры
	char symb;
	int quantity;
	double frequency;
	Letter* left;
	Letter* right;
	string code = "";
	Letter(char c, int kol); //Создание буквы
	Letter(Letter* left, Letter* right); //Создание дерева
};

void input(); //Ввод строки
void make_tree(); //Создание дерева
void set_code(Letter* let); //Определение кодов
void out_code(Letter* let); //Вывод алфавита
void out_str(); //Вывод закодированной строки
void statistic(); //Вывод статистики

Letter::Letter(char c, int kol) {
	this->symb = c;
	this->quantity = kol;
}

Letter::Letter(Letter* left, Letter* right) {
	symb = 0;
	this->left = left;
	this->right = right;
	this->frequency = left->frequency + right->frequency;
	this->quantity = left->quantity + right->quantity;
}

string str;
vector<Letter*> alphabet;
vector<Letter*> tree;
int len = 0;

void input() {
	getline(cin, str);
	bool flag;
	for (int i = 0; i < str.size(); ++i) {
		flag = false;
		for (int j = 0; j < alphabet.size(); ++j) {
			if (alphabet[j]->symb == str[i]) {
				++alphabet[j]->quantity;
				flag = true;
			}
		}
		if (!flag) alphabet.push_back(new Letter(str[i], 1));
	}
	for (int i = 0; i < alphabet.size(); ++i) alphabet[i]->frequency = (double)alphabet[i]->quantity / str.size();
	sort(alphabet.begin(), alphabet.end(), [](Letter* l1, Letter* l2) {
		return l1->frequency > l2->frequency;
		});
}

void set_code(Letter* let) {
	if (let->symb == 0) { 
		let->left->code = let->code + '0';
		let->right->code = let->code + '1';
		set_code(let->left);
		set_code(let->right);
	}
	else return;
}

void out_code(Letter* let) {
	for (int i = 0; i < alphabet.size(); i++)
		cout << alphabet[i]->symb << " " << alphabet[i]->code << endl;
}

void make_tree() {
	double min;
	int ind_left, ind_right;
	tree.resize(alphabet.size());
	for (int i = 0; i < tree.size(); ++i) tree[i] = alphabet[i];
	while (tree.size() != 1) {
		min = 2;
		for (int i = tree.size() - 1; i >= 0; --i) {
			for (int j = i - 1; j >= 0; --j) {
				if (tree[i]->frequency + tree[j]->frequency < min) {
					min = tree[i]->frequency + tree[j]->frequency;
					ind_left = j;
					ind_right = i;
				}
			}
		}
		tree.push_back(new Letter(tree[ind_left], tree[ind_right]));
		tree.erase(tree.begin() + ind_right);
		tree.erase(tree.begin() + ind_left);
	}
	set_code(tree[0]);
}

void out_str() {
	len = 0; 
	for (int i = 0; i < str.size(); ++i) { 
		for (int j = 0; j < alphabet.size(); ++j) {
			if (str[i] == alphabet[j]->symb) { 
				cout << alphabet[j]->code << ' '; 
				len += alphabet[j]->code.size();
			}
		}
	}
}

void statistic() {
	cout << "\nХранить данные в предложенном варианте в " << (double)8 * str.size() / (len) << " раз выгоднее по сравнению с кодировкой ASCII";
	int count = 0;
	for (int pow = 1; pow < alphabet.size(); pow *= 2) ++count;
	cout << "\nВ " << (double)(count * str.size()) / len << " раз выгоднее по сравнению с равномерным кодированием";
	cout << "\nСредняя длина = " << (double)len / str.size();
	double disp = 0;
	for (int i = 0; i < str.size(); ++i) {
		for (int j = 0; j < alphabet.size(); ++j) {
			if (str[i] == alphabet[j]->symb)
				disp += (alphabet[j]->code.size() - (double)len / str.size()) * (alphabet[j]->code.size() - (double)len / str.size());
		}
	}
	disp /= str.size(); 
	cout << "\nДисперсия = " << disp;
}

int main() {
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите строку для кодирования:\n";
	input();
	make_tree(); 
	cout << "\nАлфавит:\n";
	out_code(tree[0]);
	cout << "\nЗакодированная строка:\n";
	out_str(); 
	cout << '\n';
	cout << "\nСтатистика:\n";
	statistic();
	cout << '\n';
}
/*
 
Вывод программы относительно варианта: 
 
Введите строку для кодирования:
Панченков Михаил Александрович

Алфавит:
а 010
н 000
и 001
ч 1110
е 0110
к 0111
о 1010
в 1011
  1000
л 1001
П 11110
М 111110
х 111111
А 11010
с 11011
д 11000
р 11001

Закодированная строка:
11110 010 000 1110 0110 000 0111 1010 1011 1000 111110 001 111111 010 001 1001 1000 11010 1001 0110 0111 11011 010 000 11000 11001 1010 1011 001 1110

Статистика:

Хранить данные в предложенном варианте в 2 раз выгоднее по сравнению с кодировкой ASCII
В 1.25 раз выгоднее по сравнению с равномерным кодированием
Средняя длина = 4
Дисперсия = 0.733333
*/