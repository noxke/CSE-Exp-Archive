# HiSpark WiFi-IoT 鸿蒙套件样例开发--harmonyos-ssd1306

![hihope_illustration](https://gitee.com/hihopeorg/hispark-hm-pegasus/raw/master/docs/figures/hihope_illustration.png)

[HiSpark WiFi-IoT鸿蒙开发套件](https://item.taobao.com/item.htm?spm=a1z10.1-c-s.w5003-23341819265.1.bf644a82Da9PZK&id=622343426064&scene=taobao_shop) 首发于HDC 2020，是首批支持HarmonyOS 2.0的开发套件，亦是鸿蒙官方推荐套件，由润和软件HiHope量身打造，已在鸿蒙社区和广大鸿蒙开发者中得到广泛应用。

![wifi_iot](https://gitee.com/hihopeorg/hispark-hm-pegasus/raw/master/docs/figures/wifi_iot.png)



## 一、I2C API

| API名称                                                      | 说明                          |
| ------------------------------------------------------------ | ----------------------------- |
| IoTI2cInit(unsigned int id, unsigned int baudrate);         | 用指定的波特速率初始化I2C设备 |
| IoTI2cDeinit(unsigned int id);                               | 取消初始化I2C设备             |
| IoTI2cWrite(unsigned int id, unsigned short deviceAddr, const unsigned char *data, unsigned int dataLen); | 将数据写入I2C设备             |
| IoTI2cRead(unsigned int id, unsigned short deviceAddr, unsigned char *data, unsigned int dataLen); | 从I2C设备中读取数据           |
| IoTI2cSetBaudrate(unsigned int id, unsigned int baudrate);   | 设置I2C设备的波特率           |

## 二、ssd1306 API

本样例提供了一个HarmonyOS IoT硬件接口的SSD1306 OLED屏驱动库，其功能如下：

* 内置了128*64 bit的内存缓冲区，支持全屏刷新;
* 优化了屏幕刷新速率，实测最大帧率10fps;
* `libm_port`是从musl libc中抽取的`sin`和`cos`的实现；
  * 用于规避链接Hi3861 SDK中的libm_flash.a报错的问题;
* `gif2imgs.py` 可用于将gif动图中的帧分离出来;
  * 依赖 pillow 包，可以使用 `pip install pillow` 命令安装；
* `img2code.py` 可用于将图片转为C数组，每个字节表示8个像素；
  * 依赖 opecv-python 包，可以使用 `pip install opencv-python` 命令安装；

* 使用Harmony OS的IoT硬件接口;
* 接口简洁易于使用、易于移植;
* 内置了测试程序，可直接进行测试;

| API名称                                                      | 说明                       |
| ------------------------------------------------------------ | -------------------------- |
| void ssd1306_Init(void)                                      | 初始化                     |
| void ssd1306_Fill(SSD1306_COLOR color)                       | 以指定的颜色填充屏幕       |
| void ssd1306_SetCursor(uint8_t x, uint8_t y)                 | 定位光标                   |
| void ssd1306_UpdateScreen(void)                              | 更新屏幕内容               |
| char ssd1306_DrawChar(char ch, FontDef Font, SSD1306_COLOR color) | 在屏幕缓冲区绘制1个字符    |
| char ssd1306_DrawString(char* str, FontDef Font, SSD1306_COLOR color) | 将完整字符串写入屏幕缓冲区 |
| void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color) | 在屏幕缓冲区中绘制一个像素 |
| void ssd1306_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color) | 用Bresenhem算法画直线      |
| void ssd1306_DrawPolyline(const SSD1306_VERTEX *par_vertex, uint16_t par_size, SSD1306_COLOR color) | 绘制多段线                 |
| void ssd1306_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR color) | 绘制矩形                   |
| void ssd1306_DrawArc(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR color) | 绘图角度                   |
| void ssd1306_DrawCircle(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR color) | 用Bresenhem算法画圆        |
| void ssd1306_DrawBitmap(const uint8_t* bitmap, uint32_t size) | 绘图位图                   |
| void ssd1306_DrawRegion(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* data, uint32_t size, uint32_t stride) | 绘制区域                   |

## 三、如何编译

1. 将此目录复制到openharmony源码的根目录下

2. 修改openharmony源码的`build/lite/product/wifiiot.json`文件：

   将`//applications/sample/wifi-iot/app`替换为`//12_ssd1306:app`保存；

3. 在openharmony源码目录下执行：`hb build -f`


## 四、编译错误解决

本项目代码使用了鸿蒙IoT硬件子系统的I2C API接口，需要连接到hi3861的I2C相关接口；默认情况下，Hi3861的I2C编译配置没有打开，编译时会有如下错误：

```txt
riscv32-unknown-elf-ld: ohos/libs/libhal_iothardware.a(hal_wifiiot_i2c.o): in function `.L0 ':
hal_wifiiot_i2c.c:(.text.HalI2cWrite+0x12): undefined reference to `hi_i2c_write'
riscv32-unknown-elf-ld: hal_wifiiot_i2c.c:(.text.HalI2cInit+0x12): undefined reference to `hi_i2c_init'
scons: *** [output/bin/Hi3861_wifiiot_app.out] Error 1
BUILD FAILED!!!!
```

**解决方法**

需要修改device\hisilicon\hispark_pegasus\sdk_liteos\build\config\usr_config.mk文件：
`# CONFIG_I2C_SUPPORT is not set`行，修改为：`CONFIG_I2C_SUPPORT=y`

## 五、效果演示

1. 播放gif：https://www.bilibili.com/video/BV1Af4y1B7TD/
    * 使用本项目中的转换脚本将gif每一帧画面提取出来，转成bitmap数组，程序里循环播放
2. 播放视频：https://www.bilibili.com/video/BV1DK4y1f7yw/
    * C/S架构，开发板作为客户端，PC作为服务端，使用TCP传输每帧画面（因为视频帧数较多，开发板闪存放不下）
    * 播放项目源码： https://gitee.com/hihopeorg/harmonyos_oled_player

## 六、参考链接

本项目是基于afiskon的stm32-ssd1306移植的，对部分细节做了修改和优化，原项目链接：

* https://github.com/afiskon/stm32-ssd1306



### 【套件支持】

##### 1. 套件介绍  http://www.hihope.org/pro/pro1.aspx?mtt=8

##### 2. 套件购买  https://item.taobao.com/item.htm?id=622343426064&scene=taobao_shop

##### 3. 技术资料

- Gitee码云网站（OpenHarmony Sample Code等) **https://gitee.com/hihopeorg**

- HiHope官网-资源中心（SDK包、技术文档下载）[**www.hihope.org**](http://www.hihope.org/)

##### 4. 互动交流

- 润和HiHope鸿蒙技术交流-微信群（加群管理员微信13605188699，发送文字#申请加入润和官方鸿蒙群#，予以邀请入群）
- HiHope开发者社区-论坛 **https://bbs.elecfans.com/group_1429**
- 润和HiHope鸿蒙售后服务群（QQ：980599547）
- 售后服务电话（025-52668590）