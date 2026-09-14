//
// Created by ml on 2026/7/6.
//

#include "Unit.h"

#include "../Utils.h"

Unit::Unit(int l,int o):level(l),owner(o) {
    isInGrid = false;
    isDone = false;
}

//private
Coord Unit::searchEnemy(const std::vector<std::vector<Unit*>> &grid,Coord self) {
    Coord enemy = {-1,-1};
    //曼哈顿距离,最大值14，菱形搜索
    int dist = 1;
    while (dist<15) {
        for (int k=0;k<dist;++k) {
            std::vector<Coord> unitCoords=
                {{self.x-dist+k,self.y+k},{self.x+k,self.y+dist-k},{self.x+dist-k,self.y-k},{self.x-k,self.y-dist+k}};
            for (int i=0;i<4;++i) {
                Coord unitCoord = unitCoords[i];
                if (unitCoord.x>=0 && unitCoord.x<ROW && unitCoord.y>=0 && unitCoord.y<COL) {
                    Unit* unit = grid[unitCoord.x][unitCoord.y];
                    if (unit && unit->owner != owner) {
                        enemy = {unitCoord.x,unitCoord.y};
                        return enemy;
                    }
                }
            }
        }
        ++dist;
    }
    return enemy;
}

Coord Unit::searchMoveTarget(const std::vector<std::vector<Unit*>> &grid,Coord self,Coord enemy) {
    int dist = grid[self.x][self.y]->attArea;
    Coord target = enemy;
    int minDistToTarget = 50;

    for (int k=0;k<dist;++k) {
        std::vector<Coord> unitCoords=
            {{enemy.x-dist+k,enemy.y+k},{enemy.x+k,enemy.y+dist-k},{enemy.x+dist-k,enemy.y-k},{enemy.x-k,enemy.y-dist+k}};
        for (int i=0;i<4;++i) {
            Coord unitCoord = unitCoords[i];
            if (unitCoord.x>=0 && unitCoord.x<ROW && unitCoord.y>=0 && unitCoord.y<COL) {
                Unit* unit = grid[unitCoord.x][unitCoord.y];
                if (!unit) {
                    int distance = manhattanDist(self.x,self.y,unitCoord.x,unitCoord.y);
                    if (distance<=minDistToTarget) {
                        minDistToTarget = distance;
                        target = unitCoord;
                    }
                }
            }
        }
    }
    return target;
}

std::string Unit::getMovement(const std::vector<std::vector<Unit*>> &grid,Coord self,Coord target) {
    //首先确定行动方向优先顺序
    std::vector<std::string> moveSequence;
    Coord direction = {target.x-self.x,target.y-self.y};
    int dx = std::abs(direction.x);
    int dy = std::abs(direction.y);
    if ( dx==0 || dy==0 ) {
        if (dx==0) {
            moveSequence.push_back(direction.y>0?"Right":"Left");
            moveSequence.push_back("Up");
            moveSequence.push_back("Down");
            moveSequence.push_back(direction.y<0?"Right":"Left");
        }
        if (dy==0) {
            moveSequence.push_back(direction.x>0?"Down":"Up");
            moveSequence.push_back("Right");
            moveSequence.push_back("Left");
            moveSequence.push_back(direction.x<0?"Down":"Up");
        }
    }
    else {
        std::string movement1 = direction.x>0?"Down":"Up";
        std::string movement2 = direction.y>0?"Right":"Left";
        if (dx>=dy) {
            moveSequence.push_back(movement1);
            moveSequence.push_back(movement2);
            moveSequence.push_back(direction.y<0?"Right":"Left");
            moveSequence.push_back(direction.x<0?"Down":"Up");
        }
        else {
            moveSequence.push_back(movement2);
            moveSequence.push_back(movement1);
            moveSequence.push_back(direction.x<0?"Down":"Up");
            moveSequence.push_back(direction.y<0?"Right":"Left");
        }
    }
    //下面进行尝试决策
    for (int i=0;i<4;++i) {
        std::string action = moveSequence[i];
        if (action=="Left" && self.y-1>=0 && !grid[self.x][self.y-1]) {
            return "Left";
        }
        if (action=="Right" && self.y+1<COL && !grid[self.x][self.y+1]) {
            return "Right";
        }
        if (action=="Up" && self.x-1>=0 && !grid[self.x-1][self.y]) {
            return "Up";
        }
        if (action=="Down" && self.x+1<ROW && !grid[self.x+1][self.y]) {
            return "Down";
        }
    }
    return "Null";
}


void Unit::changeLevelFor(int change) {
    level += change;
    //越界调整
    if (level<1) {
        level = 1;
    }
    else if (level>3) {
        level = 3;
    }
}

void Unit::changeIsInGridTo(bool is) {
    isInGrid = is;
}

void Unit::changeIsDoneTo(bool is) {
    isDone = is;
}

UnitData Unit::getData() const{
    UnitData data;
    data.name = name;
    data.owner = owner;
    data.level = level;
    data.cost = cost;
    data.image = image;
    data.att = att;
    data.attArea = attArea;
    data.maxHp = maxHp;
    data.maxMana = maxMana;
    data.attCD = attCD;
    data.moveCD = moveCD;
    data.hp = hp;
    data.mana = mana;
    data.attTick = attTick;
    data.moveTick = moveTick;
    data.skillIntro = skillIntro;
    data.isInGrid = isInGrid;
    data.isDone = isDone;
    return data;
}

void Unit::takeDamage(int damage) {
    hp-=damage;
    if (hp<0) {
        hp=0;
    }
}


Action Unit::decideAction(const std::vector<std::vector<Unit*>> &grid,Coord self) {
    Action action = {Action::Idle,Action::Left,Action::CommonAtt,{-1,-1}};
    Coord enemy = searchEnemy(grid,self);
    int distance = manhattanDist(self.x,self.y,enemy.x,enemy.y);

    if (distance>attArea) {
        if (moveTick<moveCD) {
            action.type = Action::Idle;
            moveTick+=1;
            return action;
        }
        if (moveTick==moveCD) {
            action.type = Action::Move;
            Coord target = searchMoveTarget(grid,self,enemy);
            std::string movement = getMovement(grid,self,target);
            if (movement=="Left") {
                action.movement = Action::Left;
                moveTick = 0;
                return action;
            }
            if (movement=="Right") {
                action.movement = Action::Right;
                moveTick = 0;
                return action;
            }
            if (movement=="Up") {
                action.movement = Action::Up;
                moveTick = 0;
                return action;
            }
            if (movement=="Down") {
                action.movement = Action::Down;
                moveTick = 0;
                return action;
            }
            if (movement=="Null") {
                action.type = Action::Idle;
                return action;
            }
        }
    }

    if (distance<=attArea) {
        if (attTick<attCD) {
            action.type = Action::Idle;
            attTick+=1;
            return action;
        }
        if (attTick==attCD) {
            if (mana<maxMana) {
                action.type = Action::Attack;
                grid[enemy.x][enemy.y]->takeDamage(att);
                action.attType = Action::CommonAtt;
                action.target = enemy;
                attTick=0;
                mana+=1;
                return action;
            }
            if (mana==maxMana) {
                action.type = Action::Attack;
                this->skillAttack(grid,self,enemy);
                action.attType = Action::SkillAtt;
                action.target = enemy;
                attTick=0;
                mana=0;
                return action;
            }
        }
    }
    return action;
}
