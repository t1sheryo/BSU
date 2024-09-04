#pragma once
#include <string>


//Класс для обработки исключительных ситуаций 
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

    // Приведение к вещественному типу
    operator float() {
        return (float(numerator) / denominator);
    }

    operator double() {
        return (double(numerator) / denominator);
    }

    // Арифметические операторы над дробями
    Fraction operator + (const Fraction& other);

    Fraction operator - (const Fraction& other);

    Fraction operator * (const Fraction& other);

    Fraction operator / (const Fraction& other);

    // Составные операторы присваивания
    Fraction& operator += (const Fraction& other);

    Fraction& operator -= (const Fraction& other);

    Fraction& operator *= (const Fraction& other);

    Fraction& operator /= (const Fraction& other);

    // Операторы сравнения
    bool operator == (const Fraction& other) const;

    bool operator != (const Fraction& other) const;

    bool operator < (const Fraction& other) const;

    bool operator > (const Fraction& other) const;

    bool operator <= (const Fraction& other) const;

    bool operator >= (const Fraction& other) const;

    // ввод с потока
    friend std::ostream& operator << (std::ostream& out, const Fraction& other);

    // Вывод в поток
    friend std::istream& operator >> (std::istream& in, Fraction& other);

    // Унарный минус оператор отрицания перегрузить, как оператор получения обратной дроби
    Fraction operator ! ();

    // Инкремент и декремент     
    Fraction& operator ++ ();    

    Fraction operator ++ (int);

    Fraction& operator -- ();

    Fraction operator -- (int);

    // Оператор присваивания
    Fraction& operator = (const Fraction& oth);
};