/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
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
#include "helpers.h"
#include "myteams/logging_server.h"

static const cmdpair_t CMDS[] = {
    { "/help"        , 5  , cmd_help        } ,
    { "/login"       , 6  , cmd_login       } ,
    { "/logout"      , 7  , cmd_logout      } ,
    { "/user"        , 5  , cmd_user        } ,
    { "/users"       , 6  , cmd_users       } ,
    { "/send"        , 5  , cmd_send        } ,
    { "/messages"    , 9  , cmd_messages    } ,
    { "/subscribe"   , 10 , cmd_subscribe   } ,
    { "/unsubscribe" , 12 , cmd_unsubscribe } ,
    { "/create"      , 7  , cmd_create      } ,
    { "/list"        , 5  , cmd_list        } ,
    { "/info"        , 5  , cmd_info        } ,
    { NULL           , 0  , cmd_unknown     } ,
};

static cmdstr_t *getcmd(char *buf)
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
    for (int i = 0; CMDS[i].s; i++)
        if (!strncasecmp(CMDS[i].s, cmd, CMDS[i].slen)) {
            to.fn = CMDS[i].cmd;
            break;
        }
    to.arg = strtok(NULL, "\r\n");
    return &to;
}

void handle_cmd(char *buf, client_t *c)
{
    cmdstr_t *cmd = getcmd(buf);

    cmd->fn(c, cmd->arg);
}
