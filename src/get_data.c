#include "get_data.h"

long swap_int64(long val )
{
    val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
    val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
    return (val << 32) | ((val >> 32) & 0xFFFFFFFFULL);
}

void    get_string(pid_t pid, unsigned long addr, char *buffer, size_t size)
{
    long    ret;
    int     i = 0;

    while ((size && i < size) || (!size && i < MAX_STRING_PEEK - sizeof(long) - 1))
    {
        ret = ptrace(PTRACE_PEEKDATA, pid, addr + i, NULL);
        memcpy(buffer + i, &ret, sizeof(long));
        if (!size && memchr(&ret, 0, sizeof(long)))
            break;
        i += sizeof(long);
    }
    if (size)
        buffer[size] = 0;
}

int     get_array(pid_t pid, unsigned long addr, long *addr_array)
{
    long    ret;
    int     i, j = 0;

    while (i < 64 * sizeof(long))
    {
        ret = ptrace(PTRACE_PEEKDATA, pid, addr + i, NULL);
        addr_array[j++] = ret;
        if (ret == 0)
            break;
        i += sizeof(long);
    }
    addr_array[j] = 0;
    return j;
}

long    get_reg(pid_t pid, int reg_offset)
{
    return ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * reg_offset, NULL);
}

long get_syscall_ret(pid_t pid)
{
    return get_reg(pid, RAX);
}

t_syscall_data get_syscall_data(pid_t pid)
{
    t_syscall_data  syscall_data;

    syscall_data.info = get_syscall_info(get_reg(pid, ORIG_RAX));

    for (int i = 0; i < syscall_data.info.argc; i++)
        syscall_data.args[i] = get_reg(pid, get_arg_offset(i));

    return syscall_data;
}