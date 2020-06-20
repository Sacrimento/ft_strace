#include "trace.h"

t_stop_type get_next_sigstop(pid_t pid, int *status)
{
    ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
    waitpid(pid, status, 0);

    if (WIFSTOPPED(*status))
    {
        if (WSTOPSIG(*status) & SYSCALL_BIT)
            return SYSCALL;
        return SIGNAL;
    }
    if (WIFEXITED(*status))
        return EXITED;
}

void    handle_syscall(pid_t pid, int *in_syscall)
{
    t_syscall_data      syscall;
    static t_arg_type   ret_type;

    *in_syscall ^= 1;
    if (*in_syscall)
    {
        syscall = get_syscall_data(pid);
        ret_type = syscall.info.ret_type;
        print_syscall_data(pid, syscall);
    }
    else
        print_syscall_ret(get_syscall_ret(pid), ret_type);
}

int trace_child(t_opts *opts, pid_t pid)
{
    int         status;
    static int  in_syscall = 0;
    t_stop_type sigstop;

    waitpid(pid, &status, 0);
    ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD);

    while (1)
    {
        sigstop = get_next_sigstop(pid, &status);
        if (sigstop == SYSCALL)
            handle_syscall(pid, &in_syscall);
        else if (sigstop == SIGNAL)
            printf("SIGNAL\n");
        else
        {
            printf("EXITED\n");
            break;
        }
    }
}