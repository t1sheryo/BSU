#ifndef INC_0VARIANT_HEADER_H
#define INC_0VARIANT_HEADER_H

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>

enum State{normal = 0, paralysed, dead, defaultState};
enum Race{human = 0, dwarf, elf, defaultRace};

inline static std::string arrayState[4] {"normal", "paralysed", "dead", "defaultState"};
inline static std::string arrayRace[4] {"human", "dwarf", "elf", "defaultRace"};


inline std::map <std::string, State> convertState {
        {"normal", normal},
        {"paralysed", paralysed},
        {"dead", dead},
        {"", defaultState}
};

inline static std::map <std::string, Race> convertRace {
        {"human", human},
        {"dwarf", dwarf},
        {"elf", elf},
        {"", defaultRace}
};

inline static std::map <State, std::string> convertStateToString {
        {normal, "normal"},
        {paralysed, "paralysed"},
        {dead, "dead"},
        {defaultState, ""}
};

inline static std::map <Race, std::string> convertRaceToString {
        {human, "human"},
        {dwarf, "dwarf"},
        {elf, "elf"},
        {defaultRace, ""}
};

class Character{
private:
    inline static int generalID = 0;
    const int charID;
    std::string name;
    State state;
    const Race race;
    bool IsMoving;
    inline static int ObjectNumber = 0;

public:
    Character();
    Character(std::string n, std::string s, std::string r, bool m);
    Character(const Character& a);
    Character(Character&& a) noexcept;
    Character& operator=(const Character& a);
    Character& operator=(const Character&& a) noexcept;
    bool operator==(const Character& a);
    bool operator<(const Character& a);
    bool operator>(const Character& a);
    friend std::ostream& operator<<(std::ostream& out, const Character& a);

    [[nodiscard]] int getId() const{ return charID; }
    [[nodiscard]] std::string getName() const { return name; }
    [[nodiscard]] std::string getState() const { return convertStateToString[state]; }
    [[nodiscard]] std::string getRace() const { return convertRaceToString[race]; }
    [[nodiscard]] bool getAbilityToMove() const { return IsMoving; }
    [[nodiscard]] static int getObjectNumber() { return ObjectNumber; }

    void setName(std::string n) { name = n; }
    void setState(std::string s) { state = convertState[s]; }
    void setIsMoving(bool m) { IsMoving = m; }

    virtual void Print() const;

    virtual ~Character() = default;
};

#endif //INC_0VARIANT_HEADER_H
