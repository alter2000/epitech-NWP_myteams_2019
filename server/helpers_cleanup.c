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
    c->f.status = SOCKET_NOT_READY;
    c->mode.c = CONN_PLAIN,
    c->isauth = false;
    c->port = 0;
    mfree(c->addr_to);
    mfree(c->addr_from);
    mfree(c->user);
    mfree(c->pw);
    FD_CLR(c->f.fd, &s->readfds);
    close(c->f.fd);
    memset(c, 0, sizeof(*c));
}

void mfree(void *p)
{
    if (p) {
        free(p);
        p = NULL;
    }
}
