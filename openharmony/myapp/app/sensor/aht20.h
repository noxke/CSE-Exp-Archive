// AHT20数字温湿度传感器驱动接口文件

// 定义条件编译宏，防止头文件的重复包含和编译
#ifndef AHT20_H
#define AHT20_H

#include <stdint.h>     // 定义了几种扩展的整数类型和宏

// 声明接口函数

// 接口函数：校准
uint32_t AHT20_Calibrate(void);

// 接口函数：启动测量（触发测量）
uint32_t AHT20_StartMeasure(void);

// 接口函数：接收测量结果，拼接转换为标准值
uint32_t AHT20_GetMeasureResult(float* temp, float* humi);

// 条件编译结束
#endif  // AHT20_H
