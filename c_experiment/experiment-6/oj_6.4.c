#include <stdio.h>

void scheduler();
void execute(void (*tasks[])(), int n);
void task0()
{
    printf("task0 is called!\n");
}
void task1()
{
    printf("task1 is called!\n");
}
void task2()
{
    printf("task2 is called!\n");
}
void task3()
{
    printf("task3 is called!\n");
}
void task4()
{
    printf("task4 is called!\n");
}
void task5()
{
    printf("task5 is called!\n");
}
void task6()
{
    printf("task6 is called!\n");
}
void task7()
{
    printf("task7 is called!\n");
}

int main()
{
    scheduler();
    return 0;
}

void scheduler()
{
    void (*task[8])() = {task0, task1, task2, task3, task4, task5, task6, task7};
    void (*tasks[20])() = {};
    char input[20] = {};
    int n = 0;
    while (scanf("%s", input) != EOF)
    {
        int n = 0;
        while (input[n] >= '0' && input[n] <= '7')
        {
            tasks[n] = task[input[n] - '0'];
            n++;
        }
        execute(tasks, n);
    }
}

void execute(void (*tasks[])(), int n)
{
    int i = 0;
    while (i < n)
    {
        tasks[i++]();
    }
}