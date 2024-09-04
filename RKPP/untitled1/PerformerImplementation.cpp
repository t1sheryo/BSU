#include "Performer.h"

    Performer::Performer(int Amo, int *array, std::string _name, Genre _genre, int year):
        MusicalComposition(_name, _genre, year)
    {
        if(Amo > MaxAmountOfPerf) throw "Amount > MaxAmount";
        AmountOfPerf = Amo;
        arr = new int[AmountOfPerf];
        for(size_t i = 0; i < AmountOfPerf; ++i){
            arr[i] = array[i];
        }
    }

    Performer::Performer(const Performer &a):
            MusicalComposition(a)
    {
        AmountOfPerf = a.AmountOfPerf;
        arr = new int[AmountOfPerf];
        for(size_t i = 0; i < AmountOfPerf; ++i){
            arr[i] = a.arr[i];
        }
    }

    Performer::Performer(Performer &&a) noexcept :
            MusicalComposition(a)
    {
        if(AmountOfPerf != 0)
            delete arr;
        arr = new int[a.AmountOfPerf];
        for(size_t i = 0; i < a.AmountOfPerf; ++i){
            arr[i] = a.arr[i];
        }
        delete arr;
        AmountOfPerf = a.AmountOfPerf;
        a.AmountOfPerf = 0;
    }

    Performer& Performer::operator=(Performer&& a) noexcept{
        this->setName(a.getName());
        this->setYear(a.getYear());
        if(AmountOfPerf != 0){
            delete arr;
        }
        arr = new int[a.AmountOfPerf];
        for(size_t i = 0; i < a.AmountOfPerf; ++i){
            arr[i] = a.arr[i];
        }
        delete arr;
        AmountOfPerf = a.AmountOfPerf;
        a.AmountOfPerf = 0;
        return *this;
    }

    Performer& Performer::operator=(const Performer& a){
        this->setName(a.getName());
        this->setYear(a.getYear());
        if(AmountOfPerf != 0){
            delete arr;
        }
        AmountOfPerf = a.AmountOfPerf;
        arr = new int[AmountOfPerf];
        for(size_t i = 0; i < AmountOfPerf; ++i){
            arr[i] = a.arr[i];
        }
        return *this;
    }

    int Performer::getAmountOfPerfs() const { return AmountOfPerf; }
    int Performer::getMaxAmountOfPerfs() const { return MaxAmountOfPerf; }
    int* Performer::getArrayOfPerfs() const { return arr; }

    void Performer::setAmountOfPerfs(int a) {
        if(a > MaxAmountOfPerf) throw "AmountOfPerformers > MaxAmountOfPerformers";
        AmountOfPerf = a;
    }
    void Performer::setArrayOfPerfs(int *a) {
        for(size_t i = 0; i < AmountOfPerf; ++i){
            arr[i] = a[i];
        }
    }

    std::ostream& operator<<(std::ostream& out, const Performer& a){
        out << "ID: " << a.getID() << '\n';
        out << "Composition Name: " << a.getName() << '\n';
        out << "Genre: " << a.getGenre() << '\n';
        out << "Year: " << a.getYear() << '\n';
        out << "Maximum Amount Of Performers: " << a.getMaxAmountOfPerfs() << '\n';
        out << "Amount Of Performers: " << a.getAmountOfPerfs() << '\n';
        out << "Array: ";
        for(size_t i = 0; i < a.getAmountOfPerfs(); ++i){
            out << a.getArrayOfPerfs()[i] << ',';
        }
        return out;
    }

    Performer::~Performer(){
        delete arr;
    }

    void Performer::Print() const {
        std::cout << "ID: " << getID() << '\n';
        std::cout << "Composition Name: " << getName() << '\n';
        std::cout << "Genre: " << convertGenre[getGenre()] << '\n';
        std::cout << "Year: " << getYear() << '\n';
        std::cout << "Maximum Amount Of Performers: " << getMaxAmountOfPerfs() << '\n';
        std::cout << "Amount Of Performers: " << getAmountOfPerfs() << '\n';
        std::cout << "Array: ";
        for(size_t i = 0; i < getAmountOfPerfs(); ++i){
            std::cout << getArrayOfPerfs()[i] << ',';
        }
    }

