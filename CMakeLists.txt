cmake_minimum_required(VERSION 3.16)
project(my_Arena LANGUAGES CXX)

# 2. 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 找到 Qt 库 (这里假设你用的是 Qt6，如果是 Qt5 把 6 改成 5)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(my_Arena_Re
        main.cpp
        GUI/GameWindow.cpp
        GUI/GameWindow.h
        GAME_LOGIC/GameManager.cpp
        GAME_LOGIC/GameManager.h
        GAME_LOGIC/Player.cpp
        GAME_LOGIC/Player.h
        GAME_LOGIC/Shop.cpp
        GAME_LOGIC/Shop.h
        GAME_LOGIC/PreBoard.cpp
        GAME_LOGIC/PreBoard.h
        GAME_LOGIC/ComBoard.cpp
        GAME_LOGIC/ComBoard.h
        GAME_LOGIC/EquipmentRepo.cpp
        GAME_LOGIC/EquipmentRepo.h
        ENTITY/Unit.cpp
        ENTITY/Unit.h
        ENTITY/Equipment.cpp
        ENTITY/Equipment.h
        GUI/UnitWidget.cpp
        GUI/UnitWidget.h
        GUI/EquipmentWidget.cpp
        GUI/EquipmentWidget.h
        GUI/UnitPanel.cpp
        GUI/UnitPanel.h
        GUI/EquipmentPanel.cpp
        GUI/EquipmentPanel.h
        GUI/ParaWidget.cpp
        GUI/ParaWidget.h
        ENTITY/Hero/Knight.cpp
        ENTITY/Hero/Knight.h
        Utils.cpp
        Utils.h
        ENTITY/Hero/Mage.cpp
        ENTITY/Hero/Mage.h
        ENTITY/Hero/Assassin.cpp
        ENTITY/Hero/Assassin.h
)

# 4. 把 Qt 的库链接到我们的程序上
target_link_libraries(my_Arena_Re PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

if(MSVC)
    # 强制开启 C++17 标准支持并修正 __cplusplus 宏 (解决 Qt 报错)
    # 使用 target_compile_options 确保只对 my_Arena 生效，且覆盖全局设置
    target_compile_options(my_Arena_Re PRIVATE /Zc:__cplusplus /utf-8)

    # 同时确保 C++ 标准被正确设置（虽然 set(CMAKE_CXX_STANDARD 17) 通常够用，但显式指定更保险）
    target_compile_features(my_Arena_Re PUBLIC cxx_std_17)

    message(STATUS "已应用 MSVC 修复补丁：开启 /Zc:__cplusplus 和 /utf-8")
endif()