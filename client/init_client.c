/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** automated desc ftw
*/

#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "helpers.h"
#include "client.h"

socklen_t setup_client(client_t * const c, const char *ip)
{
    c->res.p_ent = getprotobyname("TCP") ? getprotobyname("TCP")
                : errb(strerror(errno));
    c->res.sin.sin_port = htons(c->res.port);
    c->res.sin.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip, &c->res.sin.sin_addr.s_addr) != 1) {
        errb(strerror(errno));
    }
    c->addr_from = strdup(inet_ntoa(c->res.sin.sin_addr));
    c->addr_to = strdup(ip);
    c->res.lsn.fd = socket(AF_INET, SOCK_STREAM, c->res.p_ent->p_proto);
    if (c->res.lsn.fd == -1) {
        close(c->res.lsn.fd);
        errb(strerror(errno));
    }
    return sizeof(c->res.sin);
}

void try_init_client(client_t * const c, const char *ip)
{
    setup_client(c, ip);
    if (connect(c->res.lsn.fd,
            (struct sockaddr*)&c->res.sin, sizeof(c->res.sin))) {
        close(c->res.lsn.fd);
        errb(strerror(errno));
    }
    c->res.lsn.status = SOCKET_READY;
    append_log(c, "client up\n");
}

fd_set keep_init_client(const client_t * const c)
{
    fd_set fds;

    FD_ZERO(&fds);
    FD_SET(c->res.lsn.fd, &fds);
    FD_SET(0, &fds);
    return fds;
}
