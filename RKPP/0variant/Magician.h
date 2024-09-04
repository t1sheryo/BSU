#ifndef INC_0VARIANT_MAGICIAN_H
#define INC_0VARIANT_MAGICIAN_H

#pragma once

#include <map>
#include <iostream>
#include "header.h"

enum ArtTypes{sword = 0, gun, ring, crown};

inline static std::string arrayArts[4] {"sword", "gun", "ring", "crown"};

inline static std::map <std::string, ArtTypes> convertArt{
    {"sword", sword},
    {"gun", gun},
    {"ring", ring},
    {"crown", crown}
};

class Magician : public Character{
private:
    unsigned int MaxEnergy;
    unsigned int CurEnergy;
    int ArtNumber;
    ArtTypes* arr;

public:
    Magician();
    Magician(int mE, int cE, int aN, ArtTypes* array, std::string n, std::string s, std::string r, bool m);
    Magician(const Magician& a);
    Magician(Magician&& a) noexcept;
    Magician& operator=(const Magician& a);
    Magician& operator=(Magician&& a) noexcept;
    bool operator==(const Magician& a);
    bool operator>(const Magician& a);
    bool operator<(const Magician& a);
    friend std::ostream& operator<<(std::ostream& out, const Magician& a);

    [[nodiscard]] unsigned int getMaxEnergy() const{ return MaxEnergy; }
    [[nodiscard]] unsigned int getCurEnergy() const { return CurEnergy; }
    [[nodiscard]] int getArtNumber() const { return ArtNumber; }
    [[nodiscard]] ArtTypes* getArtTypes() const { return arr; }

    void setMaxEnergy(int mE) {
        if(mE < 0 || mE < CurEnergy) throw "Incorrect number of Energy";
        MaxEnergy = mE;
    }
    void setCurEnergy(int cE) {
        if(cE < 0 || cE > MaxEnergy) throw "Incorrect number of Energy";
        CurEnergy = cE;
    }
    void setArtNumAndArr(int num, ArtTypes* a){
        delete[] arr;
        ArtNumber = num;
        arr = new ArtTypes[ArtNumber];
    }

    void Print() const override;

    ~Magician() override{
        delete[] arr;
    }
};

#endif //INC_0VARIANT_MAGICIAN_H
