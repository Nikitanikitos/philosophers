# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/30 20:34:27 by imicah            #+#    #+#              #
#    Updated: 2020/09/30 20:39:19 by imicah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_three


SRCS    =	srcs/actions.c srcs/check_arguments.c srcs/ft_atoi_itoa.c \
			srcs/ft_put.c srcs/init.c srcs/philo_three.c srcs/utils.c

OBJS    = $(SRCS:%.c=%.o)

HEADERS = -I. -pthread

FLAGS   = -Wall -Wextra -Werror

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJS)
	gcc ${FLAGS} ${HEADERS} ${OBJS} -o ${NAME}

%.o: %.c
	gcc ${FLAGS} ${HEADERS} -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

