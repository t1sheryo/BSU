#ifndef RKPP_pet_H
#define RKPP_pet_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <utility>

class owner{
private:
    static inline int ID_owner = 1;
    const int cur_id;
    std::string ownerName;
    std::vector<int> petIDs;
public:
    owner() : ownerName("unknown"), cur_id(ID_owner++) {}

    explicit owner(std::string name) : ownerName(std::move(name)), cur_id(ID_owner++) {}

    friend bool operator==(owner& a, owner& b){
        if(a.ownerName == b.ownerName)
            return true;
        return false;
    }

    [[nodiscard]] std::string getOwnerName() const{ return ownerName; }

    [[nodiscard]] int getOwnerID() const { return cur_id; }

    void addPetID(int id){ petIDs.push_back(id); }

    [[nodiscard]] size_t getPetsAmount() const{ return petIDs.size(); }

    [[nodiscard]] std::vector<int> getPetVectorID() const { return petIDs; }
};

enum types{Dog = 1, Cat, Frog}; // enum types for factory constructor

class pet{
private:
    static inline int ID_pet = 1;
    const int cur_id;
    int age;
    std::string type;
    std::string nickname;
    owner* own;
public:
    pet() : age(-1), type("unknown"), nickname("unknown"), own(nullptr), cur_id(ID_pet++) {}

    explicit pet(const std::vector <std::string>& info) : cur_id(ID_pet++) {
        nickname = info[2];
        type = info[1];
        age = stoi(info[3]);
        own = nullptr;
    }

    static pet* createPet (const types type, std::vector<owner*>& owners, const std::vector <std::string>& info);

    virtual void behavior() const = 0;

    virtual void getInfo() const = 0;

    [[nodiscard]] std::string getOwnerName() const { return own->getOwnerName(); }

    [[nodiscard]] int getAge() const { return age; }

    [[nodiscard]] std::string getType() const { return type; }

    [[nodiscard]] std::string getNickname() const { return nickname; }

    [[nodiscard]] int getPetID() const { return cur_id; }

    [[nodiscard]] owner* getOwner() const { return own; }

    void setOwner(owner* a) { own = a; }

    virtual ~pet() = default;
};

class cat : public pet{
private:
    std::string origin;
public:
    cat() : origin("unknown") {}

    explicit cat(const std::vector <std::string>& info) : pet(info) { origin = info[4]; }

    void behavior() const override{
        std::cout << "meow!\n";
    }

    void getInfo() const override{
        std::cout << "Type of pet: " << pet::getType() << "\n";
        std::cout << "cats nickname: " << pet::getNickname() << "\n";
        std::cout << "cats owner: " << pet::getOwnerName() << "\n";
        std::cout << "cats age: " << pet::getAge() << "\n";
        std::cout << "cats origin: " << origin << '\n';
    }
};

class dog : public pet{
private:
    std::string breed;
    double weight;
public:
    dog() : breed("unknown"), weight(0) {}

    explicit dog(const std::vector <std::string>& info) : pet(info) { breed = info[4]; weight = stod(info[5]); }

    void behavior() const override {
        std::cout << "gav-gav!\n";
    }

    void getInfo() const override{
        std::cout << "Type of pet: " << pet::getType() << "\n";
        std::cout << "dogs nickname: " << pet::getNickname() << "\n";
        std::cout << "dogs owner: " << pet::getOwnerName() << "\n";
        std::cout << "dogs age: " << pet::getAge() << "\n";
        std::cout << "dogs origin: " << breed << '\n';
        std::cout << "dogs weight: " << weight << '\n';
    }
};

class frog : public pet{
private:
    std::string color;
public:
    frog() : color("unknown") {}

    explicit frog(const std::vector <std::string>& info) : pet(info) { color = info[4]; }

    void behavior() const override {
        std::cout << "kva-kva!\n";
    }

    void getInfo() const override{
        std::cout << "Type of pet: " << pet::getType() << "\n";
        std::cout << "frogs nickname: " << pet::getNickname() << "\n";
        std::cout << "frogs owner: " << pet::getOwnerName() << "\n";
        std::cout << "frogs age: " << pet::getAge() << "\n";
        std::cout << "frogs origin: " << color << '\n';
    }
};

// фабричный метод с обобщенным конструктором
    pet* pet::createPet(const types type,std::vector<owner*>& owners,const std::vector <std::string>& info) {
        pet* p;
        switch (type) {
            case Dog:
                p = new dog(info);
                break;
            case Cat:
                p = new cat(info);
                break;
            case Frog:
                p = new frog(info);
                break;
//            default:
//                std::cerr << "\nunknown type!\n";
        }

        const std::string& name = info[0];
        auto it = -1;
        for(size_t i = 0; i < owners.size(); ++i){
            if(owners[i]->getOwnerName() == name){
                it = i;
            }
        }
        if(it == -1){
            owner* cur_owner = new owner(name);
            cur_owner->addPetID(p->getPetID());
            owners.emplace_back(cur_owner);
            p->setOwner(cur_owner);
        }
        else{
            owners[it]->addPetID(p->getPetID());
            p->setOwner(owners[it]);
        }
        return p;
    }


class Factory{
public:
    virtual pet* createPet(const std::vector<std::string>& info) = 0;
    virtual ~Factory() = default;
};

class DogFactory : public Factory{
public:
    pet* createPet(const std::vector<std::string>& info) override{
        return new dog(info);
    }
};

class CatFactory : public Factory{
public:
    pet* createPet(const std::vector<std::string>& info) override{
        return new cat(info);
    }
};

class FrogFactory : public Factory{
public:
    pet* createPet(const std::vector<std::string>& info) override{
        return new frog(info);
    }
};

#endif //RKPP_pet_H
