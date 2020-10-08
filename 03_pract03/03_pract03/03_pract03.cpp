#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class Item {
public:
	string name;
	int number;

	Item(string name, int number) {
		this->name=name;
		this->number = number;
	}

	void output() {
		cout << this->name << "\t" << this->number << endl;
	}
};

template<typename T>
class HashTable {
	vector<list<T>> HT;
	int size = 10;
	int hash(const T& num) {
		return num.number % size;
	}

	int hash(int num) {
		return num % size;
	}

public:

	HashTable() {
		size = 10;
		HT.resize(size);
	}

	void add(const T& num) {
		HT[hash(num)].push_back(num);
		cout << "Index = " << hash(num) << endl;
		if (HT[hash(num)].size() > 3) rehash();
	}

	void rehash() {
		queue<T> qe;
		for (int i = 0; i < size; ++i) {
			for (T elem : HT[i]) {
				qe.push(elem);
			}
		}
		size = size * 2 + 1;
		HT.clear();
		HT.resize(size);
		while (!qe.empty()) {
			this->add(qe.front());
			qe.pop();
		}
	}

	void output() {
		for (int i = 0; i < size; ++i) {
			for (T elem : HT[i]) {
				elem.output();
			}
		}
	}

	T find(int num) {
		for (T elem : HT[hash(num)]) {
			if (elem.number == num) return elem;
		}
		return T("No item", 0);
	}

	void del(int num) {
		HT[hash(num)].erase(remove_if(HT[hash(num)].begin(), HT[hash(num)].end(), [num](const T t) {
			return t.number == num;
			}), HT[hash(num)].end());
	}
};

int main() {
	HashTable<Item> HT;
	HT.add(Item("Train", 101021));
	HT.add(Item("Auto", 666771));
	HT.add(Item("Mouse", 838381));
	HT.add(Item("Bicycle", 286841));
	HT.add(Item("Moto", 273783));
	HT.add(Item("Ball", 200000));
	HT.add(Item("Kinder", 338949));
	HT.add(Item("Cactus", 100000));
	cout << endl << "Search\n\n";
	cout << HT.find(286841).name << endl;
	cout << HT.find(199999).name << endl;
	cout << HT.find(100000).name << "\n\n";
	cout << "HashTable before\n\n";
	HT.output();
	HT.del(273783);
	cout << endl << "HashTable after\n\n";
	HT.output();
}