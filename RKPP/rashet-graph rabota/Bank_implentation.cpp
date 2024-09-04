#ifndef RASHET_GRAPH_RABOTA_BANK_IMPLENTATION_CPP
#define RASHET_GRAPH_RABOTA_BANK_IMPLENTATION_CPP

#include "bank.h"
#include "MyException.h"

bank::bank(long long pounds, long long shillings, long double pennies){
    if(pounds > 1000000000 || shillings >= 20 || pennies >= 12 || pounds < 0 || shillings < 0 || pennies < 0) throw MyException("Invalid money\n");
    farting = (long long)(pennies*4) + shillings*12*4 + pounds*20*12*4;
    auto okrug = (long long)(pennies * 4);
    if((double)(okrug - (pennies * 4)) != 0){
        throw MyException("Invalid amount of penny\n");
    }
}

void bank::operator=(const bank& r){
    farting = r.farting;
}

bank bank::operator-() const{
    bank tmp;
    tmp.farting = -this->farting;
    return tmp;
}

//операций +, -, +=, -=, 8 баллов
bank bank::operator+(const bank& r){
    bank tmp;
    tmp.farting = this->farting + r.farting;
    if(tmp.farting > 1000000000) throw MyException("Money limit is reached!\n");
    return tmp;
}

bank bank::operator-(const bank& r){
    bank tmp;
    tmp.farting = this->farting - r.farting;
    return tmp;
    //if(farting < 0) throw MyException("After -, bank has negative money!\n");
}

void bank::operator-=(const bank& r){
    farting -= r.farting;
}

void bank::operator+=(const bank& r){
    farting += r.farting;
}

//сравнения (достаточно ==, <). 4 балла
bool bank::operator==(const bank& r){
    if(farting == r.farting) {
        return true;
    }
    return false;
}

bool bank::operator<(const bank& r){
    if(farting < r.farting){
        return true;
    }
    return false;
}

bool bank::operator>(const bank& r){
    if(farting > r.farting){
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const bank& r){
    long long farting = r.farting;
    long pound = (long)farting / 960;
    farting -= (pound * 960);
    long shilling = long(farting) / 48;
    farting -= (shilling * 48);
    double penny = (double)farting / 4;
    out << pound << "pd." << shilling << "sh." << penny << "p.\n";
    return out;
}

#endif //RASHET_GRAPH_RABOTA_BANK_IMPLENTATION_CPP
