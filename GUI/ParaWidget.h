//
// Created by ml on 2026/7/7.
//

#ifndef MY_ARENA_PARAWIDGET_H
#define MY_ARENA_PARAWIDGET_H

#include <QLabel>
#include "../GAME_LOGIC/Player.h"
class ParaWidget : public QWidget {
    Q_OBJECT
    QLabel* image;
    QLabel* score;
    QLabel* level;
    QLabel* hp;
    QLabel* money;
public:
    ParaWidget();
    void updatePara(PlayerData data);
};


#endif //MY_ARENA_PARAWIDGET_H