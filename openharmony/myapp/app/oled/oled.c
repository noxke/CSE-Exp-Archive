#include <stdio.h>     // 标准输入输出
#include <unistd.h>    // POSIX标准接口
#include "ohos_init.h" // 用于初始化服务(services)和功能(features)
#include "cmsis_os2.h" // CMSIS-RTOS API V2
#include "ssd1306.h"   // OLED驱动接口
#include "shared_variable.h"

#include "madoka.h"
// 画小圆
const unsigned char *frameDatas[] = {frame0Data, frame1Data, frame2Data, frame3Data, frame4Data, frame5Data, frame6Data, frame7Data, frame8Data, frame9Data, frame10Data};
const int frameNum = 11;
void DrawMadoka(void)
{
    for (int i = 0; i < 50; i++)
    {
        ssd1306_DrawBitmap(frameDatas[i%frameNum], frameDatas[i%frameNum]);
        ssd1306_UpdateScreen();
        osDelay(10);
    }
}

time_t time_raw;
char time_date[20];
char time_time[20];
struct tm *local_time;
void DrawTime(void)
{
    // 格式化时间 +8时区
    time(&time_raw);
    time_raw = time_raw + shared_variable_time_offset + 8 * 3600;
    local_time = localtime(&time_raw);
    snprintf(time_date, sizeof(time_date),
             "%04d-%02d-%02d %s",
             local_time->tm_year + 1900,
             local_time->tm_mon + 1,
             local_time->tm_mday,
             (local_time->tm_wday == 0) ? "Sun" :
             (local_time->tm_wday == 1) ? "Mon" :
             (local_time->tm_wday == 2) ? "Tue" :
             (local_time->tm_wday == 3) ? "Wed" :
             (local_time->tm_wday == 4) ? "Thu" :
             (local_time->tm_wday == 5) ? "Fri" :
             "Sat");
    snprintf(time_time, sizeof(time_time),
             "%02d:%02d:%02d",
             local_time->tm_hour,
             local_time->tm_min,
             local_time->tm_sec);
    // 设置显示位置
    ssd1306_SetCursor(20, 0);
    ssd1306_DrawString(time_time, Font_11x18, White);
    ssd1306_SetCursor(15, 20);
    ssd1306_DrawString(time_date, Font_7x10, White);
}

char temperature_str[20];
char humidity_str[20];
void DrawSensor(void)
{
    //需要补全
    sprintf(temperature_str, "Temperature: %.2f", shared_variable_temperature);
    sprintf(humidity_str, "Humidity: %.2f%", shared_variable_humidity);
    // 设置显示位置
    ssd1306_SetCursor(0, 36);
    ssd1306_DrawString(temperature_str, Font_7x10, White);
    ssd1306_SetCursor(0, 48);
    ssd1306_DrawString(humidity_str, Font_7x10, White);
}

// 主线程函数
void Ssd1306TestTask(void *arg)
{
    (void)arg;
    // 初始化OLED
    ssd1306_Init();
    ssd1306_Fill(Black);

    DrawMadoka();
    // 主循环 / fixed update
    while (1)
    {
        uint32_t start = osKernelGetTickCount();
        ssd1306_Fill(Black);
        DrawTime();
        DrawSensor();
        ssd1306_UpdateScreen();
        osDelay(100 - (osKernelGetTickCount() - start));
    }
}

// 入口函数
void OledMain(void)
{
    // 定义线程属性
    osThreadAttr_t attr;
    attr.name = "Ssd1306Task";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 10240;
    attr.priority = osPriorityNormal;

    // 创建线程
    if (osThreadNew(Ssd1306TestTask, NULL, &attr) == NULL)
    {
        printf("[OledMain] Falied to create Ssd1306TestTask!\n");
    }
}

// 运行入口函数
APP_FEATURE_INIT(OledMain);
