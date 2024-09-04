#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

class pet{
    public:
    virtual void Behavior() const = 0;
    virtual void BadBehavior() const = 0;
protected:
    string ownerName;
    string type;
    string name;
    int age;
};

class dog : public pet{
public:
    void Behavior() const{
        cout << "Dog is barking. Wuaf! Wuaf!";
    }
    void BadBehavior() const{
        cout << "Dog is shy. Hm...";
    }
};

class cat : public pet{
public:
    void Behavior() const{
        cout << "Cat is meowing. Meow! Meow!";
    }
    void BadBehavior() const{
        cout << "Cat is shy. Hm...";
    }
};

class fish : public pet{
public:
    void Behavior() const{
        cout << "Fish is swimming. Fshh! Wooh!";
    }
    void BadBehavior() const{
        cout << "Fish is on top of the water. Hm... I think it is dead(";
    }
};

int main(){
    ifstream fin("zhivotnie.txt");
    if(!fin.is_open()){
        cout << "File is not open!";
        return 1;
    }
    else{
        map<string, map<string, set<string> > > ownerAnimals; // owner - type - names
        map<string, set<string> > nameOwners; // name - owners
        map<string, map<string, int> > typeAges; // type - name - age
        string line;
        while(getline(fin,line)){
            istringstream iss(line);
            string owner,type,name;
            int age;
            getline(iss, owner, ',');
            getline(iss, type, ',');
            if (type.empty()) continue; // skip empty
            getline(iss, name, ',');
            if (name.empty()) name = "";
            iss >> age;
            ownerAnimals[owner][type].insert(name); // adress na type gde adress na name peta
            nameOwners[name].insert(owner); // adress na ownera
            typeAges[type][name] = age; // adress na name gde adress na age
        }

        for(auto& owner : ownerAnimals){
            for(auto& petType : owner.second){
                pet* currentPet;
                if(petType.first == "dog"){
                    currentPet = new dog();
                } else if (petType.first == "cat"){
                    currentPet = new cat();
                } else if (petType.first == "fish"){
                    currentPet = new fish();
                } else {
                    continue; // unknown one
                }
                for(auto& petName : petType.second){
                    currentPet->ownerName = owner.first;
                    currentPet->type = petType.first;
                    currentPet->name = petName;
                    currentPet->age = typeAges[petType.first][petName];
            
                    cout << "Owner: " << currentPet->ownerName << ", Pet Type: " << currentPet->type << ", Pet Name: "<< currentPet->name << ", Age: " << currentPet->age << endl;
                    
                    cout << "Behavior: ";
                    currentPet->Behavior();
                    cout << endl;
            
                    cout << "Bad Behavior: ";
                    currentPet->BadBehavior();
                    cout << endl << endl;
                }
            delete currentPet; // Free memory
            }
        }

        //menu
        int choice = 10;
        string animalType;
        string animalName;
        cout << "-------------------------Menu:------------------------" << endl;
        cout << "1.Count different types of animals that each owner has" << endl;
        cout << "2.Enter type of animal and it will show all owners and pet names" << endl;
        cout << "3.Enter pet name and it will show how much same pets there are" << endl;
        cout << "4.Shows information about the youngest and the oldest pet from the list" << endl;
        cout << "5.Exit" << endl;
        cout << "-------------------------------------------------------";
        while(1){
            cout << endl << "Your choice: ";
            cin >> choice;
            switch(choice){
                case 1:{
                    for(const auto& [owner, animals] : ownerAnimals){
                        int numTypes = animals.size();
                        cout << "Owner: " << owner << ", Number of animal types: " << numTypes << endl;
                    }
                    break;
                }
                case 2:{
                    cout << "Enter animal type: ";
                    cin >> animalType;
                    if(typeAges.find(animalType) != typeAges.end()){
                        for (const auto& [name, age] : typeAges[animalType]){
                            for (const auto& owner : nameOwners[name]){
                                cout << "Owner: " << owner << ", Name: " << name << endl;
                            }
                        }
                    }
                    else{
                        cout << "No animals of type " << animalType << endl;
                    }
                    break;
                }
                case 3:{
                    cout << "Enter animal name: ";
                    cin >> animalName;
                    if(nameOwners.find(animalName) != nameOwners.end()){
                        int numOwners = nameOwners[animalName].size();
                        cout << "Number of owners for type of animal " << animalName << ": " << numOwners << endl;
                    }
                    else{
                        cout << "No animal with name " << animalName << endl;
                    }
                    break;
                }
                case 4:{
                    for (const auto& [type, animals] : typeAges) {
                        int maxAge = 0, minAge = INT_MAX;
                        string oldAnimal, youngAnimal;
                        for (const auto& [name, age] : animals) {
                            if (age > maxAge) {
                                maxAge = age;
                                oldAnimal = name;
                            }
                            if (age < minAge) {
                                minAge = age;
                                youngAnimal = name;
                            }
                        }
                        if (!animals.empty()) {
                            cout << "Type: " << type << ", Oldest: " << oldAnimal << maxAge << "years, Youngest: " << youngAnimal << minAge << " years" << endl;
                        }
                    }
                    break;
                }
                case 5:
                    exit(1);
                default:
                    cout << "Wrong input number, it should be from 1 to 5" <<endl;
            }
        }
    }
}