##
## EPITECH PROJECT, 2018
## CPool_Day07_2018
## File description:
## standard makefile
##

all: server client

server: ./server/myteams_server
	cp ./server/myteams_server .

./server/myteams_server: ./server/
	$(MAKE) -C ./server/

client: ./client/myteams_cli
	cp ./client/myteams_cli.

./client/myteams_cli: ./client/
	$(MAKE) -C ./client/

clean:
	$(MAKE) -C ./server/ clean
	$(MAKE) -C ./client/ clean

fclean:
	$(MAKE) -C ./server/ fclean
	$(MAKE) -C ./client/ fclean

debug:
	$(MAKE) -C ./server/ debug
	cp server/myteams_server .
	$(MAKE) -C /client/ debug
	cp server/myteams_client .

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all debug clean fclean re
