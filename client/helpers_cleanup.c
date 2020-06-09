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

server_t *get_server(void)
{
    static server_t s = {0};

    return &s;
}

void cleanup_client(client_t *c)
{
    server_t *s = get_server();

    if (!c || c < &s->clients[0] || c > &s->clients[MAXCONN - 1])
        return;
    c->res.lsn.status = SOCKET_NOT_READY;
    c->isauth = false;
    c->res.port = 0;
    mfree(c->addr_to);
    mfree(c->addr_from);
    mfree(c->user);
    close(c->res.lsn.fd);
    memset(c, 0, sizeof(*c));
}

void mfree(void *p)
{
    if (p) {
        free(p);
        p = NULL;
    }
}

ssize_t sock_getline(int fd, char *rbuf, size_t max)
{
    ssize_t n = 1;
    char *bufp = rbuf;

    for (int c, rret; n < max; n++) {
        rret = read(fd, &c, 1);
        if (rret == 1) {
            *bufp++ = c;
            if (c == '\r' || c == '\n')
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
