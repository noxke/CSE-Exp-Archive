//参考案例程序\applications\sample\wifi-iot\app\i2c_demo\temp-humi_sensor.c

#include <stdio.h>      // 标准输入输出
#include <unistd.h>     // POSIX标准接口

#include "ohos_init.h"  // 用于初始化服务(services)和功能(features)
#include "cmsis_os2.h"  // CMSIS-RTOS API V2

#include "iot_gpio.h"   // OpenHarmony HAL：IoT硬件设备操作接口-GPIO
#include "iot_i2c.h"    // OpenHarmony HAL：IoT硬件设备操作接口-I2C
#include "iot_errno.h"  // OpenHarmony HAL：IoT硬件设备操作接口-错误代码定义
#include "hi_io.h"      // 海思 Pegasus SDK：IoT硬件设备操作接口-IO
#include "hi_adc.h"     // 海思 Pegasus SDK：IoT硬件设备操作接口-ADC

#include "aht20.h"      // AHT20数字温湿度传感器驱动接口

#include "aht20.h"
#include "shared_variable.h"

float shared_variable_temperature;
float shared_variable_humidity;

// 定义一个宏，用于标识AHT20的波特率（传输速率）
#define AHT20_BAUDRATE 400 * 1000

// 定义一个宏，用于标识要使用的I2C总线编号是I2C0
#define AHT20_I2C_IDX 0

// 主线程函数 
static void tempHumiTask(void *arg)
{
    (void)arg;

    // 接收接口的返回值
    uint32_t retval = 0;
    // 湿度值
    float humidity = 0.0f;
    // 温度值
    float temperature = 0.0f;

    // 初始化GPIO
    IoTGpioInit(HI_IO_NAME_GPIO_13);
    IoTGpioInit(HI_IO_NAME_GPIO_14);

    // 设置GPIO-13引脚功能为I2C0_SDA
    hi_io_set_func(HI_IO_NAME_GPIO_13, HI_IO_FUNC_GPIO_13_I2C0_SDA);
    // 设置GPIO-14引脚功能为I2C0_SCL
    hi_io_set_func(HI_IO_NAME_GPIO_14, HI_IO_FUNC_GPIO_14_I2C0_SCL);

    // 用指定的波特速率初始化I2C0
    IoTI2cInit(AHT20_I2C_IDX, AHT20_BAUDRATE);

    // 校准AHT20，如果校准失败，等待100ms后重试
    while (IOT_SUCCESS != AHT20_Calibrate())
    {
        printf("AHT20 sensor init failed!\r\n");
        usleep(100 * 1000);
    }

    // 工作循环
    while (1)
    {
        // 启动测量
        retval = AHT20_StartMeasure();
        if (retval != IOT_SUCCESS)
        {
            printf("trigger measure failed!\r\n");
        }

        // 接收测量结果
        retval = AHT20_GetMeasureResult(&temperature, &humidity);
        if (retval != IOT_SUCCESS)
        {
            printf("get data failed!\r\n");
        }

        // 输出测量结果
        shared_variable_temperature = temperature;
        shared_variable_humidity = humidity;
        printf("temperature: %.2f, humidity: %.2f\r\n", temperature, humidity);

        // 等待1秒
        osDelay(100);
    }
}

// 入口函数
static void tempHumiDemo(void)
{
    // 定义线程属性
    osThreadAttr_t attr;
    attr.name = "tempHumiTask";
    attr.stack_size = 4096;
    attr.priority = osPriorityNormal;

    // 创建线程
    if (osThreadNew(tempHumiTask, NULL, &attr) == NULL)
    {
        printf("[%s] Falied to create tempHumiTask!\n", __func__);
    }
}

// 运行入口函数
APP_FEATURE_INIT(tempHumiDemo);
