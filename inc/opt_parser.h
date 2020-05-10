#ifndef OPT_PARSER_H
#define OPT_PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct  s_opts
{
    int     count;
    char    *exec_path;
    char    **exec_args;
}               t_opts;

t_opts  *get_opts(int argc, char **argv);

#endif