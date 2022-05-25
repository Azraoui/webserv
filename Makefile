# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 19:11:13 by ael-azra          #+#    #+#              #
#    Updated: 2022/05/23 19:11:14 by ael-azra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRC = ./main.cpp
INC = ./webserv.hpp


all: $(NAME)

$(NAME): $(SRC)
	g++ $(SRC) -o $(NAME)

clean:
	echo -n

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re