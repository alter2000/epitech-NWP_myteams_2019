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
void cmd_help(client_t *c, char *buf);
void cmd_login(client_t *c, char *buf);
void cmd_logout(client_t *c, char *buf);
void cmd_user(client_t *c, char *buf);
void cmd_users(client_t *c, char *buf);
void cmd_send(client_t *c, char *buf);
void cmd_messages(client_t *c, char *buf);
void cmd_subscribe(client_t *c, char *buf);
void cmd_unsubscribe(client_t *c, char *buf);
void cmd_create(client_t *c, char *buf);
void cmd_list(client_t *c, char *buf);
void cmd_info(client_t *c, char *buf);

#endif
