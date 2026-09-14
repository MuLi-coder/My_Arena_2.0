//
// Created by ml on 2026/7/6.
//

#ifndef MY_ARENA_UNITPANEL_H
#define MY_ARENA_UNITPANEL_H

#include <QPushButton>
#include <QWidget>
#include "../ENTITY/Unit.h"


class UnitPanel : public QWidget{
    Q_OBJECT
    //绑定英雄
    Unit* bundledUnit;
    //标签
    QLabel* name_L;
    QLabel* image;
    QLabel* level_L;
    QLabel* cost_L;
    QLabel* att_L;
    QLabel* attArea_L;
    QLabel* attCD_L;
    QLabel* maxHp_L;
    QLabel* maxMana_L;
    QLabel* moveCD_L;
    QLabel* skillIntro_L;
    //按钮
    QPushButton* buyButton;
    QPushButton* cancelButton;
    signals:
    void buyButtonClicked(Unit* unit);
public:
    UnitPanel(QWidget* parent=nullptr);
    void setUnit(Unit* unit);
};


#endif //MY_ARENA_UNITPANEL_H