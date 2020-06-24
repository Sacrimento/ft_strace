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
    if (WIFEXITED(*status) || WIFSIGNALED(*status))
        return EXITED;
}

int     handle_syscall(pid_t pid, int *in_syscall, int written)
{
    static t_syscall_data      syscall;

    *in_syscall ^= 1;
    if (*in_syscall)
    {
        syscall = get_syscall_data(pid);
        return print_syscall_data(pid, syscall, 0);
    }
    if (syscall.info.interrupt != -1)
        print_syscall_data(pid, syscall, written);
    print_syscall_ret(get_syscall_ret(pid), syscall.info.ret_type);
    return 0;
}

void    handle_signal(pid_t pid, int in_syscall)
{
    siginfo_t   signal;

    if (in_syscall)
        printf(" = ?\n");

    ptrace(PTRACE_GETSIGINFO, pid, 0, &signal);
    print_signal(signal);

    // handle special signals : sigstop / sigcont
}

int     trace_child(t_opts *opts, pid_t pid)
{
    int         status, interrupted;
    static int  in_syscall = 0;
    t_stop_type sigstop;

    waitpid(pid, &status, 0);
    ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD);

    while (1)
    {
        sigstop = get_next_sigstop(pid, &status);
        if (sigstop == SYSCALL)
            interrupted = handle_syscall(pid, &in_syscall, interrupted);
        else if (sigstop == SIGNAL)
            handle_signal(pid, in_syscall);
        else // PROCESS ENDED
            break;
    }

    print_exit(status);
    return WEXITSTATUS(status);
}