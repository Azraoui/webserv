/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newSocket.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:21:46 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/11 14:29:37 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../includes/webserv.hpp"

namespace webserv
{
	class newSocket
	{
		private:
			int	_connection;

		public:
			newSocket();
			newSocket(int domain, int service, int protocol);
			~newSocket();
	};
}