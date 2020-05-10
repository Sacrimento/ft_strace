#ifndef GET_DATA_H
#define GET_DATA_H

#include "trace.h"
#include "syscall.h"

typedef struct  s_syscall_data
{
    t_syscall_info  info;
    long            args[6];
}               t_syscall_data;

t_syscall_data get_syscall_data(pid_t pid);
long get_syscall_ret(pid_t pid);

#endif