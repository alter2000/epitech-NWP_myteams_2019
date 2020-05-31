/*
** EPITECH PROJECT, 2020
** EPITECH 2020
** File description:
** cmd part four
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

void cmd_create(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, "This is create_cmd");
}

void cmd_list(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, "This is list_cmd");
}

void cmd_info(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, "This is info_cmd");
}

void cmd_quit(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    cleanup_client(c);
}
