/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:51:22 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/24 10:59:58 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/httpServer.hpp"

HttpServer::HttpServer(const std::vector<Vserver> &servers) : _servers(servers) {
    loadServers();
}

HttpServer::~HttpServer(){

}

// methods

void	HttpServer::loadServers(void)
{
	
};