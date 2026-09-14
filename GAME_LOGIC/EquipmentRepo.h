//
// Created by ml on 2026/7/6.
//

#ifndef MY_ARENA_EQUIPMENTREPO_H
#define MY_ARENA_EQUIPMENTREPO_H

#include <vector>

#include "../ENTITY/Equipment.h"


class EquipmentRepo {
    std::vector<Equipment*> displayEquipments;
    std::vector<Equipment*> ownedEquipments;

public:
    EquipmentRepo();
    ~EquipmentRepo();
    //数据接口
    Equipment* getEquipmentAtDisplay(int pos)const;
    Equipment* getEquipmentAtOwned(int pos)const;
    //修改接口
    void changeEquipmentAtToDisplay(int pos,Equipment* equ);
    void changeEquipmentAtToOwned(int pos,Equipment* equ);
};


#endif //MY_ARENA_EQUIPMENTREPO_H