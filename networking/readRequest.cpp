/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:38:42 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/27 18:33:52 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/readRequest.hpp"


ReadRequest::ReadRequest(): _requestContent(""){
}

ReadRequest::~ReadRequest(){
	
}

ReadRequest::ReadRequest(ReadRequest const &obj)
{
	this->_header = obj._header;
	this->_host = obj._host;
	this->_port = obj._port;
	this->_method = obj._method;
	this->_uriPath = obj._uriPath;
	this->_version = obj._version;
	this->_headerDirectives = obj._headerDirectives;
	this->_queryParams = obj._queryParams;
	this->_bodyFileFd = obj._bodyFileFd;
	this->_bodyFileLength = obj._bodyFileLength;
	this->_isRequestFinished = obj._isRequestFinished;
	this->_statusCode = obj._statusCode;
}

// methods


void	ReadRequest::parsing(char *content, int fd, ssize_t contentSize)
{
	int	readFd;

	this->generateFileName(fd);
	readFd = open(_requestFileName.c_str(), O_RDWR | O_APPEND | O_CREAT, 0666);
	if (readFd < 0)
	{
		std::cerr << "can't open " + _requestFileName + "\n";
		return ;
	}
	_requestContent.clear();
	_requestContent = std::string(content, contentSize);
	if (_header.empty())
	{
		_header.append(_requestContent.substr(0, _requestContent.find("\r\n\r\n")));
		_requestContent.erase(0, _requestContent.find("\r\n\r\n") + 4);
	}
	if (!_requestContent.empty())
	{
		size_t firstPos = _requestContent.find("\r\n") + 2;
		size_t secondPos;
		if (_requestContent.find("0\r\n\r\n") == _requestContent.npos)
			secondPos = _requestContent.find("\r\n", firstPos) - firstPos;
		else
			secondPos = _requestContent.find("0\r\n\r\n") - firstPos;
		std::cout << "first = " << firstPos << " second = " << secondPos << std::endl;
		std::cout << _requestContent.substr(firstPos, secondPos) << std::endl;
		write(readFd, _requestContent.c_str(), _requestContent.size());
	}
	close(readFd);
}

std::string		ReadRequest::getRequestFileName() const
{
	return _requestFileName;
}

void			ReadRequest::setRequestFileName(std::string fileName)
{
	this->_requestFileName = fileName;
}

void	ReadRequest::generateFileName(int fd)
{
	if (this->_requestFileName.empty())
		this->setRequestFileName("/tmp/" + std::to_string(fd) + "_clientFd_" + std::to_string(time(NULL)));
}
