//
// Created by ml on 2026/7/6.
//

#ifndef MY_ARENA_PREBOARD_H
#define MY_ARENA_PREBOARD_H

#include <vector>

#include "../ENTITY/Unit.h"
#include "../Utils.h"

class PreBoard {

    std::vector<std::vector<Unit*>> grid;
    std::vector<Unit*> bench;

public:
    PreBoard();
    //数据接口
    Unit* getUnitAtGrid(int r,int c)const;
    Unit* getUnitAtBench(int pos)const;
    //修改接口
    void changeUnitAtToGrid(int r,int c,Unit* u);
    void changeUnitAtToBench(int pos,Unit* u);
    //重置接口
    void gameReset();
};


#endif //MY_ARENA_PREBOARD_H