/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:55:45 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/14 19:19:29 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "lexer.hpp"
#include <fstream>
#include <streambuf>
#include <string>
#include <map>
#include <vector>

typedef struct s_location
{
	std::string	path;
	std::map<std::string, std::vector<std::string> > config;
} t_location;

typedef struct s_server
{
	std::map<std::string, std::vector<std::string> > config;
	std::vector<t_location> location;
} t_server;

class ServersConfig
{
	private:
		std::string	_contents;
		std::vector<t_server> _serverConf;
		void		_block_parsing(Lexer lex, t_token *token, t_server *server);
	public:
		ServersConfig(std::string contents);
		~ServersConfig();
		// Methods
		void	parsing(void);
		void	print(void);
};
int	parsingConfigFile(std::string fileName);