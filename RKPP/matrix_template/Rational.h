#ifndef MATRICES_TEMPLATE_Rational_H
#define MATRICES_TEMPLATE_Rational_H

#include <iostream>
#include <cmath>
#include <vector>

class Rational{
private:
    int numerator;
    int denominator;
    int gcd(int a, int b) {
        while (b > 0) {
            int c = a % b;
            a = b;
            b = c;
        }
        return a;
    }
    void Reduction() {
        if(denominator < 0){
            denominator *= (-1);
            numerator *= (-1);
        }
        int div = gcd(abs(numerator), denominator);
        if (div != 1) {
            numerator /= div;
            denominator /= div;
        }
    }
public:
    Rational();
    Rational(const std::string fract);
    Rational(int a){
        numerator = a;
        denominator = 1;
    }
    int to_int() const {
        int a = numerator / denominator;
        return a;
    }
    int GetNumerator() const{ return numerator; }
    int GetDenominator() const{ return denominator; }
    std::string GetRational() const{
        std::string tmp = std::to_string(numerator) + " / " + std::to_string(denominator);
        return tmp;
    }
    operator float() { return (float(numerator) / denominator); }
    operator double() { return (double(numerator) / denominator); }
    Rational operator + (const Rational& other) const;
    Rational operator - (const Rational& other) const;
    Rational operator * (const Rational& other) const;
    Rational operator * (const int& other) const;
    Rational operator * (const double& other) const;
    Rational operator / (const Rational& other) const;
    Rational& operator += (const Rational& other);
    Rational& operator -= (const Rational other);
    Rational& operator *= (const Rational& other);
    Rational& operator /= (const Rational& other);
    bool operator == (const Rational& other) const;
    bool operator == (const int& other) const{
        int a = numerator / denominator;
        return a == other ? true : false;
    }
    bool operator != (const Rational& other) const;
    bool operator < (const Rational& other) const;
    bool operator > (const Rational& other) const;
    bool operator <= (const Rational& other) const;
    bool operator >= (const Rational& other) const;
    friend std::ostream& operator << (std::ostream& out, const Rational& other);
    friend std::istream& operator >> (std::istream& in, Rational& other);
    Rational operator ! ();
    Rational& operator ++ ();
    Rational operator ++ (int);
    Rational& operator -- ();
    Rational operator -- (int);
    Rational& operator = (const Rational& oth);
};

#endif //MATRICES_TEMPLATE_Rational_H
