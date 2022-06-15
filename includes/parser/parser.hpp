/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:55:45 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/15 13:26:07 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "lexer.hpp"
#include <fstream>
#include <streambuf>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <array>

#define INVALID_DIRECTIVE -2

enum	Directives
{
	PORT,
	HOST,
	SERVER_NAME,
	ERROR_PAGE,
	MAX_FILE_SIZE,
	TIME_OUT,
	LOCATION,
	REDIRECT,
	CGI,
	ROOT,
	ALLOWED_METHODS,
	INDEX,
	AUTO_INDEX,
	AUTH_BASIC,
	UPLOAD,
	LOCATION_END,
	SERVER_END,
};

struct	ServerConfig {

    std::string _port;
    std::string _host;
    std::string _server_name;
    std::string _max_file_size;
    std::string _time_out;
    std::string _cgi;
    std::string _root;
    std::string _auto_index;
    std::string _loc_path;
    std::string _upload_store;

    std::map<std::string, std::string> _error_page;
    std::pair<std::string, std::string> _redirect;
    std::vector<std::string> _index;
    std::set<std::string> _allowed_method;

    std::vector<ServerConfig> _location;
};

void	exitError(std::string const &err);
std::vector<ServerConfig>	parsingConfigFile(std::string const &fileName);