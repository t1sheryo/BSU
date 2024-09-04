#include <iostream>
#include <string>
#include "fraction.h"

int main()
{
    try {
        Fraction f1, f2("3/-2"), f3("20/14");
        Fraction copy_f2(f2);
        std::cin >> f1;

        std::cout << "f1 fraction = " << f1.GetFraction() << "\n";
        std::cout << "f2 numerator = " << f2.GetNumerator() << "\n";
        std::cout << "f2 denominator = " << f2.GetDenominator() << "\n";
        std::cout << "f2 fraction = " << f2.GetFraction() << "\n";
        std::cout << "f3(20/14) = " << f3.GetFraction() << " (after reduction)\n\n\n\n\n";

        std::cout << "f2 fraction = " << f2.GetFraction() << "\n";
        std::cout << "f3 fraction = " << f3.GetFraction() << "\n\n\n";
        
        std::cout << "f2 to float = " << f2.operator float() << "\n";
        std::cout << "f2 to double = " << f2.operator double() << "\n\n\n";

        std::cout << "f2 + f3 = " << f2 + f3 << "\n";
        std::cout << "f2 - f3 = " << f2 - f3 << "\n";
        std::cout << "f2 * f3 = " << f2 * f3 << "\n";
        std::cout << "f2 / f3 = " << f2 / f3 << "\n\n\n";

        f2 = copy_f2;
        std::cout << "f2 = " << f2 << "\n";
        std::cout << "f2 += f3 = " << (f2 += f3) << "\n";
        f2 = copy_f2;
        std::cout << "f2 -= f3 = " << (f2 -= f3) << "\n";
        f2 = copy_f2;
        std::cout << "f2 *= f3 = " << (f2 *= f3) << "\n";
        f2 = copy_f2;
        std::cout << "f2 /= f3 = " << (f2 /= f3) << "\n\n\n";
        f2 = copy_f2;

        std::cout << std::boolalpha;
        std::cout << f2 << " < " << f3 << " : " << (f2 < f3) << '\n';
        std::cout << f2 << " > " << f3 << " : " << (f2 > f3) << '\n';
        std::cout << f2 << " <= " << f3 << " : " << (f2 <= f3) << '\n';
        std::cout << f2 << " >= " << f3 << " : " << (f2 >= f3) << '\n';
        std::cout << f2 << " == " << f3 << " : " << (f2 == f3) << '\n';
        std::cout << f2 << " != " << f3 << " : " << (f2 != f3) << "\n\n\n";

        std::cout << "f2 = " << f2 << "\n";
        std::cout << "!f2 = " << !f2 << "\n\n\n";
        f2 = copy_f2;

        std::cout << "++f = " << ++f2 << '\n';
        f2 = copy_f2;
        std::cout << "--f = " << --f2 << '\n';
        f2 = copy_f2;
        std::cout << "f++ = " << f2++ << '\n';
        f2 = copy_f2;
        std::cout << "f-- = " << f2-- << "\n\n\n";
        f2 = copy_f2;

        std::cout << "f2 = " << f2 << "\n";
        std::cout << "f3 = " << f3 << "\n\n";
        std::cout << "f2 = f3\n\n";
        f2 = f3;
        std::cout << "f2 = " << f2 << "\n\n\n";
        /*std::cin >> f1;
        std::cout << f1;*/
    }
    catch (MyException& ex) {
        std::cerr << "ERROR!\n" << ex.what() << '\n';
    }
    return 0;
}