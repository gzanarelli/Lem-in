# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/17 19:38:40 by sifouche     #+#   ##    ##    #+#        #
#    Updated: 2019/01/04 15:17:35 by gzanarel    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = lem-in

SRC = srcs/main.c srcs/queue.c srcs/bfs.c srcs/ed_karp.c srcs/parse_link.c \
	srcs/save_paths.c srcs/moove_ants.c srcs/parse_mgr.c srcs/parse_room.c \
	srcs/read_line.c srcs/room_queue.c srcs/utils.c srcs/parse_ants.c \
	srcs/compare.c srcs/r_ed_karp.c \

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra
LIB = libft/libft.a
H_FILES = libft/libft.h include/lemin.h


all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C libft/
	@echo "\n\033[32;01mlibft.a.. done !\033[00m\n"
	@gcc $(OBJ) $(LIB) -o $@
	@echo "\n\033[32;01m./lem-in.. done !\033[00m\n"

%.o: %.c $(H_FILES)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@make clean -C libft/
	@rm -f $(OBJ)
	@echo "\n\033[31;01m make clean..\033[00m\n"

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)
	@echo "\n\033[31;01m make fclean..\033[00m\n"

re: fclean all

test:
	gcc $(LIB) $(SRC) -o lemintest

norme:
	norminette $(SRC)
	norminette $(H_FILES)

normelibft:
	norminette libft/*.c
	norminette libft/*.h
