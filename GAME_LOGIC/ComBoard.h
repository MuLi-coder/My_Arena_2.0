//
// Created by ml on 2026/7/6.
//

#ifndef MY_ARENA_COMBOARD_H
#define MY_ARENA_COMBOARD_H


#include "PreBoard.h"


class ComBoard {
    std::vector<std::vector<Unit*>> grid;

public:
    ComBoard();
    void setBoard(const PreBoard* board);
    //数据接口
    Unit* getUnitAt(int r,int c)const;
    //修改接口
    void changeUnitAtTo(int r,int c,Unit* u);
    //战斗处理函数
    std::vector<Coord> marchEveryUnit();
    //重置接口
    void gameReset();
};


#endif //MY_ARENA_COMBOARD_H