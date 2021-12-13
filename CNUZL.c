#include "CNUZL.h"
#include "include.h"

/****************************排序相关****************************/

void SelectionSort(int* raw, int length) {
	for (int i = 0; i < length; i++) {
		for (int j = i; j < length; j++) {
			if (raw[j] < raw[i]) {
				int temp = raw[i];
				raw[i] = raw[j];
				raw[j] = temp;
			}
		}
	}
}


/****************************RGB灯相关****************************/
FTMn_e RGBftmn = -1;
FTM_CHn_e RGBchR = -1;
FTM_CHn_e RGBchG = -1;
FTM_CHn_e RGBchB = -1;
void RGB_Init(FTMn_e ftmn, FTM_CHn_e chR, FTM_CHn_e chG, FTM_CHn_e chB)
{
	RGBftmn = ftmn;
	RGBchR = chR;
	RGBchG = chG;
	RGBchB = chB;
	FTM_PWM_Init(ftmn, chR, 10000, 1000);
	FTM_PWM_Init(ftmn, chG, 10000, 1000);
	FTM_PWM_Init(ftmn, chB, 10000, 1000);
}

void RGB_Color(RGB_Color_Type color)
{
	switch (color)
	{
		case Red:
			FTM_PWM_Duty(RGBftmn, RGBchR, 0);
			FTM_PWM_Duty(RGBftmn, RGBchG, 1000);
			FTM_PWM_Duty(RGBftmn, RGBchB, 1000);
			break;
		case Green:
			FTM_PWM_Duty(RGBftmn, RGBchR, 1000);
			FTM_PWM_Duty(RGBftmn, RGBchG, 0);
			FTM_PWM_Duty(RGBftmn, RGBchB, 1000);
			break;
		case Blue:
			FTM_PWM_Duty(RGBftmn, RGBchR, 1000);
			FTM_PWM_Duty(RGBftmn, RGBchG, 1000);
			FTM_PWM_Duty(RGBftmn, RGBchB, 0);
			break;
		case Yellow:
			FTM_PWM_Duty(RGBftmn, RGBchR, 0);
			FTM_PWM_Duty(RGBftmn, RGBchG, 0);
			FTM_PWM_Duty(RGBftmn, RGBchB, 1000);
			break;
		case Magenta:
			FTM_PWM_Duty(RGBftmn, RGBchR, 0);
			FTM_PWM_Duty(RGBftmn, RGBchG, 1000);
			FTM_PWM_Duty(RGBftmn, RGBchB, 0);
			break;
		case Cyan:
			FTM_PWM_Duty(RGBftmn, RGBchR, 1000);
			FTM_PWM_Duty(RGBftmn, RGBchG, 0);
			FTM_PWM_Duty(RGBftmn, RGBchB, 0);
			break;
		case White:
			FTM_PWM_Duty(RGBftmn, RGBchR, 0);
			FTM_PWM_Duty(RGBftmn, RGBchG, 0);
			FTM_PWM_Duty(RGBftmn, RGBchB, 0);
			break;
	}
}

void RGB_Value(int r, int g, int b)
{
	int rValue = (int)(r * (1000 / 255.0));
	int gValue = (int)(g * (1000 / 255.0));
	int bValue = (int)(b * (1000 / 255.0));
	FTM_PWM_Duty(RGBftmn, RGBchR, 1000-rValue);
	FTM_PWM_Duty(RGBftmn, RGBchG, 1000-gValue);
	FTM_PWM_Duty(RGBftmn, RGBchB, 1000-bValue);
}