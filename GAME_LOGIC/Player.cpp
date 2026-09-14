//
// Created by ml on 2026/7/6.
//

#include "Player.h"

Player::Player() {
    hp = 100;
    level = 1;
    money = 100;
    score = 0;
}

PlayerData Player::getData() const {
    PlayerData data;
    data.level = level;
    data.hp = hp;
    data.money = money;
    data.score = score;
    return data;
}

void Player::changeHpFor(const int num) {
    hp += num;

    if (hp>100) {
        hp = 100;
    }
    else if (hp<0) {
        hp = 0;
    }
}

void Player::changeLevelFor(const int num) {
    level += num;
    if (level>10) {
        level = 10;
    }
    else if (level<1) {
        level = 1;
    }
}

void Player::changeMoneyFor(const int num) {
    money += num;
    if (money<0) {
        money = 0;
    }
}

void Player::changeScoreFor(const int num) {
    score += num;
    if (score<0) {
        score = 0;
    }
}

void Player::gameReset() {
    hp = 100;
    level = 1;
    money = 100;
    score = 0;
}
