#include "resolve_path.h"

void    replace_delimiter(char *path)
{
    int full_len = strlen(path);

    for (int i = 0; i < full_len; ++i)
        if (path[i] == ':')
            path[i] = 0;
}

char    *get_next_path(char *env_path, int offset)
{
    return (env_path[offset] ? &env_path[offset] : NULL);
}

int     check_abs_rel(char *cmd)
{
    struct stat buffer;
    
    if ((cmd[0] == '/' || (strlen(cmd) > 2 && cmd[0] == '.' && cmd[1] == '/'))
            && stat(cmd, &buffer) == 0)
        return 1;

    return 0;
}

char    *resolve_path(char *cmd)
{
    char        *env_path;
    char        *curr_path;
    char        *resolved;
    int         i = 0;
    struct stat buffer;

    if (check_abs_rel(cmd))
        return cmd;

    if (!(env_path = strdup(getenv("PATH"))))
        exit(0);

    if (!(resolved = malloc(sizeof(char) * (strlen(env_path) + strlen(cmd)))))
    {
        free(env_path);
        exit(0);
    }

    replace_delimiter(env_path);

    while ((curr_path = get_next_path(env_path, i)))
    {
        sprintf(resolved, "%s/%s", curr_path, cmd);
        if (stat(resolved, &buffer) == 0)
        {
            free(cmd);
            return resolved;
        }
        i += strlen(curr_path) + 1;
    }

    free(env_path);
    free(resolved);
    return NULL;
}