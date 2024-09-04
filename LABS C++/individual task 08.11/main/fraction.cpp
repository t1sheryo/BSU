#include "fraction.h"
#include <iostream>
#include <fstream>


Fraction::Fraction() {
	numerator = 0;
	denominator = 1;
}


Fraction::Fraction(const std::string fract) {
	std::string tmp = "";
	int count_slash = 0;
	bool numerator_is_found = false;
	if (fract[fract.size() - 1] == '/') {
		throw MyException("There is no denominator\n");
	}
	for (size_t i = 0; i < fract.size(); ++i) {
		int table_val = int(fract[i]);
		if (count_slash == 2) {
			throw MyException("There are two or more slashes! Unacceptable!\n");
		}
		if (table_val == 47) {
			count_slash++;
		}
		if (table_val < 45 || table_val == 46 || table_val > 57) {
			throw MyException("There are unacceptable symbols!\n");
		}
		if (table_val == 47 && !numerator_is_found) {
			for (int j = 0; j < tmp.size(); j++) {
				if (tmp[j] == '-' && j != 0) {
					throw MyException("There are unacceptable symbols!\n");
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
					throw MyException("There are unacceptable symbols!\n");
				}
			}
			this->denominator = stoi(tmp);
			tmp.clear();
		}
		if (this->denominator == 0) {
			throw MyException("Denominator can not equal to 0!\n");
		}
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


int gcd(int a, int b) {                     /* Наибольший общий делитель алгоритмом Евклида*/
	while (b > 0) {
		int c = a % b;
		a = b;
		b = c;
	}
	return a;
}


void Fraction::Reduction() {
	int div = gcd(abs(numerator), denominator);
	if (div != 1) {
		numerator /= div;
		denominator /= div;
	}
}


Fraction Fraction::operator + (const Fraction& other) {
	this->numerator = this->numerator * other.denominator + other.numerator * this->denominator;
	this->denominator = this->denominator * other.denominator;
	Reduction();
	return *this;
}


Fraction Fraction::operator - (const Fraction& other) {
	this->numerator = this->numerator * other.denominator - other.numerator * this->denominator;
	this->denominator = this->denominator * other.denominator;
	Reduction();
	return *this;
}


Fraction Fraction::operator * (const Fraction& other) {
	this->numerator = this->numerator * other.numerator;
	this->denominator = this->denominator * other.denominator;
	Reduction();
	return *this;
}


Fraction Fraction::operator / (const Fraction& other) {
	this->numerator *= other.denominator;
	this->denominator *= other.numerator;
	Reduction();
	return *this;
}


Fraction& Fraction::operator += (const Fraction& other) {
	this->denominator *= other.denominator;
	this->numerator = this->numerator * other.denominator + other.numerator * this->denominator;
	Reduction();
	return *this;
}


Fraction& Fraction::operator -= (const Fraction& other) {
	this->denominator *= other.denominator;
	this->numerator = this->numerator * other.denominator - other.numerator * this->denominator;
	Reduction();
	return *this;
}


Fraction& Fraction::operator *= (const Fraction& other) {
	this->numerator *= other.numerator;
	this->denominator *= other.denominator;
	Reduction();
	return *this;
}


Fraction& Fraction::operator /= (const Fraction& other) {
	this->numerator *= other.denominator;
	this->denominator *= other.numerator;
	Reduction();
	return *this;
}


bool Fraction::operator == (const Fraction& other) const{
	return (this->numerator == other.numerator && this->denominator == other.denominator);
}


bool Fraction::operator != (const Fraction& other) const {
	return (this->numerator != other.numerator || this->denominator != other.denominator);
}
 

bool Fraction::operator > (const Fraction& other) const {
	return (this->numerator * other.denominator > other.numerator * this->denominator);
}


bool Fraction::operator < (const Fraction& other) const {
	return (this->numerator * other.denominator < other.numerator * this->denominator);
}


bool Fraction::operator >= (const Fraction& other) const {
	return (this->numerator * other.denominator >= other.numerator * this->denominator);
}


bool Fraction::operator <= (const Fraction& other) const {
	return (this->numerator * other.denominator <= other.numerator * this->denominator);
}


std::ostream& operator << (std::ostream& out, const Fraction& other) {
	if (other.denominator == 1) {
		out << other.numerator;
	}
	else {
		out << other.numerator << " / " << other.denominator;
	}
	return out;
}

std::istream& operator >> (std::istream& in, Fraction& other){
	std::string s;
	std::getline(in, s);
	other = Fraction(s);
	return in;
}


Fraction Fraction::operator!() {
	int tmp = this->numerator;
	this->numerator = this->denominator;
	this->denominator = tmp;
	return *this;
}


Fraction& Fraction::operator ++ () {
	this->numerator += this->denominator;
	return *this;
}


Fraction Fraction::operator ++ (int) {
	Fraction tmp(*this);
	this->numerator += this->denominator;
	return tmp;
}


Fraction& Fraction::operator -- () {
	this->numerator -= this->denominator;
	return *this;
}


Fraction Fraction::operator -- (int) {
	Fraction tmp(*this);
	this->numerator -= this->denominator;
	return tmp;
}

Fraction& Fraction::operator = (const Fraction& other) {
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	return *this;
}