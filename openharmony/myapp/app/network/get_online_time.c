#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "shared_variable.h"


time_t shared_variable_time_offset = 0;
static const char *g_request = "GET /api/ip.txt HTTP/1.1\r\n\Content-Type: application/x-www-form-urlencoded;charset=UTF-8\r\n\Host: worldtimeapi.org\r\n\r\n";
const char addr_ip[] = "213.188.196.246";

// 从网络获取时间，计算时间偏移写入共享变量
unsigned int get_online_time()
{
    struct sockaddr_in addr = {0};
    int s, r;
    char recv_buf[2048];
    addr.sin_family = AF_INET;
    addr.sin_port = PP_HTONS(80);
    addr.sin_addr.s_addr = inet_addr(addr_ip);
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        return 1;
    }
    printf("[Get Time] allocated socket\n");
    if (connect(s, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        printf("[Get Time] socket connect failed\n");
        lwip_close(s);
        return 1;
    }
    printf("[Get Time] connected\n");
    if (lwip_write(s, g_request, strlen(g_request)) < 0) {
        lwip_close(s);
        return 1;
    }
    printf("[Get Time] socket send success\n");
    struct timeval receiving_timeout;
    // 设置 5s Timeout
    receiving_timeout.tv_sec = 5;
    receiving_timeout.tv_usec = 0;
    if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &receiving_timeout, sizeof(receiving_timeout)) < 0) {
        printf("[Get Time] failed to set socket receiving timeout\n");
        lwip_close(s);
        return 1;
    }
    printf("[Get Time] set socket receiving timeout success\n");
    // 接收 http 响应
    do {
        (void)memset_s(recv_buf, sizeof(recv_buf), 0, sizeof(recv_buf));
        r = lwip_read(s, recv_buf, sizeof(recv_buf) - 1);
        printf("[Get Time] socket recv success, r = %d\n", r);
        
        // 从响应解析时间
        time_t unixtime;
        char *p = strstr(recv_buf, "unixtime: ");
        if (p)
        {
            sscanf(p, "unixtime: %d", &unixtime);
            printf("[Get Time] time: %d\n", unixtime);
            time_t current_time;
            time(&current_time);
            shared_variable_time_offset = unixtime - current_time;
            printf("[Get Time] time offset: %d\n", shared_variable_time_offset);
            break;
        }
        else
        {
            printf("[Get Time] time not found\n");
        }
    } while (r > 0);
    
    lwip_close(s);
    return 0;
}
