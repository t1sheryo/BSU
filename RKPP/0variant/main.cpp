#include "header.h"
#include "Magician.h"
#include <functional>
#include <algorithm>

bool NameComp(std::reference_wrapper<Character> a, std::reference_wrapper<Character> b){
    return a.get().getName() < b.get().getName();
}

int main() {

    try {

        ArtTypes *arrayTest = new ArtTypes[3]{sword, ring, gun};

        Magician a(100, 90, 3, arrayTest, "alesya", "paralysed", "elf", true);

        Character b("zhopa", "normal", "human", false);

        //std::cout << a << "\n\n\n";
        //std::cout << b << "\n\n\n";

        Magician c(120102, 777, 3, arrayTest, "rizz", "normal", "human", true);

        //std::cout << b << "\n\n\n" <<  c;

        std::vector<std::reference_wrapper<Character>> men;
        men.emplace_back(c);
        men.emplace_back(a);
        men.emplace_back(b);

        std::sort(men.begin(), men.end(), NameComp);

//        for(const auto& l : men){
//            std::cout << l.get().getName() << "\n";
//        }

        int character = 0;
        int magician = 0;
        for(size_t i = 0; i < men.size(); ++i){
            if(typeid(Character) == typeid(men[i].get())){
                character++;
            }
            else if(typeid(Magician) == typeid(men[i].get())){
                magician++;
            }
        }
        std::cout << "Magicians: " << magician << "\nCharacters: " << character;

//        for(size_t i = 0; i < men.size(); ++i){
//            std::string id = typeid(men[i].get()).name();
//            std::cout << id << '\n';
//            men[i].get().Print();
//            std::cout << '\n';
//        }

//        for(const auto& k : men){
//            delete k;
//        }

    }
    catch (const char* ex){
        std::cerr << ex;
    }

    return 0;
}
