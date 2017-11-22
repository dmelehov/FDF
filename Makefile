# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/10 18:32:41 by dmelehov          #+#    #+#              #
#    Updated: 2017/06/10 19:19:13 by dmelehov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= fdf
SRC:= draw_map.c parse_map.c main.c
OBJ = $(SRC:.c=.o)
HEAD = fdf.h
FLAGS = -Wall -Wextra -Werror
LIB = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc -o $(NAME) -lmlx -framework OpenGL -framework AppKit $(OBJ) libft/libft.a
	@echo fdf has been made

%.o: %.c
		gcc $(FLAGS) -c -o  $@ $<	

cleanlib:
	make clean -C ./libft

fcleanlib:
	make fclean -C ./libft

clean: cleanlib
	rm -f $(OBJ)
	@echo *.o have been cleaned.

fclean: clean fcleanlib
	rm -f $(NAME)
	@echo *.a and *.o have been cleaned.

re: fclean all