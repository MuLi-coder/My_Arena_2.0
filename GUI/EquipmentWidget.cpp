//
// Created by ml on 2026/7/6.
//

#include "EquipmentWidget.h"

#include "UnitWidget.h"
#include<QBoxLayout>
#include<QLabel>
EquipmentWidget::EquipmentWidget(QWidget *parent): QWidget(parent) {
    //------------------开始画图--------------------//
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignCenter);
    label = new QLabel(this);
    label->setFixedSize(60,60);
    QPixmap pixmap("../images/Sword.png");
    QPixmap scaledPixmap = pixmap.scaled(60,60, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(scaledPixmap);
    mainLayout->addWidget(label);
    //---------------------画图结束---------------------//
    label->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    this->setAttribute(Qt::WA_TransparentForMouseEvents,true);

    this->hide();
}

void EquipmentWidget::setEquipment(Equipment* equ) {
    if (!equ) {
        bundledEquipment = nullptr;
        this->hide();
        return;
    }
    bundledEquipment = equ;
    EquipmentData data = equ->getData();
    QPixmap pixmap(data.image);
    QPixmap scaledPixmap = pixmap.scaled(60,60, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(scaledPixmap);

    this->show();
}

