/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** automated desc ftw
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include "types.h"

void try_init_client(client_t * const c, const char *ip);
fd_set keep_init_client(const client_t * const c);

#endif
