//该文件中连接wifi
//连接完成后调用get_online_time()


//参考案例程序\applications\sample\wifi-iot\app\wifi_demo\wifi_connect_demo.c


#include <stdio.h>          // 标准输入输出
#include <unistd.h>         // POSIX标准接口
#include <string.h>         // 字符串处理(操作字符数组)

#include "ohos_init.h"      // 用于初始化服务(services)和功能(features)
#include "cmsis_os2.h"      // CMSIS-RTOS API V2

#include "wifi_device.h"    // Wi-Fi设备接口：station模式

// lwIP：A Lightweight TCPIP stack
// 瑞典计算机科学院(SICS)的Adam Dunkels开发的一个小型(轻量)开源的TCP/IP协议栈
// 实现的重点是在保持TCP协议主要功能的基础上减少对RAM的占用
// 仅占用几十KB RAM空间，40KB ROM空间，非常适合在嵌入式系统中使用
// 
// lwIP TCP/IP协议栈：网络接口API
// netifapi：Network Interfaces API
#include "lwip/netifapi.h"
// 
// lwIP TCP/IP协议栈：SHELL命令API
#include "lwip/api_shell.h" 

// 全局变量，用于标识连接是否成功
static int g_connected = 0;

// 输出连接信息
static void PrintLinkedInfo(WifiLinkedInfo *info)
{
    // 检查参数的合法性
    if (!info)
        return;

    // 存储MAC地址字符串
    static char macAddress[32] = {0};

    // 获取MAC地址
    unsigned char *mac = info->bssid;

    // mac地址转换为字符串
    snprintf(macAddress, sizeof(macAddress), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    // 输出日志
    printf("bssid: %s, rssi: %d, connState: %d, reason: %d, ssid: %s\r\n",
           macAddress,                  // MAC地址
           info->rssi,                  // 信号强度
           info->connState,             // 连接状态
           info->disconnectedReason,    // 断开原因
           info->ssid);                 // SSID
}

// 连接状态变化回调函数
// 该回调函数有两个参数state和info
//      state表示连接状态，WIFI_STATE_AVALIABLE表示连接成功，WIFI_STATE_NOT_AVALIABLE表示连接失败
//      info类型为WifiLinkedInfo*，有多个成员，包括ssid，bssid，rssi，connState，disconnectedReason等
static void OnWifiConnectionChanged(int state, WifiLinkedInfo *info)
{
    // 检查参数的合法性
    if (!info)
        return;

    // 输出日志
    printf("%s %d, state = %d, info = \r\n", __FUNCTION__, __LINE__, state);

    // 输出连接信息
    PrintLinkedInfo(info);

    // 更新全局状态变量，在另外一个线程中轮询状态变量，这种方式实现起来比较简单
    if (state == WIFI_STATE_AVALIABLE)  // 连接成功
    {
        g_connected = 1;
    }
    else                                // 连接失败
    {
        g_connected = 0;
    }
}

// 扫描状态变化回调函数
// 该回调函数有两个参数state和size
//      state表示扫描状态，WIFI_STATE_AVALIABLE表示扫描动作完成，WIFI_STATE_NOT_AVALIABLE表示扫描动作未完成
//      size表示扫描到的热点个数
static void OnWifiScanStateChanged(int state, int size)
{
    // 简单输出日志信息，表明函数被执行了
    printf("%s %d, state = %X, size = %d\r\n", __FUNCTION__, __LINE__, state, size);
}

// 主线程函数
static void WifiConnectTask(void *arg)
{
    (void)arg;

    // WifiErrorCode类型的变量，用于接收接口返回值
    WifiErrorCode errCode;

    // 创建WiFi事件监听器
    // 参见 foundation\communication\wifi_lite\interfaces\wifiservice\wifi_event.h
    // 开启WiFi设备的STA模式之前，需要使用RegisterWifiEvent接口，向系统注册状态监听函数，用于接收状态通知
    // STA模式需要绑定如下两个回调函数：
    //  OnWifiScanStateChanged用于绑定扫描状态监听函数
    //  OnWifiConnectionChanged用于绑定连接状态监听函数
    WifiEvent eventListener = {
        // 在连接状态发生变化时，调用OnWifiConnectionChanged回调函数
        .OnWifiConnectionChanged = OnWifiConnectionChanged,
        // 在扫描状态发生变化时，调用OnWifiScanStateChanged回调函数
        .OnWifiScanStateChanged = OnWifiScanStateChanged};
    
    // 定义热点配置
    WifiDeviceConfig apConfig = {};

    // 用于保存netId
    int netId = -1;

    // 等待100ms
    osDelay(10);

    // 使用RegisterWifiEvent接口，向系统注册状态监听函数，STA模式需要绑定两个回调函数
    errCode = RegisterWifiEvent(&eventListener);

    // 打印接口调用结果
    printf("RegisterWifiEvent: %d\r\n", errCode);

    // 设置热点配置中的SSID
    strcpy(apConfig.ssid, "HarmonyOS 13");

    // 设置热点配置中的密码
    strcpy(apConfig.preSharedKey, "2256907339");

    // 设置热点配置中的加密方式(Wi-Fi security types)
    apConfig.securityType = WIFI_SEC_TYPE_PSK;

    // 工作循环
    while (1)
    {
        // 开启WiFi设备的STA模式。使其可以扫描，并且连接到AP。
        // 进行WiFi的STA模式开发前，必须先调用EnableWifi函数。
        errCode = EnableWifi();
        printf("EnableWifi: %d\r\n", errCode);
        osDelay(10);

        // 通过AddDeviceConfig接口，向系统添加热点配置，它有两个参数：
        //   第一个参数config，类型为const WifiDeviceConfig*，用于指定热点配置；
        //   第二个参数result，类型为int*，用于操作成功时返回netId；
        errCode = AddDeviceConfig(&apConfig, &netId);

        // 打印接口调用结果
        printf("AddDeviceConfig: %d\r\n", errCode);

        // 连接热点使用ConnectTo接口，他有一个参数：
        //   netId，类型为int，应该使用AddDeviceConfig接口调用成功之后result参数得到值填充；
        // ConnectTo是同步的，连接成功失败会通过返回值体现；
        // 同时，系统也会通过回调函数通知应用代码；
        g_connected = 0;
        errCode = ConnectTo(netId);

        // 打印接口调用结果
        printf("ConnectTo(%d): %d\r\n", netId, errCode);

        // 等待连接成功
        while (!g_connected)
        {
            osDelay(10);
        }

        // 输出日志
        printf("g_connected: %d\r\n", g_connected);
        osDelay(50);

        // 连接成功后，需要调用DHCP客户端接口，从热点获取IP地址
        // 使用 netifapi_netif_find("wlan0") 获取STA模式的网络接口
        struct netif *iface = netifapi_netif_find("wlan0");

        // 获取网络接口成功
        if (iface)
        {
            // 使用 netifapi_dhcp_start 接口，启动DHCP客户端
            err_t ret = netifapi_dhcp_start(iface);

            // 打印接口调用结果
            printf("netifapi_dhcp_start: %d\r\n", ret);

            // 等待DHCP服务端分配IP地址
            osDelay(200);
        }

        // 获取在线时间
        get_online_time();
        osDelay(500);

        // 断开热点使用Disconnect接口，无需参数，断开之前需要停止DHCP客户端
        // 使用 netifapi_dhcp_stop 接口，停止DHCP客户端
        err_t ret = netifapi_dhcp_stop(iface);

        // 打印接口调用结果
        printf("netifapi_dhcp_stop: %d\r\n", ret);

        // 输出日志
        printf("disconnect!\r\n");

        // 断开热点连接
        Disconnect();

        // 删除热点配置使用RemoveDevice，参数和ConnectTo类似
        RemoveDevice(netId);

        // 关闭WiFi设备的STA模式
        errCode = DisableWifi();

        // 打印接口调用结果
        printf("DisableWifi: %d\r\n", errCode);

        // 一分钟后重新连接获取时间
        osDelay(6000);
    }   // 工作循环结束
}

// 入口函数
static void WifiConnectDemo(void)
{
    // 定义线程属性
    osThreadAttr_t attr;
    attr.name = "WifiConnectTask";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    attr.stack_size = 10240;
    attr.priority = osPriorityNormal;

    // 创建线程
    if (osThreadNew(WifiConnectTask, NULL, &attr) == NULL)
    {
        printf("[WifiConnectDemo] Falied to create WifiConnectTask!\n");
    }
}

// 运行入口函数
APP_FEATURE_INIT(WifiConnectDemo);
