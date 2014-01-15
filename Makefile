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

# General options
CC		= gcc
RM		= /bin/rm
# Flags
CFLAGS	= -Wall -Wextra -Werror -pedantic
LDFLAGS	= -I $(DIR_INC)
LIB_FT	= -I libft/includes -L libft/ -lft
LIB_MLX	= -L /usr/X11/lib -lmlx -lXext -lX11
# Directories
DIR_INC	= includes
DIR_SRC	= src
DIR_OBJ	= .obj
# Files
NAME	= wolf3d
F_SRC	+= main.c eb_getdata.c eb_error.c eb_mlx.c eb_tools.c eb_draw.c \
			eb_trace.c eb_init_struct.c eb_move.c
# F_SRC	+= eb_getdata.c
# F_SRC	+= eb_error.c
# F_SRC	+= eb_mlx.c
SRC		= $(addprefix $(DIR_SRC)/, $(F_SRC))
OBJ		= $(addprefix $(DIR_OBJ)/, $(notdir $(subst .c,.o,$(SRC))))
F_INC	+= wolf3d.h
INC		= $(addprefix $(DIR_INC)/, $(F_INC))
# Color
NO_COL	= @printf "\033[0m"
BLUE	= @printf "\033[34m"
YELLOW	= @printf "\033[33m"
#GREEN	= @printf "\033[32m"
PURPLE	= @printf "\033[34m\033[40m"

# Classic Rules:
all: gdb
#all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJ)
	$(PURPLE)
	@echo "Compilation de la libft..."
	make -C libft
	$(NO_COL)
	$(YELLOW)
	$(CC) -o $@ -O3 $^ $(CFLAGS) $(LIB_FT) $(LIB_MLX)
	$(NO_COL)

$(OBJ): $(SRC) $(INC)
	$(BLUE)
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)
	$(NO_COL)
#	@echo "\033[34m$(CC) -o \033[4m$@\033[0m\033[34m -c $< $(CFLAGS) \
#	$(LDFLAGS)\033[0m"

$(DIR_OBJ):
	$(GREEN)
	/bin/mkdir $(DIR_OBJ)
	$(NO_COL)

clean:
	$(RM) -f $(OBJ)
	@echo "\033[31m$(RM) -f \033[0m\033[41m$(OBJ)\033[0m"
	$(RM) -rf $(DIR_OBJ)
	@echo "\033[31m$(RM) -rf \033[0m\033[41m$(DIR_OBJ)\033[0m"

fclean: clean
	$(RM) -f $(NAME)
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

.PHONY: all clean fclean re gdb

# Additional Rules:
gdb:
	cc -g $(SRC) -o $(NAME) $(LDFLAGS) $(LIB_FT) $(LIB_MLX) $(CFLAGS)
#	gdb $(NAME)
