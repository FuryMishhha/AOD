#include <iostream>
#include <queue>
using namespace std;

void input(int *mas,int n) {
    for (int i = 0; i < n; i++)
        cin >> mas[i];
}

void output(int *mas, int n) {
    for (int i = 0; i < n; i++)
        cout << mas[i] << ' ';
}

void Sort(int a[], int n) {
    queue <int> arr[10];
    bool f = false;
    int ch = 1;
    while (!f) {
        f = true;
        for (int i = 0; i < n; i++) {
            arr[a[i] / ch % 10].push(a[i]);
            if (a[i] / ch > 0)
                f = false;
        }
        if (!f) {
            int ind = 0;
            for (int b = 0; b < 10; b++) {
                while (!arr[b].empty()) {
                    a[ind++] = arr[b].front();
                    arr[b].pop();
                }
            }
            ch = ch * 10;
        }
    }
}

int main()
{
    setlocale(0, "");
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    int *mas = new int[n];
    cout << "Введите элементы массива: ";
    input(mas,n);
    Sort(mas, n);
    cout << "Отсортированный массив: ";
    output(mas, n);
}
