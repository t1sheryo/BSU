#pragma once
#include <string>


//����� ��� ��������� �������������� �������� 
class MyException {
private:
	std::string text;
public:
	MyException(std::string text) {
		this->text = text;
	}
	std::string what() {
		return text;
	}
};


class Fraction {
private:
	int numerator;
	int denominator;
public:

    Fraction();

    Fraction(const std::string fract);

	int GetNumerator() const{
		return numerator;
	}
	int GetDenominator() const{
		return denominator;
	}
	std::string GetFraction() const{
		std::string tmp = std::to_string(numerator) + " / " + std::to_string(denominator);
        return tmp;
	}
	
	void Reduction();

    // ���������� � ������������� ����
    operator float() {
        return (float(numerator) / denominator);
    }

    operator double() {
        return (double(numerator) / denominator);
    }

    // �������������� ��������� ��� �������
    Fraction operator + (const Fraction& other);

    Fraction operator - (const Fraction& other);

    Fraction operator * (const Fraction& other);

    Fraction operator / (const Fraction& other);

    // ��������� ��������� ������������
    Fraction& operator += (const Fraction& other);

    Fraction& operator -= (const Fraction& other);

    Fraction& operator *= (const Fraction& other);

    Fraction& operator /= (const Fraction& other);

    // ��������� ���������
    bool operator == (const Fraction& other) const;

    bool operator != (const Fraction& other) const;

    bool operator < (const Fraction& other) const;

    bool operator > (const Fraction& other) const;

    bool operator <= (const Fraction& other) const;

    bool operator >= (const Fraction& other) const;

    // ���� � ������
    friend std::ostream& operator << (std::ostream& out, const Fraction& other);

    // ����� � �����
    friend std::istream& operator >> (std::istream& in, Fraction& other);

    // ������� ����� �������� ��������� �����������, ��� �������� ��������� �������� �����
    Fraction operator ! ();

    // ��������� � ���������     
    Fraction& operator ++ ();    

    Fraction operator ++ (int);

    Fraction& operator -- ();

    Fraction operator -- (int);

    // �������� ������������
    Fraction& operator = (const Fraction& oth);
};