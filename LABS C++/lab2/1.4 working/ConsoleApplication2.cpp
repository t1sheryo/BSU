#include <iostream>
using namespace std;

void main() {
    setlocale(LC_ALL, ".1251");
    unsigned long long num, new_num = 0, copy_num, num_count = 0, degree = 0;
    int digit, count;
    cout << "Введите ваше натуральное число: ";
    cin >> num;
    while (num <= 0) {
        cout << "Ошибка! Введите натуральное число еще раз: ";
        cin >> num;
    }
    for (int i = 0; i < 10; ++i) {
        count = 0;
        copy_num = num;
        while (copy_num != 0) {
            digit = copy_num % 10;
            copy_num /= 10;
            if (digit == i) {
                count++;
            }
        }
        cout << i << "  " << count << "\n";
        if (count % 2 == 1) {
            copy_num = num;
            new_num = 0;
            num_count = 0;
            while (copy_num != 0) {
                digit = copy_num % 10;
                copy_num /= 10;
                degree = pow(10, num_count);
                if (digit != i) {
                    if (digit != 0) {
                        new_num = degree * digit + new_num;
                        num_count++;
                    }
                    else
                        num_count++;
                }
                /*cout << new_num;*/
            }
            num = new_num;
        }
    }
    cout << "Ваше готовое число: " << num;
}