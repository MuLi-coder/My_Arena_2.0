//
// Created by ml on 2026/7/7.
//

#include "ParaWidget.h"
#include <QHBoxLayout>
ParaWidget::ParaWidget() {
    image = new QLabel(this);
    QPixmap pixmap("../images/Player.png");
    QPixmap scaledPixmap = pixmap.scaled(2*60,110,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    image->setPixmap(scaledPixmap);
    image->setAlignment(Qt::AlignCenter);

    score = new QLabel(this);
    score->setText("SCORE: 0");
    score->setStyleSheet("color:black;border:none");
    score->setAlignment(Qt::AlignCenter);
    level = new QLabel(this);
    level->setText("LEVEL: 0");
    level->setStyleSheet("color:black;border:none");
    level->setAlignment(Qt::AlignCenter);
    hp = new QLabel(this);
    hp->setText("HP: 0");
    hp->setStyleSheet("color:black;border:none");
    hp->setAlignment(Qt::AlignCenter);
    money = new QLabel(this);
    money->setText("MONEY: 0");
    money->setStyleSheet("color:black;border:none");
    money->setAlignment(Qt::AlignCenter);

    QHBoxLayout* paraLayout = new QHBoxLayout(this);
    paraLayout->setContentsMargins(0,0,0,0);
    paraLayout->setSpacing(0);
    paraLayout->setAlignment(Qt::AlignCenter);
    //---------三列布局
    //左
    QVBoxLayout* paraLeftVLayout = new QVBoxLayout();
    paraLeftVLayout->setContentsMargins(0,0,0,0);
    paraLeftVLayout->setSpacing(0);
    paraLeftVLayout->setAlignment(Qt::AlignCenter);
    //中
    QVBoxLayout* paraMiddleVLayout = new QVBoxLayout();
    paraMiddleVLayout->setContentsMargins(0,0,0,0);
    paraMiddleVLayout->setSpacing(0);
    paraMiddleVLayout->setAlignment(Qt::AlignCenter);
    //右
    QVBoxLayout* paraRightVLayout = new QVBoxLayout();
    paraRightVLayout->setContentsMargins(0,0,0,0);
    paraRightVLayout->setSpacing(0);
    paraRightVLayout->setAlignment(Qt::AlignCenter);
    //融合布局
    paraLayout->addLayout(paraLeftVLayout);
    paraLayout->addLayout(paraMiddleVLayout);
    paraLayout->addLayout(paraRightVLayout);

    //-----------左控件----------//
    QWidget* leftWidget = new QWidget(this);
    leftWidget->setFixedSize(2*60,2*(60+10));
    leftWidget->setStyleSheet("background:white;border:none");
    QVBoxLayout* leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setContentsMargins(0,0,0,0);
    leftLayout->setSpacing(10);
    leftLayout->setAlignment(Qt::AlignCenter);

    QLabel* name = new QLabel(leftWidget);
    name->setFixedSize(2*60,30);
    name->setText("-------Player-------");
    name->setStyleSheet("color:black;border:none");
    name->setAlignment(Qt::AlignCenter);

    leftLayout->addWidget(name);
    leftLayout->addWidget(image);

    paraLayout->addWidget(leftWidget);

    //-----------中控件------------//
    QWidget* middleWidget = new QWidget(this);
    middleWidget->setFixedSize(2*60,2*(60+10));
    middleWidget->setStyleSheet("background:white;border:none");
    QVBoxLayout* middleLayout = new QVBoxLayout(middleWidget);
    middleLayout->setContentsMargins(0,0,0,0);
    middleLayout->setSpacing(0);
    middleLayout->setAlignment(Qt::AlignCenter);

    score->setFixedSize(2*60,30);
    level->setFixedSize(2*60,30);
    middleLayout->addWidget(score);
    middleLayout->addWidget(level);

    paraMiddleVLayout->addWidget(middleWidget);

    //------------右控件-----------//
    QWidget* rightWidget = new QWidget(this);
    rightWidget->setFixedSize(2*60,2*(60+10));
    rightWidget->setStyleSheet("background:white;border:none");
    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setContentsMargins(0,0,0,0);
    rightLayout->setSpacing(0);
    rightLayout->setAlignment(Qt::AlignCenter);

    hp->setFixedSize(2*60,30);
    money->setFixedSize(2*60,30);
    rightLayout->addWidget(hp);
    rightLayout->addWidget(money);

    paraLayout->addWidget(rightWidget);
}

void ParaWidget::updatePara(PlayerData data) {
    level->setText(QString("LEVEL: %1").arg(data.level));
    score->setText(QString("SCORE: %1").arg(data.score));
    hp->setText(QString("HP: %1").arg(data.hp));
    money->setText(QString("MONEY: %1").arg(data.money));
}

