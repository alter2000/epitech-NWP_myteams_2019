/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#ifndef HELPERS_H_
# define HELPERS_H_

# include "types.h"

typedef struct {
    unsigned short errcode;
    const char *msg;
} err_t;

void show_help(int exc);
void *errb(const char *errmsg);
void append_log(client_t *, char *);
void msgsend(int sock, char const *msg);
void mfree(void *p);

server_t *get_server(void);
client_t *get_client(void);
void cleanup_client(client_t *);
ssize_t sock_getline(int fd, char *rbuf, size_t max);

#endif
