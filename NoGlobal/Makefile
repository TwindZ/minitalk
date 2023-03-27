SERVERSRC =	server.c \
			minitalk_utils.c	\

CLIENTSRC = client.c \
			minitalk_utils.c	\

SERVEROBJS = $(SERVERSRC:%.c=%.o)
CLIENTOBJS = $(CLIENTSRC:%.c=%.o)


CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: client server

client: $(CLIENTOBJS)
	$(CC) $(CFLAGS) $(CLIENTOBJS)  -o client

server: $(SERVEROBJS)
	$(CC) $(CFLAGS) $(SERVEROBJS)  -o server

clean:
	rm -rf $(SERVEROBJS)
	rm -rf $(CLIENTOBJS)

fclean: clean
	rm -f client
	rm -f server

re: fclean all

.PHONY: all clean fclean bonus re