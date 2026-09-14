//
// Created by ml on 2026/7/6.
//

#ifndef MY_ARENA_PLAYER_H
#define MY_ARENA_PLAYER_H

struct PlayerData {
    int hp;
    int level;
    int money;
    int score;
};


class Player {
    int hp;
    int level;
    int money;
    int score;

public:
    Player();
    //数据接口
    PlayerData getData()const;
    //修改接口
    void changeHpFor(int num);
    void changeLevelFor(int num);
    void changeMoneyFor(int num);
    void changeScoreFor(int num);
    //重置接口
    void gameReset();
};


#endif //MY_ARENA_PLAYER_H