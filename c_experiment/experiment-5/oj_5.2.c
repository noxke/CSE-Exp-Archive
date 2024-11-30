#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct stu
{
    char name[20];
    int score;
} stu;

int inputRecord(stu *r, int n);   // 成绩输入
void reorder(stu *r, int n);      // 成绩排序
void outputRecord(stu *r, int n); // 输出成绩
void findRecord(stu *r, int n);   // 查找指定成绩

int main()
{
    int mode, n = 0;
    stu records[20];
    while (scanf("%d", &mode))
    {
        switch (mode)
        {
        case 1:
            n += inputRecord(records, n);
            break;
        case 2:
            reorder(records, n);
            break;
        case 3:
            outputRecord(records, n);
            break;
        case 4:
            findRecord(records, n);
            break;
        }
        if (mode == 0)
            break;
    }
    return 0;
}

int inputRecord(stu *r, int a)
{
    stu *k = r + a;
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%s %d", k->name, &(k->score));
        k++;
    }
    printf("%d records were input!\n", n);
    return n;
}

void reorder(stu *r, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if ((r + j)->score < (r + j + 1)->score)
            {
                int tmpd = (r + j)->score;
                char tmpc[20];
                strcpy(tmpc, (r + j)->name);
                (r + j)->score = (r + j + 1)->score;
                (r + j + 1)->score = tmpd;
                strcpy((r + j)->name, (r + j + 1)->name);
                strcpy((r + j + 1)->name, tmpc);
            }
        }
    }
    printf("Reorder finished!\n");
}

void outputRecord(stu *r, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", (r + i)->name, (r + i)->score);
    }
}

void findRecord(stu *re, int n)
{
    int score;
    scanf("%d", &score);
    int l = 0, r = n, mid;
    while (r - l > 1)
    {
        mid = (r + l) / 2;
        if (score > (re + mid)->score)
        {
            l = l;
            r = mid;
        }
        else if (score < (re + mid)->score)
        {
            l = mid;
            r = r;
        }
        else
        {
            break;
        }
    }
    if (score == (re + mid)->score)
    {
        printf("%s %d\n", (re + mid)->name, (re + mid)->score);
    }
    else
    {
        printf("not found!\n");
    }
}