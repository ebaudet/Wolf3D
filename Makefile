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
UNAME_S	:= $(shell uname -s)

# Files
FILES	= main.c eb_getdata.c eb_error.c eb_mlx.c eb_tools.c eb_draw.c \
		eb_trace.c eb_init_struct.c eb_move.c eb_raytracing.c eb_color.c
SRCS	= $(addprefix src/, $(FILES))
OBJS	= $(SRCS:src/%.c=.obj/%.o)
MLX_DIR	?= mlx
INC		= -I includes -I libft/includes
# INC_MLX = -I /usr/X11/include
# Flags
CFLAGS	= -Wall -Wextra -Werror -pedantic
LIB_FT	= -L libft/ -lft -lm
LIB_MLX	=
# General options
CC		= gcc
RM		= /bin/rm
# Color
NO_COL	= @printf "\033[0m"
BLUE	= @printf "\033[34m"
YELLOW	= @printf "\033[33m"
GREEN	= @printf "\033[32m"
PURPLE	= @printf "\033[34m\033[40m"

ifeq ($(UNAME_S),Darwin)
	INC		+= -isystem $(MLX_DIR) -I /usr/local/include -I /opt/homebrew/include -I /opt/X11/include
	INC_MLX	= -L $(MLX_DIR) -L /usr/local/lib -L /opt/homebrew/lib \
			  -lmlx -framework OpenGL -framework AppKit
else
	INC		+= -isystem $(MLX_DIR) -I /usr/X11/include -I /usr/local/include
	INC_MLX	= -L $(MLX_DIR) -L /usr/X11/lib -lmlx -lXext -lX11
endif

# Classic Rules:
all: $(NAME)
#all: $(DIR_OBJ) $(NAME)

$(NAME): lib_comp mlx_comp create_folder_object $(OBJS)
	$(YELLOW)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -O3 $(INC) $(INC_MLX) $(LIB_FT) $(LIB_MLX)
	$(NO_COL)

.obj/%.o: src/%.c
	$(BLUE)
	$(CC) -c $< -o $@ $(CFLAGS) $(INC)
	$(NO_COL)
	@echo "\033[34m$(CC) -o \033[4m$@\033[0m\033[34m -c $< $(CFLAGS) \
	$(INC)\033[0m"

# .obj/%.o: src/%.c
# 	$(CC) -c $< -o $@ $(FLAGS) $(INC)
# 	@echo -n .

lib_comp:
	$(PURPLE)
	@echo "Compilation de la libft..."
	make -C libft
	$(NO_COL)

mlx_comp:
	@if [ -d "$(MLX_DIR)" ]; then \
		echo "\n > \033[36mMiniLibX\033[m compiling\n"; \
		$(MAKE) -C $(MLX_DIR); \
	else \
		echo "\n > \033[33mMiniLibX not found in $(MLX_DIR)\033[m"; \
	fi

create_folder_object:
	$(GREEN)
	/bin/mkdir -p .obj
	$(NO_COL)

clean:
	@$(RM) -rf .obj
	@echo "\033[31m$(RM) -rf \033[0m\033[41m.obj\033[0m"

fclean: clean
	@$(RM) -f $(NAME)
	@make clean -C $(MLX_DIR);
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
	cc -g $(SRCS) -o $(NAME) $(INC) $(INC_MLX) $(LIB_FT) $(LIB_MLX) $(CFLAGS)
	# gdb $(NAME)

.PHONY: all lib_comp create_folder_object clean fclean re gdb
