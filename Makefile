# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/13 18:29:55 by ebaudet           #+#    #+#              #
#    Updated: 2014/01/13 18:29:55 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= wolf3d

# Files
FILES	+= main.c eb_getdata.c eb_error.c eb_mlx.c eb_tools.c eb_draw.c \
		eb_trace.c eb_init_struct.c eb_move.c eb_raytracing.c eb_color.c
SRCS	= $(addprefix src/, $(FILES))
OBJS	= $(SRCS:src/%.c=.obj/%.o)
INC		= -I includes -I libft/includes
# Flags
CFLAGS	= -Wall -Wextra -Werror -pedantic
LIB_FT	= -L libft/ -lft -lm
LIB_MLX	= -I /usr/X11/include -L /usr/X11/lib -lmlx -lXext -lX11
# General options
CC		= gcc
RM		= /bin/rm
# Color
NO_COL	= @printf "\033[0m"
BLUE	= @printf "\033[34m"
YELLOW	= @printf "\033[33m"
GREEN	= @printf "\033[32m"
PURPLE	= @printf "\033[34m\033[40m"

# Classic Rules:
all: $(NAME)
#all: $(DIR_OBJ) $(NAME)

$(NAME): lib_comp create_folder_object $(OBJS)
	$(YELLOW)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -O3 $(INC) $(LIB_FT) $(LIB_MLX)
	$(NO_COL)

.obj/%.o: srcs/%.c
	$(BLUE)
	$(CC) -c $< -o $@ $(CFLAGS) $(INC)
	$(NO_COL)
#	@echo "\033[34m$(CC) -o \033[4m$@\033[0m\033[34m -c $< $(CFLAGS) \
#	$(LDFLAGS)\033[0m"

.obj/%.o: srcs/%.c
	@$(CC) -c $< -o $@ $(FLAGS) $(INC)
	@echo -n .

lib_comp:
	$(PURPLE)
	@echo "Compilation de la libft..."
	make -C libft
	$(NO_COL)

create_folder_object:
	$(GREEN)
	/bin/mkdir -p .obj
	$(NO_COL)

clean:
	@$(RM) -rf .obj
	@echo "\033[31m$(RM) -rf \033[0m\033[41m.obj\033[0m"

fclean: clean
	@$(RM) -f $(NAME)
	@echo "\033[31m$(RM) -f \033[0m\033[41m$(NAME)\033[0m"

color:
	@echo "\033[0mcolor code : 0!\033[0m"
	@echo "\033[1mcolor code : 1!\033[0m"
	@echo "\033[4mcolor code : 4!\033[0m"
	@echo "\033[7mcolor code : 7!\033[0m"
	@echo "\033[30mcolor code : 30!\033[0m"
	@echo "\033[31mcolor code : 31!\033[0m"
	@echo "\033[32mcolor code : 32!\033[0m"
	@echo "\033[33mcolor code : 33!\033[0m"
	@echo "\033[34mcolor code : 34!\033[0m"
	@echo "\033[35mcolor code : 35!\033[0m"
	@echo "\033[36mcolor code : 36!\033[0m"
	@echo "\033[40mcolor code : 40!\033[0m"
	@echo "\033[41mcolor code : 41!\033[0m"
	@echo "\033[42mcolor code : 42!\033[0m"
	@echo "\033[43mcolor code : 43!\033[0m"
	@echo "\033[44mcolor code : 44!\033[0m"
	@echo "\033[45mcolor code : 45!\033[0m"
	@echo "\033[46mcolor code : 46!\033[0m"
	@echo "\033[47mcolor code : 47!\033[0m"

re: fclean all

# Additional Rules:
gdb:
	cc -g $(SRCS) -o $(NAME) $(INC) $(LIB_FT) $(LIB_MLX) $(CFLAGS)
	# gdb $(NAME)

.PHONY: all lib_comp create_folder_object clean fclean re gdb
