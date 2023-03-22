SERVERSRC =	server.c \
			ft_putnbr.c \
			ft_calloc.c\
			ft_itoa.c

CLIENTSRC = client.c \
			ft_atoi.c \
			ft_putnbr.c \
			ft_strncmp.c \
			ft_calloc.c\
		
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