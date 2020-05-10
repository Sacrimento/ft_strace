#include "opt_parser.h"

t_opts  *check_opts(t_opts *opts, int error)
{
    int     i = 0;
    if (error || !opts->exec_path || !(*opts->exec_path))
    {
        free(opts->exec_path);
        error++;
    }
    if (error && opts->exec_args)
        while (opts->exec_args[i])
            free(opts->exec_args[i++]);
    if (error)
    {
        if (opts->exec_args)
            free(opts->exec_args);
        free(opts);
    }
    return (error ? NULL : opts);
}

t_opts  *get_opts(int argc, char **argv)
{
    t_opts  *opts = NULL;
    int     i = 1;
    int     j = 0;

    if (argc < 2)
        return opts;
    if (!(opts = malloc(sizeof(t_opts))))
        return opts;
    
    if (!strcmp(argv[i], "-c"))
        opts->count = i++;
    opts->exec_path = strdup(argv[i]);

    if (!(opts->exec_args = malloc(sizeof(char*) * (argc - i + 1))))
        return check_opts(opts, 1);
    while (i < argc)
        if (!(opts->exec_args[j++] = strdup(argv[i++])))
            return check_opts(opts, 1);

    return check_opts(opts, 0);
}
