/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:41:30 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/26 17:03:48 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <map>
#include "./readRequest.hpp"

#define BUFFER_SIZE 1024

class ServerRequest
{
	private:
		fd_set						_master;
		fd_set						_write_fd;
		fd_set						_read_fd;
		int							_max_fd;
		std::map<int, ReadRequest>	_readRequest;

	public:
		ServerRequest();
		~ServerRequest();

		//methods
		void	clear(void);
		void	set_fd(int socketFd);
		void	set_maxFd(int fd);
		int		get_maxFd(void);
		bool	selectFd(void);
		int		fd_isset(int socketFd, std::string s);
		void	setReadAndWriteFD(void);
		void	insertClient(int fd);
		bool	receiveData(int fd);
};