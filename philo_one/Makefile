# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: iboeters <iboeters@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/15 13:21:22 by iboeters      #+#    #+#                  #
#    Updated: 2021/01/25 11:09:41 by iboeters      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo_one
SRCS	= main.c\
		  philo_one_utils.c
INC		= philo_one.h
OBJS	= ${SRCS:%.c=%.o}
FLAGS	= -Wall -Werror -Wextra -pthread

PINK 	= \033[38;2;255;204;213m
GREY 	= \033[38;2;100;100;100m
BG_GREY	= \033[48;2;38;38;38m
RESET	= \033[0m

all: $(NAME)

%.o:%.cpp
	@echo "$(GREY)$(BG_GREY)Compiling $<$(RESET)"
	@gcc $(FLAGS) -I. $(INC) -c $^ -o $@

$(NAME): $(OBJS)
	@gcc $(FLAGS) $(OBJS) -I. $(INC) -o $(NAME)
	@echo "$(GREY)---------------------------------------------"
	@echo "$(PINK)Run executable: \"./$(NAME)\"$(RESET)"

clean:
	@echo "$(BG_GREY)$(GREY)Deleting $(OBJS)$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(BG_GREY)$(GREY)Deleting $(NAME)$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
