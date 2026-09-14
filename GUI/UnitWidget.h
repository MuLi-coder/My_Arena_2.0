//
// Created by ml on 2026/7/6.
//

#ifndef MY_ARENA_UNITWIDGET_H
#define MY_ARENA_UNITWIDGET_H


#include <QWidget>
#include "../ENTITY/Unit.h"

class UnitWidget : public QWidget{
    Q_OBJECT
    const int CELL_SIZE = 60;

    QLabel* level;
    QLabel* hpBar;
    QLabel* hpLBar;
    QLabel* manaBar;
    QLabel* manaLBar;
    QLabel* image;
    //绑定当前格子的英雄
    Unit* bundledUnit;

public:
    UnitWidget(QWidget *parent);
    bool isBundled();
    bool isBundledUnitOwnedBy(int num);
    void setUnit(Unit* unit);

};


#endif //MY_ARENA_UNITWIDGET_H