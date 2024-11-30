#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 8

typedef struct Node
{
    int val;
    struct Node *next;
} *SQNode;

typedef struct Queue
{
    SQNode SQ_0;  // 下标为0的节点
    SQNode head;
    SQNode rear;
    int i;        // 头节点下标
    int length;   // 队列长度
} SQueue;

int InitSQueue(int i, SQueue *SQ);  // 初始化队列,头节点下标为
int DestroySQueue(SQueue *SQ);      // 删除队列释放内存
int EnQueue(int e, SQueue *SQ);     // 插入元素v到队尾
int DeQueue(int *v, SQueue *SQ);    // 返回并删除队列SQ的头元素
int QueueLength(int *l, SQueue *SQ);// 返回队列SQ的长度
int Full(SQueue *SQ);               // 判断队列是否为满
int Empty(SQueue *SQ);              // 判断队列是否为空 

int main()
{   
    int n, i, k, e, v;
    scanf("%d %d %d", &n, &i, &k);
    SQueue *SQ;
    InitSQueue(i, SQ);
    int j;
    for (j = 0; j < n; j++) // 读入元素
    {
        scanf("%d", &e);
        if (! Full(SQ))
        {
            EnQueue(e, SQ);
        }
    }
    if (k > MAXSIZE)    // 读取元素个数大于队列空间, error
    {
        printf("Error");
    } else if (k > n)  // 读取元素个数大于输入的元素个数, fault
    {
        printf("Fault");
    } else
    {
        if (Full(SQ))   // 队满,full
        {
            printf("Full");
        }
        for (j = 0; j < k; j++) // 读取元素
        {
            if (!Empty(SQ))
            {
                DeQueue(&v, SQ);
                printf(" %d", v);
            }
        }
    }
    DestroySQueue(SQ);
    return 0;
}

int InitSQueue(int i, SQueue *SQ)
{
    int j;
    SQNode node = malloc(sizeof(SQNode));
    SQ->SQ_0 = node;
    if (i == 0)
    {
        SQ->head = node;
        SQ->rear = node;
    }
    SQNode tmp = SQ->SQ_0;
    for (j = 1; j < MAXSIZE; j++)
    {
        SQNode node = malloc(sizeof(SQNode));
        if (i == j)
        {
            SQ->head = node;
            SQ->rear = node;
        }
        tmp->next = node;
        tmp = tmp->next;
    }
    tmp->next = SQ->SQ_0;
    SQ->i = i;
    SQ->length = 0;
    return 1;
}

int DestroySQueue(SQueue *SQ)
{
    SQNode tmp1 = SQ->SQ_0;
    SQNode tmp2 = tmp1;
    int j;
    for (j = 0; j < MAXSIZE; j++)
    {
        tmp2 = tmp1->next;
        free(tmp1);
        tmp1 = tmp2;
    }
    return 1;
}

int EnQueue(int e, SQueue *SQ)
{
    if (Full(SQ))
    {
        return 0;
    }
    SQ->rear->val = e;
    SQ->rear = SQ->rear->next;
    SQ->length++;
    return 1;
}

int DeQueue(int *v, SQueue *SQ)
{
    if (Empty(SQ))
    {
        return 0;
    }
    *v = SQ->head->val;
    SQ->head = SQ->head->next;
    SQ->length--;
    return 1;
}

int QueueLength(int *l, SQueue *SQ)
{
    *l = SQ->length;
    return 1;
}

int Full(SQueue *SQ)
{
    if (SQ->length == MAXSIZE)
    {
        return 1;
    }
    return 0;
}

int Empty(SQueue *SQ)
{
    if (SQ->length == 0)
    {
        return 1;
    }
    return 0;
}