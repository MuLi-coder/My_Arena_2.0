//
// Created by ml on 2026/7/6.
//

#ifndef MY_ARENA_EQUIPMENT_H
#define MY_ARENA_EQUIPMENT_H

#include <QString>
#include <random>

struct EquipmentData {
    QString image;

};


class Equipment {
    QString image;

public:
    Equipment();

    EquipmentData getData();
};


#endif //MY_ARENA_EQUIPMENT_H