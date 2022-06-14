# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/17 10:06:20 by gasselin          #+#    #+#              #
#    Updated: 2022/06/13 13:24:33 by gasselin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_containers

SRCS		= main.cpp vector_tests.cpp map_tests.cpp stack_tests.cpp

OBJS		= $(SRCS:.cpp=.o)
OBJ_DIR		= objs

OBJS_PATH	= $(addprefix $(OBJ_DIR)/, $(OBJS))

CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98 -g

$(NAME): $(OBJ_DIR) $(OBJS_PATH)
	$(CC) $(OBJS_PATH) -o $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
all: $(NAME)

clean :
	@rm -rf $(OBJS_PATH) $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re