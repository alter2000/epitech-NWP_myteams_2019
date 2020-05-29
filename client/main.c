/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** automated desc ftw
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include "helpers.h"
#include "types.h"

void try_init_client(client_t *c, const char *ip)
{
    struct sockaddr_in ss = {.sin_addr.s_addr = inet_addr(ip),
        .sin_port = c->res.port};
    socklen_t tmp = sizeof(ss);

    c->res.lsn.status = SOCKET_NOT_READY;
    c->res.lsn.fd = socket(AF_INET, SOCK_STREAM, c->res.p_ent->p_proto);
    if (c->res.lsn.fd == -1
        || getsockname(c->res.lsn.fd, (struct sockaddr *)&ss, &tmp) == -1) {
        close(c->res.lsn.fd);
        errb(strerror(errno));
    }
    c->addr_from = strdup(inet_ntoa(ss.sin_addr));
    c->addr_to = strdup(ip);
    c->user = NULL;
    c->pw = NULL;
    c->isauth = false;
    c->res.sin.sin_port = htons(c->res.port);
    c->res.sin.sin_family = AF_INET;
    c->res.sin.sin_addr.s_addr = htonl(INADDR_ANY);
    append_log(c, "client up\n");
}

void run_client(client_t *c)
{
}

int main(int c, char **v)
{
    int p = 0;
    client_t *cl = get_client();

    if (c == 1 || c > 3)
        show_help(84);
    if (!strncmp("-help", v[1], 5))
        show_help(0);
    p = strtol(v[2], NULL, 10);
    cl->res.port = (p > 0 && p < 65535) ? p : (long)errb("Invalid port num");
    try_init_client(cl, v[1]);
    run_client(cl);
}
