#include <iostream>
#include <string>
#include <clocale>
#include <sstream>

using namespace std;

class Changes {
public:
	static inline string* changes = new string[0];
	static inline int size = 0;
	static void push(string new_change);
	static void out();
	~Changes();
};

void Changes::push(string new_change) {
	string* copy = new string[size + 1];
	for (int i = 0; i < size; ++i) copy[i] = changes[i];
	copy[size] = new_change;
	delete[] changes;
	changes = copy;
	++size;
	//delete[] copy;
}

void Changes::out() {
	if (size == 0) {
		cout << "Замен нет";
		return;
	}
	cout << "Changes: \n";
	for (int i = 0; i < size; ++i) cout << changes[i] << '\n';
}

Changes::~Changes() {
	delete[] changes;
}

struct XIndicat {
	string num;
	bool normal = false;
	XIndicat(string num);
	XIndicat(int num);
};

XIndicat::XIndicat(string num) {
	this->num = num;
}

XIndicat::XIndicat(int num) {
	ostringstream stream;
	stream << num;
	this->num = stream.str();
}

class XTable {
public:
	static inline XIndicat** table;
	static inline int size;
	static void init(int n);
	static XIndicat* find_indicat(string num);
	static void push(string num);
};

void XTable::init(int n) {
	size = n;
	table = new XIndicat * [n];
	for (int i = 0; i < n; ++i) {
		table[i] = new XIndicat(i + 1);
	}
}

XIndicat* XTable::find_indicat(string num) {
	for (int i = 0; i < size; ++i) {
		if (table[i]->num == num) return table[i];
	}
	return new XIndicat(0);
}

void XTable::push(string num) {
	XIndicat** copy = new XIndicat * [size + 1];
	for (int i = 0; i < size; ++i) copy[i] = table[i];
	copy[size] = new XIndicat(num);
	copy[size]->normal = true;
	delete[] table;
	table = copy;
	++size;
}

struct X {
	XIndicat* indicat;
	int val;
	X(string num, int val);
	X(int num, int val);
};

X::X(string num, int val) {
	indicat = XTable::find_indicat(num);
	this->val = val;
}
X::X(int num, int val) {
	ostringstream stream;
	stream << num;
	indicat = XTable::find_indicat(stream.str());
	this->val = val;
}

struct Limitation {
	int n;
	X** x;
	string sign;
	int total;
	bool active = true;
	bool is_func;
	bool for_one_par;
	bool non_negativity = false;
	Limitation(int n, bool is_func);
	Limitation(Limitation* lim);
	Limitation(string qwe);
	void push(string num, int val);
	void out();
	~Limitation();
};

Limitation::Limitation(int n, bool is_func) {
	cout << '\n';
	this->is_func = is_func;
	this->n = n;
	x = new X * [n];
	int a;
	int count = 0;
	for (int i = 0; i < n; ++i) {
		cout << "x" << i + 1 << " = ";
		cin >> a;
		if (a != 0) ++count;
		x[i] = new X(i + 1, a);
	}
	for_one_par = (count == 1 ? true : false);
	if (!is_func) {
		cout << "sign = "; cin >> this->sign;
		cout << "total = "; cin >> this->total;
	}
	else {
		sign = "->";
		do
		{
			cout << "\n1->min\n2->max\n";
			cin >> this->total;
		} while (!(total == 1 || total == 2));
	}
}

Limitation::Limitation(Limitation* lim) {
	this->n = lim->n;
	this->active = lim->active;
	this->for_one_par = lim->for_one_par;
	this->is_func = lim->is_func;
	this->non_negativity = lim->non_negativity;
	this->sign = "<=";
	x = new X * [n];
	for (int i = 0; i < n; ++i) {
		x[i] = new X(lim->x[i]->indicat->num, -lim->x[i]->val);
	}
	this->total = -lim->total;
}

Limitation::Limitation(string qwe) {
	this->n = 1;
	x = new X * [1];
	x[0] = new X(qwe, 1);
	sign = ">=";
	this->total = 0;
	this->for_one_par = true;
	this->is_func = false;
	this->non_negativity = true;
	this->active = true;
}

void Limitation::push(string num, int val) {

	X** copy = new X * [n + 1];
	for (int i = 0; i < n; ++i) copy[i] = x[i];
	copy[n] = new X(num, val);
	copy[n]->indicat->normal = true;
	delete[] x;
	x = copy;
	++n;
}

void Limitation::out() {
	if (active) {
		for (int i = 0; i < n; ++i) {
			if (x[i]->val != 0) cout << (x[i]->val < 0 ? "" : "+") << x[i]->val << "x" << x[i]->indicat->num;
		}
		cout << sign;
		if (is_func) cout << (total == 1 ? "min" : "max");
		else cout << total;
		cout << '\n';
	}
}

Limitation::~Limitation() {
	delete[] x;
}

class Task {
public:
	int param;
	int kol;
	Limitation* function;
	Limitation** lim;
	Task();
	void func_to_standart_form();
	void check_non_neg();
	void remake_signs();
	void to_standart_form();
	void push(string num);
	void out();
	~Task();
};

Task::Task() {
	cout << "\nСколько параметров? - "; cin >> param;
	XTable::init(param);
	cout << "\nВведите функцию:";
	function = new Limitation(param, true);
	cout << "Сколько ограничений? - "; cin >> kol;
	lim = new Limitation * [kol];
	for (int i = 0; i < kol; ++i) lim[i] = new Limitation(param, false);
}

void Task::func_to_standart_form() {
	if (function->total == 1) {//->min
		for (int i = 0; i < function->n; ++i) function->x[i]->val *= -1;
		function->total = 2;//->max
	}
}

void Task::check_non_neg() {
	for (int i = 0; i < kol; ++i) {
		if (lim[i]->for_one_par && lim[i]->sign != "=") {
			for (int j = 0; j < lim[i]->n; ++j) {
				if (lim[i]->x[j]->val != 0 && lim[i]->x[j]->indicat->normal == false) {
					if (lim[i]->sign == ">=") lim[i]->x[j]->indicat->normal = true;
					else if (lim[i]->sign == "<=") {
						Changes::push("x" + lim[i]->x[j]->indicat->num + "& = -x" + lim[i]->x[j]->indicat->num);//-xn=xn&
						XTable::find_indicat(lim[i]->x[j]->indicat->num)->num = lim[i]->x[j]->indicat->num + "&";
						XTable::find_indicat(lim[i]->x[j]->indicat->num)->normal = true;
						lim[i]->sign = ">=";
						for (int k = 0; k < function->n; ++k) {
							if (function->x[k]->indicat->num == lim[i]->x[j]->indicat->num) {
								function->x[k]->val *= -1;
								break;
							}
						}
						for (int k = 0; k < kol; ++k) {
							for (int l = 0; l < lim[k]->n; ++l) {
								if (lim[k]->x[l]->indicat->num == lim[i]->x[j]->indicat->num && (i != k)) {
									lim[k]->x[l]->val *= -1;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < XTable::size; ++i) {
		if (!XTable::table[i]->normal) {
			string start = XTable::table[i]->num;
			Changes::push("x" + start + " = x" + start + "\' - x" + start + "\"");
			XTable::find_indicat(start)->num += '\'';
			XTable::push(start + "\"");
			for (int j = 0; j < function->n; ++j) {
				if (function->x[j]->indicat->num == XTable::table[i]->num && function->x[j]->val != 0) {
					function->push(start + "\"", -function->x[j]->val);
					break;
				}
			}
			for (int j = 0; j < kol; ++j) {
				if (!lim[j]->for_one_par) {
					for (int k = 0; k < lim[j]->n; ++k) {
						if (lim[j]->x[k]->indicat->num == XTable::table[i]->num && lim[j]->x[k]->val != 0) {
							lim[j]->push(start + "\"", -lim[j]->x[k]->val);
							break;
						}
					}
				}
			}
			bool need_push = true;
			for (int j = 0; j < kol; ++j) {
				if (lim[j]->for_one_par && lim[j]->sign == ">=" && lim[j]->total == 0) {
					for (int k = 0; k < lim[j]->n; ++k) {
						if (lim[j]->x[k]->val != 0 && lim[j]->x[k]->indicat->num == XTable::table[i]->num) need_push = false;
					}
				}
			}
			if (need_push) push(start + "\'");
			push(start + "\"");
		}
	}
}

void Task::remake_signs() {
	for (int i = 0; i < kol; ++i) {
		if (lim[i]->sign != "<=") {
			if (lim[i]->sign == ">=") {
				if (!lim[i]->for_one_par || lim[i]->total != 0) {
					for (int j = 0; j < lim[i]->n; ++j) lim[i]->x[j]->val *= -1;
					lim[i]->sign = "<=";
					lim[i]->total *= -1;
				}
			}
			else if (lim[i]->sign == "=") {
				lim[i]->sign = "<=";

				Limitation* additional = new Limitation(lim[i]);
				Limitation** copy = new Limitation * [kol + 1];
				for (int j = 0; j < i; ++j) copy[j] = lim[j];
				copy[i] = additional;
				for (int j = i + 1; j < kol + 1; ++j) copy[j] = lim[j - 1];
				delete[] lim;
				++kol;
				lim = copy;
				//delete[] copy;
			}
		}
	}
}

void Task::to_standart_form() {
	func_to_standart_form();
	check_non_neg();
	remake_signs();

}

void Task::push(string num) {
	Limitation** copy = new Limitation * [kol + 1];
	for (int i = 0; i < kol; ++i) copy[i] = lim[i];
	copy[kol] = new Limitation(num);
	delete[] lim;
	lim = copy;
	++kol;
}

void Task::out() {
	cout << "f: ";
	function->out();
	cout << "\nLimitations:\n";
	for (int i = 0; i < kol; ++i) lim[i]->out();
}

Task::~Task() {
	delete function;
	delete[] lim;
}

int main() {
	setlocale(LC_ALL, "");
	Task task;
	task.to_standart_form();
	cout << '\n';
	task.out();
	cout << '\n';
	Changes::out();
}
//Вывод программы
/*
Сколько параметров? - 2

Введите функцию:
x1 = 2
x2 = 7

1->min
2->max
1
Сколько ограничений? - 4

x1 = 1
x2 = 0
sign = =
total = 7

x1 = 3
x2 = 1
sign = >=
total = 24

x1 = 1
x2 = 0
sign = >=
total = 0

x1 = 0
x2 = 1
sign = <=
total = 0

f: -2x1+7x2&->max

Limitations:
-1x1<=-7
+1x1<=7
-3x1+1x2&<=-24
+1x1>=0
+1x2&>=0

Changes:
x2& = -x2
*/