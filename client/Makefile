##
## EPITECH PROJECT, 2019
## cpp_rush3_2019
## File description:
## automated desc ftw
##

SRC = $(shell find . -name "*.c")

NAME = myteams_cli
CPL = gcc
CFLAGS = -Wextra -Wall -I../include -I../libs/myteams \
		 `pkg-config --cflags uuid`
LDFLAGS += -L../libs/myteams/myteams -lmyteams \
		   `pkg-config --libs uuid`

DPL = clang
DFLAGS = $(CFLAGS)\
		 -fsanitize=address \
		 -fsanitize=alignment \
		 -fsanitize=enum \
		 -fsanitize=undefined \
		 -g -ggdb
		 # -fsanitize=nullability \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CPL) -o $(NAME) $(OBJ) $(LDFLAGS)

debug: $(SRC)
	$(DPL) $(SRC) $(DFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	find . -name 'vgcore.*' -delete
	find . -name '*.gc*' -delete
	find . -name '*.o' -delete

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

%.o: %.c
	$(CPL) $(CFLAGS) -o $@ -c $<

.PHONY: all clean fclean re
