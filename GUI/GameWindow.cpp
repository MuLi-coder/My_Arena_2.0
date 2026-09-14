//
// Created by ml on 2026/7/6.
//

#include "GameWindow.h"
#include "../ENTITY/Hero/Knight.h"
#include <QBoxLayout>
#include <QTimer>
#include <QMessageBox>


GameWindow::GameWindow(QWidget *parent): QWidget(parent) {
    gameManager = std::make_unique<GameManager>();
    unitPanel = new UnitPanel();

    //拖拽参数初始化
    isDragging = false;
    dragFromX = dragFromY = dragToX = dragToY = dragFromPos = dragToPos = -1;

    //信号插槽
    connect(gameManager.get(),&GameManager::shouldUpdateUI,this,&GameWindow::updateUI);
    connect(gameManager.get(),&GameManager::failToCombat,this,&GameWindow::failToCombat_Message);
    connect(gameManager.get(),&GameManager::failToDrag,this,&GameWindow::failToDrag_Message);
    connect(gameManager.get(),&GameManager::failToLevelUp,this,&GameWindow::failToLevelUp_Message);
    connect(gameManager.get(),&GameManager::failToBuy,this,&GameWindow::failToBuy_Message);
    connect(gameManager.get(),&GameManager::failToRefreshShop,this,&GameWindow::failToRefreshShop_Message);
    connect(gameManager.get(),&GameManager::gameStateChanged,this,&GameWindow::gameStateChanged_Deal);
    connect(gameManager.get(),&GameManager::resolve,this,&GameWindow::resolve_Message);
    connect(gameManager.get(),&GameManager::journeyEnd,this,&GameWindow::journeyEnd_Message);
    connect(unitPanel,&UnitPanel::buyButtonClicked,this,&GameWindow::buyButtonClicked_Deal);

    //--------------------------draw_the_window_start----------------------------//
    setFixedSize(1100, 800);
    //two parts: left part and right part,we choose to use QHBoxLayout
    //构建主横向布局
    QHBoxLayout* mainHLayout = new QHBoxLayout(this);
    mainHLayout->setContentsMargins(0,0,0,0);
    mainHLayout->setSpacing(10);
    //构建左侧垂直布局
    QVBoxLayout* leftVLayout = new QVBoxLayout();
    leftVLayout->setContentsMargins(0,0,0,0);
    leftVLayout->setSpacing(10);
    leftVLayout->setAlignment(Qt::AlignCenter);
    //构建右侧垂直布局
    QVBoxLayout* rightVLayout = new QVBoxLayout();
    rightVLayout->setContentsMargins(0,0,0,0);
    rightVLayout->setSpacing(30);
    rightVLayout->setAlignment(Qt::AlignCenter);
    //布局融合
    mainHLayout->addLayout(leftVLayout);
    mainHLayout->addLayout(rightVLayout);

    //-------------------左上：棋盘区--------------------//
    QWidget* gridPart = new QWidget(this);
    gridPart->setFixedSize(10*CELL_SIZE,9*(CELL_SIZE+10));
    gridPart->setStyleSheet("background:white");
    QGridLayout* gridLayout = new QGridLayout(gridPart);
    gridLayout->setContentsMargins(20,20,20,20);
    gridLayout->setSpacing(3);
    gridLayout->setAlignment(Qt::AlignCenter);
    for (int i = 0; i < ROW; ++i) {
        std::vector<QWidget*> cellGridLine;
        std::vector<UnitWidget*> gridLine;
        for (int j = 0; j < COL; ++j) {
            QWidget* cell = new QWidget(gridPart);
            cell->setFixedSize(CELL_SIZE,CELL_SIZE+10);
            if (i<ROW/2) {
                cell->setStyleSheet("background:#CFACF2 ;border:1px solid #CFACF2");
            }else {
                cell->setStyleSheet("background:#EFE9F5 ;border:1px solid #CFACF2");
            }
            QVBoxLayout* cellLayout = new QVBoxLayout(cell);
            cellLayout->setContentsMargins(0,0,0,0);
            cellLayout->setSpacing(0);
            cellLayout->setAlignment(Qt::AlignCenter);
            //放入我们的控件
            UnitWidget* ui = new UnitWidget(cell);
            cellLayout->addWidget(ui);
            gridLayout->addWidget(cell,i,j);
            //data stored
            gridLine.push_back(ui);
            cellGridLine.push_back(cell);
        }
        //data stored
        cellGrid.push_back(cellGridLine);
        grid.push_back(gridLine);
    }
    leftVLayout->addWidget(gridPart,0,Qt::AlignCenter);

    //-------------------左下：备战区--------------------//
    QWidget* benchPart = new QWidget(this);
    benchPart->setFixedSize(9.5*CELL_SIZE,1.5*CELL_SIZE);
    benchPart->setStyleSheet("border:1px solid black;background:white");
    QHBoxLayout* benchLayout = new QHBoxLayout(benchPart);
    benchLayout->setContentsMargins(0,0,0,0);
    benchLayout->setSpacing(5);
    benchLayout->setAlignment(Qt::AlignCenter);
    for (int i = 0; i < BEN; ++i) {
        //创建格子单位以及其内部布局
        QWidget* cell = new QWidget(this);
        cell->setFixedSize(CELL_SIZE,CELL_SIZE+10);
        cell->setStyleSheet("background:#EFE9F5;border:1px solid #CFACF2");
        QVBoxLayout* cellLayout = new QVBoxLayout(cell);
        cellLayout->setContentsMargins(0,0,0,0);
        cellLayout->setSpacing(0);
        cellLayout->setAlignment(Qt::AlignCenter);
        //往里放我们自定义的控件
        UnitWidget* ui = new UnitWidget(this);
        cellLayout->addWidget(ui);
        benchLayout->addWidget(cell);
        //data stored
        bench.push_back(ui);
        cellBench.push_back(cell);
    }
    leftVLayout->addWidget(benchPart,0,Qt::AlignCenter);

    //------------------------右上：参数表-------------------------//
    QWidget* paraPart = new QWidget(this);
    paraPart->setFixedSize(6*CELL_SIZE,2*(CELL_SIZE+10));
    paraPart->setStyleSheet("background:white;border:1px solid black");
    QVBoxLayout* paraLayout = new QVBoxLayout(paraPart);
    paraLayout->setContentsMargins(0,0,0,0);
    paraLayout->setSpacing(0);
    paraLayout->setAlignment(Qt::AlignCenter);

    paraWidget = new ParaWidget();
    paraLayout->addWidget(paraWidget);

    rightVLayout->addWidget(paraPart);

    //-----------------------右中1：控制面板------------------------//
    QWidget* controlPanel = new QWidget(this);
    controlPanel->setFixedSize(6*CELL_SIZE,3*CELL_SIZE);
    controlPanel->setStyleSheet("background:white;");
    QVBoxLayout* controlLayout = new QVBoxLayout(controlPanel);
    controlLayout->setContentsMargins(0,0,0,0);
    controlLayout->setSpacing(10);
    controlLayout->setAlignment(Qt::AlignCenter);
    //1---开始按钮
    startButton = new QPushButton("START",controlPanel);
    startButton->setFixedSize(90,45);
    startButton->setStyleSheet("background:green;border:1px solid green");
    controlLayout->addWidget(startButton,0,Qt::AlignCenter);
    connect(startButton,&QPushButton::clicked,this,[=]() {
        if (gameManager->getGameState()==GameState::Ready) {
            startButton->setFixedSize(85,40);
            sleepMs(100);
            startButton->setFixedSize(90,45);
            if (gameManager->requestChangeStateTo(GameState::Prepare)) {
                updateUI();
                QMessageBox::information(this,"Start!",QString(
                "The game starts! Here's what you have.\n\nYou have:\nHP==100\nMoney==20\n\nNow:\nLevel==1\nScore==0"));
            }
        }
    });
    //2---升级，准备，战斗
    QHBoxLayout* secondPart = new QHBoxLayout();
    secondPart->setContentsMargins(0,0,0,0);
    secondPart->setSpacing(10);
    secondPart->setAlignment(Qt::AlignCenter);
    controlLayout->addLayout(secondPart);

    levelUpButton = new QPushButton("LEVELup",controlPanel);
    levelUpButton->setFixedSize(80,40);
    levelUpButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
    secondPart->addWidget(levelUpButton,0,Qt::AlignCenter);
    connect(levelUpButton,&QPushButton::clicked,this,[=]() {
        if (gameManager->getGameState()==GameState::Prepare) {
            levelUpButton->setFixedSize(75,35);
            sleepMs(100);
            levelUpButton->setFixedSize(80,40);
            if (gameManager->requestPlayerLevelUp(+1)) {
                updateUI();
            }
        }
    });
    prepareButton = new QPushButton("rePrepare",controlPanel);
    prepareButton->setFixedSize(80,40);
    prepareButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
    secondPart->addWidget(prepareButton,0,Qt::AlignCenter);
    connect(prepareButton,&QPushButton::clicked,this,[=]() {
       if (gameManager->getGameState()==GameState::Combat) {
           prepareButton->setFixedSize(75,35);
           sleepMs(100);
           prepareButton->setFixedSize(80,40);
           gameManager->changeTimerState("off");
           if (gameManager->requestChangeStateTo(GameState::Prepare)) {
               updateUI();
               QMessageBox::information(this,"Success !","Time to reprepare");
           }
       }
    });
    combatButton = new QPushButton("Combat",controlPanel);
    combatButton->setFixedSize(80,40);
    combatButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
    secondPart->addWidget(combatButton,0,Qt::AlignCenter);
    connect(combatButton,&QPushButton::clicked,this,[=]() {
        if (gameManager->getGameState()==GameState::Prepare) {
            combatButton->setFixedSize(75,35);
            sleepMs(100);
            combatButton->setFixedSize(80,40);
            if (gameManager->requestChangeStateTo(GameState::Combat)) {
                gameManager->changeTimerState();
            }
        }
    });
    //3---暂停，保存，加载
    QHBoxLayout* thirdPart = new QHBoxLayout();
    thirdPart->setContentsMargins(0,0,0,0);
    thirdPart->setSpacing(10);
    thirdPart->setAlignment(Qt::AlignCenter);
    controlLayout->addLayout(thirdPart);

    pauseButton = new QPushButton("Pause",controlPanel);
    pauseButton->setFixedSize(80,40);
    pauseButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
    thirdPart->addWidget(pauseButton,0,Qt::AlignCenter);
    connect(pauseButton,&QPushButton::clicked,this,[=]() {
        if (gameManager->getGameState()==GameState::Combat) {
            pauseButton->setFixedSize(75,35);
            gameManager->changeTimerState();
            sleepMs(100);
            pauseButton->setFixedSize(80,40);
        }
    });
    saveButton = new QPushButton("Save",controlPanel);
    saveButton->setFixedSize(80,40);
    saveButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
    thirdPart->addWidget(saveButton,0,Qt::AlignCenter);
    connect(saveButton,&QPushButton::clicked,this,[=]() {
        if (gameManager->getGameState()==GameState::Prepare) {
            saveButton->setFixedSize(75,35);
            sleepMs(100);
            saveButton->setFixedSize(80,40);
            gameManager->requestSave();
        }
    });
    loadButton = new QPushButton("Load",controlPanel);
    loadButton->setFixedSize(80,40);
    loadButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
    thirdPart->addWidget(loadButton,0,Qt::AlignCenter);
    connect(loadButton,&QPushButton::clicked,this,[=]() {
       if (gameManager->getGameState()==GameState::Prepare) {
           loadButton->setFixedSize(75,35);
           sleepMs(100);
           loadButton->setFixedSize(80,40);
           gameManager->requestLoad();
       }
    });

    rightVLayout->addWidget(controlPanel,0,Qt::AlignCenter);
    //-----------------------右中2：装备栏--------------------------//
    QWidget* EquipmentPart = new QWidget(this);
    EquipmentPart->setFixedSize(6*CELL_SIZE,CELL_SIZE+20);
    EquipmentPart->setStyleSheet("background:white;border:1px solid black");
    QHBoxLayout* EquipmentLayout = new QHBoxLayout(EquipmentPart);
    EquipmentLayout->setContentsMargins(0,0,0,0);
    EquipmentLayout->setSpacing(4);
    EquipmentLayout->setAlignment(Qt::AlignCenter);
    for (int i=0; i<5; ++i) {
        QWidget* cell = new QWidget(this);
        cell->setFixedSize(CELL_SIZE,CELL_SIZE);
        cell->setStyleSheet("background:#EFE9F5;border:1px solid #CFACF2");
        QVBoxLayout* cellLayout = new QVBoxLayout(cell);
        cellLayout->setContentsMargins(0,0,0,0);
        cellLayout->setSpacing(0);
        cellLayout->setAlignment(Qt::AlignCenter);
        EquipmentWidget* ui = new EquipmentWidget(cell);
        cellLayout->addWidget(ui);
        EquipmentLayout->addWidget(cell);
        //data stored
        cellEquipmentRepo.push_back(cell);
        equipmentRepo.push_back(ui);
    }
    rightVLayout->addWidget(EquipmentPart,0,Qt::AlignCenter);

    //-----------------------右下：商店----------------------//
    QWidget* shopPart = new QWidget(this);
    shopPart->setFixedSize(6*CELL_SIZE,2*(CELL_SIZE+10));
    shopPart->setStyleSheet("background:white;border:1px solid black");
    QVBoxLayout* shopLayout = new QVBoxLayout(shopPart);
    shopLayout->setContentsMargins(0,0,0,0);
    shopLayout->setSpacing(5);
    shopLayout->setAlignment(Qt::AlignCenter);
    //-------上半部分
    QWidget* upPart = new QWidget(this);
    upPart->setFixedSize(4*CELL_SIZE,40);
    upPart->setStyleSheet("background:white;border:0.1px solid #6CA0F5");
    QHBoxLayout* upLayout = new QHBoxLayout(upPart);
    upLayout->setContentsMargins(0,0,0,0);
    upLayout->setSpacing(20);
    upLayout->setAlignment(Qt::AlignCenter);
    //1商店标签
    QLabel* label = new QLabel(upPart);
    label->setFixedSize(1.5*CELL_SIZE,30);
    label->setStyleSheet("background:#EFE9F5;border:1px solid #CFACF2 ;color:black");
    label->setAlignment(Qt::AlignCenter);
    label->setText("SHOP");
    upLayout->addWidget(label);
    //2刷新按钮
    shopButton = new QPushButton("REFRESH",upPart);
    shopButton->setFixedSize(CELL_SIZE,30);
    shopButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
    connect(shopButton,&QPushButton::clicked,this,[=]() {
        if (gameManager->getGameState()==GameState::Prepare) {
            shopButton->setFixedSize(CELL_SIZE-5,25);
            sleepMs(50);
            shopButton->setFixedSize(CELL_SIZE,30);
            int ans = QMessageBox::question(
                this,
                "Sure?",
                "Spend 5 coins to refresh?",
                QMessageBox::Yes|QMessageBox::No,
                QMessageBox::Yes);
            if (ans == QMessageBox::Yes) {
                gameManager->requestShopRefresh();
                updateUI();
            }
        }
    });
    upLayout->addWidget(shopButton);
    //下半部分
    QWidget* downPart = new QWidget(this);
    downPart->setFixedSize(5.5*CELL_SIZE,CELL_SIZE+20);
    downPart->setStyleSheet("background:white;border:1px solid #CFACF2");
    QHBoxLayout* downLayout = new QHBoxLayout(downPart);
    downLayout->setContentsMargins(0,0,0,0);
    downLayout->setSpacing(4);
    downLayout->setAlignment(Qt::AlignCenter);
    for (int i=0;i<5;++i) {
        QWidget* cell = new QWidget(this);
        cell->setFixedSize(CELL_SIZE,CELL_SIZE+10);
        cell->setStyleSheet("background:#EFE9F5;border:1px solid #CFACF2");
        QVBoxLayout* cellLayout = new QVBoxLayout(cell);
        cellLayout->setContentsMargins(0,0,0,0);
        cellLayout->setSpacing(0);
        cellLayout->setAlignment(Qt::AlignCenter);
        UnitWidget* ui = new UnitWidget(cell);
        cellLayout->addWidget(ui);
        downLayout->addWidget(cell);
        //data stored
        cellShop.push_back(cell);
        shop.push_back(ui);
    }

    shopLayout->addWidget(upPart,0,Qt::AlignCenter);
    shopLayout->addWidget(downPart,0,Qt::AlignCenter);
    rightVLayout->addWidget(shopPart,0,Qt::AlignCenter);

    //-------------------------draw_the_window_end-------------------------------//
    updateUI();
}

//private slots
void GameWindow::failToCombat_Message(int error) {
    switch (error) {
        case 0:
            QMessageBox::information(this,"Fail !","At least one unit should be deployed");
            break;
        default:
            break;
    }
}

void GameWindow::failToDrag_Message(int error) {
    switch (error) {
        case 0:
            QMessageBox::information(this,"Fail !","This is enemies' area, and you can't place your unit here");
            break;
        case 1:
            QMessageBox::information(this,"Fail !","You have already reached max number of units that can be deployed (Level)");
            break;
        default:
            break;
    }
}

void GameWindow::failToLevelUp_Message(int error) {
    switch (error) {
        case 0:
            QMessageBox::information(this,"Fail!","You don't have enough money");
            break;
        case 1:
            QMessageBox::information(this,"Fail!","You have already reached max level");
            break;
        default:
            break;
    }
}

void GameWindow::failToRefreshShop_Message(int error) {
    switch (error) {
        case 0:
            QMessageBox::information(this,"Fail!","You don't have enough money");
            break;
        default:
            break;
    }
}

void GameWindow::failToBuy_Message(int error) {
    switch (error) {
        case 0:
            QMessageBox::information(this,"Fail!","You don't have enough money");
            break;
        case 1:
            QMessageBox::information(this,"Fail!","You don't have enough space at bench");
            break;
        default:
            break;
    }
}

void GameWindow::journeyEnd_Message() {
    QMessageBox::information(this,"END !",
        "Health has fallen.\n\n Your journey ends here. \n\nRest your weary soul, and rise again!");
}

void GameWindow::resolve_Message(std::string result) {
    if (result=="Fail") {
        QMessageBox::information(this,"Failure !",
            "----You lose----\n\nBut the journey doesn't end\n\nHere's 20 coins for you and Hp minus 20\n\n\n\nRegroup and push on !");
        return;
    }
    if (result=="Success") {
        QMessageBox::information(this,"Success !",
           "----You win----\n\nThe journey is still going on\n\nHere's 40 coins for you and Score added 20\n\nPress the advantage !");
        return;
    }
    if (result=="Draw") {
        QMessageBox::information(this,"Draw !",
        "----Draw----\n\nIt's a battle of equals\n\nHere's 30 coins for you\n\nScore added 10 and Hp minus 10\n\nRecalibrate and push forward !");
        return;
    }
}


void GameWindow::gameStateChanged_Deal(GameState gameState) {
    switch (gameState) {
        case GameState::Ready:
            startButton->setStyleSheet("background:green;border:1px solid #CFACF2;color:white");
            levelUpButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            prepareButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            combatButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            pauseButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            saveButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            loadButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            shopButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            break;
        case GameState::Prepare:
            startButton->setStyleSheet("background:#76AD81;border:1px solid #CFACF2;color:white");
            levelUpButton->setStyleSheet("background:#8158d6;border:1px solid #CFACF2;color:white");
            prepareButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            combatButton->setStyleSheet("background:#8158d6;border:1px solid #CFACF2;color:white");
            pauseButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            saveButton->setStyleSheet("background:#8158d6;border:1px solid #CFACF2;color:white");
            loadButton->setStyleSheet("background:#8158d6;border:1px solid #CFACF2;color:white");
            shopButton->setStyleSheet("background:#8158d6;border:1px solid #CFACF2;color:white");
            for (int r=0;r<ROW;++r) {
                for (int c=0;c<COL;++c) {
                    if (r<ROW/2) {
                        cellGrid[r][c]->setStyleSheet("background:#CFACF2 ;border:1px solid #CFACF2");
                    }else {
                        cellGrid[r][c]->setStyleSheet("background:#EFE9F5 ;border:1px solid #CFACF2");
                    }
                }
            }
            break;
        case GameState::Combat:
            startButton->setStyleSheet("background:#76AD81;border:1px solid #CFACF2;color:white");
            levelUpButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            prepareButton->setStyleSheet("background:#8158d6;border:1px solid #CFACF2;color:white");
            combatButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            pauseButton->setStyleSheet("background:#8158d6;border:1px solid #CFACF2;color:white");
            saveButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            loadButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            shopButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            for (int r=0;r<ROW;++r) {
                for (int c=0;c<COL;++c) {
                    cellGrid[r][c]->setStyleSheet("background:#EFE9F5 ;border:1px solid #CFACF2");
                }
            }
            break;
        case GameState::Resolve:
            startButton->setStyleSheet("background:#76AD81;border:1px solid #CFACF2;color:white");
            levelUpButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            prepareButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            combatButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            pauseButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            saveButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            loadButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            shopButton->setStyleSheet("background:#CFACF2;border:1px solid #CFACF2;color:white");
            break;
    }
}



void GameWindow::buyButtonClicked_Deal(Unit* unit) {
    gameManager->requestBuyUnit(unit);
    updateUI();
}


//public
void GameWindow::updateUI(std::vector<Coord> hitCoords) {
    std::vector<std::vector<Unit*>> gridData = gameManager->getGridData();
    std::vector<Unit*> benchData = gameManager->getBenchData();
    std::vector<Equipment*> equData = gameManager->getEquipmentData();
    std::vector<Unit*> shopData = gameManager->getShopData();

    for (int i=0;i<ROW;++i) {
        for (int j=0;j<COL;++j) {
            grid[i][j]->setUnit(gridData[i][j]);
        }
    }

    for (int i=0;i<BEN;++i) {
        bench[i]->setUnit(benchData[i]);
    }

    for (int i=0;i<5;++i) {
        equipmentRepo[i]->setEquipment(equData[i]);
    }

    for (int i=0;i<5;++i) {
        shop[i]->setUnit(shopData[i]);
    }
    paraWidget->updatePara(gameManager->getPlayerData());

    if (!hitCoords.empty()) {
        for (int i=0;i<hitCoords.size();++i) {
            if (hitCoords[i].x>=0 && hitCoords[i].x<ROW && hitCoords[i].y>=0 && hitCoords[i].y<COL) {
                cellGrid[hitCoords[i].x][hitCoords[i].y]->setStyleSheet("background:#E0997B;border:1px solid #CFACF2;");
            }
        }
        sleepMs(70);
        for (int i=0;i<hitCoords.size();++i) {
            if (hitCoords[i].x>=0 && hitCoords[i].x<ROW && hitCoords[i].y>=0 && hitCoords[i].y<COL) {
                cellGrid[hitCoords[i].x][hitCoords[i].y]->setStyleSheet("background:#EFE9F5;border:1px solid #CFACF2;");
            }
        }
    }
}

void GameWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && gameManager->getGameState()==GameState::Prepare) {
        QWidget* clickedWidget = childAt(event->pos());
        for (int i=0;i<5;++i) {
            if (clickedWidget==cellShop[i] && shop[i]->isBundled()) {
                cellShop[i]->setStyleSheet("background:#CFACF2 ;border:1px solid #CFACF2 ;");
                sleepMs(150);
                cellShop[i]->setStyleSheet("background:#EFE9F5 ;border:1px solid #CFACF2 ;");
                unitPanel->move(event->globalPosition().x()-200,event->globalPosition().y()-500);
                unitPanel->setUnit(gameManager->getShopData()[i]);
                unitPanel->show();
                break;
            }
        }
    }
}

void GameWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && gameManager->getGameState()==GameState::Prepare) {
        QWidget* pressedWidget = childAt(event->pos());
        //第一种可能是从棋盘内
        for (int r=0;r<ROW;++r) {
            for (int c=0;c<COL;++c) {
                if (pressedWidget==cellGrid[r][c] && grid[r][c]->isBundled() && grid[r][c]->isBundledUnitOwnedBy(0)) {
                    cellGrid[r][c]->setStyleSheet("background:#8158d6;border:1px solid #CFACF2 ;");
                    isDragging=true;
                    dragFromX=r;
                    dragFromY=c;
                    return;
                }
            }
        }
        //第二种可能是从备战区
        for (int k=0;k<BEN;++k) {
            if (pressedWidget==cellBench[k] && bench[k]->isBundled()&& bench[k]->isBundledUnitOwnedBy(0)) {
                cellBench[k]->setStyleSheet("background:#8158d6;border:1px solid #CFACF2;");
                isDragging=true;
                dragFromPos=k;
                return;
            }
        }
    }
}

void GameWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isDragging) {
        QWidget* releasedWidget = childAt(event->pos());
        //第一种拖至棋盘
        bool isDone=false;
        for (int r=0;r<ROW;++r) {
            for (int c=0;c<COL;++c) {
                if (releasedWidget==cellGrid[r][c] && !grid[r][c]->isBundled()) {
                    dragToX=r;
                    dragToY=c;
                    if (gameManager->requestDragUnitFromTo(dragFromX,dragFromY,dragFromPos,dragToX,dragToY,dragToPos)) {
                        cellGrid[r][c]->setStyleSheet("background:#8158d6;border:1px solid #CFACF2;");
                        sleepMs(50);
                        cellGrid[r][c]->setStyleSheet("background:#EFE9F5 ;border:1px solid #CFACF2;");
                        updateUI();
                        isDone = true;
                        break;
                    }
                }
            }
            if (isDone) { break;}
        }
        //第二种拖至备战区
        for (int k=0;k<BEN;++k) {
            if (releasedWidget==cellBench[k] && !bench[k]->isBundled()) {
                dragToPos=k;
                if (gameManager->requestDragUnitFromTo(dragFromX,dragFromY,dragFromPos,dragToX,dragToY,dragToPos)) {
                    cellBench[k]->setStyleSheet("background:#8158d6;border:1px solid #CFACF2;");
                    sleepMs(50);
                    cellBench[k]->setStyleSheet("background:#EFE9F5 ;border:1px solid #CFACF2;");
                    updateUI();
                    break;
                }
            }
        }
        //清除数据
        //恢复起始点的格子
        if (dragFromX!=-1 && dragFromY!=-1) {
            cellGrid[dragFromX][dragFromY]->setStyleSheet("background:#EFE9F5 ;border:1px solid #CFACF2;");
        }
        if (dragFromPos!=-1) {
            cellBench[dragFromPos]->setStyleSheet("background:#EFE9F5 ;border:1px solid #CFACF2;");
        }
        dragFromX = dragFromY = dragFromPos = dragToX = dragToY = dragToPos = -1;
        isDragging=false;
    updateUI();
    }
}