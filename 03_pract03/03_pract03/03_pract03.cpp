#include <iostream>
#include <list>
#include <string>
#include <algorithm>

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
	const int size = 10000;
	list<T> HT[10000];

	int hash(const T& n) {
		return n.number % size;
	}

	int hash(int num) {
		return num % size;
	}

public:

	void add(const T& n) {
		HT[hash(n)].push_back(n);
		cout << "Index = " << hash(n.number)<<endl;
	}

	void output() {
		for (int i = 0; i < size; ++i) {
			for (T elem: HT[i])
				elem.output();
		}
	}

	T find(int num) {
		for (T elem : HT[num % size]) {
			if (elem.number == num) return elem;
		}
		return T("No item", 0);
	}

	void del(int num) {
		HT[hash(num)].erase(remove_if(HT[hash(num)].begin(), HT[hash(num)].end(), [num](const T elem) {
			return elem.number == num;
			}), HT[hash(num)].end());
	}
};

int main() {
	HashTable<Item> HT;
	HT.add(Item("Bicycle", 286841));
	HT.add(Item("Moto", 273783));
	HT.add(Item("Ball", 200000));
	HT.add(Item("Kinder", 338949));
	HT.add(Item("Cactus", 100000));
	cout << endl << "Search" << endl << endl;
	cout<< HT.find(286841).name << endl;
	cout << HT.find(199999).name << endl;
	cout << HT.find(100000).name << endl << endl;
	cout << "HashTable before" << endl << endl;
	HT.output();
	HT.del(273783);
	cout << endl << "HashTable after" << endl << endl;
	HT.output();
}