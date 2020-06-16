#ifndef GET_DATA_H
#define GET_DATA_H

#include "trace.h"
#include "syscall.h"

#include <string.h>

#define MAX_STRING_PEEK 4096
#define MAX_STRING_SIZE 32

typedef struct  s_syscall_data
{
    t_syscall_info  info;
    long            args[6];
}               t_syscall_data;

t_syscall_data get_syscall_data(pid_t pid);
long get_syscall_ret(pid_t pid);
void get_string(pid_t pid, unsigned long addr, char *buffer, size_t size);
int get_array(pid_t pid, unsigned long addr, long *addr_array);

#endif