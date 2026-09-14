//
// Created by ml on 2026/7/11.
//

#include "Utils.h"
#include <random>
#include <QTimer>
int randomNum(int min, int max) {
    // 1. 使用 static 关键字！确保引擎和分布器只初始化一次
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // 2. 每次调用时，用传入的 min 和 max 重新配置分布范围
    std::uniform_int_distribution<int> dis(min, max);

    // 3. 生成并返回随机数
    return dis(gen);
}
void sleepMs(int msec)
{
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, &QEventLoop::quit);
    loop.exec();
}

int manhattanDist(int x1,int y1,int x2,int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}