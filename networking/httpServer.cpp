/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:51:22 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/24 23:35:59 by ael-azra         ###   ########.fr       */
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
    while (true)
    {
        if (!_selectUtility.selectFd())
            continue;
        for (size_t i = 0; i < _serverSock.size(); i++)
        {
            // accept requests
            if (_selectUtility.fd_isset(_serverSock[i].getSocket(), "read"))
            {
                this->_acceptRequest(i);
                std::cout << "i was in acceptRequest\n";
            }
        }
        for (size_t i = 0; i < _clientsSock.size(); i++)
        {
            _selectUtility.set_maxFd(_clientsSock[i].getClientFd());
            // read
            if (_selectUtility.fd_isset(_clientsSock[i].getSocket(), "read"))
            {
                if (!this->_readRequest(_clientsSock[i].getSocket()))
                    continue;
            }
            // reponse
            if (_selectUtility.fd_isset(_clientsSock[i].getSocket(), "write"))
            {
                // reponse here
            }
        }
        std::cout << "_clientsSock.size() = " << _clientsSock.size() << std::endl;
    }
}

bool	HttpServer::_readRequest(int socketFd)
{
    std::cout << "i was in readRequest\n";
    if (socketFd)
        return true;
    return false;
}

void	HttpServer::_acceptRequest(int position)
{
    Socket tmp;
    int    option_value;
    
    tmp = _serverSock[position].accept_conncetion();
    if (tmp.getClientFd() < 0)
        return ;
    if (fcntl(tmp.getClientFd(), F_SETFL, O_NONBLOCK) < 0)
       return ;
    if (setsockopt(tmp.getClientFd(), SOL_SOCKET, SO_NOSIGPIPE, &option_value, sizeof(option_value)) < 0)
        return ;
    _clientsSock.push_back(tmp);
}