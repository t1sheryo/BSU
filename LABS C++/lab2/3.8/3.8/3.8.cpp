#include <iostream>
using namespace std;

void main() {
    setlocale(LC_ALL, ".1251");
    int a, b, digit, num;
    bool flag;
    cout << "Введите ваше натуральные числа, которые будут границами промежутка и такие, что b > a:\n";
    cin >> a >> b;
    while (a >= b || a <= 0 || b <= 0) {
        cout << "Введите такие числа, что b > a, a и в - натуральные\n";
        cin >> a >> b;
    }
    cout << "Ваши числа:  ";
    for (a; a != b; ++a) {
        num = a;
        flag = true;
        while (num != 0) {
            digit = num % 10;
            num /= 10;
            if (digit == 0)
                flag = false;
            if (digit != 0 && a % digit != 0)
                flag = false;
        }
        if (flag == true)
            cout << a << "  ";
    }
}