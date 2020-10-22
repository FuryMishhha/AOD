#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct numbers {
	int number;
	string name;
	string surname;
	string second_name;
	string address;
};
vector<numbers>num;
void print_data(numbers n) {
	cout << "Number: " << n.number << " | Address: " << n.address << " | Name: " << n.name << " | Surname: " << n.surname << " | Second Name: " << n.second_name << endl;
}
void Read_data_from_file() {
	numbers temp;
	ifstream in("input.txt");
	while (!in.eof()) {
		in >> temp.number >> temp.name >> temp.surname >> temp.second_name >> temp.address;
		num.push_back(temp);
	}
}
void Read_data_from_binary_file() {
	ifstream fin("output.txt", istream::binary);
	int size = num.size();
	num.clear();
	num.resize(size);
	for (int i = 0; i < size; i++)
		fin.read((char*)&num.at(i), sizeof(numbers));
	fin.close();
}
void Write_data_to_binary() {
	ofstream fout("output.txt", ostream::binary);
	for (int i = 0; i < num.size(); ++i)
		fout.write((char*)&num.at(i), sizeof(numbers));
	fout.close();
}
void Output() {
	for (int i = 0; i < num.size(); i++)
		print_data(num[i]);
}
void Zad_1() {
	int a;
	cout << "\n---New List---\nInput 3 first digits for numbers you want to create new list: ";
	cin >> a;
	for (int i = 0; i < num.size(); i++) {
		if ((num[i].number) / 1000000 != a) {
			num.erase(num.begin() + i);
			i--;
		}
	}
	Write_data_to_binary();
	cout << "\n---New List output---\n";
	Output();
}
void Zad_2() {
	int a;
	cout << "\n---Delete---\nInput first digit for numbers you want to delete from list: ";
	cin >> a;
	for (int i = 0; i < num.size(); i++) {
		if ((num[i].number) / 100000000 == a) {
			num.erase(num.begin() + i);
			i--;
		}
	}
	Write_data_to_binary();
	cout << "\n---List after delete---\n";
	Output();
}
int main() {
	Read_data_from_file();
	Write_data_to_binary();
	cout << "---List---\n";
	Output();
	Zad_2();
	Zad_1();
}