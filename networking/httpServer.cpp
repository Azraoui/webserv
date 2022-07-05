/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:51:22 by ael-azra          #+#    #+#             */
/*   Updated: 2022/07/05 02:37:05 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/httpServer.hpp"

std::map<int, std::string> status_code; // first : key | second : string value of error 

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
            _serverSock.back().addServer(i);
            _open_ports.push_back(_servers[i]._port);
        }
    }
};

void fill_map_error_value()
{
    status_code.insert(std::make_pair(200, "OK"));
    status_code.insert(std::make_pair(201, "Created"));
    status_code.insert(std::make_pair(204, "No Content"));
    
    status_code.insert(std::make_pair(301, "Moved Permanently"));
    
    status_code.insert(std::make_pair(400, "Bad Request"));
    status_code.insert(std::make_pair(403, "Forbidden"));
    status_code.insert(std::make_pair(404, "Not Found"));
    status_code.insert(std::make_pair(405, "Method Not Allowed"));
    status_code.insert(std::make_pair(409, "Conflict"));
    status_code.insert(std::make_pair(413, "Request Entity Too Large"));
    status_code.insert(std::make_pair(414, "Request-URI Too Long"));
    
    status_code.insert(std::make_pair(500, "Internal Server Error"));
    status_code.insert(std::make_pair(501, "Not Implemented"));
}

void    HttpServer::runServers(void)
{
    fill_map_error_value(); // FILL STATUS_CODE MAP
    _selectUtility.clear();
    for (size_t i = 0; i < _serverSock.size(); i++)
    {
        _selectUtility.set_fd(_serverSock[i].getSocket());
        _selectUtility.set_maxFd(_serverSock[i].getSocket());
    }
    while (true)
    {
        _selectUtility.setReadAndWriteFD();
        if (!_selectUtility.selectFd())
            continue;
        for (size_t i = 0; i < _serverSock.size(); i++)
        {
            // accept requests
            if (_selectUtility.fd_isset(_serverSock[i].getSocket(), "read"))
                this->_acceptRequest(i);
        }
        for (size_t i = 0; i < _clientsSock.size(); i++)
        {
            // read
            if (_selectUtility.fd_isset(_clientsSock[i].getClientFd(), "read"))
            {
                if (!this->_readRequest(_clientsSock[i].getClientFd()))
                {
                    _clientsSock.erase(_clientsSock.begin() + i);
                    continue;
                }
            }
            // reponse
            if (_selectUtility.fd_isset(_clientsSock[i].getClientFd(), "write"))
            {
                int fd = _clientsSock[i].getClientFd();
                //if (_selectUtility.getRequest(fd).getUriPath().find(".php") != std::string::npos)
                    //cgi cgi( _selectUtility.getRequest(fd));
                if (_selectUtility.getRequest(fd).getifrequestFinished())
                    _response(fd, i);
                // reponse here
            }
        }
    }
}

bool	HttpServer::_readRequest(int clientFd)
{
    if (!_selectUtility.readData(clientFd))
        return false;
    return true;
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
    _selectUtility.set_fd(tmp.getClientFd());
    _selectUtility.set_maxFd(tmp.getClientFd());
    _selectUtility.insertClient(tmp.getClientFd());
}

void	HttpServer::_response(int clientFd, int i)
{
    // _selectUtility.
    // if (_selectUtility.getRequest(clientFd).getMethod() == "GET")
    //     _handleGetMethod(_selectUtility.getRequest(clientFd), _servers[_clientsSock[i].getServerPosition()]);
    std::string test = "HTTP/1.1 200 OK\r\n";
    write(clientFd, test.c_str(), test.size());
    FD_CLR(clientFd, &_selectUtility._master);
    close(clientFd);
    _clientsSock.erase(_clientsSock.begin() + i);
    _selectUtility.erase(clientFd);
}

// void    HttpServer::_handleGetMethod(ReadRequest request, Vserver &server)
// {
    
// }
