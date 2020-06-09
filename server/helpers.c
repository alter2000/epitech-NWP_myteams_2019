/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "helpers.h"

void show_help(int exc)
{
    puts("USAGE: ./myteams_server port\n\n"
        "\tport  is the port number on which the server socket listens\n");
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

ssize_t sock_getline(int fd, char *rbuf, size_t max)
{
    ssize_t n = 1;
    char *bufp = rbuf;

    for (int c, rret; n < max; n++, c = 0) {
        rret = read(fd, &c, 1);
        if (rret == 1) {
            *bufp++ = c;
            if (c == '\n' || c == '\r')
                break;
        } else if (rret == 0) {
            if (n == 1)
                return 0;
            else
                break;
        } else
            return -1;
    }
    *bufp = 0;
    return n;
}
