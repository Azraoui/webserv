/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:41:30 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/24 18:20:47 by ael-azra         ###   ########.fr       */
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


class ServerRequest
{
	private:
		fd_set	_read_fd;
		fd_set	_write_fd;
		int		_max_fd;

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

};