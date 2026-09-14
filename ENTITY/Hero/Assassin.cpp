//
// Created by ml on 2026/7/15.
//

#include "Assassin.h"
#include "../../Utils.h"

Assassin::Assassin(int l,int o): Unit(l,o) {
    //固定属性直接绑定
    name = "Assassin";
    //非固定属性，初始化为相应等级属性
    cost = 15+10*(level-1);
    switch (level) {
        case 1:
            image = "../images/Assassin1.png";
            break;
        case 2:
            image = "../images/Assassin2.png";
            break;
        case 3:
            image = "../images/Assassin3.png";
            break;
        default:
            image = "NULL";
    }
    att = 30+15*(level-1);
    attArea = 1;
    maxHp = 60+10*(level-1);
    maxMana = 10-(level-1);
    attCD = 6-1*(level-1);
    moveCD = 5-1*(level-1);
    //血量，蓝量，攻击，移动---动态属性都点满
    hp = maxHp;
    mana = 0;
    attTick = attCD;
    moveTick = 0;
    //技能描述
    skillIntro = "SKILL:\n一剑封喉：锁定目标直接击杀";
}

void Assassin::reset() {
    //依照等级重置非固定属性
    cost = 15+10*(level-1);
    switch (level) {
        case 1:
            image = "../images/Assassin1.png";
            break;
        case 2:
            image = "../images/Assassin2.png";
            break;
        case 3:
            image = "../images/Assassin3.png";
            break;
        default:
            image = "NULL";
    }
    att = 30+15*(level-1);
    attArea = 1;
    maxHp = 60+10*(level-1);
    maxMana = 10-(level-1);
    attCD = 6-1*(level-1);
    moveCD = 5-1*(level-1);
    //血量，蓝量，攻击，移动---动态属性都点满
    hp = maxHp;
    mana = 0;
    attTick = attCD;
    moveTick = 0;
}

void Assassin::skillAttack(const std::vector<std::vector<Unit *> > &grid, Coord self, Coord enemy) {
    if (enemy.x>=0 && enemy.x<ROW && enemy.y>=0 && enemy.y<COL) {
        grid[enemy.x][enemy.y]->takeDamage(1000);
    }
}
