//
// Created by ml on 2026/7/6.
//

#ifndef MY_ARENA_UNIT_H
#define MY_ARENA_UNIT_H

#include <QString>
#include <QLabel>
#include <random>

struct UnitData {
    QString name;
    int owner;
    int level;
    int cost;
    QString image;
    int att;
    int attArea;
    int maxHp;
    int maxMana;
    int attCD;
    int moveCD;
    int hp;
    int mana;
    int attTick;
    int moveTick;
    QString skillIntro;
    bool isInGrid;
    bool isDone;
};

struct Coord {
    int x;
    int y;
};

struct Action {
    enum Type {Idle,Move,Attack};
    enum Movement {Left,Right,Up,Down};
    enum AttType {CommonAtt,SkillAtt};


    Type type;
    Movement movement;
    AttType attType;
    Coord target;
};


class Unit {
protected:
    //固定属性
    QString name;
    int owner;      //
    //非固定数据：静态数据，动态数据
    int level;      //
    //等级绑定的静态属性
    int cost;
    QString image;
    int att;
    int attArea;
    int maxHp;
    int maxMana;
    int attCD;
    int moveCD;
    //战斗中途变化的动态属性
    int hp;
    int mana;
    int attTick;
    int moveTick;
    //技能的文字描述
    QString skillIntro;
    //是否在战场
    bool isInGrid;
    bool isDone;

    //私有辅助函数
    Coord searchEnemy(const std::vector<std::vector<Unit*>> &grid,Coord self);
    Coord searchMoveTarget(const std::vector<std::vector<Unit*>> &grid,Coord self,Coord enemy);
    std::string getMovement(const std::vector<std::vector<Unit*>> &grid,Coord self,Coord target);

    virtual void skillAttack(const std::vector<std::vector<Unit*>> &grid,Coord self,Coord enemy)=0;

public:
    Unit(int l,int o);
    virtual ~Unit() = default;
    //数值依照等级重置所有非固定数据：升级，打扫战场用
    virtual void reset() = 0;
    void changeLevelFor(int change);
    void changeIsInGridTo(bool is);
    void changeIsDoneTo(bool is);
    UnitData getData()const;
    //战斗函数
    Action decideAction(const std::vector<std::vector<Unit*>>& grid,Coord self);
    void takeDamage(int damage);
};


#endif //MY_ARENA_UNIT_H