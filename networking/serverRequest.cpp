/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:49:04 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/24 12:48:13 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/serverRequest.hpp"

ServerRequest::ServerRequest() : _max_fd(0){
	
}

ServerRequest::~ServerRequest(){
	
}

// methods

void ServerRequest::clear() // this function clear fd_set struct
{
	FD_ZERO(&this->_read_fd);
}


void	ServerRequest::set_fd(int socketFd) // this function add socketFd to fdset
{
	FD_SET(socketFd, &this->_read_fd);
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

bool	ServerRequest::selectFd(void)
{
	timeval tmv;
	fd_set  err;

	tmv.tv_sec = 30;
	tmv.tv_usec = 0;
	if (select(_max_fd, &_read_fd, &_write_fd, &err, &tmv) < 0)
		return false;
	return true;
}