# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suhelal <suhelal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 14:41:54 by suhelal           #+#    #+#              #
#    Updated: 2024/09/05 14:28:27 by suhelal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

CFLAGS	= -Wall -Wextra -Werror -pthread

NAME	= philo

CFILES 	   = main.c init_data.c error_check/check_arg.c routine.c error_check/arg_func.c error_check/check_error.c \
error_check/arg_utils.c create_philo.c check_death_meal.c routine_utils.c \

all: $(NAME)

$(NAME): $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME)

clean: clean
	rm -f $(NAME) 

fclean: clean
	rm -f $(NAME)

re: clean $(NAME)
