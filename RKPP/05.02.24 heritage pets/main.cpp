#include "animal.h"


int main() {

    std::cout << "Application accepts next description of pets:\ndog: owners name, type of pet, nickname, age, breed, weight;\n" <<
    "cat: owners name, type of pet, nickname, age, origin;\n" << "frog: owners name, type of pet, nickname, age, color;\n";

    std::vector <pet*> pets;

    std::string path = "input.txt";

    std::ifstream input(path);
    if(!input.is_open()) {
        std::cerr << "File is not opened!\n";
        exit(1);
    }
    else if(input.peek() == EOF) std::cerr << "File is empty!\n";


    while(input.peek() != EOF){
        std::vector <std::string> info;
        std::string s, tmp;
        input >> s;
        s += ',';
        for(const auto a : s){
            if(a == ','){
                std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
                info.push_back(tmp);
                tmp.clear();
                continue;
            }
            tmp.push_back(a);
        }
        std::string name = info[1];
        if(name == "dog"){
            dog *a = new dog(info);
            pets.emplace_back(a);
        }
        else if(name == "cat"){
            cat *a = new cat(info);
            pets.emplace_back(a);
        }
        else if(name == "frog"){
            frog *a = new frog(info);
            pets.emplace_back(a);
        }
        else{
            std::cerr << "Non-existing type of pet\n";
        }
        info.clear();
    }

    while(true){
        char sym;
        std::cout << "\nEnter \"1\" to continue\nEnter other button to quit\n";
        std::cin >> sym;
        if(sym != '1')
            break;

        point:
        std::cout << "Choose what you want to do:\n"
        << "1)Count the number of different types of animals each owner has;\n"
        << "2)For a specific type of animal (entered by the user), display all its owners and names;\n"
        << "3)Determine how many species of animals have a certain nickname (the nickname is entered by the user);\n"
        << "4)Display information about the age of the oldest and youngest animal of each species;\n"
        << "5)Display information about all pets;\n";

        int choice = 0;
        std::cin >> choice;

        std::string user_type;
        std::string user_nickname;
        std::set <std::string> types_w_nick;
        std::map <std::string, std::set<std::string>> owners;
        std::map <std::string,  std::vector<std::string>> pet_types;
        std::map <std::string, std::pair<int, int>> pets_age;

        switch (choice) {
            case 1:
                for(const auto a : pets){
                    owners[a->getOwner()].emplace(a->getType());
                }
                for(const auto& a : owners){
                    std::cout << "Owner " << a.first << " has " << a.second.size() << " types of pets: ";
                    for(const auto& b : a.second){
                        std::cout << b << "; ";
                    }
                    std::cout << '\n';
                }
                break;
            case 2:
                std::cout << "Enter the type of pet you want to display info about: ";
                std::cin >> user_type;
                for(const auto a : pets) {
                    if (a->getType() == user_type) {
                        pet_types[a->getOwner()].emplace_back(a->getNickname());
                    }
                }
                for(const auto& a : pet_types){
                    std::cout << "Owner " << a.first << " : ";
                    for(const auto& b : a.second){
                        std::cout << b << "; ";
                    }
                    std::cout << '\n';
                }
                break;
            case 3:
                std::cout << "Enter the nickname with which you want to display pets: ";
                std::cin >> user_nickname;
                for(const auto a : pets){
                    if(a->getNickname() == user_nickname){
                        types_w_nick.emplace(a->getType());
                    }
                }
                std::cout << "There are " << types_w_nick.size() << " types of pets with nickname \""
                << user_nickname << "\" : ";
                for(const auto& b : types_w_nick){
                    std::cout << b << "; ";
                }
                std::cout << '\n';
                break;
            case 4:
                for(auto a : pets){
                    if(a->getAge() > pets_age[a->getType()].second){
                        pets_age[a->getType()].second = a->getAge();
                    }
                    if(pets_age[a->getType()].first == 0){
                        pets_age[a->getType()].first = a->getAge();
                    }
                    if(pets_age[a->getType()].first > a->getAge()){
                        pets_age[a->getType()].first = a->getAge();
                    }
                }
                for(const auto& a : pets_age){
                    std::cout << "Type " << a.first << " : " << "Youngest->" << a.second.first << ", Oldest->" << a.second.second << '\n';
                }
                break;
            case 5:
                for(const auto a : pets){
                    a->getInfo();
                    std::cout << '\n';
                }
                break;
            default:
                std::cout << "Choice was not correct! If you want to continue, press 1";
                std::cin >> sym;
                if(sym == '1')
                    goto point;
        }
    }

    pets[0]->behavior();
    pets[1]->behavior();
    pets[2]->behavior();
    pets[3]->behavior();
    pets[4]->behavior();


    for(const auto a : pets){
        delete a;
    }

    return 0;
}
