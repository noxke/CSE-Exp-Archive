# arch/x86/entry/syscalls/syscall_64.tbl
# my_syscall
548 	64      my_add             	__x64_sys_my_add
549		64      my_max	            __x64_sys_my_max
550 	64      my_hello           	__x64_sys_my_hello

# include/linux/syscalls.h
// my_syscalls
asmlinkage long sys_my_add(int a, int b);
asmlinkage long sys_my_max(int a, int b, int c);
asmlinkage void * sys_my_hello(const char *name);

# kernel/sys.c
// my_syscalls
SYSCALL_DEFINE2(my_add, int, a, int, b)
{
    return a + b;
}

SYSCALL_DEFINE3(my_max, int, a, int, b, int, c)
{
	int max = a;
	if (b > max)
	{
		max = b;
	}
	if (c > max)
	{
		max = c;
	}
	return max;
}

SYSCALL_DEFINE1(my_hello, const char *, name)
{
	return NULL;
}
