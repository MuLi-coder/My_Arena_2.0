//
// Created by ml on 2026/7/6.
//

#ifndef MY_ARENA_EQUIPMENTWIDGET_H
#define MY_ARENA_EQUIPMENTWIDGET_H

#include <QWidget>
#include "../ENTITY/Equipment.h"
class EquipmentWidget : public QWidget{
    Q_OBJECT
    QLabel *label;
    //绑定的装备
    Equipment* bundledEquipment;
public:
    EquipmentWidget(QWidget *parent);

    void setEquipment(Equipment* equipment);
};


#endif //MY_ARENA_EQUIPMENTWIDGET_H