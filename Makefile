# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/27 17:07:31 by vmercadi          #+#    #+#              #
#    Updated: 2018/02/20 15:19:18 by vmercadi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC = srcs/fractol.c srcs/init.c srcs/display.c srcs/fractals.c srcs/event.c \
      srcs/utils.c srcs/fractals2.c

VERSION_GET := $(shell sw_vers | grep "ProductVersion:" | tail -c 8 | head -c 5)
SIERRA = 10.12
EL_CAPITAN = 10.11
MLX_S = autre/minilibx_macos_sierra/
MLX_ = autre/minilibx_macos/
ifeq ($(VERSION_GET), $(SIERRA))
    MLX = $(MLX_S)
else
    MLX = $(MLX_)
endif

CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
MFLAGS = -framework OpenGL -framework AppKit -L $(MLX) -lmlx -lpthread -O3

INCLUDES = -I includes -I autre/minilibx_macos -I libft

SRCO = $(SRC:%.c=%.o)

LIB = libft/libft.a

.PHONY: all re cleans

all: $(NAME)

$(NAME):$(SRCO)
	@make -s -C $(MLX)
	@make -s -C libft/
	@gcc $(FLAGS) $(LIB) -o $(NAME) $(SRC) $(MFLAGS) $(INCLUDES)
	@echo "\033[32;3m---------------------------------------"
	@echo "Everything compiled nicely and softly !"
	@echo "---------------------------------------\x1b[0m"

it: all
	@./fractol M

clean:
	@rm -rf $(SRCO)
	@make clean -s -C libft/
	@make clean -s -C $(MLX)/

fclean: clean
	@rm -rf $(NAME)
	@make fclean -s -C libft/

re: fclean all

ultra: all clean

reit: re clean
	@./fractol M
