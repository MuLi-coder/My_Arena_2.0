//
// Created by ml on 2026/7/6.
//

#include "PreBoard.h"

PreBoard::PreBoard()
{
    grid.resize(ROW,std::vector<Unit*>(COL,nullptr));
    bench.resize(BEN,nullptr);
}

Unit* PreBoard::getUnitAtGrid(const int r,const int c) const{
    if (r<0 || r>=ROW || c<0 || c>=COL) {return nullptr;}
    return grid[r][c];
}

Unit* PreBoard::getUnitAtBench(const int pos) const {
    if (pos<0 || pos>=BEN) {return nullptr;}
    return bench[pos];
}

void PreBoard::changeUnitAtToGrid(const int r,const int c,Unit* u) {
    if (r<0 || r>=ROW || c<0 || c>=COL) {return;}
    //只要被拖上场，则标记为在战场中，只有被拉回备战区，状态才更改
    if (u) {
       u->changeIsInGridTo(true);
    }
    grid[r][c] = u;
}

void PreBoard::changeUnitAtToBench(int pos, Unit *u) {
    if (pos<0 || pos>=BEN) {return;}
    //只有被拉到备战区，状态才发生改变
    if (u) {
        u->changeIsInGridTo(false);
    }
    bench[pos] = u;
}

void PreBoard::gameReset() {
    //由于不管理生命周期，所以直接置空即可
    for (int r=0;r<ROW;r++) {
        for (int c=0;c<COL;c++) {
            grid[r][c] = nullptr;
        }
    }
    for (int k=0;k<BEN;k++) {
        bench[k]=nullptr;
    }
}
