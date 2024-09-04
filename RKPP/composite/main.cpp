#include "Animal.h"

CompositePet* createTeam(){
    CompositePet* team = new CompositePet;
    for(int i = 0; i < 10; ++i)
        team->addPet(new dog);
    for(int i = 0; i < 5; ++i)
        team->addPet(new cat);
    for(int i = 0; i < 3; ++i){
        team->addPet(new frog);
    }
    return team;
}

int main() {

    std::vector <std::string> copy;

    std::cout << "Application accepts next description of pets:\ndog: ownersInfo name, type of pet, nickname, age, breed, weight;\n" <<
              "cat: ownersInfo name, type of pet, nickname, age, origin;\n" << "frog: ownersInfo name, type of pet, nickname, age, color;\n";

    std::string path = "input.txt";

    std::ifstream input(path);
    if(!input.is_open()) {
        std::cerr << "File is not opened!\n";
        exit(1);
    }
    else if(input.peek() == EOF) std::cerr << "File is empty!\n";

    std::map <int, pet*> pets;  // container for storing pointers to pets
    std::vector<owner*> owners;   // container for storing pointers to owners

    std::map <std::string, types> convert{  // converting std::string pet type into type "types"
            {"dog", Dog},
            {"cat", Cat},
            {"frog", Frog}
    };

    while(input.peek() != EOF){    // parsing string
        std::vector <std::string> info;   // vector with info which each string contains
        std::string s, tmp;
        input >> s;
        s += ',';
        for(const auto a : s){   // fill vector info
            if(a == ','){
                std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
                info.push_back(tmp);
                tmp.clear();
                continue;
            }
            tmp.push_back(a);
        }
        std::string cur_type = info[1];
        std::string ownerName = info[0];


        //implementing factory method with generic constructor
        types con = convert[cur_type];
        if(con != 0) {
            pet *cur_p = pet::createPet(con, owners, info);
            pets.emplace(cur_p->getPetID(), cur_p);
        }
        else{
            std::cerr << "\nunknown type!\n";
        }


        // implementing classic factory method
//        Factory* cur_pet;
//        types con = convert[cur_type];
//        bool flag = false;
//        switch (con) {
//            case Dog:
//                cur_pet = new DogFactory;
//                break;
//            case Cat:
//                cur_pet = new CatFactory;
//                break;
//            case Frog:
//                cur_pet = new FrogFactory;
//                break;
//            default:
//                flag = true;
//                std::cerr << "\nunknown type: " << cur_type << '\n';
//                break;
//        }
//
//        if(!flag) {
//            auto cur_p = cur_pet->createPet(info);
//            auto it = -1;
//            for (size_t i = 0; i < owners.size(); ++i) {
//                if (owners[i]->getOwnerName() == ownerName) {
//                    it = i;
//                }
//            }
//            if (it == -1) {
//                owner *cur_owner = new owner(ownerName);
//                cur_owner->addPetID(cur_p->getPetID());
//                owners.emplace_back(cur_owner);
//                cur_p->setOwner(cur_owner);
//            } else {
//                owners[it]->addPetID(cur_p->getPetID());
//                cur_p->setOwner(owners[it]);
//            }
//
//            pets.emplace(cur_p->getPetID(), cur_p);
//        }

        copy = info;
        info.clear();
    }

    while(true){    // menu
        char sym;
        std::cout << "\nEnter \"1\" to continue\nEnter other button to quit\n";    //  asking if user wants to continue
        std::cin >> sym;
        if(sym != '1')    // quits the cycle if user doesnt enter necessary value
            break;

        point:    // goto point
        std::cout << "-----------------------------------menu-----------------------------------\n"
                  << "1)Count the number of different types of animals each owner has\n"
                  << "2)For a specific type of animal (entered by the user), display all its ownersInfo and names\n"
                  << "3)Determine how many species of animals have a certain nickname (the nickname is entered by the user)\n"
                  << "4)Display information about the age of the oldest and youngest animal of each species\n"
                  << "5)Display information about all pets\n";    // option of menu

        int choice = 0;
        std::cin >> choice;    // reading users choice in menu

        bool flag = false;

        std::string user_type;
        std::string user_nickname;
        std::map <std::string, std::pair<int, int>> pets_age;  // case 4

        if(pets.empty())
            std::cerr << "No pets!\n";

        std::cout << "-----------------------------------\n";
        switch (choice) {
            case 1:   // number of different types of animals each owner has
                for(const auto& a : owners){
                    std::cout << "Owner " << a->getOwnerName() << " has " << a->getPetsAmount() << " types of pets: ";
                    std::vector <int> cur_ids(a->getPetVectorID());
                    for(const auto b : cur_ids){
                        std::cout << pets[b]->getType() << "; ";
                    }
                    std::cout << '\n';
                }
                std::cout << "\n---------------------------------------------" <<'\n';
                break;
            case 2:  // for a specific type of animal display all its ownersInfo and names
                std::cout << "Enter the type of pet you want to display info about: ";
                std::cin >> user_type;
                std::transform(user_type.begin(), user_type.end(), user_type.begin(), ::tolower);
                for(const auto& a : pets){
                    if(a.second->getType() == user_type){
                        a.second->getInfo();
                        std::cout << "---------------------------------------------" <<'\n';
                        flag = true;
                    }
                }
                if(!flag)
                    std::cerr << "No pets with needed type\n";
                break;
            case 3:   // determine how many species of animals have a certain nickname
                std::cout << "Enter the nickname with which you want to display pets: ";
                std::cin >> user_nickname;
                std::transform(user_nickname.begin(), user_nickname.end(), user_nickname.begin(), ::tolower);
                for(const auto& a : pets){
                    if(a.second->getNickname() == user_nickname){
                        a.second->getInfo();
                        std::cout << "---------------------------------------------" <<'\n';
                        flag = true;
                    }
                }
                if(!flag)
                    std::cerr << "No pets with needed nickname\n";
                break;
            case 4:  // oldest and youngest
                for(auto a : pets){
                    if(a.second->getAge() > pets_age[a.second->getType()].second){
                        pets_age[a.second->getType()].second = a.second->getAge();
                    }
                    if(pets_age[a.second->getType()].first == 0){
                        pets_age[a.second->getType()].first = a.second->getAge();
                    }
                    if(pets_age[a.second->getType()].first > a.second->getAge()){
                        pets_age[a.second->getType()].first = a.second->getAge();
                    }
                }
                for(const auto& a : pets_age){
                    std::cout << "Type " << a.first << " : " << "Youngest->" << a.second.first << ", Oldest->" << a.second.second << '\n';
                }
                std::cout << "---------------------------------------------" <<'\n';
                break;
            case 5:   // all info about all pets
                for(const auto a : pets){
                    a.second->getInfo();
                    std::cout << "---------------------------------------------" <<'\n';
                }
                break;
            default:   // remaining case
                std::cout << "Choice was not correct! If you want to continue, press 1\n";
                std::cin >> sym;
                if(sym == '1')
                    goto point;
        }
    }

    for(const auto& a : pets){    // calling behavior method for all existing pets
        std::string nick = a.second->getNickname();
        if(nick.empty())
            nick = "unknown";
        std::cout << nick << ": ";
        a.second->behavior();
    }

    pet* b = pets[1];
    pet* a = std::move(b);
    //std::cout << "\n" << b->getAge() << " " << b->getNickname() << " " << b->getOwnerName();
    //std::cout << "\n" << a->getAge() << " " << a->getNickname() << " " << a->getOwnerName();
    b->getInfo();
    std::cout << "\n\n\n";
    a->getInfo();
    for(const auto& a : pets){    // releasing pets memory
        delete a.second;
    }
    for(const auto& a : owners){  // releasing owners memory
        delete a;
    }

    CompositePet* army = new CompositePet;
    for(int i = 0; i < 2; ++i){
        army->addPet(createTeam());
    }
    std::cout << "\n\nOverall strength: " << army->getStrength() << '\n';
    delete army;



    return 0;
}
