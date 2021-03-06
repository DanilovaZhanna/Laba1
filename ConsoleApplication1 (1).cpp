//  29. В заданной матрице вывести р-ю строку и q-й столбец.

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Ввод номера
int InputNumber(const char *txt, int min, int max) 
{
	int num;
	cout << txt << endl;
	cin >> num;
	while ((num < min) || (num > max))
	{
		cout << "Недопустимое значение" << endl;
		cin >> num;
	}
	return num;
}

// Ввод размерности из файла
void InputMatrSizeFile(ifstream &in, int &n, int &m)
{
	if (in.is_open())
	{
		in >> n;
		in >> m;
	}
}

// Счтение матрицы из файла
void InputMatrFile(ifstream &in, int** matr, int n, int m)
{
	if (in.is_open())
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				in >> matr[i][j];
	}
}

// Вывод матрицы
void PrintMatr(int** matr, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << matr[i][j] << ' ';
		cout << endl;
	}
}

//вывод результата в файл(p строка, q столбец)
void OutputResFile(int **matr, int n, int m, int p, int q)
{
	ofstream FileOut("output.txt");
	if (FileOut.is_open())
	{
		FileOut << p << "-я cтрока:" << endl;
		for (int j = 0; j < m; j++)
			FileOut << matr[p - 1][j] << " ";
		FileOut << endl;
		FileOut << q << "-й cтолбец:" << endl;
		for (int i = 0; i < n; i++)
			FileOut << matr[i][q - 1] << endl;
	}
	FileOut.close();
}


//вывод результата в консоль
void OutputResKey(int **mas, int n, int m, int p, int q)
{
	cout << p << "-я cтрока:" << endl;
	for (int j = 0; j < m; j++)
		cout << mas[p - 1][j] << " ";
	cout << endl;
	cout << q << "-й cтолбец:" << endl;
	for (int i = 0; i < n; i++)
		cout << mas[i][q - 1] << endl;
}

// Через массив указателей создаем матрицу введенного размера
int** CreateMatr(int n, int m)
{
	int **A; 
	A = new int *[n];
	for (int i = 0; i < n; i++) {
		A[i] = new int[m];
	}
	return A;
}

// Ввод матрицы с клавиатуры
void InputMatrKey(int** mas, int &n, int &m)
{
	n = InputNumber("Введите количество строк", 1, 50);
	m = InputNumber("Введите количество столбцов", 1, 50);
	for (int i = 0; i < n; ++i)
		mas[i] = new int[m];
	cout << "Заполните массив: " << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> mas[i][j];
}

//выбор пункта меню ввода
int SelectInputMenuItem(void)
{
	cout << "1 - Ввод массива из консоли" << endl;
	cout << "2 - Ввод массива из файла" << endl;
	return InputNumber("0 - выход", 0, 2);
}
//выбор пункта меню вывода результата
int SelectResultMenuItem(void)
{
	cout << "1 - Вывести результат в консоль" << endl;
	cout << "2 - Вывести результат в файл" << endl;
	return InputNumber("0 - выход", 0, 2);
}


int main()
{
	// Русские буквы
	setlocale(LC_ALL, "Russian");
	ifstream FInput("input.txt");

	int n, m, // Размерность матрицы
		p, q; // строчка и столбец которые надо вывести

	int** Matr = new int*[0];

	int MenuItem = -1;
	MenuItem = SelectInputMenuItem();
	switch (MenuItem)
	{
	case 1:
		InputMatrKey(Matr, n, m);
		break;
	case 2:
		InputMatrSizeFile(FInput, n, m);
		Matr = CreateMatr(n, m);
		InputMatrFile(FInput, Matr, n, m);
		PrintMatr(Matr, n, m);
		FInput.close();
		break;
	default:
		return 0;
	}

	p = InputNumber("Введите номер строки (p):", 1, n);
	q = InputNumber("Введите номер столбца (q):", 1, m);

	int SubMenuItem = -1;
	SubMenuItem = SelectResultMenuItem();
	switch (SubMenuItem)
	{
	case 1:
		OutputResKey(Matr, n, m, p, q);
		break;
	case 2:
		OutputResFile(Matr, n, m, p, q);
		break;
	default:
		return 0;
	}
	return 0;
}