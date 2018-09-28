# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/09 17:06:46 by mmoya        #+#   ##    ##    #+#        #
#    Updated: 2018/09/28 19:44:54 by mmoya       ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #
NAME = libft.a

HEAD = libft.h

FLAG = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c ft_memalloc.c ft_memccpy.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memrchr.c \
ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c \
ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_striter.c \
ft_striteri.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
ft_strncmp.c ft_strncpy.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strstr.c \
ft_tolower.c ft_toupper.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
ft_strtrim.c ft_strsplit.c ft_lstnew.c ft_lstiter.c ft_lstadd.c ft_lstmap.c \
ft_lstdel.c ft_lstdelone.c ft_isblank.c ft_isupper.c ft_islower.c \
ft_strndup.c ft_swap.c ft_print2dstr.c ft_sqrt.c ft_countdigit.c ft_ltoa.c \
ft_strrealloc.c ft_strsplittrim.c ft_strsplittrimq.c get_next_line.c \
ft_strsplitq.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEAD) Makefile
	ar rcs $(NAME) $(OBJ)

%.o: $(SRCS)%.c
	gcc $(FLAG) -c $*.c

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
