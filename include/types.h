/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** automated desc ftw
*/

#ifndef TYPES_H_
# define TYPES_H_

# include <sys/types.h>
# include <netinet/in.h>
# include <netdb.h>
# include <stdbool.h>

/* maximum connections ("clients"/"requests") */
/* cannot be `static const int` because it's used in definitions */
# define MAXCONN (51)

/* maximum buffer size for commands */
# define MAXBUFLEN (4096)

typedef enum {
    SOCKET_NOT_READY = 0,
    SOCKET_READY,
    SOCKET_INUSE,
    SOCKET_ERROR
} sstatus_t;

typedef struct {
    sstatus_t status;
    int fd;
} socket_t;

typedef struct {
    enum cmode_s {
        CONN_PLAIN = 0,
        CONN_PASV,
        CONN_ACTV,
    } c;
    int fd;
} cmode_t;

typedef struct {
    socket_t f;
    char *addr_to;
    char *addr_from;
    unsigned short port;
    char *user;
    char *pw;
    bool isauth;
    cmode_t mode;
} client_t;

typedef struct {
    socket_t lsn;
    unsigned short port;
    struct protoent *p_ent;
    struct sockaddr_in sin;
} serverres_t;

typedef struct {
    serverres_t res;
    client_t clients[MAXCONN];
    fd_set readfds;
    int maxsd;
    int active;
} server_t;

#endif
