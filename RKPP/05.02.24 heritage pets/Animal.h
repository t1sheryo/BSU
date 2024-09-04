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


class pet{
protected:
    std::string owner;
    int age;
    std::string type;
    std::string nickname;

public:

    pet() : owner("unknown"), age(0), type("unknown"), nickname("unknown") {}

    explicit pet(const std::vector <std::string>& info){
        owner = info[0];
        nickname = info[2];
        type = info[1];
        age = stoi(info[3]);
    }

    virtual void behavior() const = 0;

    virtual void getInfo() const = 0;

    [[nodiscard]] std::string getOwner() const { return owner; }

    [[nodiscard]] int getAge() const { return age; }

    [[nodiscard]] std::string getType() const { return type; }

    [[nodiscard]] std::string getNickname() const { return nickname; }

    virtual ~pet(){ /*std::cout << "\npet_destructor called!\n";*/ }
};


class cat : public pet{
private:
    std::string origin;

public:

    cat() : origin("unknown") {}

    explicit cat(const std::vector <std::string>& info) : pet(info) { origin = info[4]; }

    void behavior() const override{
        std::cout << "\nmeow!\n";
    }

    void getInfo() const override{
        std::cout << "Type of pet: " << type << "\n";
        std::cout << "cats nickname: " << nickname << "\n";
        std::cout << "cats owner: " << owner << "\n";
        std::cout << "cats age: " << age << "\n";
        std::cout << "cats origin: " << origin << '\n';
    }

    ~cat() override{ /*std::cout << "\ncat_destructor called!\n";*/ }
};


class dog : public pet{
private:
    std::string breed;
    double weight;

public:

    dog() : breed("unknown"), weight(0) {}

    explicit dog(const std::vector <std::string>& info) : pet(info) { breed = info[4]; weight = stod(info[5]); }

    void behavior() const override {
        std::cout << "\ngav-gav!\n";
    }

    void getInfo() const override{
        std::cout << "Type of pet: " << type << "\n";
        std::cout << "dogs nickname: " << nickname << "\n";
        std::cout << "dogs owner: " << owner << "\n";
        std::cout << "dogs age: " << age << "\n";
        std::cout << "dogs origin: " << breed << '\n';
        std::cout << "dogs weight: " << weight << '\n';
    }

    ~dog() override{ /*std::cout << "\ndog_destructor called!\n";*/ }
};


class frog : public pet{
private:
    std::string color;

public:

    frog() : color("unknown") {}

    explicit frog(const std::vector <std::string>& info) : pet(info) { color = info[4]; }

    void behavior() const override {
        std::cout << "\nkva-kva!\n";
    }

    void getInfo() const override {
        std::cout << "Type of pet: " << type << "\n";
        std::cout << "frogs nickname: " << nickname << "\n";
        std::cout << "frogs owner: " << owner << "\n";
        std::cout << "frogs age: " << age << "\n";
        std::cout << "frogs origin: " << color << '\n';
    }

    ~frog() override{ /*std::cout << "\nfrog_destructor called!\n";*/ }
};


#endif //RKPP_pet_H
