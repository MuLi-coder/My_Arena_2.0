//
// Created by ml on 2026/7/10.
//

#include "Knight.h"

#include "../../Utils.h"

Knight::Knight(int l,int o): Unit(l,o) {
    //固定属性直接绑定
    name = "Knight";
    //非固定属性，初始化为相应等级属性
    cost = 5+10*(level-1);
    switch (level) {
        case 1:
            image = "../images/Knight1.png";
            break;
        case 2:
            image = "../images/Knight2.png";
            break;
        case 3:
            image = "../images/Knight3.png";
            break;
        default:
            image = "NULL";
    }
    att = 10+10*(level-1);
    attArea = 1;
    maxHp = 100+20*(level-1);
    maxMana = 10-1*(level-1);
    attCD = 10-1*(level-1);
    moveCD = 10-1*(level-1);
    //血量，蓝量，攻击，移动---动态属性都点满
    hp = maxHp;
    mana = 0;
    attTick = attCD;
    moveTick = 0;
    //技能描述
    skillIntro = "SKILL:\n70%几率1.5倍暴击\n20%几率2倍暴击\n8%几率3倍暴击\n2%几率5倍暴击";
}

void Knight::reset() {
    //依照等级重置非固定属性
    cost = 5+10*(level-1);
    switch (level) {
        case 1:
            image = "../images/Knight1.png";
            break;
        case 2:
            image = "../images/Knight2.png";
            break;
        case 3:
            image = "../images/Knight3.png";
            break;
        default:
            image = "NULL";
    }
    att = 10+10*(level-1);
    attArea = 1;
    maxHp = 100+20*(level-1);
    maxMana = 10-1*(level-1);
    attCD = 10-1*(level-1);
    moveCD = 10-1*(level-1);
    //血量，蓝量，攻击，移动---动态属性都点满
    hp = maxHp;
    mana = 0;
    attTick = attCD;
    moveTick = 0;
}

void Knight::skillAttack(const std::vector<std::vector<Unit *> > &grid, Coord self, Coord enemy) {
    int rand = randomNum();
    if (rand<70) {
        grid[enemy.x][enemy.y]->takeDamage(att*1.5);
    }
    else if (rand<90) {
        grid[enemy.x][enemy.y]->takeDamage(att*2);
    }
    else if (rand<98) {
        grid[enemy.x][enemy.y]->takeDamage(att*3);
    }else {
        grid[enemy.x][enemy.y]->takeDamage(att*5);
    }
}
