# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/08 19:56:26 by gaesteve          #+#    #+#              #
#    Updated: 2024/12/15 20:53:28 by gaesteve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

BONUS = 0

CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -g3

MLX_PATH	= ./library/minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH	= ./library/libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

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

OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

INC			=	-I ./includes/\
				-I ./library/libft/\
				-I ./library/minilibx-linux/

all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)/init \
		$(OBJ_PATH)/intro \
		$(OBJ_PATH)/parsing \
		$(OBJ_PATH)/movement \
		$(OBJ_PATH)/render \
		$(OBJ_PATH)/debug \
		$(OBJ_PATH)/exit

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -DBONUS=$(BONUS) -c $< -o $@ $(INC) 2>/dev/null

$(NAME): $(OBJS)
	@echo "Compilation en cours..."
	@$(CC) $(CFLAGS) -DBONUS=$(BONUS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm
ifeq ($(BONUS), 1)
	@echo "\033[1;32m✅ Bonus compilation complete! $(NAME) BONUS is ready!\033[0m"
else
	@echo "\033[1;34m✅ Normal compilation complete! $(NAME) is ready!\033[0m"
endif

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(MLX):
	@make -sC $(MLX_PATH) >/dev/null 2>&1


bonus:
	@make --no-print-directory all BONUS=1

clean:
	@echo "\033[1;33m🧹 Cleaning object files...\033[0m"
	@rm -rf $(OBJ_PATH)
	@make -sC $(LIBFT_PATH) clean >/dev/null
	@make -sC $(MLX_PATH) clean >/dev/null
	@echo "\033[1;32m✅ Clean complete.\033[0m"

fclean: clean
	@echo "\033[1;31m🚮 Removing executable...\033[0m"
	@rm -f $(NAME)
	@make -sC $(LIBFT_PATH) fclean >/dev/null
	@echo "\033[1;32m✅ Full clean complete.\033[0m"

re: fclean all

.PHONY: all re clean fclean bonus
