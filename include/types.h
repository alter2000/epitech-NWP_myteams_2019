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
# include <uuid/uuid.h>

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
    socket_t lsn;
    unsigned short port;
    struct protoent *p_ent;
    struct sockaddr_in sin;
} res_t;

typedef struct {
    res_t res;
    /* server: location of client to send data to */
    /* client: location of server to send data to */
    char *addr_to;
    /* client: self */
    char *addr_from;
    char *user;
    uuid_t uuid;
    /* client: unused */
    bool isauth;
} client_t;

typedef struct {
    res_t res;
    client_t clients[MAXCONN];
    fd_set readfds;
    int maxsd;
    int active;
} server_t;

#endif
