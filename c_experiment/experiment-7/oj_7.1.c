#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct stuNode
{
    char id[20];   // 学号
    char name[20]; // 姓名
    int english;   //英语成绩
    int math;      // 数学成绩
    int physics;   // 物理成绩
    int c_program; // c成绩
    struct stuNode *next;
} * stuNode, node;

stuNode input(stuNode head);      // 输入成绩
stuNode output(stuNode head);     // 输出成绩
stuNode modify(stuNode head);     // 修改记录
stuNode average(stuNode head);    // 计算每个人均分
stuNode output_sum(stuNode head); // 输出总成绩
stuNode quit(stuNode head);       // 退出

int main()
{
    stuNode (*funcs[])(stuNode head) = {quit, input, output, modify, average, output_sum}; // 函数指针数组
    stuNode head = NULL;                                                                   // 链表头指针
    int op;
    while (scanf("%d", &op) != EOF)
    {
        if (op < 0 || op > 5)
        {
            return -1;
        }
        head = funcs[op](head); // 执行对应操作
        if (op == 0)
        {
            break;
        }
    }
    return 0;
}

stuNode input(stuNode head) // 输入成绩
{
    int n, i = 0;
    stuNode new_head, tail;
    scanf("%d", &n); // 记录数量
    if (n != 0)      // 第一个学生信息，头节点
    {
        new_head = malloc(sizeof(node));
        scanf("%s", new_head->id);
        scanf("%s", new_head->name);
        scanf("%d", &(new_head->english));
        scanf("%d", &(new_head->math));
        scanf("%d", &(new_head->physics));
        scanf("%d", &(new_head->c_program));
        new_head->next = NULL;
        tail = new_head;
    }
    while (i++ < n - 1) // 添加尾节点
    {
        tail->next = malloc(sizeof(node));
        tail = tail->next;
        scanf("%s", tail->id);
        scanf("%s", tail->name);
        scanf("%d", &(tail->english));
        scanf("%d", &(tail->math));
        scanf("%d", &(tail->physics));
        scanf("%d", &(tail->c_program));
        tail->next = NULL;
    }
    if (head == NULL) // 原链表为空链表，直接返回新链表
    {
        head = new_head;
    }
    else // 将新链表连接到原链表尾部
    {
        tail = head;
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = new_head;
    }
    printf("完成了%d位同学的成绩输入\n", n);
    return head; // 返回链表头节点
}

stuNode output(stuNode head) // 输出成绩
{
    stuNode tail = head;
    while (tail != NULL)
    {
        printf("%s ", tail->id);
        printf("%s ", tail->name);
        printf("%d ", tail->english);
        printf("%d ", tail->math);
        printf("%d ", tail->physics);
        printf("%d\n", tail->c_program);
        tail = tail->next; // 指向下一个节点
    }
    return head;
}

stuNode modify(stuNode head) // 修改记录
{
    stuNode curNode = head;
    if (curNode == NULL)
    {
        return NULL;
    }
    char id[20];
    int k;
    scanf("%s %d", id, &k); // 学号和要修改的字段
    while (curNode != NULL)
    {
        if (strcmp(curNode->id, id) == 0) // 寻找学号相等的节点
        {
            switch (k)
            {
            case 0:
                scanf("%s", curNode->name);
                break;
            case 1:
                scanf("%d", &(curNode->english));
                break;
            case 2:
                scanf("%d", &(curNode->math));
                break;
            case 3:
                scanf("%d", &(curNode->physics));
                break;
            case 4:
                scanf("%d", &(curNode->c_program));
                break;
            }
            printf("%s ", curNode->id); // 输出修改后的节点
            printf("%s ", curNode->name);
            printf("%d ", curNode->english);
            printf("%d ", curNode->math);
            printf("%d ", curNode->physics);
            printf("%d\n", curNode->c_program);
            break;
        }
        curNode = curNode->next;
    }
    return head;
}

stuNode average(stuNode head) // 计算每个人均分
{
    stuNode curNode = head;
    while (curNode != NULL)
    {
        printf("%s ", curNode->id);   // 输出id
        printf("%s ", curNode->name); // 输出姓名
        float avrg = ((float)curNode->english + (float)curNode->math + (float)curNode->physics + (float)curNode->c_program) / 4.0;
        printf("%.2f\n", avrg);  // 四科均分
        curNode = curNode->next; // 指向下一个学生
    }
    return head;
}

stuNode output_sum(stuNode head) // 输出总成绩
{
    stuNode curNode = head;
    while (curNode != NULL)
    {
        printf("%s ", curNode->id);   // 输出id
        printf("%s ", curNode->name); // 输出姓名
        int sum = curNode->english + curNode->math + curNode->physics + curNode->c_program;
        printf("%d ", sum);  // 四科总分
        float avrg = (float)sum / 4.0;
        printf("%.2f\n", avrg);  // 四科均分
        curNode = curNode->next; // 指向下一个学生
    }
    return head;
}

stuNode quit(stuNode head) // 退出
{
    if (head == NULL)
    {
        return NULL;
    }
    quit(head->next); // 使用递归从链表末尾释放节点内存
    free(head);
    return NULL;
}