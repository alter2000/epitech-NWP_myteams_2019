/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "helpers.h"
#include "server.h"

static void keep_init_server(server_t *s);

void try_init_server(server_t *s)
{
    s->res.p_ent = getprotobyname("TCP") ? getprotobyname("TCP")
        : errb(strerror(errno));
    s->res.lsn.fd = socket(AF_INET, SOCK_STREAM, s->res.p_ent->p_proto);
    if (s->res.lsn.fd == -1) {
        close(s->res.lsn.fd);
        errb(strerror(errno));
    }
    s->res.sin.sin_port = htons(s->res.port);
    s->res.sin.sin_family = AF_INET;
    s->res.sin.sin_addr.s_addr = htonl(INADDR_ANY);
    keep_init_server(s);
}

static void keep_init_server(server_t *s)
{
    int tmp = 1;

    if (setsockopt(s->res.lsn.fd, SOL_SOCKET,
            SO_REUSEADDR | SO_REUSEPORT, &tmp, sizeof(tmp)) == -1
        || bind(s->res.lsn.fd, (const struct sockaddr *)&s->res.sin,
            sizeof(s->res.sin)) == -1
        || listen(s->res.lsn.fd, MAXCONN) == -1) {
            close(s->res.lsn.fd);
            errb(strerror(errno));
    }
}
