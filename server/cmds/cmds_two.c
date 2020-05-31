/*
** EPITECH PROJECT, 2020
** EPITECH 2020
** File description:
** cmds part two
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

void cmd_user(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, "This is user_cmd");
}

void cmd_users(client_t *c, char *buf)
{
    server_t *s = get_server();
    char buff[MAX_BODY_LENGTH] = {0};

    if (buf)
        memset(buf, 0, strlen(buf));
    for (size_t i = 0; i < MAXCONN; i++)
        if (s->clients[i].isauth) {
            sprintf(buff, "%s %s\n", s->clients[i].uuid, s->clients[i].user);
            msgsend(c->res.lsn.fd, buff);
        }
}

void cmd_send(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, "This is send_cmd");
}

void cmd_subscribe(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, "This is subscribe_cmd");
}

void cmd_unsubscribe(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, "This is unsubscribe_cmd");
}
