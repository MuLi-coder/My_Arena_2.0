//
// Created by ml on 2026/7/15.
//

#include "Mage.h"

#include "../../Utils.h"

Mage::Mage(int l,int o): Unit(l,o) {
    //固定属性直接绑定
    name = "Mage";
    //非固定属性，初始化为相应等级属性
    cost = 7+10*(level-1);
    switch (level) {
        case 1:
            image = "../images/Mage1.png";
            break;
        case 2:
            image = "../images/Mage2.png";
            break;
        case 3:
            image = "../images/Mage3.png";
            break;
        default:
            image = "NULL";
    }
    att = 20+15*(level-1);
    attArea = 2+0.5*(level-1);
    maxHp = 70+20*(level-1);
    maxMana = 15-(level-1);
    attCD = 15-1*(level-1);
    moveCD = 13-1*(level-1);
    //血量，蓝量，攻击，移动---动态属性都点满
    hp = maxHp;
    mana = 0;
    attTick = attCD;
    moveTick = 0;
    //技能描述
    skillIntro = "SKILL:\n大火球：2倍暴击";
}

void Mage::reset() {
    //依照等级重置非固定属性
    cost = 7+10*(level-1);
    switch (level) {
        case 1:
            image = "../images/Mage1.png";
            break;
        case 2:
            image = "../images/Mage2.png";
            break;
        case 3:
            image = "../images/Mage3.png";
            break;
        default:
            image = "NULL";
    }
    att = 20+15*(level-1);
    attArea = 2+0.5*(level-1);
    maxHp = 70+20*(level-1);
    maxMana = 15-(level-1);
    attCD = 15-1*(level-1);
    moveCD = 13-1*(level-1);
    //血量，蓝量，攻击，移动---动态属性都点满
    hp = maxHp;
    mana = 0;
    attTick = attCD;
    moveTick = 0;
}

void Mage::skillAttack(const std::vector<std::vector<Unit *> > &grid, Coord self, Coord enemy) {
    if (enemy.x>=0 && enemy.x<ROW && enemy.y>=0 && enemy.y<COL) {
        grid[enemy.x][enemy.y]->takeDamage(att*2);
    }
}
