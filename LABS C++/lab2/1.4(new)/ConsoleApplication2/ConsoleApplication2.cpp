#include <iostream>
using namespace std;

void main() {
    setlocale(LC_ALL, ".1251");
    unsigned long long num, new_num = 0, copy_num, count_2 = 0, left, right, degree_l, degree_r;
    int digit, count;
    cout << "Введите ваше натуральное число: ";
    cin >> num;
    while (num <= 0) {
        cout << "Ошибка! Введите натуральное число еще раз: ";
        cin >> num;
    }
    for (int i = 0; i < 10; ++i) {
        count = 0;
        count_2 = 0;
        copy_num = num;
        while (copy_num != 0) {
            digit = copy_num % 10;
            copy_num /= 10;
            count_2++;
            if (digit == i) {
                count++;
            }
        }
        /*cout << i << "  " << count << "  " << count_2 << "\n";*/
        if (count % 2 == 1) {
            copy_num = num;
            new_num = 0;
            while (count != 0) {
                while (count_2 != 0) {
                    degree_l = pow(10, count_2);
                    degree_r = pow(10, count_2 - 1);
                    left = copy_num / degree_l;
                    right = copy_num % degree_r;
                    digit = (copy_num - left * degree_l - right) / degree_r;
                    if (digit == i) {
                        new_num = left * degree_r + right;
                        count--;
                    }
                    /*cout << copy_num << "  " << left << "  " << right << "  " << digit << "\n";*/
                    count_2--;
                }
            }
            num = new_num;
        }
    }
    cout << "Ваше готовое число: " << num;
}