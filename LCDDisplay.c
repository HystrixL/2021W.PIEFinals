/***************************************************************
   @实验名称：       LCD 参数调节
   @固件库平台：     固件库 V7.0 版本
   @作者：			Hil.
   @板载芯片：       MK60DN512VLQ10
   @实验效果：
****************************************************************/

#include "include.h"

#define MaxMonitor 32
#define MaxParameterLibrary 3

typedef struct {
    float dirP;
    float dirD;
    float spdP;
    float spdI;
    int BaseSpeed;
    int TurningSpeed;
    float Precision;
} Parameter;

typedef struct {
    char Name[6];
    float Value;
} Monitor;

Monitor Monitors[MaxMonitor];
int Length = 0;
Parameter parameter = {1.7F, 80.0F, 0.8F, 0.5F, 420, 340, 1.0F};
bool isLocking = true;
int Page = 0;
int Selected = 0;
int InfoFreshTimer = 0;

const Parameter ParameterLibrary[MaxParameterLibrary] = {{1.7F, 80.0F, 0.8F, 0.5F, 420, 340, 1.0F},
                                                         {1.7F, 100.0F, 1.0F, 0.8F, 480, 360, 1.0F},
                                                         {1.8F, 100.0F, 1.0F, 0.8F, 500, 400, 1.0F}};
int ParameterIndex = 0;

void FreshLCD(void);
void ParameterAdjustmentInit(void);

Parameter LCDShower(void) {
    if (GPIO_ReadBit(GPIOD, 12) == 0) {
        while ((GPIO_ReadBit(GPIOD, 12) == 0));
        if (isLocking) {
            Page--;
            if (Page < 0) Page = (Length - 1) / 8 + 1;
        } else {
            Selected--;
            if (Selected < 0) Selected = 6;
        }
        FreshLCD();
    }
    if (GPIO_ReadBit(GPIOD, 10) == 0) {
        while ((GPIO_ReadBit(GPIOD, 10) == 0));
        if (isLocking) {
            Page++;
            if (Page > (Length - 1) / 8 + 1) Page = 0;
        } else {
            Selected++;
            if (Selected > 6) Selected = 0;
        }
        FreshLCD();

    }
    if (Page != 0) {
        InfoFreshTimer++;
        if (InfoFreshTimer > 3000) {
            InfoFreshTimer = 0;
            FreshLCD();
        }
        return parameter;
    }
    if ((GPIO_ReadBit(GPIOD, 9) == 0)) {
        while ((GPIO_ReadBit(GPIOD, 9) == 0));
        isLocking = !isLocking;
        FreshLCD();
    }
    if (GPIO_ReadBit(GPIOD, 8) == 0) {
        while ((GPIO_ReadBit(GPIOD, 8) == 0));
        if (isLocking) {
            ParameterIndex--;
            if (ParameterIndex < 0) ParameterIndex = MaxParameterLibrary - 1;
            parameter = ParameterLibrary[ParameterIndex];
        } else {
            switch (Selected) {
                case 0:
                    parameter.Precision /= 10.0F;
                    break;
                case 1:
                    parameter.dirP -= parameter.Precision;
                    break;
                case 2:
                    parameter.dirD -= parameter.Precision;
                    break;
                case 3:
                    parameter.spdP -= parameter.Precision;
                    break;
                case 4:
                    parameter.spdI -= parameter.Precision;
                    break;
                case 5:
                    parameter.BaseSpeed -= 10;
                    break;
                case 6:
                    parameter.TurningSpeed -= 10;
                    break;
            }
        }

        FreshLCD();
    }
    if (GPIO_ReadBit(GPIOD, 11) == 0) {
        while ((GPIO_ReadBit(GPIOD, 11) == 0));
        if (isLocking) {
            ParameterIndex++;
            if (ParameterIndex > MaxParameterLibrary - 1) ParameterIndex = 0;
            parameter = ParameterLibrary[ParameterIndex];
        } else {
            switch (Selected) {
                case 0:
                    parameter.Precision *= 10.0F;
                    break;
                case 1:
                    parameter.dirP += parameter.Precision;
                    break;
                case 2:
                    parameter.dirD += parameter.Precision;
                    break;
                case 3:
                    parameter.spdP += parameter.Precision;
                    break;
                case 4:
                    parameter.spdI += parameter.Precision;
                    break;
                case 5:
                    parameter.BaseSpeed += 10;
                    break;
                case 6:
                    parameter.TurningSpeed += 10;
                    break;
            }
        }

        FreshLCD();
    }
    return parameter;
}

void ParameterAdjustmentInit(void) {
    LCD_Init();
    GPIO_QuickInit(GPIOD, 8, kGPIO_Mode_IPU);
    GPIO_QuickInit(GPIOD, 9, kGPIO_Mode_IPU);
    GPIO_QuickInit(GPIOD, 10, kGPIO_Mode_IPU);
    GPIO_QuickInit(GPIOD, 11, kGPIO_Mode_IPU);
    GPIO_QuickInit(GPIOD, 12, kGPIO_Mode_IPU);
    for (int i = 0; i < MaxMonitor; ++i) {
        Monitors[i].Value = -256;
    }
    FreshLCD();
}

void UpdateValue(char name[6], float value) {
    for (int i = 0; i < 32; ++i) {
        if (strcmp(Monitors[i].Name, name) == 0) {
            Monitors[i].Value = value;
            return;
        }
    }

    for (int i = 0; i < 6; ++i) {
        Monitors[Length].Name[i] = name[i];
    }
    Monitors[Length].Value = value;
    Length++;
}

void FreshLCD(void) {
    LCD_CLS();
    if (Page == 0) {
        LCD_P6x8Str(10, 0, "Precision = ");
        LCD_P6x8Str(10, 1, "dirP = ");
        LCD_P6x8Str(10, 2, "dirD = ");
        LCD_P6x8Str(10, 3, "spdP = ");
        LCD_P6x8Str(10, 4, "spdI = ");
        LCD_P6x8Str(10, 5, "BS = ");
        LCD_P6x8Str(10, 6, "TS = ");
        if (!isLocking) LCD_P6x8Str(0, Selected, ">");
        LCD_Printfloat(80, 0, parameter.Precision, 5);
        LCD_Printfloat(80, 1, parameter.dirP, 5);
        LCD_Printfloat(80, 2, parameter.dirD, 5);
        LCD_Printfloat(80, 3, parameter.spdP, 5);
        LCD_Printfloat(80, 4, parameter.spdI, 5);
        LCD_PrintU16(80, 5, parameter.BaseSpeed);
        LCD_PrintU16(80, 6, parameter.TurningSpeed);
    } else {
        for (int i = (Page - 1) * 8; i < Page * 8; i++) {
            if (Monitors[i].Value != -256) {
                LCD_P6x8Str(0, i - (Page - 1) * 8, Monitors[i].Name);
                LCD_Printfloat(50, i - (Page - 1) * 8, Monitors[i].Value, 5);
            }

        }
    }
}
