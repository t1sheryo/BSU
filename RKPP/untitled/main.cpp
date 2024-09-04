#include <iostream>
#include "MusicalComposition.h"
#include "Performer.h"
#include <functional>
#include <vector>

//std::vector<std::reference_wrapper<MusicalComposition>>& sortVector(int target, std::vector<std::reference_wrapper<MusicalComposition>>& vec){
//    int count = 0;
//    for(size_t i = 0; i < vec.size(); ++i){
//        if(typeid(Performer) == typeid(vec[i].get())){
//            count++;
//            Performer* tmp1 = dynamic_cast<Performer*>(&vec[i].get());
//        }
//        else{}
//        for(size_t j = 0; j < vec.size(); ++j){
//
//        }
//    }
//}

int main() {

    try {
        const int year = 2013;
        const int targetArray = 10;

        int *arr1 = new int[3]{1, 7, 3};
        int *arr2 = new int[2]{9, 1};

        MusicalComposition sample1("molodec", song, 1999);
        Performer sample2(3, arr1, "george", dance, 1902);
        sample1 = sample2;
        std::cout << sample1 << "\n\n\n";
        MusicalComposition sample3 = std::move(sample1);
        std::cout << sample1 << "\n\n\n" << sample3 << "\n\n\n";



        MusicalComposition a("molodec", song, 1999);
        MusicalComposition b(a);
        MusicalComposition c("vasylich", opera, 2013);

        std::cout << a << "\n\n\n" << b << "\n\n\n" << c << "\n\n\n";
        a = c;
        std::cout << c << "\n\n\n";

        Performer d(3, arr1, "george", dance, 1902);
        Performer l(2, arr2, "Kevini", symphony, 1000);
        Performer j(d);

        std::cout << d << "\n\n\n" << l << "\n\n\n" << j << "\n\n\n";
        j = l;
        std::cout << j << "\n\n\n";

        std::cout << a << "\n\n\n" << j;

        std::vector<std::reference_wrapper<MusicalComposition>> music {a, b ,c, d, l, j};
        int musicalCounter = 0;
        int performerCounter = 0;
        std::map <Genre, int> counter;
        for(size_t i = 0; i < music.size(); ++i){
            if(typeid(MusicalComposition) == typeid(music[i].get())){
                musicalCounter++;
            }
            if(typeid(Performer) == typeid(music[i].get())){
                performerCounter++;
            }
            switch (music[i].get().getGenre()) {
                case song:
                    counter[song]++;
                    break;
                case opera:
                    counter[opera]++;
                    break;
                case symphony:
                    counter[symphony]++;
                    break;
                case dance:
                    counter[dance]++;
                    break;
                default:
                    break;
            }
        }
        std::cout << "\n\n\nSongs: " << counter[song] << "\n" <<
                  "Operas: " << counter[opera] << '\n' <<
                  "Symphonies: " << counter[symphony] << '\n' <<
                  "Dances: " << counter[dance] << "\n\n\n";
        std::cout << "Musicals: " << musicalCounter << "\n" <<
                  "Performers: " << performerCounter << '\n';

        for(size_t i = 0; i < music.size(); ++i){
            if(music[i].get().getYear() == year){
                std::cout << "\n\n\n" << music[i].get() << "\n\n\n";
            }
        }

        for(size_t i = 0; i < music.size(); ++i){
            music[i].get().Print();
        }
    }
    catch (const char* ex){
        std::cerr << ex;
    }

    return 0;
}
