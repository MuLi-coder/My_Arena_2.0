//
// Created by ml on 2026/7/15.
//

#ifndef MY_ARENA_MAGE_H
#define MY_ARENA_MAGE_H

#include "../Unit.h"

class Mage :public Unit{
public:
    Mage(int l,int o);
    void reset()override;
    void skillAttack(const std::vector<std::vector<Unit *>> &grid, Coord self, Coord enemy) override;
};


#endif //MY_ARENA_MAGE_H