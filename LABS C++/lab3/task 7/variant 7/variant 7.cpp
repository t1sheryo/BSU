#include <iostream>
using namespace std;

int MAX_ABS(int* arr, int n) {
	int max_abs = abs(*arr);
	int number = 0;
	for (int i = 0; i < n; ++i) {
		if (abs(*(arr + i)) > max_abs) {
			max_abs = *(arr + i);
			number = i;
		}
	}
	cout << "\nМаксимальное по модулю число находится на " << number + 1 << " позиции и равно " << max_abs << endl;
	return 0;
}

int SUM_BETWEEN_TWO_POSITIVE(int* arr, int n) {
	int sum = 0, left = -1, right = -1, count = 1;
	if (n <= 2) {
		cout << "Ошибка! Слишком мало элементов!";
	}
	else {
		for (int i = 0; i < n; ++i) {
			if (*(arr + i) > 0) {
				switch (count) {
				case 1:
					left = i;
					count++;
					break;
				case 2:
					right = i;
					count++;
					break;
				default:
					break;
				}
			}
		}
	}
	if (left == -1 || right == -1) {
		cout << "Недостаточно положительных элементов";
	}
	else {
		for (left + 1; left + 1 < right; ++left) {
			sum += *(arr + left + 1);
		}
	}
	cout << "Сумма элементов массива, расположенных между первым и вторым положительными элементами = " << sum << endl;
	return 0;
}

int main() {
	setlocale(LC_ALL, ".1251");
	srand(time(NULL));
	const int max_n = 20;				/*max_n - максимальный размер массива*/
	int n, way, count = 0, count_most = 0, rep = 0, temp = 0, copy_count = 0;				/* n - размер массива*/
	int arr[max_n];
	cout << "Сколько элементов должно быть в вашем массиве?(максимальное значение = " << max_n << "): ";
	cin >> n;
	while (n < 1 || n > max_n) {
		cout << "Ошибка! Количество элементов массива должно быть больше 0 и меньше " << max_n << "! Введите значение удовлетворяющее условиям: ";
		cin >> n;
	}
	cout << "Каким способом вы хотите заполнить массив:\n1) С помощью клавиатуры\n2) С помощью генератора рандомных чисел\n";
	cin >> way;
	while (way != 1 && way != 2) {
		cout << "Введите корректное число(1 или 2)";
		cin >> way;
	}
	switch (way) {
	case 1:
		for (int i = 0; i < n; ++i) {
			cout << "Введите значение " << i + 1 << " элемента массива: ";
			cin >> arr[i];
		}
		break;
	case 2:
		cout << "Введите левую границу генерации рандомных чисел: ";
		int max_left, max_right;				/*max_left - левая граница, max_right - правая граница*/
		cin >> max_left;
		cout << "Введите правую границу генерации рандомных чисел: ";
		cin >> max_right;
		while (max_left >= max_right) {
			cout << "Ошибка! Введите такие числа, чтобы левая граница была меньше правой:\n";
			cin >> max_left >> max_right;
		}
		for (int i = 0; i < n; ++i) {
			arr[i] = max_left + rand() % ((max_right + 1) - max_left);
		}
		break;
	default:
		cout << "Ошибка!";
		break;
	}
	cout << "Ваш массив: ";
	for (int i = 0; i < n; ++i) {
		cout << arr[i] << "  ";
	}
	MAX_ABS(arr, n);
	SUM_BETWEEN_TWO_POSITIVE(arr, n);
	int most_freq = arr[0];
	while (rep < n) {
		count_most = 1;
		for (int i = rep; i < n; ++i) {
			count = 1;
			for (int x = 0; x < n; ++x) {
				if (arr[i] == arr[x]) {
					if (i != x)
						count++;
				}
			}
			if (count > count_most) {
				count_most = count;
				most_freq = arr[i];
				/*cout << "Самый часто повторяющийся элемент: " << most_freq << "\nКоличество его повторений: " << count << endl;*/
			}
		}
		if (count_most < 2) {
			cout << "Повторяющиеся элементы не найдены!\n";
			break;
		}
		copy_count = count;
		while (count > 0) {
			int i = rep;
			for (int a = rep; a < n; ++a) {
				if (arr[a] == most_freq) {
					temp = arr[i];
					arr[i] = arr[a];
					arr[a] = temp;
					count--;
					i++;
				}
			}
		}
		rep += copy_count;
	}
	cout << "Ваш новый массив: ";
	for (int b = 0; b < n; ++b) {
		cout << arr[b] << "  ";
	}
	return 0;
}