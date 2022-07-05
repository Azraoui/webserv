/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:51:22 by ael-azra          #+#    #+#             */
/*   Updated: 2022/07/05 18:40:39 by yer-raki         ###   ########.fr       */
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
                if (_selectUtility.getRequest(fd).getifrequestFinished())
                {
                    _responseServer(fd, i);
                }
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
void    HttpServer::_handling_method_allowed_error(ReadRequest request, Vserver &server)
{
    int pos_loc;
    Location loc;
    std::set<std::string>::iterator it;
    
    pos_loc = matchLocationAndUri(server._locations, request.getUriPath());
    loc = server._locations[pos_loc];
    for (it = loc._allowed_methods.begin(); it != loc._allowed_methods.end(); it++)
    {
        // std::cout << "--------------" << std::endl;
        // std::cout << *it << " | " << request.getMethod() << std::endl;
        if (*it == request.getMethod())
            return;
        // std::cout << "--------------" << std::endl;
    }
    for (it = server._allowed_methods.begin(); it != server._allowed_methods.end(); it++)
    {
        // std::cout << "--------------------------------------------------------\n" << std::endl;
        // std::cout << "--------------" << std::endl;
        // std::cout << *it << " | " << request.getMethod() << std::endl;
        if (*it == request.getMethod())
            return;
        // std::cout << "--------------" << std::endl;
    }
    request.setIsBadRequest(std::make_pair(true, 405));
    std::cout << "ERROR 405 !!" << std::endl;
}
void	HttpServer::_responseServer(int clientFd, int i)
{
    _selectUtility.getRequest(clientFd).handling_response_errors();
    _handling_method_allowed_error(_selectUtility.getRequest(clientFd), _servers[_clientsSock[i].getServerPosition()]);
    
    if (_selectUtility.getRequest(clientFd).getMethod() == "GET")
        _handleGetMethod(_selectUtility.getRequest(clientFd), _servers[_clientsSock[i].getServerPosition()]);
    // std::string msg = "HTTP/1.1 500 " + status_code.at(500) + "\n" + "Content-Type: text/html\n"+ "Content-Length: " + std::to_string(errorPage("500").size()) + "\n\n" + errorPage("500");
    // write(clientFd, msg.c_str(), msg.size());
    // ServerResponse response(_selectUtility.getRequest(clientFd), _servers[_clientsSock[i].getServerPosition()]);
    // _selectUtility.getRequest(clientFd)
    // if (_selectUtility.getRequest(clientFd).getMethod() == "GET")
    //     _handleGetMethod(_selectUtility.getRequest(clientFd), _servers[_clientsSock[i].getServerPosition()]);
    _selectUtility.getRequest(clientFd).handling_response_errors();
    std::string test = "HTTP/1.1 301 OK\nLocation: https://google.com/\n\n";
    write(clientFd, test.c_str(), test.size());
    FD_CLR(clientFd, &_selectUtility._master);
    close(clientFd);
    _clientsSock.erase(_clientsSock.begin() + i);
    _selectUtility.erase(clientFd);
}

void    HttpServer::_handleGetMethod(ReadRequest request, Vserver &server)
{
    int i;
    std::string rootAndUri;

    // server._locations[i]._allowed_methods;
    i = matchLocationAndUri(server._locations, request.getUriPath());
    if (i != -1)
    {
        std::string temp = request.getUriPath();
        temp = temp.erase(0, server._locations[i]._locationPath.size());
        if (!server._locations[i]._rootPath.empty())
            rootAndUri = server._locations[i]._rootPath + temp;
        else // i should handle in config file if i don't find root in server and in location -> throw error
            rootAndUri = server._rootPath + temp;
    }
    std::cout << rootAndUri << std::endl;
}
