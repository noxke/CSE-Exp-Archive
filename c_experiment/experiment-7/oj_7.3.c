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
stuNode sort(stuNode head);       // 排序
stuNode quit(stuNode head);       // 退出

stuNode bubble_sort(stuNode head, int rev); // 冒泡排序
stuNode select_sort(stuNode head, int rev); // 选择排序
stuNode reverse(stuNode head);                      // 逆序链表，返回新的链表
int node_lt(stuNode aNode, stuNode bNode);          // 判断a节点是否小于b节点
int node_gt(stuNode aNode, stuNode bNode); // 判断a节点是否大于b节点

int main()
{
    stuNode (*funcs[])(stuNode head) = {quit, input, output, modify, average, output_sum, sort}; // 函数指针数组
    stuNode head = NULL;                                                                         // 链表头指针
    int op;
    while (scanf("%d", &op) != EOF)
    {
        if (op < 0 || op > 6)
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
        printf("%d ", sum); // 四科总分
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

stuNode sort(stuNode head) // 排序
{
    int mode, rev;
    scanf("%d %d", &rev, &mode);                                        // 输入排序方法和升降序
    head = mode == 0 ? select_sort(head, rev) : bubble_sort(head, rev); // 排序
    average(head);  // 按照平均分输出
    return head;
}

stuNode bubble_sort(stuNode head, int rev) // 冒泡排序
{
    stuNode curNode, lastNode, tmpNode;
    tmpNode = head; // 用来记录循环
    while (tmpNode != NULL) // 循环链表长度次
    {
        curNode = head; // 交换冒泡
        lastNode = NULL;    // 记录前一个节点，用于链表的连接
        if (curNode == NULL || curNode->next == NULL)   // 空链表或只有一个元素不进行排序
        {
            continue;
        }
        while (curNode->next != NULL)
        {
            if (node_gt(curNode, curNode->next) == 1)   // 当前节点比下一个节点大，交换
            {
                if (lastNode == NULL)   // curNode为第一个节点，即头节点
                {
                    head = curNode->next;
                    curNode->next = head->next;
                    head->next = curNode;
                    lastNode = head;    // 更新lastNode
                }
                else
                {
                    lastNode->next = curNode->next;
                    curNode->next = lastNode->next->next;
                    lastNode->next->next = curNode;
                    lastNode = lastNode->next;  // 更新lastNode
                }
            }
            else    // 下一个节点比curNode大
            {
                lastNode = curNode; // 更新lastNode
                curNode = curNode->next;
            }
        }
        tmpNode = tmpNode->next;
    }
    if (rev == 1)   // 降序排列
    {
        head = reverse(head);
    }
    return head;    // 返回排序后的新链表
}

stuNode select_sort(stuNode head, int rev) // 选择排序
{
    stuNode new_head = NULL, new_tail, tmpNode, minNode;
    while (head != NULL)
    {
        minNode = head;
        tmpNode = head;
        while (tmpNode != NULL) // 寻找最小节点
        {
            if (node_lt(tmpNode, minNode) == 1)
            {
                minNode = tmpNode;
            }
            tmpNode = tmpNode->next;
        }
        if (new_head == NULL)   // 将最小的节点添加到新链表中，升序排列
        {
            new_head = minNode;
            new_tail = new_head;
        }
        else
        {
            new_tail->next = minNode;
            new_tail = new_tail->next;
        }
        tmpNode = head; // 从原链表中删除取出的最小节点
        if (tmpNode == minNode) // 与第一个节点相等
        {
            head = head->next;  // 删除头节点
        }
        else
        {
            while (tmpNode->next != NULL)   // 找到最小节点并从链表中删除
            {
                if (tmpNode->next == minNode)
                {
                    tmpNode->next = tmpNode->next->next;
                    break;
                }
                tmpNode = tmpNode->next;
            }
        }
    }
    if (rev == 1)   // 降序排列
    {
        new_head = reverse(new_head);
    }
    return new_head;    // 返回排序后的新链表
}

stuNode reverse(stuNode head) // 逆序链表，返回新的链表
{
    stuNode new_head = NULL, tmp;
    while (head != NULL)
    {
        tmp = head;           // 依次取出头节点
        head = head->next;    // 头节点指向下一个节点
        tmp->next = new_head; // 将取出的头节点插入到新的链表头部
        new_head = tmp;
    }
    return new_head; // 返回新的头节点
}

int node_lt(stuNode aNode, stuNode bNode) // 判断a节点是否小于b节点
{
    if (aNode == NULL || bNode == NULL)
    {
        return -1;
    }
    if (aNode->english + aNode->math + aNode->physics + aNode->c_program <
        bNode->english + bNode->math + bNode->physics + bNode->c_program)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int node_gt(stuNode aNode, stuNode bNode) // 判断a节点是否大于b节点
{
    if (aNode == NULL || bNode == NULL)
    {
        return -1;
    }
    if (aNode->english + aNode->math + aNode->physics + aNode->c_program >
        bNode->english + bNode->math + bNode->physics + bNode->c_program)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}