#include "opt_parser.h"
#include "trace.h"

int usage(void)
{
    printf("Usage\n");
    return 1;
}

int exec_child(t_opts *opts)
{
    ptrace(PTRACE_TRACEME, getpid(), NULL, NULL);
    kill(getpid(), SIGSTOP);
    execvp(opts->exec_path, opts->exec_args);
}

int __exit(t_opts *opts, int ret)
{
    return ret;
}

int run(t_opts *opts)
{
    pid_t pid = fork();

    if (pid == -1)
        return __exit(opts, 1);
    if (pid == 0)
        return exec_child(opts);
    return trace_child(opts, pid);
}

int main(int argc, char **argv)
{
    t_opts  *opts = get_opts(argc, argv);

    if (!opts)
        return usage();

    return run(opts);
}