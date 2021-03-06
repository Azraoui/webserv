/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:55:45 by ael-azra          #+#    #+#             */
/*   Updated: 2022/07/22 20:39:10 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <iostream>
#include <streambuf>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <array>
#include <stack>
#define INVALID_DIRECTIVE -2


struct Location
{
	std::string                                         _locationPath;

	std::string                                         _rootPath;
	std::string                                         _autoindex;
	std::string                                         _maxBodySize;
	std::string                                         _uploadPath;

	std::map<std::string, std::string>                  _cgi;
	std::vector<std::string>                            _index;
	std::vector<std::string>                            _serverNames;
	std::map<std::string, std::string>      _errorPage;
	std::pair<std::string, std::string>                 _redirection;
	std::set<std::string>                           	_allowed_methods;
};

struct Vserver
{
		std::vector<std::string>                            _serverNames;
		std::vector<Location>                               _locations;

		std::string                                         _locationPath;
		std::string                                         _rootPath;
		std::string                                         _autoindex;
		std::string                                         _maxBodySize;
		std::string                                         _uploadPath;
		
		std::map<std::string, std::string>      _errorPage;
		std::pair<std::string, std::string>                 _redirection;

		std::vector<std::string>                            _index;
		std::set<std::string>                           	_allowed_methods;

		std::set<std::pair<std::string, int> >				_listen;
		size_t                                              _port;
		std::string                                         _host;
};

void					exitError(std::string const &err);
std::vector<Vserver>	parsingConfigFile(std::string const &fileName);
bool					isEqual(const std::pair<std::string, int> &element);