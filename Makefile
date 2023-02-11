# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/09 12:15:19 by mle-biha          #+#    #+#              #
#    Updated: 2023/02/09 12:15:45 by mle-biha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --------------------------- Constant --------------------------- #

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror -I.
NAME				= server
CLIENT_NAME			= client
NAME_BONUS			= server_bonus
CLIENT_NAME_BONUS 	= client_bonus
INCLUDE				= -I $(DIR_LIBFT)
LIB					= -L $(DIR_LIBFT) -lft
	
# --------------------------- Sources --------------------------- #
	
# Files	
DIR_LIBFT			= Libft
LIBFT				= Libft/libft.a
		
# Sources and objects
SRC_SERVER			= server.c
SRC_CLIENT			= client.c
OBJ_SERVER			= $(SRC_SERVER:.c=.o)
OBJ_CLIENT			= $(SRC_CLIENT:.c=.o)

SRC_SERVER_BONUS	= server_bonus.c
SRC_CLIENT_BONUS	= client_bonus.c
OBJ_SERVER_BONUS	= $(SRC_SERVER_BONUS:.c=.o)
OBJ_CLIENT_BONUS	= $(SRC_CLIENT_BONUS:.c=.o)

OBJS				= $(OBJ_SERVER) $(OBJ_CLIENT)
OBJS_BONUS			= $(OBJ_SERVER_BONUS) $(OBJ_CLIENT_BONUS)

# --------------------------- Colors --------------------------- #

GREEN				= \e[1;32m
YELLOW				= \e[1;33m
BLUE				= \e[1;34m
MAGENTA				= \e[1;35m
NO_COLOR			= \e[0m

# --------------------------- Rules --------------------------- #

all: $(NAME) $(CLIENT_NAME) $(LIBFT)

$(LIBFT):
	@echo "\n$(MAGENTA)Creating Libft...$(NO_COLOR)"
	@make -C $(DIR_LIBFT) --no-print-directory
	@echo "$(GREEN)Libft OK !$(NO_COLOR)\n"
	
$(NAME): $(OBJ_SERVER) $(LIBFT)
	@echo "$(MAGENTA)Creating Server...$(NO_COLOR)"	
	@$(CC) $(CFLAGS) $(OBJ_SERVER) $(INCLUDE) $(LIB) -o $(NAME)
	@echo "$(GREEN)Server OK !$(NO_COLOR)\n"

$(CLIENT_NAME): $(OBJ_CLIENT) $(LIBFT)
	@echo "$(MAGENTA)Creating Client...$(NO_COLOR)"	
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) $(INCLUDE) $(LIB) -o $(CLIENT_NAME)
	@echo "$(GREEN)Client OK !$(NO_COLOR)\n"

$(NAME_BONUS): $(OBJ_SERVER_BONUS) $(LIBFT)
	@echo "$(BLUE)Creating Server Bonus...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) $(INCLUDE) $(LIB) -o $(NAME_BONUS)
	@echo "$(GREEN)Server Bonus OK !$(NO_COLOR)\n"

$(CLIENT_NAME_BONUS): $(OBJ_CLIENT_BONUS) $(LIBFT)
	@echo "$(BLUE)Creating Client Bonus...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) $(INCLUDE) $(LIB) -o $(CLIENT_NAME_BONUS)
	@echo "$(GREEN)Client Bonus OK !$(NO_COLOR)\n"

bonus: $(NAME_BONUS) $(CLIENT_NAME_BONUS) $(LIBFT)

%.o: %.c
	@$(CC) $(INCLUDE) -o $@ -c $< $(CFLAGS)

clean:
	@echo "\n$(YELLOW)Cleaning objects !$(NO_COLOR)"
	@rm -f $(OBJS) $(OBJS_BONUS)
	@make -C $(DIR_LIBFT) --no-print-directory clean
	@echo "$(GREEN)Objects cleaned !$(NO_COLOR)\n"
	
fclean: clean
	@echo "$(YELLOW)Cleaning everything !$(NO_COLOR)"
	@rm -f $(NAME) $(CLIENT_NAME) $(NAME_BONUS) $(CLIENT_NAME_BONUS)
	@make -C $(DIR_LIBFT) --no-print-directory fclean
	@echo "$(GREEN)Everything cleaned !$(NO_COLOR)\n"

re: fclean all

.PHONY : clean fclean re 