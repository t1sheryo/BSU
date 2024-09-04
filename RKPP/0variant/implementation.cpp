#include "header.h"


    Character::Character():
        charID(++generalID),
        name("-"),
        state(convertState[""]),
        race(convertRace[""]),
        IsMoving(false){
            ObjectNumber++;
    }

    Character::Character(std::string n, std::string s, std::string r, bool m):
        charID(++generalID),
        race(convertRace[r]){
            name = n;
            state = convertState[s];
            IsMoving = m;
            ObjectNumber++;
    }

    Character::Character(const Character& a):
    charID(++generalID),
    race(a.race){
        name = a.name;
        state = a.state;
        IsMoving = a.IsMoving;
        ObjectNumber++;
    }

    Character::Character(Character&& a) noexcept : charID(++generalID), race(a.race){
        name = std::move(a.name);
        state = a.state;
        IsMoving = a.IsMoving;
        ObjectNumber++;
    }

    Character& Character::operator=(const Character &&a) noexcept {
        name = std::move(a.name);
        state = a.state;
        IsMoving = a.IsMoving;
        return *this;
    }

    Character& Character::operator=(const Character &a) {
        name = a.name;
        state = a.state;
        IsMoving = a.IsMoving;
        return *this;
    }

    bool Character::operator<(const Character &a) {
        return name < a.name;
    }

    bool Character::operator>(const Character &a) {
        return name > a.name;
    }

    bool Character::operator==(const Character &a) {
        if(name == a.name && state == a.state && race == a.race && IsMoving == a.IsMoving){
            return true;
        }
        return false;
    }

    std::ostream& operator<<(std::ostream& out, const Character& a){
        out << "ID: " << a.charID << '\n';
        out << "Name: " << a.name << '\n';
        out << "State: " << arrayState[a.state] << '\n';
        out << "Race: " << arrayRace[a.race] << '\n';
        out << "Ability to move: " << a.IsMoving << '\n';
        out << "Real Objects Numbers: " << a.ObjectNumber << '\n';
        return out;
    }

    void Character::Print() const {
        std::cout << "ID: " << charID << '\n';
        std::cout  << "Name: " << name << '\n';
        std::cout  << "State: " << arrayState[state] << '\n';
        std::cout  << "Race: " << arrayRace[race] << '\n';
        std::cout  << "Ability to move: " << IsMoving << '\n';
        std::cout  << "Real Objects Numbers: " << ObjectNumber << '\n';
    }

