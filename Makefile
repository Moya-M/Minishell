# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/01/26 19:06:36 by mmoya        #+#   ##    ##    #+#        #
#    Updated: 2018/09/25 23:37:01 by mmoya       ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = minishell

SRCPATH = ./srcs/

SRCS =	main.c \
		builtin.c \
		env.c \
		error.c \
		setenv.c \
		execute.c \
		expansions.c

OBJ = $(SRCS:.c=.o)

HEAD = -I ./includes/

FLAGS = -Wall -Wextra -Werror

LIBPATH = ./libft/

LIB = libft.a

MSG_LIB= "\033[1;42m┎┰─────╢ LIBFT ║\033[0m"

MSG_LIBEND= "\033[1;42m┖┸─────╢ END ║\033[0m"

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(LIBPATH)$(LIB) $(OBJ)
	@gcc $(FLAGS) $(HEAD) $(LIBPATH)$(LIB) $(OBJ) -o $(NAME)
	@echo "\033[1;44m┌──────────────────────────────┐\033[0m"
	@echo "\033[1;44m│        minishell DONE        │\033[0m"
	@echo "\033[1;44m└──────────────────────────────┘\033[0m"

$(LIBPATH)$(LIB):
	@echo $(MSG_LIB)
	@$(MAKE) -C $(LIBPATH)

%.o: $(SRCPATH)%.c ./includes/minishell.h
	@echo "\033[1mCompiled :	\033[34m\"$*\"\033[0m"
	@gcc $(FLAGS) $(HEAD) -c $< -o $@

clean:
	@/bin/rm -f $(OBJ)
	@echo "\033[1mRemoved :  \033[31m\"*.o\"\033[0m"
	@echo $(MSG_LIB)
	@$(MAKE) fclean -C $(LIBPATH)
	@echo $(MSG_LIBEND)

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[1mRemoved :  \033[31m\"$(NAME)\"\033[0m"

re: fclean all
