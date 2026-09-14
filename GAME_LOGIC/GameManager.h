//
// Created by ml on 2026/7/6.
//

#ifndef MY_ARENA_GAMEMANAGER_H
#define MY_ARENA_GAMEMANAGER_H

#include<memory>
#include <QObject>

#include "PreBoard.h"
#include "ComBoard.h"
#include "Player.h"
#include "Shop.h"
#include "EquipmentRepo.h"
#include <QTimer>

enum class GameState {
    Ready,
    Prepare,
    Combat,
    Resolve
};

struct NumOfUnitAlive {
    int friendCount;
    int enemyCount;
};

struct Prob {
    std::string name;
    int level;
};


class GameManager: public QObject {
    Q_OBJECT
    //游戏状态
    GameState gameState;
    //战斗管理
    QTimer timer;
    //数据管理
    std::unique_ptr<PreBoard> preBoard;
    std::unique_ptr<ComBoard> comBoard;
    std::unique_ptr<Player> player;
    std::unique_ptr<Shop> shop;
    std::unique_ptr<EquipmentRepo> equipmentRepo;

    //私有辅助函数
    void changeStateTo(GameState newState);
    int countUnitInGrid();
    NumOfUnitAlive countUnitAlive();
    void recoverSelfField();
    void clearEnemyField();
    void recoverEnemyField();
    void tickOfCombat();
    void gotoNextLevel(std::string result);
    Prob randUnit(int score);
    void setNewEnemy();
    void enterResolve(NumOfUnitAlive result);
    void resetTheGame();
public:
    GameManager();

    //面向GUI的数据接口
    GameState getGameState() const;
    std::vector<std::vector<Unit*>> getGridData()const;
    std::vector<Unit*> getBenchData()const;
    std::vector<Equipment*> getEquipmentData()const;
    std::vector<Unit*> getShopData()const;
    PlayerData getPlayerData()const;
    //面向GUI的请求接口
    bool changeTimerState(std::string newState = "null");
    bool requestLoad();//todo
    bool requestSave();//todo
    bool requestChangeStateTo(GameState newGameState);
    bool requestPlayerLevelUp(int num);
    bool requestShopRefresh();
    bool requestBuyUnit(Unit* unit);
    bool requestDragUnitFromTo(int fromX,int fromY,int fromPos,int toX,int toY,int toPos);

    signals:
    void shouldUpdateUI(std::vector<Coord> hitCoords={});
    void failToCombat(int error);
    void gameStateChanged(GameState GameState);
    void failToLevelUp(int error);
    void failToRefreshShop(int error);
    void failToBuy(int error);
    void failToDrag(int error);
    void resolve(std::string result);
    void journeyEnd();
};


#endif //MY_ARENA_GAMEMANAGER_H