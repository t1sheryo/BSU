#include <iostream>
using namespace std;

int MaxElemColumns(int** matrix, int n) {
	bool flag = true;
	int max = 0;
	for (int j = 0; j < n; ++j) {
		max = matrix[0][j];
		flag = true;
		for (int i = 0; i < n; ++i) {
			if (matrix[i][j] > 0 && flag == true)
				flag = false;
			if (matrix[i][j] > max)
				max = matrix[i][j];
		}
		if (flag == true)
			cout << "Максимальный элемент в " << j + 1 << " столбце = " << max << endl;
		else
			cout << j + 1 << " столбик содержит положительные элементы!\n";
	}
	return 0;
}

int MaxElemHighRightTriangle(int** matrix, int n) {
	int max = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - i; ++j) {
			if (matrix[i][j + i] > max)
				max = matrix[i][j + i];
		}
	}
	cout << "Максимальный элемент верхнего правого треугольника матрицы = " << max;
	return 0;
}

int main() {
	setlocale(LC_ALL, ".1251");
	srand(time(NULL));
	int way, n;
	cout << "Какую размерность своей квадратной матрицы вы хотите? ";
	cin >> n;
	int** matrix = new int* [n];
	for (int a = 0; a < n; ++a) {
		matrix[a] = new int[n];
	}
	while (n < 1) {
		cout << "Ошибка! Количество элементов матрицы должно быть больше 0! Введите значение удовлетворяющее условиям: ";
		cin >> n;
	}
	cout << "Каким способом вы хотите заполнить массив:\n1) С помощью клавиатуры\n2) С помощью генератора рандомных чисел\n";
	cin >> way;
	while (way != 1 && way != 2) {
		cout << "Введите корректное число(1 или 2): ";
		cin >> way;
	}
	switch (way) {
	case 1:
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cout << "Введите значение matrix[" << i << "][" << j << "]: ";
				cin >> matrix[i][j];
			}
		}
		break;
	case 2:
		cout << "Введите левую границу генерации рандомных чисел: ";
		int max_left, max_right;	/*max_left - левая граница, max_right - правая граница*/
		cin >> max_left;
		cout << "Введите правую границу генерации рандомных чисел: ";
		cin >> max_right;
		while (max_left >= max_right) {
			cout << "Ошибка! Введите такие числа, чтобы левая граница была меньше правой:\n";
			cin >> max_left >> max_right;
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				matrix[i][j] = rand() % (max_right - max_left + 1) + max_left;
			}
		}
		break;
	default:
		cout << "Ошибка!";
		break;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
	MaxElemColumns(matrix, n);
	MaxElemHighRightTriangle(matrix, n);
	for (int a = 0; a < n; ++a) {
		delete[] matrix[a];
	}
	delete[] matrix;
	return 0;
}