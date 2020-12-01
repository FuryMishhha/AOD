#include <iostream>
#include <vector>
using namespace std;
class Equation {
private:
	vector<vector<int>> multiply;
	vector<vector<int>> brackets;
	vector<int> matrixes;
	string equation;
public:
	Equation() {
		int size, temp; // Количество матриц и переменная для ввода
		cout << "Введите кол-во матриц:\n";
		cin >> size; size += 1;
		cout << "\nВведите последовательность размерностей матриц:\n";
			for (int i = 0; i < size; i++) {
				cin >> temp;
				matrixes.push_back(temp);
			}
	}
	void getOrder() {
		int n = matrixes.size() - 1;
		for (int i = 0; i < n; i++) {
			multiply.push_back(vector <int>());
			brackets.push_back(vector <int>());
			for (int a = 0; a < n; a++) { 
				multiply[i].push_back(0);
				brackets[i].push_back(0);
			}
		}
		int j;
		for (int l = 1; l < n; l++) { 
			for (int i = 0; i < n - l; i++) {
				j = i + l;
				multiply[i][j] = INT_MAX;
				for (int k = i; k < j; k++) {
					int q = multiply[i][k] + multiply[k + 1][j] + matrixes[i] * matrixes[k + 1] * matrixes[j+ 1];
					if (q < multiply[i][j]) {
						multiply[i][j] = q;
						brackets[i][j] = k;
					}
				}
			}
		}
		form(0, n - 1, 0);
		cout << "\nОптимальный порядок: " << equation << "\n";
	}
	void form(int i, int j, int flag) {
		if (i == j) equation += "A";
		else {
			if (flag != 0) equation += "(";
			form(i, brackets[i][j], 1);
			equation += "*";
			form(brackets[i][j] + 1, j, 1);
			if (flag != 0) equation += ")";
		}
	}
};
int main() {
	setlocale(LC_ALL, "Russian");
	Equation AOD;
	AOD.getOrder();
}
/*
Введите кол-во матриц:
6

Введите последовательность размерностей матриц:
5 10 3 12 5 50 6

Оптимальный порядок: (A*A)*((A*A)*(A*A))
*/