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

void cmd_unknown(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, 500, "This is just unknown");
}
void cmd_help(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, 500, "This is help_cmd");
}

void cmd_login(client_t *c, char *buf)
{
    if (!buf || !*buf) {
        msgsend(c->res.lsn.fd, 500, "Sorry, cannot do that!");
        return;
    }
    if (c->isauth) {
        mfree(c->user);
        c->user = strdup(buf);
    } else {
        c->user = strdup(buf);
        c->isauth = true;
    }
    append_log(c, buf);
    msgsend(c->res.lsn.fd, 500, "This is login_cmd");
    server_event_user_logged_in(c->user);
}

void cmd_logout(client_t *c, char *buf)
{
    if (c->isauth) {
        mfree(c->user);
        c->isauth = false;
        server_event_user_logged_out(c->user);
    } else {
        msgsend(c->res.lsn.fd, 500, "cannot logout when not logged in");
    }
    append_log(c, buf);
    msgsend(c->res.lsn.fd, 500, "This is logout_cmd");
}

void cmd_user(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, 500, "This is user_cmd");
}

void cmd_users(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, 500, "This is users_cmd");
}

void cmd_send(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, 500, "This is send_cmd");
}

void cmd_messages(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, 500, "This is messages_cmd");
}

void cmd_subscribe(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, 500, "This is subscribe_cmd");
}

void cmd_unsubscribe(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, 500, "This is unsubscribe_cmd");
}

void cmd_create(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, 500, "This is create_cmd");
}

void cmd_list(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, 500, "This is list_cmd");
}

void cmd_info(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, 500, "This is info_cmd");
}

void cmd_quit(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    cleanup_client(c);
}
