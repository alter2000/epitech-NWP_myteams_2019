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
#include "cmds.h"
#include "client.h"
#include "myteams/logging_client.h"

static int cl_cmd_unknown(const char *a, const char *b)
{
    (void)b;
    printf("%s is not a valid command\n", a);
    return 0;
}

static const cl_cmdpair_t CMDS_CL[] = {
    { "/login"  , 6 , client_event_loggedin   } ,
    { "/logout" , 7 , client_event_loggedout } ,
    { NULL      , 0 , cl_cmd_unknown     } ,
};

void getcmd_cl(client_t *c, char *buf)
{
    cl_cmdptr fn = cl_cmd_unknown;
    char *cmd = strtok(buf, " ");

    if (!cmd)
        fn((const char*)c->uuid, c->user);
    for (int i = 0; CMDS_CL[i].s; i++)
        if (!strncasecmp(CMDS_CL[i].s, cmd, CMDS_CL[i].slen)) {
            CMDS_CL[i].cmd((const char*)c->uuid, c->user);
            return;
        }
}
