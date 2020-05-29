#ifndef TRACE_H
#define TRACE_H

#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <sys/reg.h>

#include "opt_parser.h"
#include "get_data.h"
#include "print.h"

#define SYSCALL_BIT 0x80

typedef enum    e_stop_type
{
    SYSCALL,
    SIGNAL,
    EXITED,
}               t_stop_type;

int trace_child(t_opts *opts, pid_t pid);

#endif