# W.PIE TheOpenSourceConvention

cmake_minimum_required(VERSION 3.20)
project(W.PIEOSC)

set(CMAKE_C_STANDARD 99)

# 引入库文件
include_directories(../../../../Libraries/Board/inc)
include_directories(../../../../Libraries/drivers/inc)
include_directories(../../../../Libraries/user/Inc)
include_directories(../../../../Libraries/startup/CMSIS/Inc)
include_directories(../../../../Libraries/startup/FatFs)
include_directories(../../../../Libraries/startup/USB)
include_directories(../../../../Libraries/Board/src)
include_directories(../../../../Libraries/drivers/src)
include_directories(../../../../Libraries/user)
include_directories(../../../../Libraries/startup/FatFs/option)

add_executable(W.PIEOSC main.c LCDDisplay.c CNUZL.c CNUZL.h)

#BY XianYu_Hil