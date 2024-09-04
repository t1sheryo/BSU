#include <iostream>
#include <string>
using namespace std;

void main() {
	setlocale(LC_ALL, ".1251");
	int n, count = 0, digit, numb, index;
	cout << "Введите значение вашего натурального числа: \n";
	cin >> n;
	while (n <= 0) {
		cout << "Ошибка! Введите натуральное число: ";
		cin >> n;
		cout << "\n";
	}
	string s = to_string(n), str_digit;
	for (int i = 0; i < 10; i++) {
		count = 0;
		numb = n;
		while (numb != 0) {
			digit = numb % 10;
			numb /= 10;
			if (i == digit) {
				count++;
			}
		}
		if (count % 2 == 1) {
			digit = i;
			str_digit = to_string(digit);
			while (count > 0) {
				index = s.find(str_digit);
				s.erase(index, 1);
				count--;
			}
		}
	}
	if (s.empty())
		n = 0;
	else
		n = stoi(s);
	cout << "Ваше новое число: " << n;
}