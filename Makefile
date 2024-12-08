# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/08 19:56:26 by gaesteve          #+#    #+#              #
#    Updated: 2024/12/08 20:06:01 by gaesteve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program file name
NAME	= cub3d

# Mode
BONUS = 0

# Compiler and compilation flags
CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -g3

# Minilibx
MLX_PATH	= ./library/minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

# Libft
LIBFT_PATH	= ./library/libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Sources
SRC_PATH = ./code_source/
SRC		= 	main.c \
			intro/main_menu.c \
			intro/intro.c \
			init/init_data.c \
			init/init_mlx.c \
			init/init_textures.c \
			parsing/check_args.c \
			parsing/parse_data.c \
			parsing/get_file_data.c \
			parsing/check_map.c \
			parsing/check_map_utils.c \
			parsing/check_textures.c \
			parsing/create_map.c \
			parsing/fill_color.c \
			parsing/utils.c \
			render/render.c \
			render/texture.c \
			render/raycasting.c \
			render/minimap_render.c \
			render/minimap_image.c \
			movement/player_dir.c \
			movement/input.c \
			movement/player_move.c \
			movement/player_position.c \
			movement/player_rotate.c \
			exit/error.c \
			exit/exit.c \
			exit/free.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# Includes
INC			=	-I ./includes/\
				-I ./library/libft/\
				-I ./library/minilibx-linux/

# Main rule
all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

# Objects directory rule
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/init
	@mkdir -p $(OBJ_PATH)/intro
	@mkdir -p $(OBJ_PATH)/parsing
	@mkdir -p $(OBJ_PATH)/movement
	@mkdir -p $(OBJ_PATH)/render
	@mkdir -p $(OBJ_PATH)/debug
	@mkdir -p $(OBJ_PATH)/exit
	@echo "Creating object directories..."

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -DBONUS=$(BONUS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	@echo "Compilation en cours..."
	@$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm
	@echo "$(NAME) est prêt !"

# Libft rule
$(LIBFT):
	@echo "Building libft..."
	@make -sC $(LIBFT_PATH)

# MLX rule
$(MLX):
	@echo "Building minilibx..."
	@make -sC $(MLX_PATH)

bonus:
	@make all BONUS=1

# Clean up build files rule
clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_PATH)
	@make -sC $(LIBFT_PATH) clean >/dev/null
	@make -sC $(MLX_PATH) clean >/dev/null

# Remove program executable
fclean: clean
	@echo "Removing executable..."
	@rm -f $(NAME)
	@make -sC $(LIBFT_PATH) fclean >/dev/null

# Clean + remove executable
re: fclean all

.PHONY: all re clean fclean bonus


