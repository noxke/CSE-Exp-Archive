#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int k;             // 编号
    struct node *next; // 下一个节点
} * pNode, node;

pNode initLinkList(int n); // 初始化循环链表

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    if (n <= 1) // 只有一个人错误退出
    {
        return -1;
    }
    pNode cursor = initLinkList(n);
    pNode last = cursor->next; // 找到第一个人的前一个人，即最后一个人
    while (last->next != cursor)
    {
        last = last->next;
    }
    int i = 0;             // 报数器
    int first = 1;         // 第一个出圈？
    while (cursor != last) // 超过一个人
    {
        i++;
        if (i == m) // 报到m，出圈
        {
            if (first == 1)
            {
                first = 0;
                printf("%d", cursor->k);
            }
            else
            {
                printf(" %d", cursor->k);
            }
            i = 0;                 // 重置报数器
            cursor = cursor->next; // 从链表中删除以及出圈的节点，重新连接链表
            free(last->next);
            last->next = cursor;
        }
        else // 没有出圈，向后移动
        {
            cursor = cursor->next;
            last = last->next;
        }
    }
    printf("\n%d", cursor->k); // 最后留下的人
    free(cursor);
    return 0;
}

pNode initLinkList(int n)
{
    pNode head = malloc(sizeof(node)); // 创建链表指针
    head->k = 1;                       // 为第一个节点赋值
    head->next = NULL;
    pNode tail = head; //用于连接链表节点
    for (int i = 2; i <= n; i++)
    {
        tail->next = malloc(sizeof(node)); // 新的节点
        tail = tail->next;
        tail->k = i;
        tail->next = NULL;
    }
    tail->next = head; // 将链表尾节点与头节点连接形成循环链表
    return head;
}