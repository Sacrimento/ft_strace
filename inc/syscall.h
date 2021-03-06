#ifndef SYSCALL_H
#define SYSCALL_H

#include <sys/reg.h>

typedef enum arg_type
{
    INT,
    UINT,
    LONG,
    ULONG,
    STRING,
    SIZED_STRING,
    FILENAME,
    STRING_ARRAY,
    ADDR
}           t_arg_type;

typedef struct  s_syscall_info
{
    char        *name;
    int         argc;
    t_arg_type  arg_types[6];
    int         interrupt;
    t_arg_type  ret_type;
}               t_syscall_info;

t_syscall_info  get_syscall_info(int id);
int             get_arg_offset(int arg_index);

#endif