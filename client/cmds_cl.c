/*
** EPITECH PROJECT, 2020
** rrushat e klientit
** File description:
** comunism propaganda
*/

#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../include/cmds.h"
#include "../include/client.h"

static const cmdpair_cl CMDS_CL[] = {
    { "/help"        , 5  , cmd_help        } ,
    { NULL           , 0  , cmd_unknown     } ,
};

static cmdstr_t *getcmd_cl(char *buf)
{
    static cmdstr_t to = {NULL, cmd_unknown};
    char *cmd = NULL;

    to.arg = NULL;
    to.fn = cmd_unknown;
    if (strlen(buf) < 3)
        return &to;
    cmd = strtok(buf, " ");
    if (!cmd)
        return &to;
    for (int i = 0; CMDS_CL[i].s; i++)
        if (!strncasecmp(CMDS_CL[i].s, cmd, CMDS_CL[i].slen)) {
            to.fn = CMDS_CL[i].cmd;
            break;
        }
    to.arg = strtok(NULL, "\r\n");
    return &to;
}

void handle_cmd_cl(char *buf, client_t *c)
{
    cmdstr_t *cmd = getcmd_cl(buf);

    cmd->fn(c, cmd->arg);
}
