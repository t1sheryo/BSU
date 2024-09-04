#include "MusicalComposition.h"

    MusicalComposition::MusicalComposition(std::string name, Genre _genre, int _year):
        ID(++generalID),
        genre(_genre),
        nameComp(name),
        year(_year){}

    MusicalComposition::MusicalComposition(const MusicalComposition& a):
        ID(++generalID),
        genre(a.genre)
    {
        nameComp = a.nameComp;
        year = a.year;
    }

    MusicalComposition::MusicalComposition(MusicalComposition &&a) noexcept:
        ID(++generalID),
        genre(a.genre)
    {
        nameComp = a.nameComp;
        year = a.year;
        a.nameComp = "";
        a.year = 0;
    }

    MusicalComposition& MusicalComposition::operator=(MusicalComposition &&a) noexcept {
        if(&a == this)
            return *this;
        nameComp = a.nameComp;
        year = a.year;
        a.nameComp = "";
        a.year = 0;
        return *this;
    }

    MusicalComposition& MusicalComposition::operator=(const MusicalComposition &a) {
        nameComp = a.nameComp;
        year = a.year;
        return *this;
    }

    bool MusicalComposition::operator==(const MusicalComposition &a) {
        if(nameComp == a.nameComp && genre == a.genre && year == a.year){
            return true;
        }
        return false;
    }

    std::ostream& operator<<(std::ostream& out, MusicalComposition& a){
        out << "ID: " << a.ID << '\n';
        out << "Composition Name: " << a.nameComp << '\n';
        out << "Genre: " << a.genre << '\n';
        out << "Year: " << a.year << '\n';
        return out;
    }

    int MusicalComposition::getID() const { return ID; }
    std::string MusicalComposition::getName() const { return nameComp; }
    Genre MusicalComposition::getGenre() const { return genre; }
    int MusicalComposition::getYear() const { return year; }

    void MusicalComposition::setName(std::string a) { nameComp = a; }
    void MusicalComposition::setYear(int a) { year = a; }

    void MusicalComposition::Print() const {
        std::cout << "ID: " << ID << '\n';
        std::cout << "Composition Name: " << nameComp << '\n';
        std::cout << "Genre: " << convertGenre[genre] << '\n';
        std::cout << "Year: " << year << '\n';
    }