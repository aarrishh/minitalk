# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/08 21:43:20 by arimanuk          #+#    #+#              #
#    Updated: 2025/06/11 21:19:21 by arimanuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minitalk
SERVER  = server
CLIENT  = client
HEADERS = minitalk.h

PRINTF_DIR = ./ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

SERVER_FILES = server.c
CLIENT_FILES = client.c

SERVER_OBJS = $(SERVER_FILES:.c=.o)
CLIENT_OBJS = $(CLIENT_FILES:.c=.o)

CC = cc
CFLAGS  = -Wall -Werror -Wextra -I$(PRINTF_DIR)
LDFLAGS = -L$(PRINTF_DIR) -lftprintf

all: $(NAME)

$(NAME): $(PRINTF) $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(PRINTF):
	make -C $(PRINTF_DIR)

clean:
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
