# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbyrne <mbyrne@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/31 21:22:50 by mbyrne            #+#    #+#              #
#    Updated: 2025/02/04 09:52:29 by mbyrne           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFTDIR = libft

LIBFT = $(LIBFTDIR)/libft.a
SRCS = 	pipex.c process.c path.c utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFTDIR)
	rm -rf $(OBJS)
fclean: clean
	make fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re