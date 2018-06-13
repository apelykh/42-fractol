#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apelykh <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/15 15:10:02 by apelykh           #+#    #+#              #
#    Updated: 2017/10/15 15:10:03 by apelykh          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

EXEC_NAME = fractol
CC = gcc
C_FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -framework OpenGl -framework AppKit
CL_FLAGS = -framework OpenCL

MAC_SYS_VERSION = $(shell sw_vers -productVersion | cut -d '.' -f 1,2)
ifeq ($(MAC_SYS_VERSION), 10.12)
	MLX_DIR = mlx_10.12/
else
	MLX_DIR = mlx_10.11/
endif

LIBFT_DIR = libft/
INCLUDE_DIR = ./includes

LIBMLX = $(addprefix $(MLX_DIR), libmlx.a)
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

SRC_DIR = ./src
SRC_FILES = main.c \
			init.c \
			cl_utils_init.c \
			cl_utils_compile.c \
			cl_utils_exec.c \
			control_events.c \
			params_modification.c \

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:.c=.o)

LOG_CLEAR		= \033[2K
LOG_UP 			= \033[A
LOG_NOCOLOR		= \033[0m
LOG_BLACK		= \033[1;30m
LOG_RED			= \033[1;31m
LOG_GREEN		= \033[1;32m
LOG_YELLOW		= \033[1;33m
LOG_BLUE		= \033[1;34m
LOG_VIOLET		= \033[1;35m
LOG_CYAN		= \033[1;36m
LOG_WHITE		= \033[1;37m

PROJ_LOG_COLOR = $(LOG_GREEN)

.phony: all

all: $(EXEC_NAME)

makelib:
	@ make -C $(MLX_DIR)
	@ make -C $(LIBFT_DIR)

libclean:
	@ make -C $(MLX_DIR) clean
	@ make -C $(LIBFT_DIR) fclean

$(EXEC_NAME): makelib $(OBJ)
	@ $(CC) $(C_FLAGS) $(CL_FLAGS) $(MLX_FLAGS) $(LIBMLX) $(LIBFT) $(OBJ) -o $(EXEC_NAME)
	@ echo "[+] $(PROJ_LOG_COLOR)[$(EXEC_NAME)]$(LOG_NOCOLOR) compiled"

%.o: %.c $(SRC)
	@ $(CC) $(C_FLAGS) -I $(INCLUDE_DIR) -o $@ -c $<

clean: libclean
	@ /bin/rm -f $(OBJ)
	@ echo "[+] $(PROJ_LOG_COLOR)[$(EXEC_NAME)]$(LOG_NOCOLOR) .o files deleted"

fclean: clean
	@ /bin/rm -f $(NAME)
	@ echo "[+] $(PROJ_LOG_COLOR)[$(EXEC_NAME)]$(LOG_NOCOLOR) binary file deleted"

re: fclean all