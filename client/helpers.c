/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

static const err_t STRSTATUS[] = {

    { 0, NULL }
};

client_t *get_client()
{
    static client_t c = {0};

    return &c;
}

void show_help(int exc)
{
    puts("USAGE: ./myteams_cli ip port\n\tip\tis the server ip address"
            "on which the server socket listens\n\tport\tis the port number"
            "on which the server socket listens");
    exit(exc);
}

void *errb(const char *errmsg)
{
    fputs(errmsg, stderr);
    fputs("\n", stderr);
    exit(84);
    return 0;
}

void append_log(client_t *c, char *buf)
{
    if (!buf || strlen(buf) < 3)
        return;
    fprintf(stderr, "%s:%d: %s", c->addr_from, c->port, buf);
}

void msgsend(int sock, int code, char *msg)
{
    if (!msg || !*msg)
        for (size_t i = 0; STRSTATUS[i].errcode; i++)
            if (STRSTATUS[i].errcode == code) {
                msg = (char *)STRSTATUS[i].msg;
                break;
            }
    dprintf(sock, "%d %s\r\n", code, msg);
}
