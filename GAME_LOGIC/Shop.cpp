//
// Created by ml on 2026/7/6.
//

#include "Shop.h"
#include "../Utils.h"

//public
Shop::Shop() {
    displayUnits.resize(5,nullptr);
    ownedUnits.resize(40,nullptr);
}

Shop::~Shop() {
    for (int i = 0; i < 5; i++) {
        delete displayUnits[i];
    }
    for (int i = 0; i < ownedUnits.size(); i++) {
        delete ownedUnits[i];
    }
}

Unit* Shop::getUnitAtDisplay(const int pos) const{
    if (pos<0 || pos>5) {
        return nullptr;
    }
    return displayUnits[pos];
}

Unit* Shop::getUnitAtOwned(int pos) const {
    if (pos<0 || pos>5) {
        return nullptr;
    }
    return ownedUnits[pos];
}

void Shop::changeUnitAtToDisplay(int pos, Unit *u) {
    if (pos<0 || pos>5) {
        return;
    }
    displayUnits[pos] = u;
}

void Shop::addUnitToOwned(Unit* u) {
    if (u==nullptr) {return;}
    for (int i = 0; i < 40; i++) {
        if (ownedUnits[i]==nullptr) {
            ownedUnits[i] = u;
            break;
        }
    }
}

void Shop::removeUnitAtOwned(int pos) {
    if (pos<0 || pos>40) {
        return;
    }
    delete ownedUnits[pos];
    ownedUnits[pos] = nullptr;
}

void Shop::refresh() {
    //清理旧内存
    for (int i = 0; i < 5; ++i) {
        delete displayUnits[i];
        displayUnits[i] = nullptr;
    }
    //使用新内存
    for (int i = 0; i < 5;++i) {
        std::string randUnit_name = "null";
        int randUnit_level = 1;

        int randType = randomNum(0,30);
        if (randType<=30) { randUnit_name="Assassin";}
        if (randType<=20) { randUnit_name="Knight";}
        if (randType<=10) { randUnit_name="Mage";}

        int randLevel = randomNum();
        if (randLevel<30) {
            randUnit_level=2;
        }
        if (randLevel<10) {
            randUnit_level=3;
        }

        if (randUnit_name=="Knight") {
            displayUnits[i]=new Knight(randUnit_level,0);
        }
        else if (randUnit_name=="Mage") {
            displayUnits[i]=new Mage(randUnit_level,0);
        }
        else if (randUnit_name=="Assassin") {
            displayUnits[i]=new Assassin(randUnit_level,0);
        }
    }
}

void Shop::gameReset() {
    //管理生命周期，所以delete然后置空
    for (int i = 0; i < 5; ++i) {
        delete displayUnits[i];
        displayUnits[i] = nullptr;
    }
    for (int i = 0; i < 40; ++i) {
        delete ownedUnits[i];
        ownedUnits[i] = nullptr;
    }
}
