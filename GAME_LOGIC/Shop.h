//
// Created by ml on 2026/7/6.
//

#ifndef MY_ARENA_SHOP_H
#define MY_ARENA_SHOP_H
#include <vector>

#include "../ENTITY/Unit.h"
#include "../ENTITY/Hero/Knight.h"
#include "../ENTITY/Hero/Mage.h"
#include "../ENTITY/Hero/Assassin.h"

class Shop {
    std::vector<Unit*> displayUnits;
    std::vector<Unit*> ownedUnits;

    //私有辅助函数

public:
    Shop();
    ~Shop();
    //数据接口
    Unit* getUnitAtDisplay(int pos)const;
    Unit* getUnitAtOwned(int pos)const;
    //修改接口
    void changeUnitAtToDisplay(int pos,Unit* u);
    void addUnitToOwned(Unit* u);
    void removeUnitAtOwned(int pos);
    //刷新
    void refresh();
    //重置接口
    void gameReset();
};


#endif //MY_ARENA_SHOP_H