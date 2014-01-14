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
F_SRC	+= main.c
F_SRC	+= eb_getdata.c
F_SRC	+= eb_error.c
SRC		= $(addprefix $(DIR_SRC)/, $(F_SRC))
OBJ		= $(addprefix $(DIR_OBJ)/, $(subst .c,.o,$(SRC)))
F_INC	+= ft_select.h
INC		= $(addprefix $(DIR_INC)/, $(F_INC))

# Classic Rules:
all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJ)
	@echo "\033[31mCompilation de la libft...\033[0m"
	@make -C libft
	@$(CC) -o $@ $^ $(CFLAGS) $(LIB_FT) $(LIB_MLX)
	@echo "\033[33m$(CC) -o \033[4m$@\033[0m\033[33m $^ $(CFLAGS) $(LIB_FT) \
	$(LIB_MLX)\033[0m"

$(addprefix $(DIR_OBJ)/, %.o): %.c $(INC)
	@$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)
	@echo "\033[34m$(CC) -o \033[4m$@\033[0m\033[34m -c $< $(CFLAGS) \
	$(LDFLAGS)\033[0m"

$(DIR_OBJ):
	@echo "create  folder $(DIR_OBJ)/$(DIR_SRC)"
	@/bin/mkdir $(DIR_OBJ)
	@/bin/mkdir $(DIR_OBJ)/$(DIR_SRC)

clean:
	@$(RM) -f $(OBJ)
	@echo "\033[31m$(RM) -f \033[0m\033[41m$(OBJ)\033[0m"
	@$(RM) -rf $(DIR_OBJ)
	@echo "\033[31m$(RM) -rf \033[0m\033[41m$(DIR_OBJ)\033[0m"

fclean: clean
	@$(RM) -f $(NAME)
	@echo "\033[31m$(RM) -f \033[0m\033[41m$(NAME)\033[0m"

re: fclean all

.PHONY: all clean fclean re

# Additional Rules:
gdb:
	cc -g $(FLAGS) $(SRC) -o $(NAME) $(LDFLAGS) $(LIB_FT) $(LIB_MLX)
	gdb $(NAME)
