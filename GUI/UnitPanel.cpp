//
// Created by ml on 2026/7/6.
//

#include "UnitPanel.h"

#include <QHBoxLayout>
#include <QScrollArea>

#include "GameWindow.h"

UnitPanel::UnitPanel(QWidget *parent):QWidget(parent) {
    bundledUnit = nullptr;
    this->setFixedSize(400,400);
    this->setStyleSheet("background:white;border:1px solid #CFACF2");
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    QVBoxLayout* mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0,15,0,0);
    mainVLayout->setSpacing(10);
    mainVLayout->setAlignment(Qt::AlignTop);
    //1固定标牌
    QVBoxLayout* solidLayout = new QVBoxLayout();
    solidLayout->setContentsMargins(0,0,0,0);
    solidLayout->setSpacing(0);
    solidLayout->setAlignment(Qt::AlignCenter);
    QLabel* solid_L = new QLabel(this);
    solid_L->setFixedSize(150,40);
    solid_L->setAlignment(Qt::AlignCenter);
    solid_L->setText("PROPERTY PANEL");
    solid_L->setStyleSheet("background:white;border:1px solid #CFACF2;color:black");
    solidLayout->addWidget(solid_L,0,Qt::AlignCenter);
    //2面板部分
    QHBoxLayout* mainlayout = new QHBoxLayout();
    mainlayout->setContentsMargins(0,0,0,0);
    mainlayout->setSpacing(10);
    mainlayout->setAlignment(Qt::AlignCenter);
    //构建左右纵向布局
    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->setContentsMargins(0,0,0,0);
    leftLayout->setSpacing(5);
    leftLayout->setAlignment(Qt::AlignCenter);
    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins(0,0,0,0);
    rightLayout->setSpacing(10);
    rightLayout->setAlignment(Qt::AlignCenter);
    //添加布局
    mainlayout->addLayout(leftLayout);
    mainlayout->addLayout(rightLayout);

    //--------先画左半边--------//

    //1---名称
    name_L = new QLabel(this);
    name_L->setFixedSize(100,40);
    name_L->setText("name");
    name_L->setAlignment(Qt::AlignCenter);
    name_L->setStyleSheet("background:white;border:1px solid #CFACF2;color:black");
    leftLayout->addWidget(name_L,0,Qt::AlignCenter);
    //2---图片
    QPixmap pixmap("../images/Knight1.png");
    QPixmap scaledPixmap = pixmap.scaled(190,300,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    image = new QLabel(this);
    image->setPixmap(scaledPixmap);
    image->setAlignment(Qt::AlignCenter);
    leftLayout->addWidget(image,0,Qt::AlignCenter);

    //---------再画右半边---------//
    //1---上方参数区
    QWidget* upPart = new QWidget(this);
    upPart->setFixedSize(180,160);
    upPart->setStyleSheet("background:white;border:1px solid #CFACF2");
    rightLayout->addWidget(upPart,0,Qt::AlignCenter);
    QVBoxLayout* vLayout = new QVBoxLayout(upPart);
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(0);
    vLayout->setAlignment(Qt::AlignCenter);
    //第一层
    QHBoxLayout* firstLayout = new QHBoxLayout();
    firstLayout->setContentsMargins(0,0,0,0);
    firstLayout->setSpacing(0);
    firstLayout->setAlignment(Qt::AlignCenter);
    vLayout->addLayout(firstLayout);
    level_L = new QLabel(upPart);
    level_L->setFixedSize(90,40);
    level_L->setAlignment(Qt::AlignCenter);
    level_L->setText("LEVEL: 1");
    level_L->setStyleSheet("background:white;border:1px solid #CFACF2;color:black");
    firstLayout->addWidget(level_L,0,Qt::AlignCenter);
    cost_L = new QLabel(upPart);
    cost_L->setFixedSize(90,40);
    cost_L->setAlignment(Qt::AlignCenter);
    cost_L->setText("COST: 5");
    cost_L->setStyleSheet("background:white;border:1px solid #CFACF2 ;color:black");
    firstLayout->addWidget(cost_L,0,Qt::AlignCenter);
    //第二层
    QHBoxLayout* secondLayout = new QHBoxLayout();
    secondLayout->setContentsMargins(0,0,0,0);
    secondLayout->setSpacing(0);
    secondLayout->setAlignment(Qt::AlignCenter);
    vLayout->addLayout(secondLayout);
    att_L = new QLabel(upPart);
    att_L->setFixedSize(90,40);
    att_L->setAlignment(Qt::AlignCenter);
    att_L->setText("ATT: 1");
    att_L->setStyleSheet("background:white;border:1px solid #CFACF2 ;color:black");
    secondLayout->addWidget(att_L,0,Qt::AlignCenter);
    attArea_L = new QLabel(upPart);
    attArea_L->setFixedSize(90,40);
    attArea_L->setAlignment(Qt::AlignCenter);
    attArea_L->setText("attAREA: 1");
    attArea_L->setStyleSheet("background:white;border:1px solid #CFACF2;color:black");
    secondLayout->addWidget(attArea_L,0,Qt::AlignCenter);
    //第三层
    QHBoxLayout* thirdLayout = new QHBoxLayout();
    thirdLayout->setContentsMargins(0,0,0,0);
    thirdLayout->setSpacing(0);
    thirdLayout->setAlignment(Qt::AlignCenter);
    vLayout->addLayout(thirdLayout);
    attCD_L = new QLabel(upPart);
    attCD_L->setFixedSize(90,40);
    attCD_L->setAlignment(Qt::AlignCenter);
    attCD_L->setText("attCD: 1");
    attCD_L->setStyleSheet("background:white;border:1px solid #CFACF2;color:black");
    thirdLayout->addWidget(attCD_L,0,Qt::AlignCenter);
    maxHp_L = new QLabel(upPart);
    maxHp_L->setFixedSize(90,40);
    maxHp_L->setAlignment(Qt::AlignCenter);
    maxHp_L->setText("maxHP: 1");
    maxHp_L->setStyleSheet("background:white;border:1px solid #CFACF2;color:black");
    thirdLayout->addWidget(maxHp_L,0,Qt::AlignCenter);
    //第四层
    QHBoxLayout* fourthLayout = new QHBoxLayout();
    fourthLayout->setContentsMargins(0,0,0,0);
    fourthLayout->setSpacing(0);
    fourthLayout->setAlignment(Qt::AlignCenter);
    vLayout->addLayout(fourthLayout);
    maxMana_L = new QLabel(upPart);
    maxMana_L->setFixedSize(90,40);
    maxMana_L->setAlignment(Qt::AlignCenter);
    maxMana_L->setText("maxMANA: 1");
    maxMana_L->setStyleSheet("background:white;border:1px solid #CFACF2 ;color:black");
    fourthLayout->addWidget(maxMana_L,0,Qt::AlignCenter);
    moveCD_L = new QLabel(upPart);
    moveCD_L->setFixedSize(90,40);
    moveCD_L->setAlignment(Qt::AlignCenter);
    moveCD_L->setText("moveCD: 1");
    moveCD_L->setStyleSheet("background:white;border:1px solid #CFACF2;color:black");
    fourthLayout->addWidget(moveCD_L,0,Qt::AlignCenter);
    //2--技能说明区
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setFixedSize(180,80);
    scrollArea->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    skillIntro_L = new QLabel(scrollArea);
    skillIntro_L->setFixedSize(160,300);
    skillIntro_L->setStyleSheet("background:#EFE9F5;border:1px solid #CFACF2;color:black");
    skillIntro_L->setText("skill");
    skillIntro_L->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    skillIntro_L->setWordWrap(true); // 依然需要开启换行
    scrollArea->setWidget(skillIntro_L); // 将 Label 放入滚动区域
    rightLayout->addWidget(scrollArea,0,Qt::AlignCenter);
    //加入布局
    mainVLayout->addLayout(solidLayout);
    mainVLayout->addLayout(mainlayout);
    //3---按钮
    //3--购买按钮
    buyButton = new QPushButton("BUY",this);
    buyButton->setFixedSize(90,40);
    buyButton->move(70,340);
    buyButton->setStyleSheet("background:green;color:white");
    connect(buyButton,&QPushButton::clicked,this,[=]() {
        buyButton->move(75,345);
        buyButton->setFixedSize(80,30);
        sleepMs(100);
        buyButton->move(70,340);
        buyButton->setFixedSize(90,40);
        this->hide();
        emit buyButtonClicked(bundledUnit);
    });

    cancelButton = new QPushButton("CANCEL",this);
    cancelButton->setFixedSize(90,40);
    cancelButton->move(240,340);
    cancelButton->setStyleSheet("background:gray;color:black");
    connect(cancelButton,&QPushButton::clicked,this,[=]() {
        cancelButton->move(245,345);
        cancelButton->setFixedSize(80,30);
        sleepMs(100);
        cancelButton->move(240,340);
        cancelButton->setFixedSize(90,40);
        this->hide();
    });
    this->hide();
}


void UnitPanel::setUnit(Unit* unit) {
    if (!unit) {return;}
    bundledUnit = unit;

    UnitData data = unit->getData();
    name_L->setText(data.name);
    QPixmap pixmap(data.image);
    QPixmap scaledPixmap = pixmap.scaled(190,300,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    image->setPixmap(scaledPixmap);

    level_L->setText(QString("LEVEL: %1").arg(data.level));
    cost_L->setText(QString("COST: %1").arg(data.cost));
    att_L->setText(QString("ATT: %1").arg(data.att));
    attArea_L->setText(QString("attArea: %1").arg(data.attArea));
    attCD_L->setText(QString("attCD: %1").arg(data.attCD));
    maxHp_L->setText(QString("maxHP: %1").arg(data.maxHp));
    maxMana_L->setText(QString("maxMana: %1").arg(data.maxMana));
    moveCD_L->setText(QString("moveCD: %1").arg(data.moveCD));
    skillIntro_L->setText(data.skillIntro);
}