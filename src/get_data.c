#include "get_data.h"

void    get_string(pid_t pid, unsigned long addr, char *buffer)
{
    long    ret;
    int     i = 0;

    bzero(buffer, 64);
    while (i < 64)
    {
        ret = ptrace(PTRACE_PEEKDATA, pid, addr + i, NULL);
        memcpy(buffer + i, &ret, sizeof(long));
        if (memchr(&ret, 0, sizeof(long)))
            break;
        i += sizeof(long);
    }

    buffer[63] = 0;
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