#ifndef KR1_PERFORMER_H
#define KR1_PERFORMER_H

#include "MusicalComposition.h"

class Performer : public MusicalComposition{
private:
    const int MaxAmountOfPerf = 20;
    int AmountOfPerf;
    int* arr;

public:
    Performer() = delete;
    Performer(int Amo, int* array, std::string _name, Genre _genre, int year);
    Performer(const Performer& a);

    Performer(Performer&& a) noexcept;
    Performer& operator=(Performer&& a) noexcept;

    Performer& operator=(const Performer& a);
    friend std::ostream& operator<<(std::ostream& out, const Performer& a);

    void Print() const override;

    [[nodiscard]] int getMaxAmountOfPerfs() const;
    [[nodiscard]] int getAmountOfPerfs() const;
    [[nodiscard]] int* getArrayOfPerfs() const;

    void setAmountOfPerfs(int a);
    void setArrayOfPerfs(int* a);

    ~Performer() override;

};

#endif //KR1_PERFORMER_H
