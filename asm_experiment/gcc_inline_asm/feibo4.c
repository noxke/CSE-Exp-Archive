int feibo4(int n)           // 入口参数edi，出口参数eax
{
    int result;
    asm volatile(           // 内联汇编部分，入口参数n使用内存指针n传递，出口参数使用内存指针result传递
        "mov %1, %%eax;"    // 从指向n的内存地址取出n的值传入eax中
        "cmp $2, %%eax;"    // 比较n与2的大小
        "jg r;"             // n大于2时递归计算
        "mov $1, %%eax;"    // n小于等于2时直接返回1
        "jmp endf;"
        "r:;"
        "sub $1, %%eax;"    // n - 1
        "mov %%eax, %%edi;" // 将n - 1传递给edi寄存器，函数入口参数
        "call feibo4;"      // feibo4(n-1)
        "mov %%eax, %0;"    // 将函数出口参数保存到result所在的内存中
        "mov %1, %%eax;"    // 从指向n的内存地址取出n的值传入eax中
        "sub $2, %%eax;"    // n - 2
        "mov %%eax, %%edi;" // 将n - 2传递给edi寄存器，函数入口参数
        "call feibo4;"      // feibo4(n-2)
        "add %0, %%eax;"    // %0中储存的为feibo4(n-1)的值，将其加到feibo4(n-2)的计算结果中
                            // 即eax中储存的为feibo4(n-1)+feibo4(n-2)
        "endf:"
        "mov %%eax, %0;"    // 将返回值传送到result所在的内存中
        : "=m"(result)      // OUTPUT出口参数，使用内存传参，通过%0调用
        : "m"(n));          // INPUT入口参数，使用内存传参，通过%1调用
    return result;
}