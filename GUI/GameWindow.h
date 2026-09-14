#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <memory>
#include <iostream>
#include "../GAME_LOGIC/GameManager.h"
#include "ParaWidget.h"
#include "UnitWidget.h"
#include "EquipmentWidget.h"
#include "UnitPanel.h"
#include "EquipmentPanel.h"
#include "../Utils.h"



class GameWindow : public QWidget {
    Q_OBJECT
    const int CELL_SIZE = 60;
    std::unique_ptr<GameManager> gameManager;
    //参数面板控件
    ParaWidget* paraWidget;
    //格子控件存储
    std::vector<std::vector<QWidget*>> cellGrid;
    std::vector<QWidget*> cellBench;
    std::vector<QWidget*> cellEquipmentRepo;
    std::vector<QWidget*> cellShop;
    //按钮控件存储
    QPushButton* startButton;
    QPushButton* levelUpButton;
    QPushButton* prepareButton;
    QPushButton* combatButton;
    QPushButton* pauseButton;
    QPushButton* saveButton;
    QPushButton* loadButton;
    QPushButton* shopButton;
    //单位控件存储
    std::vector<std::vector<UnitWidget*>> grid;
    std::vector<UnitWidget*> bench;
    std::vector<EquipmentWidget*> equipmentRepo;
    std::vector<UnitWidget*> shop;
    //子页面
    UnitPanel* unitPanel;
    // EquipmentPanel* equipmentPanel;
    //拖拽功能参数
    bool isDragging;
    int dragFromX, dragFromY,dragFromPos;
    int dragToX, dragToY,dragToPos;

private slots:
    //GameManager
    void failToCombat_Message(int error);
    void failToDrag_Message(int error);
    void failToLevelUp_Message(int error);
    void failToRefreshShop_Message(int error);
    void failToBuy_Message(int error);
    void journeyEnd_Message();
    void resolve_Message(std::string result);
    void gameStateChanged_Deal(GameState gameState);
    //QWidget
    void buyButtonClicked_Deal(Unit* unit);

public:
    explicit GameWindow(QWidget *parent = nullptr);
    void updateUI(std::vector<Coord> hitCoords={});

    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

};

#endif // GAMEWINDOW_H