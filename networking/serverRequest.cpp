/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yer-raki <yer-raki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:49:04 by ael-azra          #+#    #+#             */
/*   Updated: 2022/07/06 15:29:16 by yer-raki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serverRequest.hpp"

ServerRequest::ServerRequest() : _max_fd(-1){
	
}

ServerRequest::~ServerRequest(){
	
}

// methods

void ServerRequest::clear() // this function clear fd_set struct
{
	FD_ZERO(&this->_master);
	FD_ZERO(&this->_read_fd);
	FD_ZERO(&this->_write_fd);
}


void	ServerRequest::set_fd(int socketFd) // this function add socketFd to fdset
{
	FD_SET(socketFd, &this->_master);
}

void	ServerRequest::set_maxFd(int fd)
{
	if (_max_fd < fd)
		_max_fd = fd;
}

int		ServerRequest::get_maxFd(void)
{
	return _max_fd;
}

void	ServerRequest::setReadAndWriteFD(void)
{
	this->_read_fd = _master;
	this->_write_fd = _master;
}

bool	ServerRequest::selectFd(void)
{
	if (select(_max_fd + 1, &_read_fd, &_write_fd, NULL, NULL) <= 0)
		return false;
	return true;
}

int		ServerRequest::fd_isset(int socketFd, std::string s) // cheack if fd is ready to read or to write
{
	if (s == "read")
		return (FD_ISSET(socketFd, &_read_fd));
	else if (s == "write")
		return (FD_ISSET(socketFd, &_write_fd));
	return 0;
}

void	ServerRequest::insertClient(int fd)
{
	_readRequest.insert(std::make_pair(fd, ReadRequest()));
}

bool	ServerRequest::readData(int fd)
{
	char buffer[BUFFER_SIZE];
	ssize_t recv_ret;

	bzero(buffer, BUFFER_SIZE);
	recv_ret = read(fd, buffer, BUFFER_SIZE);
	if (recv_ret <= 0)
	{
		_readRequest.erase(fd);
		FD_CLR(fd, &_master);
		close(fd);
		return (false);
	}
	_readRequest[fd].parsing(buffer, fd, recv_ret);
	return (true);
}

ReadRequest  &ServerRequest::getRequest(int fd)
{
	return _readRequest[fd];
	// if (_readRequest.find(fd) != _readRequest.end())
	// 	return _readRequest.at(fd);
	// return ReadRequest();
}

void	ServerRequest::erase(int fd)
{
	_readRequest.erase(fd);
}

// void	ServerRequest::setResponse(int fd, ReadRequest request)
// {
// 	_sendResponse.insert(fd, ServerResponse(request));
// }