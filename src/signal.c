#include <signal_.h>

const char  *get_signame(int signo)
{
    static const char *signames[] =
    {
        "SIGHUP",
        "SIGINT",
        "SIGQUIT",
        "SIGILL",
        "SIGTRAP",
        "SIGIOT",
        "SIGBUS",
        "SIGFPE",
        "SIGKILL",
        "SIGUSR",
        "SIGSEGV",
        "SIGUSR2",
        "SIGPIPE",
        "SIGALRM",
        "SIGTERM",
        "SIGSTKFLT",
        "SIGCONT",
        "SIGSTOP",
        "SIGTSTP",
        "SIGTTIN",
        "SIGTTOU",
        "SIGURG",
        "SIGXCPU",
        "SIGXFSZ",
        "SIGVTALRM",
        "SIGPROF",
        "SIGWINCH",
        "SIGIOl",
        "SIGPWR"
    };
    return signames[signo - 1];
}

void        print_signal(siginfo_t signal)
{
    printf(
        "--- %s {si_signo=%d, si_code=%d, si_pid=%d, si_uid=%d} ---\n",
        get_signame(signal.si_signo),
        signal.si_signo,
        signal.si_code,
        signal.si_pid,
        signal.si_uid
    );
}

void        print_exit(int status)
{
    printf(" = ?\n");
    if (WIFEXITED(status))
        printf("+++ exited with %d +++\n", WEXITSTATUS(status));
    else
    {
        if (WCOREDUMP(status))
            printf("+++ killed by %s (core dumped) +++\n", get_signame(WTERMSIG(status)));
        else
            printf("+++ killed by %s +++\n", get_signame(WTERMSIG(status)));
    }
}
