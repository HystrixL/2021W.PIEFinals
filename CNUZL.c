#include "CNUZL.h"
#include "include.h"

/****************************排序相关****************************/

void SelectionSort(int *raw, int length) {
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

void QuickSort(int *arr, int low, int high) {
    if (low < high) {
        int i = low;
        int j = high;
        int k = arr[low];
        while (i < j) {
            while (i < j && arr[j] >= k) {
                j--;
            }

            if (i < j) {
                arr[i++] = arr[j];
            }

            while (i < j && arr[i] < k) {
                i++;
            }

            if (i < j) {
                arr[j--] = arr[i];
            }
        }

        arr[i] = k;

        QuickSort(arr, low, i - 1);
        QuickSort(arr, i + 1, high);
    }
}


/****************************RGB灯相关****************************/
FTMn_e RGBftmn = -1;
FTM_CHn_e RGBchR = -1;
FTM_CHn_e RGBchG = -1;
FTM_CHn_e RGBchB = -1;

void RGB_Init(FTMn_e ftmn, FTM_CHn_e chR, FTM_CHn_e chG, FTM_CHn_e chB) {
    RGBftmn = ftmn;
    RGBchR = chR;
    RGBchG = chG;
    RGBchB = chB;
    FTM_PWM_Init(ftmn, chR, 10000, 1000);
    FTM_PWM_Init(ftmn, chG, 10000, 1000);
    FTM_PWM_Init(ftmn, chB, 10000, 1000);
}

void RGB_Color(RGB_Color_Type color) {
    switch (color) {
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
        case Null:
            FTM_PWM_Duty(RGBftmn, RGBchR, 1000);
            FTM_PWM_Duty(RGBftmn, RGBchG, 1000);
            FTM_PWM_Duty(RGBftmn, RGBchB, 1000);
            break;
    }
}

void RGB_Value(int r, int g, int b) {
    int rValue = r * 1000 / 255;
    int gValue = g * 1000 / 255;
    int bValue = b * 1000 / 255;
    FTM_PWM_Duty(RGBftmn, RGBchR, 1000 - rValue);
    FTM_PWM_Duty(RGBftmn, RGBchG, 1000 - gValue);
    FTM_PWM_Duty(RGBftmn, RGBchB, 1000 - bValue);
}

/****************************蜂鸣器相关****************************/
FTMn_e BuzzerFtmn = -1;
FTM_CHn_e BuzzerCh = -1;

void Buzzer_Init(FTMn_e ftmn, FTM_CHn_e ch) {
    BuzzerFtmn = ftmn;
    BuzzerCh = ch;
    FTM_PWM_Init(BuzzerFtmn, BuzzerCh, Ti, 250);
}

void Buzzer_Tone(Buzzer_Tone_Type tone) {
    FTM_PWM_Freq(BuzzerFtmn, tone);
}

void Buzzer_Volume(int volume) {
    FTM_PWM_Duty(BuzzerFtmn, BuzzerCh, volume * 5);
}

void Buzzer_Music(Buzzer_Music_Type music) {
    switch (music) {
        case Nothing:
            break;
    }
}