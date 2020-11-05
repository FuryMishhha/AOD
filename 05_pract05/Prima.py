s=1000000
k=int(input("Введите количество вершин графа: "))
a=[]
b = [False] * k
edge=0
m_s=0
print("Введите матрицу смежности графа:") #Ввод матрицы для графа
for i in range(k):
    row = input().split()
    for i in range(len(row)):
        row[i] = int(row[i])
    a.append(row)
b[0]=True
print("Границы : Вес")
while edge<k-1: #Построение остовного дерева
    minn=s
    x=0
    y=0
    for i in range (k): #Алгоритм вычисления наименьшего веса
        if b[i]:
            for j in range (k):
                if not b[j] and a[i][j]:
                    if minn>a[i][j]:
                        minn=a[i][j]
                        x=i
                        y=j
    print(x+1,"---",y+1," : ",a[x][y]) #Вывод ветвей и веса между ними
    m_s+=a[x][y]
    b[y]=True
    edge+=1
print("Минимальная сумма = ", m_s) #Вывод минимального веса для остовного дерева
"""
14.2.1
0 1 2 0 10
1 0 0 3 6
2 0 0 4 7
0 3 4 0 11
10 6 7 11 0
Границы : Вес
1 --- 2  :  1
1 --- 3  :  2
2 --- 4  :  3
2 --- 5  :  6
Минимальная сумма =  12

======================

14.2.2
0 7 0 2 0 4
7 0 1 2 0 0
0 1 0 2 3 0
2 2 2 0 6 1
0 0 3 6 0 8
4 0 0 1 8 0
Границы : Вес
1 --- 4  :  2
4 --- 6  :  1
4 --- 2  :  2
2 --- 3  :  1
3 --- 5  :  3
Минимальная сумма =  9

======================

14.2.3
0 20 0 0 0 23 1
20 0 15 0 0 0 4
0 15 0 3 0 0 9
0 0 3 0 17 0 16
0 0 0 17 0 28 25
23 0 0 0 28 0 36
1 4 9 16 25 36 0
Границы : Вес
1 --- 7  :  1
7 --- 2  :  4
7 --- 3  :  9
3 --- 4  :  3
4 --- 5  :  17
1 --- 6  :  23
Минимальная сумма =  57

======================

14.2.4
0 2 6 4 0 0
2 0 0 7 8 0
6 0 0 8 0 5
4 7 8 0 2 8
0 8 0 2 0 4
0 0 5 8 4 0
Границы : Вес
1 --- 2  :  2
1 --- 4  :  4
4 --- 5  :  2
5 --- 6  :  4
6 --- 3  :  5
Минимальная сумма =  17
"""

