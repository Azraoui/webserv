# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 19:11:13 by ael-azra          #+#    #+#              #
#    Updated: 2022/06/13 16:01:13 by ael-azra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRC = ./main.cpp ./parser/parser.cpp \
		./parser/lexer.cpp ./parser/token.cpp

INC = ./webserv.hpp ./parser/parser.hpp

FLAG = c++ -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC)
	$(FLAG) $(SRC) -o $(NAME)

clean:
	echo -n

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re