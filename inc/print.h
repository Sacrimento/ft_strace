#ifndef PRINT_H
#define PRINT_H

typedef struct s_syscall_data t_syscall_data;
typedef enum arg_type t_arg_type;

#include <ctype.h>

#include "get_data.h"
#include "errno_str.h"

void    print_syscall_data(pid_t pid, t_syscall_data syscall);
void    print_syscall_ret(long ret, t_arg_type ret_type);

#endif