#include "print.h"

void    print_string(pid_t pid, unsigned long addr)
{
    char    str[64];

    get_string(pid, addr, str);

    printf("\"%.32s\"", str);

    if (strlen(str) > 32)
        printf("...");
}

void    print_string_array(pid_t pid, unsigned long addr)
{
    unsigned long   addr_array[64];
    int             i = 0;
    int             len;

    len = get_array(pid, addr, addr_array);

    //putchar('c');
    if (len > 8)
        printf("/* %d vars */", len);
    else
        while (addr_array[i] != 0)
        {
            print_string(pid, addr_array[i]);
            if (addr_array[i++ + 1] != 0)
                printf(", ");
        }
    //putchar('c');
}

void    convert_and_print_arg(pid_t pid, long arg, t_arg_type type)
{
    switch (type)
    {
        case INT:
            printf("%d", (int)arg); break;
        case UINT:
            printf("%u", (unsigned int)arg); break;
        case LONG:
            printf("%ld", arg); break;
        case ULONG:
            printf("%lu", (unsigned long)arg); break;
        case ADDR:
            printf("%p", (void *)arg); break;
        case STRING:
            print_string(pid, (unsigned long)arg); break;
        case STRING_ARRAY:
            print_string_array(pid, (unsigned long)arg); break;
        default: break;
    }
}

void    print_syscall_data(pid_t pid, t_syscall_data syscall)
{
    printf("%s(", syscall.info.name);

    for (int i = 0; i < syscall.info.argc; i++)
    {
        convert_and_print_arg(pid, syscall.args[i], syscall.info.arg_types[i]);
        if (i + 1 < syscall.info.argc)
            printf(", ");
    }

    printf(")");
}

void    print_syscall_ret(long ret)
{
    printf(" = %ld\n", ret);
}
