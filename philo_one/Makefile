# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: iboeters <iboeters@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/15 13:21:22 by iboeters      #+#    #+#                  #
#    Updated: 2021/06/28 15:30:00 by iboeters      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo_one
SRCS	= philosophers.c\
		  philosophers_utils.c\
		  eat_sleep_think_repeat.c\
		  valid_input.c\
		  threading.c\
		  check_dead.c
INC		= philosophers.h
OBJS	= ${SRCS:%.c=%.o}
FLAGS	= -Wall -Werror -Wextra -pthread

PINK 	= \033[38;2;255;204;213m
GREY 	= \033[38;2;100;100;100m
BG_GREY	= \033[48;2;38;38;38m
RESET	= \033[0m

all: $(NAME)

%.o:%.c
	@echo "$(GREY)$(BG_GREY)Compiling $<$(RESET)"
	@gcc $(FLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	@gcc $(FLAGS) $(OBJS) -I $(INC) -o $(NAME)
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
