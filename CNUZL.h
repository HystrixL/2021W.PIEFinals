#include "include.h"
#pragma once

//-------------------------------------------------------------------
// �������
//-------------------------------------------------------------------

/*!
 * @brief ѡ������
 * @param raw    ����������
 * @param length ���鳤��
 */
void SelectionSort(int *raw, int length);

/*!
 * @brief ��������
 * @param arr    ����������
 * @param low   �������λ
 * @param high  �������λ
 * @note lowӦΪ�������������ͨ��Ϊ0;\n highӦΪ�������������ͨ��Ϊ���鳤��-1
 */
void QuickSort(int *arr, int low, int high);

//-------------------------------------------------------------------
// RGB�����
//-------------------------------------------------------------------

/*!
 * @brief ��ɫ�����б�
 * @enum Red    	��
 * @enum Green  	��
 * @enum Blue  	    ��
 * @enum Yellow 	��
 * @enum Magenta    ���
 * @enum Cyan  	    ��
 * @enum White      ��
 * @enum Null       ��ɫ
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
 * @brief RGB���ٳ�ʼ��
 * @param ftmn  ģ���
 * @param chR   ��ɫͨ����
 * @param chG   ��ɫͨ����
 * @param chB   ��ɫͨ����
 */
void RGB_Init(FTMn_e ftmn, FTM_CHn_e chR, FTM_CHn_e chG, FTM_CHn_e chB);

/*!
 * @brief RGB�����л���ɫ
 * @param color     ��ɫ����
 */
void RGB_Color(RGB_Color_Type color);

/*!
 * @brief RGB��ɫ��
 * @param r     ��ɫ��ֵ(255)
 * @param g     ��ɫ��ֵ(255)
 * @param b     ��ɫ��ֵ(255)
 */
void RGB_Value(int r, int g, int b);


//-------------------------------------------------------------------
// ���������
//-------------------------------------------------------------------

/*!
 * @brief ����������
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
} Buzzer_Tone_Type;//�����������б�

/*!
 * @brief ���������ְ�
 * @enum Nothing ��
 */
typedef enum{
  Nothing
} Buzzer_Music_Type;//���������ְ�

/*!
 * @brief ���������ٳ�ʼ��
 * @note Ĭ������50
 * @param ftmn     ������ģ���
 * @param ch    ������ͨ����
 */
void Buzzer_Init(FTMn_e ftmn, FTM_CHn_e ch);

/*!
 * @brief ��������������
 * @param tone     ����
 */
void Buzzer_Tone(Buzzer_Tone_Type tone);

/*!
 * @brief ��������������
 * @param volume ����
 * @note ��Χ��0~100
 */
void Buzzer_Volume(int volume);

/*!
 * @brief ���������ְ�����
 * @param music ���ְ�����
 */
void Buzzer_Music(Buzzer_Music_Type music);