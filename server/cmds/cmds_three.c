/*
** EPITECH PROJECT, 2020
** EPITECH 2020
** File description:
** cmds part three
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
#include <uuid/uuid.h>
#include "cmds.h"
#include "helpers.h"
#include "types.h"
#include "myteams/logging_server.h"

static const char *HELPMSG = "Welcome to the server\n"
    "Please type /login [username] to login"
    "\ntype /logout to logout from the server\n"
    "type /user to show the user\n"
    "type /users to show the users\n\n";

void cmd_help(client_t *c, char *buf)
{
    (void)buf;
    msgsend(c->res.lsn.fd, HELPMSG);
}

void cmd_login(client_t *c, char *buf)
{
    if (!buf || !*buf || strlen(buf) > MAX_NAME_LENGTH) {
        msgsend(c->res.lsn.fd, "username too long or null");
        return;
    }
    if (c->isauth) {
        mfree(c->user);
        c->user = strdup(strtok(buf, "\""));
    } else {
        c->user = strdup(strtok(buf, "\""));
        c->isauth = true;
        uuid_generate(c->uuid);
    }
    append_log(c, strtok(buf, "\""));
    msgsend(c->res.lsn.fd, "should be logged in");
    server_event_user_logged_in(c->user);
}

void cmd_logout(client_t *c, char *buf)
{
    if (c->isauth) {
        server_event_user_logged_out(c->user);
        c->isauth = false;
    } else {
        msgsend(c->res.lsn.fd, "cannot logout when not logged in");
    }
    append_log(c, buf);
    msgsend(c->res.lsn.fd, "should be logged out");
}

void cmd_unknown(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, "This is just unknown");
}

void cmd_messages(client_t *c, char *buf)
{
    if (buf)
        memset(buf, 0, strlen(buf));
    msgsend(c->res.lsn.fd, "This is messages_cmd");
}
