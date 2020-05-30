#include "opt_parser.h"
#include "trace.h"
#include "resolve_path.h"

int usage(void)
{
    printf("Usage\n");
    return 1;
}

int fatal(const char *strerr, t_opts *opts, int ret)
{
    return ret;
}

int exec_child(t_opts *opts)
{
    if (!(opts->exec_path = resolve_path(opts->exec_path)))
        return fatal("can't stat", opts, 1);

    ptrace(PTRACE_TRACEME, getpid(), NULL, NULL);
    kill(getpid(), SIGSTOP);
    execv(opts->exec_path, opts->exec_args);
}

int run(t_opts *opts)
{
    pid_t pid = fork();

    if (pid == -1)
        return fatal("pid error", opts, 1);
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