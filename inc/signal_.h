#ifndef SIGNAL__H
#define SIGNAL__H

#include "trace.h"

void        print_signal(siginfo_t signal);
void        print_exit(int status);

#endif