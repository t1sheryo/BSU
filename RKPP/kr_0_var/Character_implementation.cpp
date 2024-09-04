#include <utility>
#include "Character.h"

Character::Character(): charID(++generalID), name("unknown"), state(defaultState), race(defaultRace), IsMoving(false) { ObjectNumber++; }

Character::Character(std::string n, std::string s, std::string r, bool m): charID(++generalID), race(convertRace[r]) {
    name = n;
    state = convertState[s];
    IsMoving = m;
    ObjectNumber++;
}
