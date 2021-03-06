/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** automated desc ftw
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include "types.h"
# include "cmds.h"

typedef int (*cl_cmdptr)(char const *, char const *);

typedef struct {
    char *arg;
    cl_cmdptr fn;
} cl_cmdstr_t;

typedef struct {
    const char * const s;
    short slen;
    cl_cmdptr cmd;
} cl_cmdpair_t;

void getcmd_cl(client_t *c, char *buf);
void handle_cmd_cl(char *buf, client_t *c);
void try_init_client(client_t * const c, const char *ip);
fd_set keep_init_client(const client_t * const c);

#endif
