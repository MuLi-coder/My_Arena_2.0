//
// Created by ml on 2026/7/10.
//

#ifndef MY_ARENA_KNIGHT_H
#define MY_ARENA_KNIGHT_H

#include "../Unit.h"

class Knight : public Unit{
public:
    Knight(int l,int o);
    void reset()override;
    void skillAttack(const std::vector<std::vector<Unit *>> &grid, Coord self, Coord enemy) override;
};


#endif //MY_ARENA_KNIGHT_H