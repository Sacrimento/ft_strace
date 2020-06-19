#include "print.h"

void    print_string(pid_t pid, unsigned long addr, int is_filename, size_t size)
{
    static char *non_printable[7] = {"\\a", "\\b", "\\t", "\\n", "\\v", "\\f", "\\r"};
    char    str[MAX_STRING_PEEK] = {0};

    if (size)
        size = (size > 32 ? 32 : size + (sizeof(long) - size % sizeof(long)));
    get_string(pid, addr, str, size);

    printf("\"");
    if (is_filename)
        printf("%s", str);
    else
        for (int i = 0; (!size && i < MAX_STRING_SIZE && str[i] != 0) || (size && i < size); ++i)
        {
            if (str[i] > 6 && str[i] < 14)
                printf("%s", non_printable[str[i] - 7]);
            else if (isprint(str[i]))
                printf("%c", str[i]);
            else
                printf("\\%o", (unsigned char)str[i]);
        }
    printf("\"");

    if (size == 32 || (!is_filename && strlen(str) > 32))
        printf("...");
}

void    print_string_array(pid_t pid, unsigned long addr)
{
    unsigned long   addr_array[64];
    int             i = 0;
    int             len;

    len = get_array(pid, addr, addr_array);

    if (len > 8)
        printf("/* %d vars */", len);
    else
    {
        while (addr_array[i] != 0)
        {
            print_string(pid, addr_array[i], 0, 0);
            if (addr_array[++i] != 0)
                printf(", ");
        }
    }
}

void    convert_and_print_arg(pid_t pid, t_syscall_data syscall, int arg_index)
{
    long    arg = syscall.args[arg_index];

    switch (syscall.info.arg_types[arg_index])
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
            printf((!arg ? "NULL" : "%p"), (void *)arg); break;
        case FILENAME:
            print_string(pid, (unsigned long)arg, 1, 0); break;
        case STRING:
            print_string(pid, (unsigned long)arg, 0, 0); break;
        case SIZED_STRING:
            print_string(pid, (unsigned long)arg, 0, (size_t)syscall.args[arg_index + 1]); break;
        case STRING_ARRAY:
            printf("[");
            print_string_array(pid, (unsigned long)arg);
            printf("]"); break;
        default: break;
    }
}

void    print_syscall_data(pid_t pid, t_syscall_data syscall)
{
    printf("%s(", syscall.info.name);

    for (int i = 0; i < syscall.info.argc; i++)
    {
        convert_and_print_arg(pid, syscall, i);
        if (i + 1 < syscall.info.argc)
            printf(", ");
    }

    printf(")");
}

void    print_syscall_ret(long ret)
{
    printf(" = %ld\n", ret);
}
