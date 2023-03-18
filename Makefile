NAME = client

SRC =	client.c \ server.c
		
OBJS_DIR = objs/
OBJS = $(SRC:%.c=%.o)
OBJS := $(OBJS:%=$(OBJS_DIR)%)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  -o $(NAME)

$(OBJS_DIR)%.o:%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re