// AHT20数字温湿度传感器驱动源文件
//参考案例程序\applications\sample\wifi-iot\app\i2c_demo\aht20.c

// AHT20数字温湿度传感器驱动源文件

#include "aht20.h"      // AHT20数字温湿度传感器驱动接口

#include <stdio.h>      // 标准输入输出
#include <unistd.h>     // POSIX标准接口
#include <string.h>     // 字符串处理(操作字符数组)

// OpenHarmony HAL：IoT硬件设备操作接口-I2C
// base/iot_hardware/peripheral/interfaces/kits提供了一系列IoT
// 硬件设备操作的接口，包括FLASH,GPIO,I2C,PWM,UART,WATCHDOG等。
#include "iot_i2c.h"

// OpenHarmony HAL：IoT硬件设备操作接口-错误代码定义
#include "iot_errno.h"

// 定义一个宏，用于标识要使用的I2C总线编号是I2C0
#define AHT20_I2C_IDX 0

// 定义一个宏，用于标识上电启动时间（20ms）
#define AHT20_STARTUP_TIME     20*1000

// 定义一个宏，用于标识初始化（校准）时间（40ms）
#define AHT20_CALIBRATION_TIME 40*1000

// 定义一个宏，用于标识测量时间（75ms）
#define AHT20_MEASURE_TIME     75*1000

// 定义一个宏，用于标识AHT20数字温湿度传感器的设备地址（0x38）
#define AHT20_DEVICE_ADDR   0x38

// 定义一个宏，用于标识AHT20数字温湿度传感器的读地址（0x71）
#define AHT20_READ_ADDR     ((0x38<<1)|0x1)

// 定义一个宏，用于标识AHT20数字温湿度传感器的写地址（0x70）
#define AHT20_WRITE_ADDR    ((0x38<<1)|0x0)

// 定义一个宏，用于标识初始化（校准）命令
#define AHT20_CMD_CALIBRATION       0xBE

// 定义一个宏，用于标识初始化（校准）命令的第1字节参数
#define AHT20_CMD_CALIBRATION_ARG0  0x08

// 定义一个宏，用于标识初始化（校准）命令的第2字节参数
#define AHT20_CMD_CALIBRATION_ARG1  0x00

// 定义一个宏，用于标识触发测量命令
#define AHT20_CMD_TRIGGER       0xAC

// 定义一个宏，用于标识触发测量命令的第1字节参数
#define AHT20_CMD_TRIGGER_ARG0  0x33

// 定义一个宏，用于标识触发测量命令的第2字节参数
#define AHT20_CMD_TRIGGER_ARG1  0x00

// 定义一个宏，用于标识软复位命令
// 用于在无需关闭和再次打开电源的情况下，重新启动传感器系统，软复位所需时间不超过20毫秒
#define AHT20_CMD_RESET      0xBA

// 定义一个宏，用于标识获取状态命令
#define AHT20_CMD_STATUS     0x71

// 获取状态命令的回复有两种情况：
// 1. 初始化后触发测量之前，STATUS 只回复 1B 状态值；
// 2. 触发测量之后，STATUS 回复6B： 1B 状态值 + 2B 湿度 + 4b湿度 + 4b温度 + 2B 温度
//      RH = Srh / 2^20 * 100%
//      T  = St  / 2^20 * 200 - 50

// 1字节状态值：bit[7] 忙闲指示位

// 定义一个宏，用于标识忙闲指示位掩码的左移位数
#define AHT20_STATUS_BUSY_SHIFT 7

// 定义一个宏，用于标识忙闲指示位的掩码
#define AHT20_STATUS_BUSY_MASK  (0x1<<AHT20_STATUS_BUSY_SHIFT)

// 定义一个宏，用于标识忙闲指示位的值
#define AHT20_STATUS_BUSY(status) ((status & AHT20_STATUS_BUSY_MASK) >> AHT20_STATUS_BUSY_SHIFT)

// 1字节状态值：bit[6:5] 工作模式位

// 定义一个宏，用于标识当前工作模式位掩码的左移位数
#define AHT20_STATUS_MODE_SHIFT 5

// 定义一个宏，用于标识当前工作模式位的掩码
#define AHT20_STATUS_MODE_MASK  (0x3<<AHT20_STATUS_MODE_SHIFT)

// 定义一个宏，用于标识当前工作模式位的值
#define AHT20_STATUS_MODE(status) ((status & AHT20_STATUS_MODE_MASK) >> AHT20_STATUS_MODE_SHIFT)

// 1字节状态值：bit[4] 保留位

// 1字节状态值：bit[3] 校准使能位

// 定义一个宏，用于标识校准使能位掩码的左移位数
#define AHT20_STATUS_CALI_SHIFT 3

// 定义一个宏，用于标识校准使能位的掩码
#define AHT20_STATUS_CALI_MASK  (0x1<<AHT20_STATUS_CALI_SHIFT)

// 定义一个宏，用于标识校准使能位的值
#define AHT20_STATUS_CALI(status) ((status & AHT20_STATUS_CALI_MASK) >> AHT20_STATUS_CALI_SHIFT)

// 1字节状态值：bit[2:0] 保留位

// 定义一个宏，用于标识测量结果的长度（6字节）
#define AHT20_STATUS_RESPONSE_MAX 6

// 定义一个宏，用于标识温湿度值计算公式中的2^20
#define AHT20_RESLUTION            (1<<20)  // 2^20

// 定义一个宏，用于标识接收测量结果的重试次数
#define AHT20_MAX_RETRY 10

// 实现AHT20读写接口，封装下层的HAL接口、AHT20设备地址、读地址、和写地址

// AHT20读写接口：AHT20读
static uint32_t AHT20_Read(uint8_t *buffer, uint32_t buffLen)
{
    // 从I2C设备中读取数据
    uint32_t retval = IoTI2cRead(AHT20_I2C_IDX,     // 指定I2C总线ID
                                 AHT20_READ_ADDR,   // 指定读地址
                                 buffer,            // 指定读取数据的缓冲区
                                 buffLen);          // 指定读取数据的长度
    if (retval != IOT_SUCCESS)                      // 读取失败
    {
        // 打印读取失败的日志
        printf("I2cRead() failed, %0X!\n", retval);
        // 返回IoTI2cRead()返回的错误值
        return retval;
    }
    // 读取成功，返回IOT_SUCCESS
    return IOT_SUCCESS;
}

// AHT20读写接口：AHT20写
static uint32_t AHT20_Write(uint8_t *buffer, uint32_t buffLen)
{
    // 向I2C设备中写入数据
    uint32_t retval = IoTI2cWrite(AHT20_I2C_IDX,    // 指定I2C总线ID
                                  AHT20_WRITE_ADDR, // 指定写地址
                                  buffer,           // 指定写入数据的缓冲区
                                  buffLen);         // 指定写入数据的长度
    if (retval != IOT_SUCCESS)                      // 写入失败
    {
        // 打印写入失败的日志
        printf("I2cWrite() failed, %0X!\n", retval);
        // 返回IoTI2cWrite()返回的错误值
        return retval;
    }
    // 写入成功，返回IOT_SUCCESS
    return IOT_SUCCESS;
}

// 实现AHT20发送命令接口，封装AHT20读写接口、AHT20命令代码和相关参数

// AHT20发送命令接口：发送获取状态命令
static uint32_t AHT20_StatusCommand(void)
{
    // 定义一个缓冲区，用于存放命令代码
    uint8_t statusCmd[] = { AHT20_CMD_STATUS };
    // 发送获取状态命令
    return AHT20_Write(statusCmd, sizeof(statusCmd));
}

// AHT20发送命令接口：发送软复位命令
static uint32_t AHT20_ResetCommand(void)
{
    // 定义一个缓冲区，用于存放命令代码
    uint8_t resetCmd[] = {AHT20_CMD_RESET};
    // 发送软复位命令
    return AHT20_Write(resetCmd, sizeof(resetCmd));
}

// AHT20发送命令接口：发送初始化命令，进行校准
static uint32_t AHT20_CalibrateCommand(void)
{
    // 定义一个缓冲区，用于存放命令代码
    uint8_t clibrateCmd[] = {AHT20_CMD_CALIBRATION, AHT20_CMD_CALIBRATION_ARG0, AHT20_CMD_CALIBRATION_ARG1};
    // 发送初始化命令，进行校准
    return AHT20_Write(clibrateCmd, sizeof(clibrateCmd));
}

// AHT20发送命令接口：发送触发测量命令，开始测量
uint32_t AHT20_StartMeasure(void)
{
    // 定义一个缓冲区，用于存放命令代码
    uint8_t triggerCmd[] = {AHT20_CMD_TRIGGER, AHT20_CMD_TRIGGER_ARG0, AHT20_CMD_TRIGGER_ARG1};
    // 发送触发测量命令，开始测量
    return AHT20_Write(triggerCmd, sizeof(triggerCmd));
}

// 实现AHT20功能接口，封装下层接口、状态值的数据结构、测量结果的数据结构、
// 等待时间（包括上电启动时间、初始化校准时间、测量时间等）、和温湿度的具体计算公式

// AHT20功能接口：校准
// 读取温湿度值之前，首先要看状态字的校准使能位Bit[3]是否为 1(通过发送0x71可以获取一个字节的状态字)，
// 如果不为1，要发送0xBE命令(初始化)，此命令参数有两个字节， 第一个字节为0x08，第二个字节为0x00。
uint32_t AHT20_Calibrate(void)
{
    // 接收接口的返回值
    uint32_t retval = 0;

    // 定义一个缓冲区，用于接收测量结果
    uint8_t buffer[AHT20_STATUS_RESPONSE_MAX] = { 0 };

    // 初始化缓冲区
    memset(&buffer, 0x0, sizeof(buffer));

    // 发送获取状态命令
    retval = AHT20_StatusCommand();
    if (retval != IOT_SUCCESS) {
        return retval;
    }

    // 读取AHT20的回复数据
    retval = AHT20_Read(buffer, sizeof(buffer));
    if (retval != IOT_SUCCESS) {
        return retval;
    }

    // 状态字（1字节状态值）的忙闲指示位Bit[7]为设备忙，或者校准使能位Bit[3]为未校准
    if (AHT20_STATUS_BUSY(buffer[0]) || !AHT20_STATUS_CALI(buffer[0])) {
        // 发送软复位命令
        retval = AHT20_ResetCommand();
        if (retval != IOT_SUCCESS) {
            return retval;
        }

        // 等待上电启动时间（20ms）
        usleep(AHT20_STARTUP_TIME);

        // 发送初始化命令，进行校准
        retval = AHT20_CalibrateCommand();

        // 等待初始化（校准）时间（40ms）
        usleep(AHT20_CALIBRATION_TIME);

        // 返回校准结果
        return retval;
    }

    // 返回成功
    return IOT_SUCCESS;
}

// AHT20功能接口：开始测量
// 直接使用下层 AHT20发送命令接口 的AHT20_StartMeasure函数即可，这里就不再封装了

// AHT20功能接口：接收测量结果，拼接转换为标准值
uint32_t AHT20_GetMeasureResult(float* temp, float* humi)
{
    // 相关变量定义
    uint32_t retval = 0, i = 0;

    // 检查参数的合法性
    if (temp == NULL || humi == NULL) {
        return IOT_FAILURE;
    }

    // 定义一个缓冲区，用于接收测量结果
    uint8_t buffer[AHT20_STATUS_RESPONSE_MAX] = { 0 };

    // 初始化缓冲区
    memset(&buffer, 0x0, sizeof(buffer));

    // 接收测量结果
    retval = AHT20_Read(buffer, sizeof(buffer));
    if (retval != IOT_SUCCESS) {
        return retval;
    }

    // 注意：传感器在采集时需要时间,主机发出测量指令（0xAC）后，延时75毫秒以上再读取转换后的数据并判断返回的状态位是否正常。
    // 若状态字（1字节状态值）的忙闲指示位Bit[7]为0代表数据可正常读取，为1时传感器为忙状态，主机需要等待数据处理完成。
    // 重试接收测量结果
    for (i = 0; AHT20_STATUS_BUSY(buffer[0]) && i < AHT20_MAX_RETRY; i++) {
        // printf("AHT20 device busy, retry %d/%d!\r\n", i, AHT20_MAX_RETRY);
        // 等待测量时间（75ms）
        usleep(AHT20_MEASURE_TIME);
        // 接收测量结果
        retval = AHT20_Read(buffer, sizeof(buffer));
        if (retval != IOT_SUCCESS) {
            return retval;
        }
    }

    // 达到最大重试次数，返回失败
    if (i >= AHT20_MAX_RETRY) {
        printf("AHT20 device always busy!\r\n");
        return IOT_FAILURE;
    }

    // 成功接收测量结果
    // 计算湿度值
    uint32_t humiRaw = buffer[1];                           // 字节2
    humiRaw = (humiRaw << 8) | buffer[2];                   // 字节3
    humiRaw = (humiRaw << 4) | ((buffer[3] & 0xF0) >> 4);   // 字节4的前四位
    *humi = humiRaw / (float)AHT20_RESLUTION * 100;         // 根据公式计算湿度值

    // 计算温度值
    uint32_t tempRaw = buffer[3] & 0x0F;                    // 字节4的后四位
    tempRaw = (tempRaw << 8) | buffer[4];                   // 字节5
    tempRaw = (tempRaw << 8) | buffer[5];                   // 字节6
    *temp = tempRaw / (float)AHT20_RESLUTION * 200 - 50;    // 根据公式计算温度值
    // printf("humi = %05X, %f, temp= %05X, %f\r\n", humiRaw, *humi, tempRaw, *temp);
    // 返回成功
    return IOT_SUCCESS;
}
