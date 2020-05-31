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
    fputs(errmsg, stdout);
    fputs("\n", stdout);
    exit(84);
    return 0;
}

void append_log(client_t *c, char *buf)
{
    if (!buf || strlen(buf) < 3)
        return;
    fprintf(stdout, "%s:%d: %s", c->addr_from, c->res.port, buf);
}

void msgsend(int sock, char const *msg)
{
    dprintf(sock, "%s\r\n", msg);
}
