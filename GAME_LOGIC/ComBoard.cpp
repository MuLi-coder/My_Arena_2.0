//
// Created by ml on 2026/7/6.
//

#include "ComBoard.h"

ComBoard::ComBoard() {
    grid.resize(ROW,std::vector<Unit*>(COL,nullptr));
}

void ComBoard::setBoard(const PreBoard* board) {
    for (int r=0;r<ROW;r++) {
        for (int c=0;c<COL;c++) {
            grid[r][c] = board->getUnitAtGrid(r,c);
        }
    }
}
Unit* ComBoard::getUnitAt(const int r,const int c) const {
    if (r<0 || r>=ROW || c<0 || c>=COL) {
        return nullptr;
    }
    return grid[r][c];
}

void ComBoard::changeUnitAtTo(int r, int c, Unit* u) {
    if (r<0 || r>=ROW || c<0 || c>=COL) {return;}
    grid[r][c] = u;
}

std::vector<Coord> ComBoard::marchEveryUnit() {
    //我们存储一下所有的受击坐标，向上传
    std::vector<Coord> hitCoords = {};
    //遍历每一个单位
    for (int r=0;r<ROW;r++) {
        for (int c=0;c<COL;c++) {
            Unit* unit = grid[r][c];
            if (unit && !unit->getData().isDone) {
                unit->changeIsDoneTo(true);
                Coord selfCoord = {r,c};
                Action action = unit->decideAction(grid,selfCoord);
                switch (action.type) {
                    case Action::Move:
                        switch (action.movement) {
                            case Action::Left:
                                grid[r][c-1] = unit;
                                grid[r][c] = nullptr;
                                break;
                            case Action::Right:
                                grid[r][c+1] = unit;
                                grid[r][c] = nullptr;
                                break;
                            case Action::Up:
                                grid[r-1][c] = unit;
                                grid[r][c] = nullptr;
                                break;
                            case Action::Down:
                                grid[r+1][c] = unit;
                                grid[r][c] = nullptr;
                                break;
                        }
                        break;
                    case Action::Attack:
                        switch (action.attType) {
                            case Action::CommonAtt:
                                hitCoords.push_back(action.target);
                                break;
                            case Action::SkillAtt:
                                hitCoords.push_back(action.target);
                                break;
                        }
                        break;
                    case Action::Idle:
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return hitCoords;
}

void ComBoard::gameReset() {
    for (int r=0;r<ROW;r++) {
        for (int c=0;c<COL;c++) {
            grid[r][c] = nullptr;
        }
    }
}
