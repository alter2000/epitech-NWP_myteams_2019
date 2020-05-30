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

socklen_t setup_client(client_t *c, const char *ip)
{
    c->res.p_ent = getprotobyname("TCP") ? getprotobyname("TCP")
                : errb(strerror(errno));
    c->res.sin.sin_family = AF_INET;
    c->res.sin.sin_port = htons(c->res.port);
    c->res.sin.sin_addr.s_addr = htonl(INADDR_ANY);
    c->addr_from = strdup(inet_ntoa(c->res.sin.sin_addr));
    c->addr_to = strdup(ip);
    c->res.lsn.fd = socket(AF_INET, SOCK_STREAM, c->res.p_ent->p_proto);
    return sizeof(c->res.sin);
}

void try_init_client(client_t *c, const char *ip)
{
    socklen_t tmp = setup_client(c, ip);

    if (c->res.lsn.fd == -1
        || getsockname(c->res.lsn.fd,
            (struct sockaddr *)&c->res.sin, &tmp) == -1
        || connect(c->res.lsn.fd,
            (struct sockaddr*)&c->res.sin, sizeof(c->res.sin))) {
        /* || setsockopt(c->res.lsn.fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, */
        /*         &tmp, sizeof(tmp)) == -1 */
        /* || bind(c->res.lsn.fd, (const struct sockaddr *)&c->res.sin, */
        /*     sizeof(c->res.sin)) == -1 */
        /* || listen(c->res.lsn.fd, MAXCONN) == -1) { */
        close(c->res.lsn.fd);
        errb(strerror(errno));
    }
    c->res.lsn.status = SOCKET_READY;
    append_log(c, "client up\n");
}

fd_set keep_init_client(client_t *c)
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

    buf[0] = getc(stdin);
    if (send(fd, buf, 1, 0) == -1)
        errb(strerror(errno));
}

void run_client(client_t *c)
{
    fd_set fds = keep_init_client(c);
    struct timeval ts = {.tv_sec = 3};
    int curfd = select(c->res.lsn.fd + 1, &fds, NULL, NULL, &ts);

    if (curfd <= 0)
        errb(curfd ? strerror(errno) : "server connection timed out");
    if (c->res.lsn.fd != 0 && FD_ISSET(c->res.lsn.fd, &fds))
        get_from_server(c->res.lsn.fd);
    else if (FD_ISSET(0, &fds))
        send_to_server(c->res.lsn.fd);
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
