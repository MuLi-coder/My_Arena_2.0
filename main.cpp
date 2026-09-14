#include <QApplication>
#include "GUI/GameWindow.h" // 引入你的主窗口头文件

int main(int argc, char *argv[]) {
    // 1. 创建 Qt 应用程序对象
    // 它是整个 GUI 程序的“心脏”，负责处理所有的事件（鼠标点击、键盘输入等）
    QApplication app(argc, argv);

    // 2. 创建并显示主窗口
    GameWindow window; // 在栈上创建，程序结束时会自动销毁
    window.show();     // 调用 show() 让窗口真正显示在屏幕上

    // 3. 进入事件循环（Event Loop）
    // 程序会一直停留在这里，不断监听用户的操作
    // 直到你关闭了最后一个窗口，或者调用了 QApplication::quit()
    return app.exec();
}