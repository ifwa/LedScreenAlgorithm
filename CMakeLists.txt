cmake_minimum_required(VERSION 3.6)
project(LedScreenAlgorithm)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/App/Config.h
        src/App/Includes.h
        src/App/Main.c
        src/App/Typedef.h
        src/Display/LedAct.c
        src/Display/LedAct.h
        src/Display/LedEffect.c
        src/Display/LedEffect.h
        src/Display/LedProcess.c
        src/Display/LedProcess.h
        src/Effects/EffectDown.c
        src/Effects/EffectDown.h
        src/Effects/EffectFixed.c
        src/Effects/EffectFixed.h
        src/Effects/EffectLaser.c
        src/Effects/EffectLaser.h
        src/Effects/EffectLeft.c
        src/Effects/EffectLeft.h
        src/Effects/EffectRight.c
        src/Effects/EffectRight.h
        src/Effects/EffectScroll.c
        src/Effects/EffectScroll.h
        src/Effects/EffectSnow.c
        src/Effects/EffectSnow.h
        src/Effects/EffectUp.c
        src/Effects/EffectUp.h
        src/Simulator/Simulator.c
        src/Simulator/Simulator.h)

find_library(LIB_NCURSES ncurses)
find_library(LIB_PTHREAD pthread)

add_executable(LedScreenAlgorithm ${SOURCE_FILES})

target_link_libraries(LedScreenAlgorithm
        ${LIB_NCURSES}
        ${LIB_PTHREAD})