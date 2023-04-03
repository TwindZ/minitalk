# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emlamoth <emlamoth@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 15:19:36 by emlamoth          #+#    #+#              #
#    Updated: 2023/04/03 15:19:37 by emlamoth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVERSRC =	server.c \
			minitalk_utils.c	\

CLIENTSRC = client.c \
			minitalk_utils.c	\

SERVEROBJS = $(SERVERSRC:%.c=%.o)
CLIENTOBJS = $(CLIENTSRC:%.c=%.o)

CLIENT = client
SERVER = server

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(CLIENT) $(SERVER)

$(NAME) :

$(CLIENT): $(CLIENTOBJS)
	$(CC) $(CFLAGS) $(CLIENTOBJS)  -o $(CLIENT)

$(SERVER): $(SERVEROBJS)
	$(CC) $(CFLAGS) $(SERVEROBJS)  -o $(SERVER)

clean:
	rm -rf $(SERVEROBJS)
	rm -rf $(CLIENTOBJS)

fclean: clean
	rm -f $(CLIENT)
	rm -f $(SERVER)

bonus: all

re: fclean all

.PHONY: all clean fclean bonus re