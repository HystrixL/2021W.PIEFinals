#include "include.h"
#pragma once

/****************************排序相关****************************/

//选择排序(参数： 待排序数组，数组长度)
void SelectionSort(int *raw, int length);


/****************************RGB灯相关****************************/

typedef enum
{
	Red,		//红
	Green,		//绿
	Blue,		//蓝
	Yellow,		//黄
	Magenta,	//洋红
	Cyan,		//青
	White		//白
} RGB_Color_Type;//颜色名称列表

//RGB快速初始化(参数： 模块号，红色通道号，绿色通道号，蓝色通道号)
void RGB_Init(FTMn_e ftmn, FTM_CHn_e chR, FTM_CHn_e chG, FTM_CHn_e chB);
//RGB快速切换颜色（参数： 颜色名称）
void RGB_Color(RGB_Color_Type color);
//RGB调色盘（参数： R，G，B）
void RGB_Value(int r, int g, int b);


/****************************蜂鸣器相关****************************/
