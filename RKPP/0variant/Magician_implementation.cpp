#include "Magician.h"
#include <exception>

    Magician::Magician(): MaxEnergy(0), CurEnergy(0), ArtNumber(0), arr(nullptr) {}

    Magician::Magician(int mE, int cE, int aN, ArtTypes* array, std::string n, std::string s,
                       std::string r, bool m): Character(n, s, r, m) {
        if(mE < 0) throw "Max Energy < 0";
        if(cE < 0 || cE > mE) throw "Current Energy is incorrect!";
        MaxEnergy = mE;
        CurEnergy = cE;
        ArtNumber = aN;
        arr = new ArtTypes[ArtNumber];
        for(size_t i = 0; i < ArtNumber; ++i){
            arr[i] = array[i];
        }
    }

    Magician::Magician(const Magician& a): Character(a.getName(), a.getState(), a.getRace(), a.getAbilityToMove()) {
        MaxEnergy = a.MaxEnergy;
        CurEnergy = a.CurEnergy;
        ArtNumber = a.ArtNumber;
        arr = new ArtTypes[ArtNumber];
        for (size_t i = 0; i < ArtNumber; ++i) {
            arr[i] = a.arr[i];
        }
    }

    Magician::Magician(Magician &&a) noexcept:
        arr(a.arr)
    {
        MaxEnergy = a.MaxEnergy;
        CurEnergy = a.CurEnergy;
        ArtNumber = a.ArtNumber;
        a.arr = nullptr;
        this->setName(a.getName());
        this->setState(a.getState());
        this->setIsMoving(a.getAbilityToMove());
        a.MaxEnergy = 0;
        a.CurEnergy = 0;
        a.ArtNumber = 0;
        a.setName("erased");
    }

    Magician& Magician::operator=(Magician &&a) noexcept{
        if(&a == this){
            return *this;
        }
        if(arr != nullptr) {
            delete arr;
        }
        MaxEnergy = a.MaxEnergy;
        CurEnergy = a.CurEnergy;
        ArtNumber = a.ArtNumber;
        arr = a.arr;
        a.arr = nullptr;
        a.MaxEnergy = 0;
        a.CurEnergy = 0;
        a.ArtNumber = 0;
        a.setName("erased");
        return *this;
    }

    Magician& Magician::operator=(const Magician &a) {
        MaxEnergy = a.MaxEnergy;
        CurEnergy = a.CurEnergy;
        if(ArtNumber != 0)
            delete[] arr;
        ArtNumber = a.ArtNumber;
        arr = new ArtTypes[ArtNumber];
        for(size_t i = 0 ; i < ArtNumber; ++i){
            arr[i] = a.arr[i];
        }
        this->setName(a.getName());
        this->setState(a.getState());
        this->setIsMoving(a.getAbilityToMove());
        return *this;
    }

    bool Magician::operator==(const Magician &a) {
        if(MaxEnergy == a.MaxEnergy && CurEnergy == a.CurEnergy && ArtNumber == a.ArtNumber && this->getName() == a.getName()
         && this->getState() == a.getState() && this->getRace() == a.getRace() && this->getAbilityToMove() == a.getAbilityToMove()){
            for(size_t i = 0; i < this->ArtNumber; ++i){
                if(arr[i] != a.arr[i])
                    return false;
            }
        }
        return true;
    }

    bool Magician::operator>(const Magician &a) {
        return CurEnergy > a.CurEnergy;
    }

    bool Magician::operator<(const Magician &a) {
        return CurEnergy < a.CurEnergy;
    }

    std::ostream& operator<<(std::ostream& out, const Magician& a){
        out << "ID: " << a.getId() << '\n';
        out << "Name: " << a.getName() << '\n';
        out << "State: " << a.getState() << '\n';
        out << "Race: " << a.getRace() << '\n';
        out << "Ability to move: " << a.getAbilityToMove() << '\n';
        out << "Real Objects Numbers: " << a.getObjectNumber() << '\n';
        out << "Maximum Energy: " << a.MaxEnergy << '\n';
        out << "Current Energy: " << a.CurEnergy << '\n';
        out << "Artifacts Number: " << a.ArtNumber << '\n';
        for(size_t i = 0; i < a.ArtNumber; ++i){
             out << "Arr[" << i << "]: " << arrayArts[a.arr[i]] << '\n';
        }
        return out;
    }

    void Magician::Print() const {
        std::cout << "ID: " << getId() << '\n';
        std::cout << "Name: " << getName() << '\n';
        std::cout << "State: " << getState() << '\n';
        std::cout << "Race: " << getRace() << '\n';
        std::cout << "Ability to move: " << getAbilityToMove() << '\n';
        std::cout << "Real Objects Numbers: " <<getObjectNumber() << '\n';
        std::cout << "Maximum Energy: " << MaxEnergy << '\n';
        std::cout << "Current Energy: " << CurEnergy << '\n';
        std::cout << "Artifacts Number: " << ArtNumber << '\n';
        for(size_t i = 0; i < ArtNumber; ++i){
            std::cout << "Arr[" << i << "]: " << arrayArts[arr[i]] << '\n';
        }
    }