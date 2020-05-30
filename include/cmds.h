/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#ifndef CMDS_H_
# define CMDS_H_

# include "types.h"

typedef void (*cmdptr)(client_t *, char *);

typedef struct {
    char *arg;
    cmdptr fn;
} cmdstr_t;

typedef struct {
    const char * const s;
    short slen;
    cmdptr cmd;
} cmdpair_t;

void handle_cmd(char *buf, client_t *);

void cmd_unknown(client_t *, char *buf);

#endif
