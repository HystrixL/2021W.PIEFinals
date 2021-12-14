#include "include.h"
#pragma once

//-------------------------------------------------------------------
// 排序相关
//-------------------------------------------------------------------

/*!
 * @brief 选择排序
 * @param raw    待排序数组
 * @param length 数组长度
 */
void SelectionSort(int *raw, int length);

/*!
 * @brief 快速排序
 * @param arr    待排序数组
 * @param low   排序最低位
 * @param high  排序最高位
 * @note low应为数组最低索引，通常为0;\n high应为数组最大索引，通常为数组长度-1
 */
void QuickSort(int *arr, int low, int high);

//-------------------------------------------------------------------
// RGB灯相关
//-------------------------------------------------------------------

/*!
 * @brief 颜色名称列表
 * @enum Red    	红
 * @enum Green  	绿
 * @enum Blue  	    蓝
 * @enum Yellow 	黄
 * @enum Magenta    洋红
 * @enum Cyan  	    青
 * @enum White      白
 * @enum Null       无色
 */
typedef enum
{
	Red,
	Green,
	Blue,
	Yellow,
	Magenta,
	Cyan,
	White,
    Null
} RGB_Color_Type;

/*!
 * @brief RGB快速初始化
 * @param ftmn  模块号
 * @param chR   红色通道号
 * @param chG   绿色通道号
 * @param chB   蓝色通道号
 */
void RGB_Init(FTMn_e ftmn, FTM_CHn_e chR, FTM_CHn_e chG, FTM_CHn_e chB);

/*!
 * @brief RGB快速切换颜色
 * @param color     颜色名称
 */
void RGB_Color(RGB_Color_Type color);

/*!
 * @brief RGB调色盘
 * @param r     红色数值(255)
 * @param g     绿色数值(255)
 * @param b     蓝色数值(255)
 */
void RGB_Value(int r, int g, int b);


//-------------------------------------------------------------------
// 蜂鸣器相关
//-------------------------------------------------------------------

/*!
 * @brief 蜂鸣器音调
 * @enum Do
 * @enum Re
 * @enum Mi
 * @enum Fa
 * @enum Sol
 * @enum La
 * @enum Ti
 */
typedef enum {
    Do = 262,
    Re = 294,
    Mi = 330,
    Fa = 349,
    Sol = 392,
    La = 440,
    Ti = 494
} Buzzer_Tone_Type;//蜂鸣器音调列表

/*!
 * @brief 蜂鸣器音乐包
 * @enum Nothing 无
 */
typedef enum{
  Nothing
} Buzzer_Music_Type;//蜂鸣器音乐包

/*!
 * @brief 蜂鸣器快速初始化
 * @note 默认音量50
 * @param ftmn     蜂鸣器模块号
 * @param ch    蜂鸣器通道号
 */
void Buzzer_Init(FTMn_e ftmn, FTM_CHn_e ch);

/*!
 * @brief 蜂鸣器调节音调
 * @param tone     音调
 */
void Buzzer_Tone(Buzzer_Tone_Type tone);

/*!
 * @brief 蜂鸣器调节音量
 * @param volume 音量
 * @note 范围：0~100
 */
void Buzzer_Volume(int volume);

/*!
 * @brief 蜂鸣器音乐包播放
 * @param music 音乐包名称
 */
void Buzzer_Music(Buzzer_Music_Type music);