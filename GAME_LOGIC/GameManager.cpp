//
// Created by ml on 2026/7/6.
//

#include "GameManager.h"
#include <iostream>


GameManager::GameManager() {
    gameState = GameState::Ready;
    timer.setInterval(100);
    connect(&timer, &QTimer::timeout,this,&GameManager::tickOfCombat);
    timer.stop();

    preBoard = std::make_unique<PreBoard>();
    comBoard = std::make_unique<ComBoard>();
    player = std::make_unique<Player>();
    shop = std::make_unique<Shop>();
    equipmentRepo = std::make_unique<EquipmentRepo>();
}

//private

int GameManager::countUnitInGrid() {
    int count = 0;
    for (int r=ROW/2;r<ROW;++r) {
        for (int c=0;c<COL;++c) {
            Unit* unit = preBoard->getUnitAtGrid(r,c);
            if (unit && unit->getData().owner==0) {
                count++;
            }
        }
    }
    return count;
}

NumOfUnitAlive GameManager::countUnitAlive() {
    NumOfUnitAlive result;
    result.friendCount=0;
    result.enemyCount=0;
    for (int i=0;i<ROW;++i) {
        for (int j=0;j<COL;++j) {
            Unit* unit = comBoard->getUnitAt(i,j);
            if (unit) {
                UnitData data = unit->getData();
                if (data.owner==0 && data.hp>0) {
                    result.friendCount++;
                }
                else if (data.owner==1 && data.hp>0) {
                    result.enemyCount++;
                }
            }
        }
    }
    return result;
}

void GameManager::recoverSelfField() {
    for (int r=ROW/2;r<ROW;++r) {
        for (int c=0;c<COL;++c) {
            if (preBoard->getUnitAtGrid(r,c)){
                preBoard->getUnitAtGrid(r,c)->reset();
            }
        }
    }
}

void GameManager::recoverEnemyField() {
    for (int r=0;r<ROW/2;++r) {
        for (int c=0;c<COL;++c) {
            if (preBoard->getUnitAtGrid(r,c)){
                preBoard->getUnitAtGrid(r,c)->reset();
            }
        }
    }
}

void GameManager::clearEnemyField() {
    for (int r=0;r<ROW/2;++r) {
        for (int c=0;c<COL;++c) {
            delete preBoard->getUnitAtGrid(r,c);
            preBoard->changeUnitAtToGrid(r,c,nullptr);
        }
    }
}

void GameManager::tickOfCombat() {
    std::cout<<"------------clock arrived-----------"<<std::endl;
    std::cout<<"1--end detected--"<<std::endl;
    NumOfUnitAlive result = countUnitAlive();
    if (result.friendCount==0 || result.enemyCount==0) {
        timer.stop();
        changeStateTo(GameState::Resolve);
        enterResolve(result);
    }
    std::cout<<"2--march every unit--"<<std::endl;
    std::vector<Coord> hitCoords = comBoard->marchEveryUnit();
    std::cout<<"3-clear the dead and reset state--"<<std::endl;
    for (int r=0;r<ROW;++r) {
        for (int c=0;c<COL;++c) {
            Unit* unit = comBoard->getUnitAt(r,c);
            if (unit){
                unit->changeIsDoneTo(false);
                if (unit->getData().hp==0) {
                    comBoard->changeUnitAtTo(r,c,nullptr);
                }
            }
        }
    }
    emit shouldUpdateUI(hitCoords);
}

void GameManager::gotoNextLevel(std::string result) {
    std::cout<<"------Next Level-------"<<std::endl;
    if (result=="Success") {
        recoverSelfField();
        clearEnemyField();
        setNewEnemy();
        return;
    }
    if (result=="Fail" || result == "Draw") {
        recoverSelfField();
        recoverEnemyField();
        return;
    }

}

Prob GameManager::randUnit(int score) {
    Prob randUnit = {"Null",1};
    int probHas=0;
    int twoLevelProb =0;
    int threeLevelProb=0;

    if (score<100) {
        probHas=90;
        twoLevelProb=70;
        threeLevelProb=95;
    }
    else if(score<200) {
        probHas=80;
        twoLevelProb=50;
        threeLevelProb=90;
    }else {
        probHas=40;
        twoLevelProb=40;
        threeLevelProb=80;
    }

    int randHas = randomNum();
    if (randHas>probHas) {
        int randType = randomNum(0,30);
        if (randType<30) { randUnit.name="Knight";}
        if (randType<20) { randUnit.name="Mage";}
        if (randType<10) { randUnit.name="Assassin";}
    }
    int randLevel = randomNum();
    if (randLevel>twoLevelProb) {
        randUnit.level=2;
    }
    if (randLevel>threeLevelProb) {
        randUnit.level=3;
    }

    return randUnit;
}

void GameManager::setNewEnemy() {
    int score = player->getData().score;
    for (int r=0;r<ROW/2;++r) {
        for (int c=0;c<COL;++c) {
            Prob unit = randUnit(score);
            if (unit.name=="Knight") {
                preBoard->changeUnitAtToGrid(r,c,new Knight(unit.level,1));
            }
            else if (unit.name=="Mage") {
                preBoard->changeUnitAtToGrid(r,c,new Mage(unit.level,1));
            }
            else if (unit.name=="Assassin") {
                preBoard->changeUnitAtToGrid(r,c,new Assassin(unit.level,1));
            }
        }
    }
}

void GameManager::changeStateTo(GameState newState) {
    switch (newState) {
        case GameState::Ready:
            gameState=newState;
            break;
        case GameState::Prepare:
            gameState=newState;
            break;
        case GameState::Combat:
            gameState=newState;
            break;
        case GameState::Resolve:
            gameState=newState;
            break;
        default:
            break;
    }
    emit gameStateChanged(gameState);
}

void GameManager::enterResolve(NumOfUnitAlive result) {
    if (result.friendCount==0 && result.enemyCount!=0) {
        //fail
        player->changeMoneyFor(+20);
        player->changeHpFor(-20);
        emit resolve("Fail");
        if (player->getData().hp==0) {
            emit journeyEnd();
            changeStateTo(GameState::Ready);
            resetTheGame();
            return;
        }
        changeStateTo(GameState::Prepare);
        gotoNextLevel("Fail");
    }
    else if (result.friendCount!=0 && result.enemyCount==0) {
        //success
        player->changeMoneyFor(+40);
        player->changeScoreFor(+20);
        emit resolve("Success");
        changeStateTo(GameState::Prepare);
        gotoNextLevel("Success");
    }
    else if (result.friendCount==0 && result.enemyCount==0) {
        //draw
        player->changeMoneyFor(+30);
        player->changeScoreFor(+10);
        player->changeHpFor(-10);
        emit resolve("Draw");
        changeStateTo(GameState::Prepare);
        gotoNextLevel("Draw");
    }
}

void GameManager::resetTheGame() {
    preBoard->gameReset();
    comBoard->gameReset();
    player->gameReset();
    shop->gameReset();
    // equipmentRepo->gameReset();
}


//public

GameState GameManager::getGameState() const {
    return gameState;
}

std::vector<std::vector<Unit*>> GameManager::getGridData() const{
    std::vector<std::vector<Unit*>> gridData;
    gridData.resize(ROW,std::vector<Unit*>(COL,nullptr));
    if (gameState==GameState::Prepare) {
        for (int i=0;i<ROW;++i) {
            for (int j=0;j<COL;++j) {
                gridData[i][j] = preBoard->getUnitAtGrid(i,j);
            }
        }
    }
    else if (gameState==GameState::Combat) {
        for (int i=0;i<ROW;++i) {
            for (int j=0;j<COL;++j) {
                gridData[i][j] = comBoard->getUnitAt(i,j);
            }
        }
    }
    return gridData;
}

std::vector<Unit *> GameManager::getBenchData() const{
    std::vector<Unit*> benchData;
    benchData.resize(BEN,nullptr);
    for (int i=0;i<BEN;++i) {
        benchData[i] = preBoard->getUnitAtBench(i);
    }
    return benchData;
}

std::vector<Equipment*> GameManager::getEquipmentData() const{
    std::vector<Equipment*> equipmentData;
    equipmentData.resize(5,nullptr);
    for (int i=0;i<5;++i) {
        equipmentData[i] = equipmentRepo->getEquipmentAtDisplay(i);
    }
    return equipmentData;
}

std::vector<Unit*> GameManager::getShopData() const{
    std::vector<Unit*> shopData;
    shopData.resize(5,nullptr);
    for (int i=0;i<5;++i) {
        shopData[i] = shop->getUnitAtDisplay(i);
    }
    return shopData;
}

PlayerData GameManager::getPlayerData() const {
    return player->getData();
}

bool GameManager::changeTimerState(std::string newState) {
    if (newState=="on") {
        timer.start();
    }
    else if (newState=="off") {
        timer.stop();
    }
    else {
        if (timer.isActive()) {
            timer.stop();
        }else {
            timer.start();
        }
    }
    return true;
}

bool GameManager::requestLoad() {

    return true;
}

bool GameManager::requestSave() {

    return true;
}

bool GameManager::requestChangeStateTo(GameState newGameState) {
    switch (newGameState) {
        case GameState::Prepare:
            if (gameState==GameState::Ready) {
                //手动放置第一关敌人
                preBoard->changeUnitAtToGrid(2,2,new Knight(1,1));
                changeStateTo(newGameState);
                return true;
            }
            if (gameState==GameState::Combat) {
                changeStateTo(newGameState);
                return true;
            }
        case GameState::Combat:
            comBoard->setBoard(preBoard.get());
            if (countUnitInGrid()==0) {
                emit failToCombat(0);
                return false;
            }
            changeStateTo(newGameState);
            return true;
        default:
            return false;
    }
}

bool GameManager::requestPlayerLevelUp(int num) {
    PlayerData data = player->getData();
    if (data.money < 5 ) {
        emit failToLevelUp(0);
        return false;
    }
    if (data.level == 10) {
        emit failToLevelUp(1);
        return false;
    }
    player->changeLevelFor(num);
    player->changeMoneyFor(-5);
    return true;
}

bool GameManager::requestShopRefresh() {
    if (player->getData().money<5) {
        emit failToRefreshShop(0);
        return false;
    }
    player->changeMoneyFor(-5);
    shop->refresh();
    return true;
}

bool GameManager::requestBuyUnit(Unit *unit) {
    if (!unit){return false;}

    //1检验金币是否足够
    if (player->getData().money<unit->getData().cost) {
        emit failToBuy(0);
        return false;
    }
    //2检验备战区是否已满,同时定位最左侧空位
    for (int i=0;i<BEN;++i) {
        if (!preBoard->getUnitAtBench(i)) {
            //定位购买的英雄位置
            int position = 0;
            for (int k=0;k<5;++k) {
                if (shop->getUnitAtDisplay(k)==unit) {
                    position = k;
                }
            }
            //转移数据
            shop->changeUnitAtToDisplay(position,nullptr);
            shop->addUnitToOwned(unit);
            //扣除玩家金币
            player->changeMoneyFor(0-unit->getData().cost);
            //然后指针给到棋盘备战区
            preBoard->changeUnitAtToBench(i,unit);
            return true;
        }
        if (i == 7) {
            emit failToBuy(1);
            return false;
        }
    }
    return false;
}

bool GameManager::requestDragUnitFromTo(int fromX, int fromY, int fromPos, int toX, int toY, int toPos) {
    //首先确定起点和终点的位置
    std::string fromPlace;
    std::string toPlace;
    if (fromX!=-1 && fromY!=-1 && fromPos ==-1) {
        fromPlace = "Grid";
    }
    if (fromX==-1 && fromY==-1 && fromPos !=-1) {
        fromPlace = "Bench";
    }
    if (toX!=-1 && toY!=-1 && toPos ==-1) {
        toPlace = "Grid";
    }
    if (toX==-1 && toY==-1 && toPos !=-1) {
        toPlace = "Bench";
    }
    //下面是四种情况的拖拽具体逻辑
    if (fromPlace=="Grid"&&toPlace=="Grid") {
        if (fromX==toX&&fromY==toY) {
            return false;
        }
        if (toX<ROW/2) {
            emit failToDrag(0);
            return false;
        }
        Unit* unit = preBoard->getUnitAtGrid(fromX,fromY);
        preBoard->changeUnitAtToGrid(fromX,fromY,nullptr);
        preBoard->changeUnitAtToGrid(toX,toY,unit);
        return true;
    }
    if (fromPlace=="Grid"&&toPlace=="Bench") {
        Unit* unit = preBoard->getUnitAtGrid(fromX,fromY);
        preBoard->changeUnitAtToGrid(fromX,fromY,nullptr);
        preBoard->changeUnitAtToBench(toPos,unit);
        return true;
    }
    if (fromPlace=="Bench"&&toPlace=="Grid") {
        if (toX<ROW/2) {
            emit failToDrag(0);
            return false;
        }
        if (countUnitInGrid()==player->getData().level) {
            emit failToDrag(1);
            return false;
        }
        Unit* unit = preBoard->getUnitAtBench(fromPos);
        preBoard->changeUnitAtToBench(fromPos,nullptr);
        preBoard->changeUnitAtToGrid(toX,toY,unit);
        return true;
    }
    if (fromPlace=="Bench"&&toPlace=="Bench") {
        if (fromPos==toPos) {
            return false;
        }
        Unit* unit = preBoard->getUnitAtBench(fromPos);
        preBoard->changeUnitAtToBench(fromPos,nullptr);
        preBoard->changeUnitAtToBench(toPos,unit);
        return true;
    }
    return false;
}
