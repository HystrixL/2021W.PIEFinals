#include "include.h"
#pragma once

/****************************�������****************************/

//ѡ������(������ ���������飬���鳤��)
void SelectionSort(int *raw, int length);


/****************************RGB�����****************************/

typedef enum
{
	Red,		//��
	Green,		//��
	Blue,		//��
	Yellow,		//��
	Magenta,	//���
	Cyan,		//��
	White		//��
} RGB_Color_Type;//��ɫ�����б�

//RGB���ٳ�ʼ��(������ ģ��ţ���ɫͨ���ţ���ɫͨ���ţ���ɫͨ����)
void RGB_Init(FTMn_e ftmn, FTM_CHn_e chR, FTM_CHn_e chG, FTM_CHn_e chB);
//RGB�����л���ɫ�������� ��ɫ���ƣ�
void RGB_Color(RGB_Color_Type color);
//RGB��ɫ�̣������� R��G��B��
void RGB_Value(int r, int g, int b);


/****************************���������****************************/
