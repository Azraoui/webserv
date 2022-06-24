/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:51:22 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/24 15:16:23 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/httpServer.hpp"

HttpServer::HttpServer(const std::vector<Vserver> &servers) : _servers(servers) {
    this->_loadServers();
}

HttpServer::~HttpServer(){
}

// methods

void	HttpServer::_loadServers(void)
{
	for (size_t i = 0; i < _servers.size(); i++)
    {
        if (std::find(_open_ports.begin(), _open_ports.end(), _servers[i]._port) != _open_ports.end())
            continue;
        else
        {
            _serverSock.push_back(Socket());
            _serverSock.back().initSocket(_servers[i]._host, _servers[i]._port);
            _serverSock.back().bindSocket();
            _serverSock.back().listenSocket();
            _open_ports.push_back(_servers[i]._port);
        }
    }
};

void    HttpServer::runServers(void)
{
    _selectUtility.clear();
    for (size_t i = 0; i < _serverSock.size(); i++)
    {
        _selectUtility.set_fd(_serverSock[i].getSocket());
        _selectUtility.set_maxFd(_serverSock[i].getSocket());
    }
    while (true) // main loop
    {
        if (!_selectUtility.selectFd())
            continue;
        for (size_t i = 0; i < _serverSock.size(); i++)
        {
            // read

            // reponse
        }
    }
}