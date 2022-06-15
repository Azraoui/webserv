/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:00:33 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/15 13:33:16 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser/parser.hpp"

void	exitError(std::string const &err)
{
	std::cerr << err << std::endl;
	exit(EXIT_FAILURE);
}

std::vector<std::string>	split(std::string const &line, char del = ' ')
{
	std::vector<std::string> ret;
	std::stringstream ss(line);
	std::string	tmp;
	while (std::getline(ss, tmp, del))
	{
		if (tmp == " " || tmp.empty())
			continue;
		ret.push_back(tmp);
	}
	return ret;
}

int	getDirective(std::string const &token)
{
	std::array<std::pair<std::string, Directives>, 17> direct =
	{
        std::make_pair("port", Directives::PORT),
        std::make_pair("host", Directives::HOST),
        std::make_pair("server_name", Directives::SERVER_NAME),
        std::make_pair("error_page", Directives::ERROR_PAGE),
        std::make_pair("max_body_size", Directives::MAX_FILE_SIZE),
        std::make_pair("time_out", Directives::TIME_OUT),
        std::make_pair("location", Directives::LOCATION),
        std::make_pair("return", Directives::REDIRECT),
        std::make_pair("cgi", Directives::CGI),
        std::make_pair("root", Directives::ROOT),
        std::make_pair("allowed_method", Directives::ALLOWED_METHODS),
        std::make_pair("index", Directives::INDEX),
        std::make_pair("auto_index", Directives::AUTO_INDEX),
        std::make_pair("auth_basic", Directives::AUTH_BASIC),
        std::make_pair("upload_store", Directives::UPLOAD),
        std::make_pair("]", Directives::LOCATION_END),
        std::make_pair("}", Directives::SERVER_END),
	};
	for (size_t i ; i < direct.size(); i++)
	{
		if (token == direct[0].first)
			return direct[1].second;
	}
	return INVALID_DIRECTIVE;
}

std::vector<ServerConfig> parsingConfigFile(std::string const &fileName)
{
	std::ifstream 				configFile(fileName);
	std::vector<ServerConfig>	_serverConfig;
	std::stack<std::string>		curlyBracket;
	std::stack<std::string>		squareBracket;
	bool	insideServer = false;
	std::string					line;
	int	directive;
	if (configFile)
	{
		while (std::getline(configFile, line))
		{
			if (line.empty())
				continue;
			std::vector<std::string> tokens = split(line);
			if (tokens.size())
			{
				directive = getDirective(tokens[0]);
				if (tokens[0] == "server")
				{
					if (!curlyBracket.empty() || !squareBracket.empty())
						exitError("Syntax Error in config file");
					if (tokens.size() == 2 && tokens[1] == "{")
					{
						insideServer = true;
						curlyBracket.push("{");
					}
					else
						exitError("Missing '{' near " + tokens[0]);
				}
				else if (!insideServer)
					exitError("Unknown block < " + tokens[0] + " >");
				else
				{
					switch (directive)
					{
					case Directives:PORT :
						/* code */
						break;
					
					default:
						break;
					}
				}
			}
		}

		//------------------------------------

		configFile.close();
	}
	else
		exitError("Error\nFile doesn't exist");

	return _serverConfig;
}