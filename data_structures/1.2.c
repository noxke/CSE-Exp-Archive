#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 5        // 栈的最大高度

typedef struct node
{
    int coef;           // 底数
    int exp;            // 系数
    int layer;          // 节点所处层数
    struct node *next;  // 当前节点下一层节点
}node, *pstack;

void create_node(node *new_node, int coef, int exp);    // 初始化一个节点
pstack push(pstack top, node *new_node);                // 将新节点new_node压入栈中，返回新的栈顶
node *pop(pstack top);                                  // 弹出最上层元素，并将弹出的元素返回
int full(pstack top);                                   // 判断栈是否为满，栈满返回1
int empty(pstack top);                                  // 判断栈是否为空，栈空返回1

int main()
{
    int c, c1, c2, e, e1, e2;
    pstack stack1 = malloc(sizeof(node));   // 栈1的栈顶，栈顶始终为空元素，栈顶的下一层元素为最后压入的元素
    pstack stack2 = malloc(sizeof(node));   // 栈2的栈顶
    create_node(stack1, 0, 0);
    create_node(stack2, 0, 0);
    while (scanf("%d %d", &c, &e))          // 读取第一组数据
    {
        if (full(stack1))                   // 栈满停止读取
        {
            printf("Full!");
            return 0;
        }
        node *new_node = malloc(sizeof(node));
        create_node(new_node, c, e);
        stack1 = push(stack1, new_node);    // 压入新的节点
    }
    getchar();  // 过滤掉数据中的";"
    while (scanf("%d %d", &c, &e))          // 读取第二组数据
    {
        if (full(stack2))
        {
            printf("Full!");
            return 0;
        }
        node *new_node = malloc(sizeof(node));
        create_node(new_node, c, e);
        stack2 = push(stack2, new_node);
        char tmp = getchar();
        if ((tmp == '\n') || (tmp == EOF))   // 数据末尾遇到换行符返回
        {
            break;
        }
    }
    while ((!empty(stack1)) && (!empty(stack2)))    // 栈1与栈2均不为空
    {
        node *pnode1 = pop(stack1); // 从栈中取出最上层元素
        node *pnode2 = pop(stack2);
        c1 = pnode1->coef;
        c2 = pnode2->coef;
        e1 = pnode1->exp;
        e2 = pnode2->exp;
        if (e1 > e2){   // 比较系数大小降幂输出
            printf("%d %d ", c1, e1);
            free(pnode1);   // 释放输出节点的内存
            stack2 = push(stack2, pnode2);  // 将未输出的节点重新压入栈中
        } else if (e2 > e1)
        {
            printf("%d %d ", c2, e2);
            free(pnode2);
            stack1 = push(stack1, pnode1);
        } else
        {
            printf("%d %d ", c1+c2, e1);
            free(pnode1);
            free(pnode2);
        }
    }
    while (!empty(stack1))  // 依次输出栈中剩余元素
    {
        node *pnode1 = pop(stack1);
        c1 = pnode1->coef;
        e1 = pnode1->exp;
        printf("%d %d ", c1, e1);
        free(pnode1);
    }
    while (!empty(stack2))
    {
        node *pnode2 = pop(stack2);
        c2 = pnode2->coef;
        e2 = pnode2->exp;
        printf("%d %d ", c2, e2);
        free(pnode2);
    }
    free(stack1);   // 释放栈顶内存
    free(stack2);
    return 0;
}

void create_node(node *new_node, int coef, int exp)
{
    new_node->coef = coef;
    new_node->exp = exp;
    new_node->layer = 0;
    new_node->next = NULL;
}

pstack push(pstack top, node *new_node)
{
    if (full(top))  // 栈满不再压入元素
    {
        return top;
    }
    new_node->layer = top->layer;   // 将new_node压入并更新栈顶
    new_node->next = top->next;
    top->next = new_node;
    top->layer++;
    return top;
}

node *pop(pstack top)
{
    if (empty(top)) // 栈为空无法弹出元素
    {
        return NULL;
    }
    node *tmp = top->next;  // 返回最上层元素并更新栈顶
    top->next = top->next->next;
    top->layer--;
    return tmp;
}

int full(pstack top)
{
    if (top->layer == MAXLEN)   // 根据栈顶layer判断栈是否为满
    {
        return 1;
    }
    return 0;
}

int empty(pstack top)
{
    if (top->layer == 0)    // 根据栈顶layer判断栈是否为空
    {
        return 1;
    }
    return 0;
}