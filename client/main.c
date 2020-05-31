/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** automated desc ftw
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "helpers.h"
#include "types.h"
#include "client.h"

// TODO: commands

static void sigclose(int signum)
{
    cleanup_client(get_client());
    errb(strsignal(signum));
}

void get_from_server(int fd)
{
    char buf[MAXBUFLEN] = {0};
    int rv = recv(fd, buf , 1 , 0);

    if (rv == 0) {
        errb("Connection closed by remote\n");
    } else if (rv < 0) {
        errb(strerror(errno));
    } else
        write(STDOUT_FILENO, buf, rv);
}

void send_to_server(int fd)
{
    char *buf = NULL;
    size_t n = 0;

    while (getline(&buf, &n, stdin) != -1) {
        write(fd, buf, strlen(buf));
        free(buf);
        n = 0;
    }
}

void run_client(client_t * const cli)
{
    fd_set fds = keep_init_client(cli);
    int curfd = select(cli->res.lsn.fd + 1, &fds, NULL, NULL, NULL);

    if (curfd <= 0)
        errb(curfd ? strerror(errno) : "server connection timed out");
    send_to_server(cli->res.lsn.fd);
    FD_CLR(cli->res.lsn.fd, &fds);
}

int main(int c, char **v)
{
    int p = 0;
    client_t *cli = get_client();

    signal(SIGINT, sigclose);
    signal(SIGPIPE, sigclose);
    if (c == 1 || c > 3)
        show_help(84);
    if (!strncmp("-help", v[1], 5))
        show_help(0);
    p = strtol(v[2], NULL, 10);
    cli->res.port = (p > 0 && p < 65535) ? p : (long)errb("Invalid port num");
    try_init_client(cli, v[1]);
    run_client(cli);
}
