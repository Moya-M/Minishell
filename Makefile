# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/01/26 19:06:36 by mmoya        #+#   ##    ##    #+#        #
#    Updated: 2018/09/27 18:13:29 by mmoya       ###    #+. /#+    ###.fr      #
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

.PHONY : all clean fclean re lib

all: lib $(NAME)

$(NAME): $(OBJ) $(LIBPATH)$(LIB) Makefile
	gcc $(FLAGS) $(HEAD) $(LIBPATH)$(LIB) $(OBJ) -o $(NAME)

lib:
	@$(MAKE) -C $(LIBPATH)

%.o: $(SRCPATH)%.c ./includes/minishell.h Makefile
	gcc $(FLAGS) $(HEAD) -c $< -o $@

clean:
	/bin/rm -f $(OBJ)
	$(MAKE) fclean -C $(LIBPATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
