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
    socklen_t tmp = setup_client(c, ip);

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
    if (c->res.lsn.fd != 0)
        FD_SET(c->res.lsn.fd, &fds);
    FD_SET(0, &fds);
    return fds;
}

void get_from_server(int fd)
{
    char buf[MAXBUFLEN] = {0};
    int rv = recv(fd, buf , 1 , 0);

    if (rv == 0) {
        errb("Connection closed by remote\n");
    } else if (rv < 0)
        /* TODO */
        return;
}

void send_to_server(int fd)
{
    char buf[MAXBUFLEN] = {0};

    while (true) {
    buf[0] = getc(stdin);
    if (send(fd, buf, 1, 0) == -1)
        errb(strerror(errno));
    }
}

void run_client(client_t * const cli)
{
    fd_set fds = keep_init_client(cli);
    struct timeval ts = {.tv_sec = 3};
    int curfd = select(cli->res.lsn.fd + 1, &fds, NULL, NULL, &ts);

    if (curfd <= 0)
        errb(curfd ? strerror(errno) : "server connection timed out");
    if (cli->res.lsn.fd != 0 && FD_ISSET(cli->res.lsn.fd, &fds))
        get_from_server(cli->res.lsn.fd);
    else if (FD_ISSET(0, &fds))
        send_to_server(cli->res.lsn.fd);
}

int main(int c, char **v)
{
    int p = 0;
    client_t *cli = get_client();

    if (c == 1 || c > 3)
        show_help(84);
    if (!strncmp("-help", v[1], 5))
        show_help(0);
    p = strtol(v[2], NULL, 10);
    cli->res.port = (p > 0 && p < 65535) ? p : (long)errb("Invalid port num");
    try_init_client(cli, v[1]);
    run_client(cli);
}
