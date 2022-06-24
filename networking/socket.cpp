/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:28:51 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/24 21:58:05 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/socket.hpp"

Socket    Socket::accept_conncetion(void)
{
	_clientFd = accept(this->getSocket(), (struct sockaddr *)&_clientAddr, &_clientLent);
	if (_clientFd < 0)
	{
		std::cerr << "Failled to accept connection" << std::endl;
		return Socket();
	}
	return *this;
}