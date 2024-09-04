#include <iostream>
#include <cmath>
using namespace std;

void main() {
	setlocale(LC_ALL, ".1251");
	int n, squared, count = 0, k, remain = 0, degree = 0;
	cout << "Введите ваше натуральное число: ";
	cin >> n;
	while (n <= 0) {
		cout << "Ошибка! Введите натуральное число: ";
		cin >> n;
	}
	for (int i = 1; i != n + 1; ++i) {
		k = i;
		count = 0;
		squared = k * k;
		while (k != 0) {
			k /= 10;
			count++;
		}
		degree = pow(10, count);
		remain = squared % degree;
		if (remain == i)
			cout << i << " ";
	}
}