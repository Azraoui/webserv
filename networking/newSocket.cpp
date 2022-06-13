/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newSocket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:21:44 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/11 14:31:19 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "newSocket.hpp"

webserv::newSocket::newSocket()
{
	_connection = socket(AF_INET, SOCK_STREAM, 0);
}

webserv::newSocket::newSocket(int domain, int service, int protocol)
{
	_connection = socket(domain, service, protocol);
}

webserv::newSocket::~newSocket()
{
	
}