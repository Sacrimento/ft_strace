#ifndef RESOLVE_PATH_H
#define RESOLVE_PATH_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char    *resolve_path(char *cmd);

#endif