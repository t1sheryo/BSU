#ifndef KR_0_VAR_CHARACTER_H
#define KR_0_VAR_CHARACTER_H

#include <string>
#include <map>

enum State{normal = 0, paralysed, dead, defaultState};
enum Race{human = 0, dwarf, elf, defaultRace};

std::map <std::string, State> convertState {
    {"normal", normal},
    {"paralysed", paralysed},
    {"dead", dead}
};

std::map <std::string, Race> convertRace {
    {"human", human},
    {"dwarf", dwarf},
    {"elf", elf}
};

static int ObjectNumber = 0;

class Character{
private:
    inline static int generalID = 0;
    const int charID;
    std::string name;
    State state;
    const Race race;
    bool IsMoving;
    static int ObjectNumber;

public:
     Character();
     Character(std::string n, std::string s, std::string r, bool m);
     Character(const Character& a);
     void operator=(const Character& a);
     bool operator<(const Character& a);
     friend std::ostream& operator<<(std::ostream out, const Character& a);

     [[nodiscard]] int getId() const{ return charID; }
     [[nodiscard]] std::string getName() const { return name; }
     [[nodiscard]] State getState() const { return state; }
     [[nodiscard]] Race getRace() const { return race; }
     [[nodiscard]] bool getAbilityToMove() const { return IsMoving; }
     [[nodiscard]] int getObjectNumber() const { return ObjectNumber; }

     void setName(std::string n) { name = n; }
     void setState(std::string s) { state = convertState[s]; }
     void setIsMoving(bool m) { IsMoving = m; }
};


#endif //KR_0_VAR_CHARACTER_H
