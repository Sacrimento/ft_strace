#ifndef PRINT_H
#define PRINT_H

typedef struct s_syscall_data t_syscall_data;

#include <ctype.h>

#include "get_data.h"

void    print_syscall_data(pid_t pid, t_syscall_data syscall);
void    print_syscall_ret(long ret);

#endif