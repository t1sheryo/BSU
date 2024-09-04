#ifndef RASHET_GRAPH_RABOTA_BANK_H
#define RASHET_GRAPH_RABOTA_BANK_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <exception>

class bank{
private:
    long long farting;
    const long long max_money = 960000000000;
public:
    bank(long long pounds, long long shillings, long double pennies);

    bank() : farting(0){}

    [[nodiscard]] long long GetFarting() const { return farting; }

    void SetFarting(long long a) { farting = a; }

    void operator=(const bank& r);

    bank operator-() const;

    bank operator+(const bank& r);

    bank operator-(const bank& r);

    void operator-=(const bank& r);

    void operator+=(const bank& r);

    bool operator==(const bank& r);

    bool operator<(const bank& r);

    bool operator>(const bank& r);

    friend std::ostream& operator<<(std::ostream& out, const bank& r);

};

#endif
