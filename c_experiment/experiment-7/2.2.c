#include "stdio.h"
#include "stdlib.h"
struct s_list
{
    int data;            /* 数据域 */
    struct s_list *next; /* 指针域 */
};
void create_list(struct s_list **headp, int *p);
void main(void)
{
    struct s_list *head = NULL, *p;
    int s[] = {1, 2, 3, 4, 5, 6, 7, 8, 0}; /* 0为结束标记 */
    create_list(&head, s);                  /* 创建新链表 */
    p = head;                              /*遍历指针p指向链头 */
    while (p)
    {
        printf("%d\t", p->data); /* 输出数据域的值 */
        p = p->next;             /*遍历指针p指向下一结点 */
    }
    printf("\n");
}
void create_list(struct s_list **headp, int *p)
{
    struct s_list *loc_head = NULL, *new_head;
    if (p[0] == 0) /* 相当于*p==0 */
        ;
    else
    {
        while (*p)
        { /* new_head所指结点的指针域指向动态创建的结点 */
            new_head = (struct s_list *)malloc(sizeof(struct s_list));
            new_head->next = loc_head; /* new_head指向新创建的结点 */
            new_head->data = *p++; /* 向新创建的结点的数据域赋值 */
            loc_head = new_head;
        }
    }
    *headp = loc_head; /* 使头指针headp指向新创建的链表 */
}
