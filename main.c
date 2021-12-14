/***************************************************************
@ʵ�����ƣ�       ETR
@�̼���ƽ̨��     �̼��� V7.0 �汾
@���ߣ�
@����оƬ��       MK60DN512VLQ10
@ʵ��Ч����
****************************************************************/

#include "include.h"
#include "LCDDisplay.c"
#include "CNUZL.h"
#include "CNUZL.c"

#pragma ide diagnostic ignored "EndlessLoop"
#define E 2.718

void Init(void);
float GetBattery(void);
void CoreClock(void);
void LightsSwitch(void);
void LCDUpdate(void);
void MotorPI(void);
void LostLineStop(void);
//void VODebug(void);
//void E_handler(void);
//void ReedSwitches(void);

typedef struct {
    int Max;
    int Min;
    int Avg;
    int Process;
} ElecSensor;
ElecSensor OutsideLeft = {0, 10000000, 0, 0}, OutsideRight = {0, 10000000, 0, 0},
        InsideLeft = {0, 10000000, 0, 0}, InsideRight = {0, 10000000, 0, 0};

Parameter parameter;

bool isCollecting = false;
bool isRunning = false;

int nowSpeed = 0;
int ExpectSpeedOutput = 500;
int ExpectSpeed = 0;
int SpeedError = 0;
int LastSpeedError = 0;
int currentSpeedOutput = 0;

float angleRate = 0;
float processDiffer = 0;
float lastProcessDiffer = 0;

int RunningTimer = 0;
int StopTimer = 0;

const int MidAngle = 77;
const int MaxAngle = 8;
const int MaxSpeed = 1000;

int main(void) {
    Init();

    while (1) {
        //��������
        if (GPIO_ReadBit(GPIOD, 13) == 0) {
            while (GPIO_ReadBit(GPIOD, 13) == 0);
            isCollecting = !isCollecting;
        }
        if (GPIO_ReadBit(GPIOD, 14) == 0) {
            while (GPIO_ReadBit(GPIOD, 14) == 0);
            isRunning = !isRunning;
            ExpectSpeedOutput = 0;
            if (isRunning) {
                LCD_CLS();
                GPIO_WriteBit(GPIOD, 0, 1);
                GPIO_WriteBit(GPIOD, 0, 1);
            }
        }
        //RGB״̬���
        LightsSwitch();
        //LCD���ݸ���
        if (!isRunning) LCDUpdate();
        //����˲�
        OutsideLeft.Avg = adc_ave(ADC1_SE16, ADC_12bit, 6, 4);
        OutsideRight.Avg = adc_ave(ADC1_DP1, ADC_12bit, 6, 4);
        InsideLeft.Avg = adc_ave(ADC0_SE16, ADC_12bit, 6, 4);
        InsideRight.Avg = adc_ave(ADC0_DP1, ADC_12bit, 6, 4);
        //��һ������
        if (isCollecting) {
            if (OutsideLeft.Avg > OutsideLeft.Max) OutsideLeft.Max = OutsideLeft.Avg;
            if (OutsideRight.Avg > OutsideRight.Max) OutsideRight.Max = OutsideRight.Avg;
            if (InsideLeft.Avg > InsideLeft.Max) InsideLeft.Max = InsideLeft.Avg;
            if (InsideRight.Avg > InsideRight.Max) InsideRight.Max = InsideRight.Avg;
        }
        //��һ��
        if (OutsideLeft.Max == 0 || OutsideRight.Max == 0 || InsideRight.Max == 0 || InsideLeft.Max == 0) continue;
        OutsideLeft.Process = OutsideLeft.Avg * (int) pow(2, 12) / OutsideLeft.Max;
        OutsideRight.Process = OutsideRight.Avg * (int) pow(2, 12) / OutsideRight.Max;
        InsideLeft.Process = InsideLeft.Avg * (int) pow(2, 12) / InsideLeft.Max;
        InsideRight.Process = InsideRight.Avg * (int) pow(2, 12) / InsideRight.Max;

        //��̬Ȩ�����
        processDiffer = (sqrtf((float) OutsideLeft.Process) - sqrtf((float) OutsideRight.Process) +
                         sqrtf((float) InsideLeft.Process) - sqrtf((float) InsideRight.Process)) /
                        (sqrtf((float) OutsideLeft.Process) + sqrtf((float) OutsideRight.Process) +
                         sqrtf((float) InsideLeft.Process) + sqrtf((float) InsideRight.Process));
        //�޷�
        if (processDiffer > 1) processDiffer = 1;
        if (processDiffer < -1) processDiffer = -1;
        //���PD
        angleRate = parameter.dirP * (processDiffer) + parameter.dirD * (processDiffer - lastProcessDiffer);
        //�޷�
        if (angleRate > 1) angleRate = 1;
        if (angleRate < -1) angleRate = -1;
        //�����ֵ
        FTM_PWM_Duty(FTM2, FTM_CH1, MidAngle + (int) (angleRate * (float) MaxAngle));
        //����޷�
        currentSpeedOutput = ExpectSpeedOutput;
        if (currentSpeedOutput > MaxSpeed) currentSpeedOutput = MaxSpeed;
        if (currentSpeedOutput < -MaxSpeed) currentSpeedOutput = -MaxSpeed;
        //�����ֵ
        if (currentSpeedOutput >= 0) {
            FTM_PWM_Duty(FTM0, FTM_CH0, 0);
            FTM_PWM_Duty(FTM0, FTM_CH1, currentSpeedOutput);
            FTM_PWM_Duty(FTM0, FTM_CH2, 0);
            FTM_PWM_Duty(FTM0, FTM_CH3, currentSpeedOutput);
        } else {
            FTM_PWM_Duty(FTM0, FTM_CH0, abs(currentSpeedOutput));
            FTM_PWM_Duty(FTM0, FTM_CH1, 0);
            FTM_PWM_Duty(FTM0, FTM_CH2, abs(currentSpeedOutput));
            FTM_PWM_Duty(FTM0, FTM_CH3, 0);
        }

        lastProcessDiffer = processDiffer;

    }
}

/*!
 * @brief LCD���ݸ���
 */
void LCDUpdate(void) {
    parameter = LCDShower();

    UpdateValue("OAvgL", (float) OutsideLeft.Avg);
    UpdateValue("OAvgR", (float) OutsideRight.Avg);
    UpdateValue("OMaxL", (float) OutsideLeft.Max);
    UpdateValue("OMaxR", (float) OutsideRight.Max);
    UpdateValue("OPDL", (float) OutsideLeft.Process);
    UpdateValue("OPDR", (float) OutsideRight.Process);
    UpdateValue("OLmR", (float) OutsideLeft.Process - (float) OutsideRight.Process);
    UpdateValue("OLaR", (float) OutsideLeft.Process + (float) OutsideRight.Process);
    UpdateValue("LDP", lastProcessDiffer);
    UpdateValue("kD", parameter.dirD * (processDiffer - lastProcessDiffer));
    UpdateValue("ANGLE", angleRate);
    UpdateValue("OMA", (float) (OutsideLeft.Process - OutsideRight.Process) /
                       (float) (OutsideLeft.Process + OutsideRight.Process));
    UpdateValue("Bat", GetBattery());
    UpdateValue("SPD", (float) ExpectSpeedOutput);
    UpdateValue("NOWSPD", (float) nowSpeed);
    UpdateValue("CSO", (float) currentSpeedOutput);
    UpdateValue("ES", (float) ExpectSpeed);
    UpdateValue("IAvgL", (float) InsideLeft.Avg);
    UpdateValue("IAvgR", (float) InsideRight.Avg);
    UpdateValue("IMaxL", (float) InsideLeft.Max);
    UpdateValue("IMaxR", (float) InsideRight.Max);
    UpdateValue("IPDL", (float) InsideLeft.Process);
    UpdateValue("IPDR", (float) InsideRight.Process);
    UpdateValue("ILmR", (float) InsideLeft.Process - (float) InsideRight.Process);
    UpdateValue("ILaR", (float) InsideLeft.Process + (float) InsideRight.Process);
    UpdateValue("IMA", (float) (InsideLeft.Process - InsideRight.Process) /
                       (float) (InsideLeft.Process + InsideRight.Process));
}

/*!
 * @brief ��ȡ��ص�ѹ
 */
float GetBattery(void) {
    return 4 * 3.3F * (float) ADC_Once(ADC0_DM1, ADC_16bit) / 65536;
}

/*!
 * @brief ��ʼ��
 */
void Init(void) {
    //UART_Init(UART0,9600);
    //RGB
    RGB_Init(FTM0, FTM_CH5, FTM_CH6, FTM_CH4);
    //LCD�л�
    ParameterAdjustmentInit();
    //���
    ADC_Init(ADC1_SE16);//OutsideLeft
    ADC_Init(ADC1_DP1);//OutsideRight
    ADC_Init(ADC0_SE16);//InsideLeft
    ADC_Init(ADC0_DP1);//InsideRight
    //���
    ADC_Init(ADC0_DM1);
    //���
    FTM_PWM_Init(FTM0, FTM_CH0, 10000, 0);
    FTM_PWM_Init(FTM0, FTM_CH1, 10000, 0);
    FTM_PWM_Init(FTM0, FTM_CH2, 10000, 0);
    FTM_PWM_Init(FTM0, FTM_CH3, 10000, 0);
    //���
    FTM_PWM_Init(FTM2, FTM_CH1, 50, 77);
    //ָʾ��
    GPIO_QuickInit(GPIOD, 0, kGPIO_Mode_OPP);
    GPIO_QuickInit(GPIOD, 1, kGPIO_Mode_OPP);
    GPIO_QuickInit(GPIOD, 2, kGPIO_Mode_OPP);
    GPIO_QuickInit(GPIOD, 3, kGPIO_Mode_OPP);
    GPIO_WriteBit(GPIOD, 0, 1);
    GPIO_WriteBit(GPIOD, 1, 1);
    GPIO_WriteBit(GPIOD, 2, 1);
    GPIO_WriteBit(GPIOD, 3, 1);
    //����
    GPIO_QuickInit(GPIOD, 13, kGPIO_Mode_IPU);
    GPIO_QuickInit(GPIOD, 14, kGPIO_Mode_IPU);
    //����ʱ��
    FTM_QUAD_Init(FTM1);
    pit_init_ms(PIT0, 20);
    set_vector_handler(PIT0_VECTORn, CoreClock);
    enable_irq(PIT0_IRQn);
    // ����ʾ��������
    /*    pit_init_ms(PIT1, 10);
    set_vector_handler(PIT1_VECTORn, VODebug);
    enable_irq(PIT1_IRQn);
    set_irq_priority(PIT1,1);
    */
    //�ɻɹ�ͣ��
    /*
    GPIO_QuickInit(GPIOE, 4, kGPIO_Mode_IPU);
    PORT_FuncQuickInit(PTE4, IRQ_FALLING);
    set_vector_handler(PORTE_VECTORn, E_handler);
    enable_irq (PORTE_IRQn);
    */
}

/*!
 * @brief RGB��Ч�л�
 */
void LightsSwitch(void) {
    if (isRunning) {
        RGB_Color(Green);
    } else {
        if (isCollecting) RGB_Color(Blue);
        else RGB_Color(Red);
    }
}


/*!
 * @brief ������ʱ��
 * @note T=20ms
 */
void CoreClock(void) {
    MotorPI();
    LostLineStop();
    if (isRunning) RunningTimer++;
    else RunningTimer = 0;

    PIT_Flag_Clear(PIT0);
}

/*!
 * @brief ���PI
 */
void MotorPI(void) {
    nowSpeed = FTM_QUAD_Get(FTM1);

    if (isRunning)
        ExpectSpeed = (int) (parameter.BaseSpeed - fabs((parameter.BaseSpeed - parameter.TurningSpeed) *
                                                        (pow(E, pow(angleRate, 2)) - 1)));
    else
        ExpectSpeed = 0;

    SpeedError = ExpectSpeed - nowSpeed;
    ExpectSpeedOutput += (int) (parameter.spdP * (float) (SpeedError - LastSpeedError) +
                                parameter.spdI * (float) SpeedError);

    LastSpeedError = SpeedError;

    FTM_QUAD_Clean(FTM1);
}

/*!
 * @brief ����ͣ��
 */
void LostLineStop(void) {
    if (OutsideLeft.Avg < 500 && OutsideRight.Avg < 500 && isRunning) {
        StopTimer++;
        if (StopTimer > 100) {
            isRunning = false;
            GPIO_WriteBit(GPIOD, 0, 0);
        }
    } else {
        if (StopTimer != 0) StopTimer = 0;
    }
}

/*
void E_handler(void) {
//PORT_FUNC(E, 4, ReedSwitches);
}
void ReedSwitches(void) {
if(RunningTimer>500)
{
isRunning = false;
GPIO_WriteBit(GPIOD,1,0);
    }

}
*/

/*void VODebug(void){
int32_t VOMonitor[3] = {ExpectSpeed,nowSpeed,currentSpeedOutput};
vcan_sendware(VOMonitor,sizeof(VOMonitor));
PIT_Flag_Clear(PIT1);
}*/