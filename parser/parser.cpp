/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:00:33 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/14 19:42:40 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser/parser.hpp"

// Constructor and deconstructor

ServersConfig::ServersConfig(std::string contents) : _contents(contents)
{

}

ServersConfig::~ServersConfig()
{

}

// Methods

// private:

void	ServersConfig::_block_parsing(Lexer lex, t_token *token, t_server *server)
{
	while (token != NULL && (token = lex.get_next_token()) != NULL && token->type != token->TOKEN_RBRACE)
	{
		if (token->type == token->TOKEN_LBRACE)
			token = lex.get_next_token();
		else
		{
			std::cerr << "Missing { after server Block\n";
			exit(1);
		}
		while (token->type == token->TOKEN_ID && token->value != "location")
		{
			std::string	key;
			key = token->value;
			std::vector<std::string> v_args;
			while ((token = lex.get_next_token()) != NULL && token->type == token->TOKEN_ID)
			{
				if (token->value[token->value.length() -1] == '\n')
				{
					std::cerr << "Missing ; in end of line\n";
					exit(1);
				}
				v_args.push_back(token->value);
			}
			server->config.insert(std::make_pair(key, v_args));
			if (token->type != token->TOKEN_SEMI)
			{
				std::cerr << "Missing ; in end of line\n";
				exit(1);
			}
			token = lex.get_next_token();
			key.clear();
			v_args.clear();
		}
		if (token->type == token->TOKEN_ID && token->value == "location")
		{
			token = lex.get_next_token();
			if (token->type == token->TOKEN_ID)
			{
				t_location vlocation;
				std::string key;
				std::vector<std::string> value;
				vlocation.path = token->value;
				token = lex.get_next_token();
				if (token->type == token->TOKEN_LSBRACE)
				{
					token = lex.get_next_token();
					while (token->type == token->TOKEN_ID)
					{
						key = token->value;
						while ((token = lex.get_next_token()) != NULL && token->type == token->TOKEN_ID)
						{
							if (token->value[token->value.length() -1] == '\n')
							{
								std::cerr << "Missing ; in end of line\n";
								exit(1);
							}
							value.push_back(token->value);
						}
						vlocation.config.insert(std::make_pair(key, value));
						server->location.push_back(vlocation);
						if (token->type != token->TOKEN_SEMI)
						{
							std::cerr << "Missing ; in end of line\n";
							exit(1);
						}
						token = lex.get_next_token();
						value.clear();
						key.clear();
					}
					if (token->type != token->TOKEN_RSBRACE)
					{
						std::cerr << "Missing to close location with ']'\n";
						exit(1);
					}
					token = lex.get_next_token();
				}
				else
				{
					std::cerr << "Missing [ after path in Location block\n";
					exit(1);
				}
			}
			else
			{
				std::cerr << "Missing path near location\n";
				exit(1);
			}
		}
		if (token->type != token->TOKEN_RBRACE)
		{
			std::cerr << "Missing to close server block with '}'\n";
			exit(1);
		}
	}
}

// public:

void	ServersConfig::parsing(void)
{
	Lexer lex = Lexer(_contents);
	t_token	*token = NULL;
	t_server	*server = NULL;
	while ((token = lex.get_next_token()) != NULL)
	{
		if (token->type == token->TOKEN_ID && (token->value == "server" || token->value == "server\n"))
		{
			_block_parsing(lex, token, server);
			_serverConf.push_back(*server);
		}
		else
		{
			std::cerr << "Error\nUnknown Block " << token->value << std::endl;
			exit(1);
		}
	}
}

void	ServersConfig::print(void)
{
			std::cout << "i was here" << std::endl;
	std::vector<t_server>::iterator it;
	std::vector<t_location>::iterator vit;
	std::map<std::string, std::vector<std::string> >::iterator mit;
	std::vector<std::string>::iterator sit;
	for (it = _serverConf.begin(); it != _serverConf.end(); ++it)
	{
		for (mit = it->config.begin(); mit != it->config.end(); ++mit)
		{
			std::cout << "key = " << mit->first << '\t';
		}
	}
}
// Functions

int	parsingConfigFile(std::string fileName)
{
	std::ifstream configFile(fileName);

	if (configFile)
	{
		std::string contents;
		configFile.seekg(0, std::ios::end);   
		contents.reserve(configFile.tellg());
		configFile.seekg(0, std::ios::beg);
		contents.assign((std::istreambuf_iterator<char>(configFile)),
            std::istreambuf_iterator<char>());

		//------------------------------------
		ServersConfig s = ServersConfig(contents);
		s.parsing();
		//  s.print();
	// 		Lexer lex = Lexer(contents);
	// t_token *token = NULL;
	// 	while ((token = lex.get_next_token()) != NULL)
	// 	{
	// 		std::cout << "type = " << token->type << " " << " value = {" << token->value<<"}" << std::endl;
	// 	}
		configFile.close();
	}
	else
		std::cout << "Error\nFile doesn't exist" << std::endl;
	return (0);
}