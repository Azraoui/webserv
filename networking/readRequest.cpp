/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:38:42 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/28 18:01:26 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/readRequest.hpp"


ReadRequest::ReadRequest():_isChunked(false), _requestContent(""), _chunkSize(0), _chunkContent(""){
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
	// this 2 variable need to set in header request
	_isChunked = true;
	_bodyFileLength = 1;
	if (!_requestContent.empty() && _isChunked && _bodyFileLength > 0)
	{
		size_t end, start = 0;
		std::string	temp;
		bool isFinish;
		end = _requestContent.find("\n", start);
		if (_requestContent.find("0\r\n\r\n") != _requestContent.npos)
			_requestContent.erase(_requestContent.find("0\r\n\r\n"), 5);
		while (end != _requestContent.npos)
		{
			if (!_chunkSize)
			{
				std::stringstream s;
				s << _requestContent.substr(start, end - start);
				s >> std::hex >> _chunkSize;
				isFinish = false;
				std::cout << _requestContent.substr(start, end - start) << std::endl << _chunkSize << std::endl;
			}
			else if (_chunkSize != _chunkContent.size())
			{
				_chunkContent.append(_requestContent.substr(start, (end + 1) - start));
				temp.append(_requestContent.substr(start, (end + 1) - start));
				if (_chunkContent.size() > _chunkSize)
					_chunkContent.erase(_chunkSize);
				if (_chunkSize == _chunkContent.size())
				{
					write(readFd, _chunkContent.c_str(), _chunkSize);
					_chunkSize = 0;
					_chunkContent.clear();
					isFinish = true;
				}
			}
			start = end + 1;
			end = _requestContent.find("\n", start);
			if (end == _requestContent.npos && _requestContent.size() > temp.size() && !isFinish)
				_chunkContent.append(_requestContent.substr(start, _requestContent.length() - start));
		}
	}
	else
	{
		write(readFd, _requestContent.c_str(), _requestContent.size());
		_requestContent.clear();
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
