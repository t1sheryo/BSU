#include "Rational.h"

Rational::Rational() {
    numerator = 0;
    denominator = 1;
}
Rational::Rational(const std::string fract) {
    std::string tmp = "";
    int count_slash = 0;
    bool numerator_is_found = false;
    if (fract[fract.size() - 1] == '/') {
        throw "There is no denominator\n";
    }
    for (size_t i = 0; i < fract.size(); ++i) {
        int table_val = int(fract[i]);
        if (count_slash == 2) {
            throw "There are two or more slashes! Unacceptable!\n";
        }
        if (table_val == 47) {
            count_slash++;
        }
        if (table_val < 45 || table_val == 46 || table_val > 57) {
            throw "There are unacceptable symbols!\n";
        }
        if (table_val == 47 && !numerator_is_found) {
            for (int j = 0; j < tmp.size(); j++) {
                if (tmp[j] == '-' && j != 0) {
                    throw "There are unacceptable symbols!\n";
                }
            }
            this->numerator = stoi(tmp);
            numerator_is_found = true;
            tmp.clear();
            continue;
        }
        tmp.push_back(fract[i]);
        if ((i == fract.size() - 1) && numerator_is_found) {
            for (int j = 0; j < tmp.size(); j++) {
                if (tmp[j] == '-' && j != 0) {
                    throw "There are unacceptable symbols!\n";
                }
            }
            this->denominator = stoi(tmp);
            tmp.clear();
        }
//        if (this->denominator == 0) {
//            throw "Denominator can not equal to 0!\n";
//        }
        if ((i == fract.size() - 1) && !numerator_is_found) {
            this->numerator = stoi(tmp);
            this->denominator = 1;
            tmp.clear();
        }
    }
    if (denominator < 0) {
        denominator *= (-1);
        numerator *= (-1);
    }
    Reduction();
}
Rational Rational::operator+(const Rational& other) const{
    Rational tmp(*this);
    tmp.numerator = tmp.numerator * other.denominator + other.numerator * tmp.denominator;
    tmp.denominator = tmp.denominator * other.denominator;
    tmp.Reduction();
    return tmp;
}
Rational Rational::operator-(const Rational& other) const{
    Rational tmp(*this);
    tmp.numerator = tmp.numerator * other.denominator - other.numerator * tmp.denominator;
    tmp.denominator = tmp.denominator * other.denominator;
    tmp.Reduction();
    return tmp;
}
Rational Rational::operator*(const Rational& other) const{
    Rational tmp(*this);
    tmp.numerator = tmp.numerator * other.numerator;
    tmp.denominator = tmp.denominator * other.denominator;
    tmp.Reduction();
    return tmp;
}
Rational Rational::operator*(const int& other) const{
    Rational tmp(*this);
    tmp.numerator = tmp.numerator * other;
    tmp.Reduction();
    return tmp;
}
Rational Rational::operator*(const double& other) const{
    Rational tmp(*this);
    tmp.numerator = tmp.numerator * (int)other;
    tmp.Reduction();
    return tmp;
}
Rational Rational::operator/(const Rational& other)const {
    Rational tmp(*this);
    tmp.numerator *= other.denominator;
    tmp.denominator *= other.numerator;
    tmp.Reduction();
    return tmp;
}
Rational& Rational::operator+=(const Rational& other) {
    Rational& tmp(*this);
    tmp = tmp + other;
    return tmp;
}
Rational& Rational::operator-=(const Rational other) {
    Rational& tmp(*this);
    tmp = tmp - other;
    return tmp;
}
Rational& Rational::operator*=(const Rational& other) {
    Rational& tmp(*this);
    tmp = tmp * other;
    return tmp;
}
Rational& Rational::operator/=(const Rational& other) {
    Rational& tmp(*this);
    tmp = tmp / other;
    return tmp;
}
bool Rational::operator==(const Rational& other) const{
    return (this->numerator == other.numerator && this->denominator == other.denominator);
}
bool Rational::operator!=(const Rational& other) const {
    return (this->numerator != other.numerator || this->denominator != other.denominator);
}
bool Rational::operator>(const Rational& other) const {
    return (this->numerator * other.denominator > other.numerator * this->denominator);
}
bool Rational::operator < (const Rational& other) const {
    return (this->numerator * other.denominator < other.numerator * this->denominator);
}
bool Rational::operator >= (const Rational& other) const {
    return (this->numerator * other.denominator >= other.numerator * this->denominator);
}
bool Rational::operator <= (const Rational& other) const {
    return (this->numerator * other.denominator <= other.numerator * this->denominator);
}
std::ostream& operator << (std::ostream& out, const Rational& other) {
    if (other.denominator == 1) {
        out << other.numerator;
    }
    else {
        out << other.numerator << "/" << other.denominator;
    }
    return out;
}
std::istream& operator >> (std::istream& in, Rational& other){
    std::string s;
    in >> s;
    other = Rational(s);
    return in;
}
Rational Rational::operator!() {
    int tmp = this->numerator;
    this->numerator = this->denominator;
    this->denominator = tmp;
    return *this;
}
Rational& Rational::operator++() {
    this->numerator += this->denominator;
    return *this;
}
Rational Rational::operator++(int) {
    Rational tmp(*this);
    this->numerator += this->denominator;
    return tmp;
}
Rational& Rational::operator--() {
    this->numerator -= this->denominator;
    return *this;
}
Rational Rational::operator--(int) {
    Rational tmp(*this);
    this->numerator -= this->denominator;
    return tmp;
}
Rational& Rational::operator=(const Rational& other) {
    this->numerator = other.numerator;
    this->denominator = other.denominator;
    return *this;
}
