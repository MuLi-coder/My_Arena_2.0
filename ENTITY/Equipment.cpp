//
// Created by ml on 2026/7/6.
//

#include "Equipment.h"

Equipment::Equipment() {
    image = "NULL";
}

EquipmentData Equipment::getData() {
    EquipmentData data;
    data.image = image;
    return data;
}
