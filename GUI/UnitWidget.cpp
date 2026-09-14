//
// Created by ml on 2026/7/6.
//

#include "UnitWidget.h"
#include<QBoxLayout>
#include<QLabel>
UnitWidget::UnitWidget(QWidget *parent): QWidget(parent) {

    bundledUnit = nullptr;
    //-----------------------------画图部分----------------------------//
    this->setStyleSheet("border:0.1px;background:transparent");
    this->setFixedSize(CELL_SIZE, CELL_SIZE+10);

    QVBoxLayout* mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0,0,2,0);
    mainVLayout->setSpacing(1);
    mainVLayout->setAlignment(Qt::AlignCenter);

    //1-------上方等级，血条，蓝条---------//
    //构建左右布局
    QWidget* upPart = new QWidget(this);
    upPart->setFixedSize(CELL_SIZE-1,12);
    upPart->setStyleSheet("background:transparent");
    QHBoxLayout* upLayout = new QHBoxLayout(upPart);
    upLayout->setContentsMargins(0,0,0,0);
    upLayout->setSpacing(1);
    upLayout->setAlignment(Qt::AlignCenter);

    //------------左侧等级-----------
    level = new QLabel(upPart);
    level->setFixedSize(12,12);
    level->setStyleSheet("color:black;background:white;border:1px solid grey");
    level->setText("1");
    level->setAlignment(Qt::AlignCenter);
    upLayout->addWidget(level);

    //------------右侧两条-------------
    QWidget* barPart = new QWidget(upPart);
    barPart->setFixedSize(CELL_SIZE-15,7);
    barPart->setStyleSheet("background:transparent");
    QVBoxLayout* barLayout = new QVBoxLayout(barPart);
    barLayout->setContentsMargins(0,0,0,0);
    barLayout->setSpacing(0);

    //----右侧上方血条
    hpBar = new QLabel(barPart);
    hpBar->setFixedSize(CELL_SIZE-15,4);
    hpBar->setStyleSheet("background:transparent");
    QHBoxLayout* hpBarLayout = new QHBoxLayout(hpBar);
    hpBarLayout->setContentsMargins(0,0,0,0);
    hpBarLayout->setSpacing(0);
    hpBarLayout->setAlignment(Qt::AlignLeft);
    //左侧血条
    hpLBar = new QLabel(hpBar);
    hpLBar->setFixedSize(CELL_SIZE-15,4);
    hpLBar->setStyleSheet("background:#18BA6F");
    hpBarLayout->addWidget(hpLBar);
    //血条加入布局
    barLayout->addWidget(hpBar);

    //-----右侧下方蓝条
    manaBar = new QLabel(barPart);
    manaBar->setFixedSize(CELL_SIZE-15,3);
    manaBar->setStyleSheet("background:transparent");
    QHBoxLayout* manaBarLayout = new QHBoxLayout(manaBar);
    manaBarLayout->setContentsMargins(0,0,0,0);
    manaBarLayout->setSpacing(0);
    manaBarLayout->setAlignment(Qt::AlignLeft);
    //左侧蓝条
    manaLBar = new QLabel(manaBar);
    manaLBar->setFixedSize(CELL_SIZE-15,3);
    manaLBar->setStyleSheet("background:blue");
    manaBarLayout->addWidget(manaLBar);
    //蓝条加入布局
    barLayout->addWidget(manaBar);

    //整体加入上方布局
    upLayout->addWidget(barPart);

    //2--------底部图片-------//
    image = new QLabel(this);
    image->setFixedSize(CELL_SIZE-8, CELL_SIZE-4);

    QPixmap pixmap("../images/Knight1.png");
    QPixmap scaledPixmap = pixmap.scaled(CELL_SIZE-4, CELL_SIZE-4, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    image->setPixmap(scaledPixmap);

    //两部分加入主布局
    mainVLayout->addWidget(upPart);
    mainVLayout->addWidget(image);
    //------------------------------------画图结束---------------------------------//
    //设置鼠标穿透
    upPart->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    level->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    barPart->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    hpBar->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    hpLBar->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    manaBar->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    manaLBar->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    image->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    //初始化隐藏
    this->hide();
}

bool UnitWidget::isBundled() {
    if (bundledUnit) {
        return true;
    }
    return false;
}

bool UnitWidget::isBundledUnitOwnedBy(int num) {
    if (!bundledUnit) { return false;}
    if (bundledUnit->getData().owner == num) {
        return true;
    }
    return false;
}

void UnitWidget::setUnit(Unit* unit) {
    if (!unit) {
        bundledUnit = nullptr;
        this->hide();
        return;
    }
    bundledUnit = unit;

    UnitData data = unit->getData();
    level->setText(QString("%1").arg(data.level));
    hpLBar->setFixedWidth(45*data.hp/data.maxHp);
    if (data.owner == 0) {
        hpLBar->setStyleSheet("background:green");
    }else {
        hpLBar->setStyleSheet("background:red");
    }
    manaLBar->setFixedWidth(45*data.mana/data.maxMana);
    QPixmap pixmap;
    pixmap.load(data.image);
    QPixmap scaledPixmap = pixmap.scaled(CELL_SIZE-4, CELL_SIZE-4, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    image->setPixmap(scaledPixmap);
    this->show();
}

