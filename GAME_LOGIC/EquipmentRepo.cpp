//
// Created by ml on 2026/7/6.
//

#include "EquipmentRepo.h"

EquipmentRepo::EquipmentRepo() {
    displayEquipments.resize(5,nullptr);
    ownedEquipments.resize(5,nullptr);
}

EquipmentRepo::~EquipmentRepo() {
    for (int i = 0; i < 5; i++) {
        delete ownedEquipments[i];
    }
}

Equipment* EquipmentRepo::getEquipmentAtDisplay(const int pos) const {
    if (pos<0 || pos>5) {
        return nullptr;
    }
    return displayEquipments[pos];
}

Equipment* EquipmentRepo::getEquipmentAtOwned(const int pos) const {
    if (pos<0 || pos>5) {
        return nullptr;
    }
    return ownedEquipments[pos];
}

void EquipmentRepo::changeEquipmentAtToDisplay(int pos, Equipment *equ) {
    if (pos<0 || pos>5) {
        return;
    }
    displayEquipments[pos] = equ;
}

void EquipmentRepo::changeEquipmentAtToOwned(int pos, Equipment *equ) {
    if (pos<0 || pos>5) {
        return;
    }
    ownedEquipments[pos] = equ;
}
