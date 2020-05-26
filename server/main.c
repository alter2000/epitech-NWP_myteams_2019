/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "types.h"
#include "helpers.h"
#include "server.h"
#include "cmds.h"

static void sigclose(int signum)
{
    server_t *s = get_server();

    for (size_t i = 0; i < MAXCONN; i++)
        cleanup_client(&s->clients[i]);
    if (s->res.lsn.fd != -1)
        close(s->res.lsn.fd);
    errb(strsignal(signum));
}

int main(int c, char **v)
{
    int p = 0;
    server_t *s = get_server();

    signal(SIGINT, sigclose);
    signal(SIGPIPE, sigclose);
    if (c != 2)
        show_help(84);
    if (!strncmp(v[1], "-help", 5))
        show_help(0);
    p = strtol(v[1], NULL, 10);
    s->res.port = (p > 0 && p < 65535) ? p : (long)errb("Invalid port num");
    try_init_server(s);
    run_server(s);
}
