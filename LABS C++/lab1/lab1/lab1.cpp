#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

int main() {
	setlocale(LC_ALL, ".1251");
	double eps, x, res = M_PI / 2, temp, zn = 1;
	cout << "Введите значание x, больше 1, и epsilon\n";
	cin >> x >> eps;
	if (x <= 1) {
		while (x <= 1) {
			cout << "Ошибка(значение x должно быть больше 1)\n" << "Введите значение x заново\n";
			cin >> x;
		}
	}
	temp = (-1) / x;
	while (fabs(temp) >= eps) {
		res += temp;
		temp *= zn;
		zn += 2;
		temp = (-temp) / (zn * x * x);
	}
	cout << "Значение arctg(x) по таблице: " << atan(x) << "\n" << "Значение arctg(x), полученное нами: " << res;
	return 0;
}