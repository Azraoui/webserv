# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 19:11:13 by ael-azra          #+#    #+#              #
#    Updated: 2022/07/20 19:06:12 by ael-azra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRC = ./main.cpp ./parser/parser.cpp \
		./networking/httpServer.cpp ./networking/socket.cpp \
		./networking/serverRequest.cpp ./networking/readRequest.cpp \
		./networking/touls.cpp \
		./networking/serverResponse.cpp \
		./cgi/cgi.cpp

INC = ./includes/parser.hpp ./includes/httpServer.hpp \
		./includes/socket.hpp ./includes/serverRequest.hpp \
		./includes/readRequest.hpp \
		./includes/touls.hpp \
		./includes/serverResponse.hpp \
		./cgi/cgi.hpp

FLAG = c++ -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(INC)
	@$(FLAG) $(SRC) -o $(NAME)

run: all
	@ ./webserv

clean:
	@echo -n

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re