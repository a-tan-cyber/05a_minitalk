# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/31 21:45:04 by amtan             #+#    #+#              #
#    Updated: 2026/01/02 22:51:18 by amtan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC       = cc
CFLAGS   = -Wall -Wextra -Werror
CPPFLAGS = -I include -I libft

NAME   = minitalk
NAME_1 = server
NAME_2 = client

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

SRC_DIR       = src
SRC_BONUS_DIR = src_bonus

SRC_COMMON_MANDATORY = \
	$(SRC_DIR)/protocol_bits.c \
	$(SRC_DIR)/utils.c

SRC_SERVER_MANDATORY = \
	$(SRC_DIR)/server_main.c \
	$(SRC_DIR)/server_signal.c

SRC_CLIENT_MANDATORY = \
	$(SRC_DIR)/client_main.c \
	$(SRC_DIR)/client_send.c

SRC_COMMON_BONUS = \
	$(SRC_BONUS_DIR)/protocol_bits.c \
	$(SRC_DIR)/utils.c

SRC_SERVER_BONUS = \
	$(SRC_DIR)/server_main.c \
	$(SRC_BONUS_DIR)/server_signal_bonus.c

SRC_CLIENT_BONUS = \
	$(SRC_DIR)/client_main.c \
	$(SRC_BONUS_DIR)/client_send_bonus.c

BONUS ?= 0

OBJ_DIR_MANDATORY = obj
OBJ_DIR_BONUS     = obj_bonus

MODE_FILE = .mode

ifeq ($(BONUS),1)
OBJ_ROOT    = $(OBJ_DIR_BONUS)
SRC_COMMON  = $(SRC_COMMON_BONUS)
SRC_SERVER  = $(SRC_SERVER_BONUS)
SRC_CLIENT  = $(SRC_CLIENT_BONUS)
else
OBJ_ROOT    = $(OBJ_DIR_MANDATORY)
SRC_COMMON  = $(SRC_COMMON_MANDATORY)
SRC_SERVER  = $(SRC_SERVER_MANDATORY)
SRC_CLIENT  = $(SRC_CLIENT_MANDATORY)
endif

OBJ_COMMON = $(addprefix $(OBJ_ROOT)/,$(SRC_COMMON:.c=.o))
OBJ_SERVER = $(OBJ_COMMON) $(addprefix $(OBJ_ROOT)/,$(SRC_SERVER:.c=.o))
OBJ_CLIENT = $(OBJ_COMMON) $(addprefix $(OBJ_ROOT)/,$(SRC_CLIENT:.c=.o))

DEPS = $(OBJ_SERVER:.o=.d) $(OBJ_CLIENT:.o=.d)

DEPFLAGS = -MMD -MP -MF $(@:.o=.d) -MT $@

all: $(NAME)

$(NAME): $(NAME_1) $(NAME_2)

$(MODE_FILE): FORCE
	@printf '%s\n' '$(BONUS)' | cmp -s - $@ 2>/dev/null \
	|| printf '%s\n' '$(BONUS)' > $@

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

$(NAME_1): $(MODE_FILE) $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o $@

$(NAME_2): $(MODE_FILE) $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $@

$(OBJ_ROOT)/%.o: %.c $(MODE_FILE)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR_MANDATORY) $(OBJ_DIR_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_1) $(NAME_2) $(MODE_FILE)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus:
	$(MAKE) BONUS=1 all

FORCE:

-include $(DEPS)

.PHONY: all clean fclean re bonus FORCE $(NAME)
