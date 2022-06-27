/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:38:42 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/26 20:24:07 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/readRequest.hpp"


ReadRequest::ReadRequest():_requestFile("test.txt")
{
}

ReadRequest::~ReadRequest(){
	
}

// methods

void	ReadRequest::parsing(std::string content, int fd)
{
	this->creatRequestFile(fd);
	(void)content;
	// _requestFile.open(_requestFileName, std::fstream::app, std::fstream::out, std::fstream::in);
}


std::string		ReadRequest::getRequestFileName() const
{
	return _requestFileName;
}

void			ReadRequest::setRequestFileName(std::string fileName)
{
	this->_requestFileName = fileName;
}

void	ReadRequest::creatRequestFile(int fd)
{
	if (this->_requestFileName.empty())
		this->setRequestFileName("/tmp/" + std::to_string(fd) + "_clientFd");
}
