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

static const cl_cmdpair_t CMDS_CL[] = {
    { "/help"        , 5  , cmd_help        } ,
    { NULL           , 0  , cmd_unknown     } ,
};

void getcmd_cl(client_t *c, char *buf)
{
    cl_cmdptr fn = cmd_unknown;
    char *cmd = strtok(buf, " ");

    if (!cmd)
        fn(c->uuid, c->user);
    for (int i = 0; CMDS_CL[i].s; i++)
        if (!strncasecmp(CMDS_CL[i].s, cmd, CMDS_CL[i].slen)) {
            CMDS_CL[i].cmd(c->uuid, c->user);
            return;
        }
}
