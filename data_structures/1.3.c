#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 20        // 栈的最大高度

typedef struct node
{
    float coef;           // 底数
    int exp;            // 系数
    int layer;          // 节点所处层数
    struct node *next;  // 当前节点下一层节点
}node, *pstack;

void create_node(node *new_node, float coef, int exp);    // 初始化一个节点
pstack push(pstack top, node *new_node);                // 将新节点new_node压入栈中，返回新的栈顶，
pstack sort_push(pstack top, node *new_node);           // 插入时进行排序，返回新的栈顶
node *pop(pstack top);                                  // 弹出最上层元素，并将弹出的元素返回
int full(pstack top);                                   // 判断栈是否为满，栈满返回1
int empty(pstack top);                                  // 判断栈是否为空，栈空返回1

float read(char *input, int *i);    // 替代scanf函数

int main()
{
    char input[1000] = {'\0'};
    gets(input);
    int i = 0;
    float sign_flag = 1;    // 记录加减运算

    float c;
    int e;
    pstack stack1 = malloc(sizeof(node));   // 栈1的栈顶，栈顶始终为空元素，栈顶的下一层元素为最后压入的元素
    create_node(stack1, 0, 0);
    while (1)          // 读取第一组数据
    {
        if (full(stack1))                   // 栈满停止读取
        {
            printf("Full!");
            return 0;
        }
        while (input[i] == ' ') i++;    // 使用read函数从字符串input中读取数据
        if (input[i] == '+' && input[i+1] == ' ')   // 判断两个多项式之间的计算为加或减
        {
            sign_flag = 1;
            i++;
            break;
        } else if (input[i] == '-' && input[i+1] == ' ')
        {
            sign_flag = -1;
            i++;
            break;
        }
        c = read(input, &i);
        e = (int) read(input, &i);
        node *new_node = malloc(sizeof(node));
        create_node(new_node, c, e);
        stack1 = sort_push(stack1, new_node);    // 压入新的节点
    }
    while (1)          // 读取第二组数据
    {
        if (full(stack1))                   // 栈满停止读取
        {
            printf("Full!");
            return 0;
        }
        while (input[i] == ' ') i++;
        c = read(input, &i);
        e = (int) read(input, &i);
        c = sign_flag * c;
        node *new_node = malloc(sizeof(node));
        create_node(new_node, c, e);
        stack1 = sort_push(stack1, new_node);    // 压入新的节点
        if (input[i] == '\0')   // 读取数据到末尾，退出循环
        {
            break;
        }
    }
    int is_output = 0;
    while (!empty(stack1))  // 依次输出栈中剩余元素
    {
        node *pnode = pop(stack1);
        c = pnode->coef;
        e = pnode->exp;
        if (c != 0) // 不输出系数为0的项
        {
            is_output = 1;
            printf("%g %d ", c, e);
        }
        free(pnode);
    }
    if (is_output == 0) // 如果所有系数为0，输出0 0
    {
        printf("0 0");
    }
    free(stack1);   // 释放栈顶内存
    return 0;
}

void create_node(node *new_node, float coef, int exp)
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

pstack sort_push(pstack top, node *new_node) // 插入时进行排序
{
    if (full(top))  // 栈满不再压入元素
    {
        return top;
    }
    pstack tmp_stack = malloc(sizeof(node));    // 临时栈用于插入排序
    create_node(tmp_stack, 0, 0);
    while (1)
    {
        if (empty(top)) // 为空直接压入
        {
            top = push(top, new_node);
            break;
        }
        node *tmp_node = pop(top);
        if (new_node->exp > tmp_node->exp) // 新插入的节点exp大于原最上层节点exp，压入到栈顶
        {
            top = push(top, tmp_node);  // 先压入临时取出的节点
            top = push(top, new_node);  // 再压入新的节点
            break;
        } else if (new_node->exp == tmp_node->exp)  // 新插入节点的exp与原最上层节点相同，合并节点
        {
            new_node->coef = new_node->coef + tmp_node->coef;
            top = push(top, new_node);
            free(tmp_node); // 释放多余节点内存
            break;
        } else  // 新插入节点的exp较小
        {
            tmp_stack = push(tmp_stack, tmp_node);  // 将临时节点压入临时栈中
        }
    }
    while (!empty(tmp_stack))   // 将放入临时栈中的节点压入到原栈中
    {
        node *tmp_node = pop(tmp_stack);
        top = push(top, tmp_node);
    }
    free(tmp_stack);    // 释放临时栈的内存
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


float read(char *input, int *i)  // 替代scanf函数
{
    float ret = 0;
    float sign_flag = 1;
    int w = 0;  // 记录小数点前后
    while(*(input+(*i)) == ' ') (*i)++;
    while(*(input+(*i)) != ' ')
    {
        char ch = *(input+(*i));
        (*i)++;
        if (ch == '-')
        {
            sign_flag = -1;
            continue;
        } else if (ch == '+')
        {
            sign_flag = 1;
            continue;
        } else if (ch == '.')
        {
            w = 1;
        }
        else if (ch >= '0' && ch <= '9')
        {
            float d = ch - '0';
            if (w == 0)  // 小数点前
            {
                ret = ret * 10 + d;
            } else  // 小数点后
            {
                int j;
                for (j = 0; j < w; j++)
                {
                    d = d * 0.1;
                }
                ret = ret + d;
                w++;
            }
        } else
        {
            break;
        }
    }
    return ret * sign_flag;
}