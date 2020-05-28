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
#include "helpers.h"
#include "types.h"

int main(int c, char **v)
{
    int p = 0;
    client_t *cl = get_client();

    if (c == 1 || c > 3)
        show_help(84);
    if (!strncmp("-help", v[1], 5))
        show_help(0);
    p = strtol(v[1], NULL, 10);
    cl->ip = (p > 0 && p < 65535) ? p : (long)errb("Invalid port num");
    p = strtol(v[2], NULL, 10);
    cl->port = (p > 0 && p < 65535) ? p : (long)errb("Invalid port num");
    try_init_client(cl);
    run_client(cl);
}
