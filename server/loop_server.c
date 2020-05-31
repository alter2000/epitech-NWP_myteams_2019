/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "server.h"
#include "helpers.h"
#include "cmds.h"
#include "reqs.h"

static int check_req(server_t *s);
static void check_clients(client_t cs[MAXCONN], fd_set *, int *);
static int new_req(server_t *s);
static void do_clients(client_t cs[MAXCONN], fd_set *fds);

void run_server(server_t *s)
{
    for (int cl_sock, idx = 0; true;
            cl_sock = 0, idx = idx < MAXCONN - 1 ? idx + 1 : 0) {
        cl_sock = check_req(s);
        if (cl_sock)
            add_req(cl_sock, &s->res.sin, &s->clients[idx]);
        do_clients(s->clients, &s->readfds);
    }
}

static int check_req(server_t *s)
{
    FD_ZERO(&s->readfds);
    FD_SET(s->res.lsn.fd, &s->readfds);
    s->maxsd = s->res.lsn.fd;
    s->res.lsn.status = SOCKET_READY;
    check_clients(s->clients, &s->readfds, &s->maxsd);
    s->active = select(s->maxsd + 1, &s->readfds, NULL, NULL, NULL);
    if (s->active < 0 && errno != EINTR) {
        close(s->res.lsn.fd);
        errb(strerror(errno));
    }
    return new_req(s);
}

static void check_clients(client_t cs[MAXCONN],
        fd_set *readfds, int *total_sockfds)
{
    for (size_t i = 0; i < MAXCONN; i++) {
        if (cs[i].res.lsn.fd <= *total_sockfds)
            continue;
        switch (cs[i].res.lsn.status) {
            case SOCKET_READY:
            case SOCKET_ERROR:
                FD_CLR(cs[i].res.lsn.fd, readfds);
                cs[i].res.lsn.status = SOCKET_NOT_READY;
            case SOCKET_NOT_READY:
                FD_SET(cs[i].res.lsn.fd, readfds);
                cs[i].res.lsn.status = SOCKET_READY;
            case SOCKET_INUSE:
            default:
                break;
        }
        if (cs[i].res.lsn.fd > *total_sockfds)
            *total_sockfds = cs[i].res.lsn.fd;
    }
}

static int new_req(server_t *s)
{
    int cl_sock = 0;
    socklen_t t = sizeof(s->res.sin);

    if (!FD_ISSET(s->res.lsn.fd, &s->readfds))
        return 0;
    cl_sock = accept(s->res.lsn.fd, (struct sockaddr *)&s->res.sin, &t);
    if (cl_sock == -1) {
        close(s->res.lsn.fd);
        errb(strerror(errno));
    }
    return cl_sock;
}

static void do_clients(client_t cs[MAXCONN], fd_set *fds)
{
    char buf[MAX_BODY_LENGTH];

    for (size_t i = 0; i < MAXCONN; i++)
        if (FD_ISSET(cs[i].res.lsn.fd, fds)) {
            memset(buf, 0, MAX_BODY_LENGTH);
            if (read(cs[i].res.lsn.fd, buf, MAX_BODY_LENGTH) < 2) {
                append_log(&cs[i], "disconnected\n");
                cmd_quit(&cs[i], buf);
                continue;
            }
            append_log(&cs[i], buf);
            handle_cmd(buf, &cs[i]);
        }
}
