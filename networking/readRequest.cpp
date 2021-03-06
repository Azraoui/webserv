/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:38:42 by ael-azra          #+#    #+#             */
/*   Updated: 2022/07/23 15:49:36 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/readRequest.hpp"


ReadRequest::ReadRequest():  _connection(false), _bodyFileLength(0), _isRequestFinished(false), _isChunked(false), _requestContent(""), _chunkSize(0), _chunkContent(""){
	_is_bad_request.first = false;
	_cookies = "";
	_contentType = "";
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
	this->_is_bad_request.first = false;
	this->_requestFileName = obj._requestFileName;
	this->_cookies = obj._cookies;
	this->_contentType = obj._contentType;
}

// methods

// private

void	ReadRequest::_parseHeader(void)
{
	size_t end, start = 0;
	std::vector<std::string> vtmp;
	std::string	stmp;

	_header.append("\n");
	end = _header.find("\n", start);
	while (end != _header.npos)
	{
		stmp = _header.substr(start, end - start);
		if (stmp.find("\r") != stmp.npos)
			stmp.erase(stmp.find("\r"));
		vtmp = split(stmp, ' ');
		if (start == 0)
		{
			if (vtmp.size() != 3)
			{
				setIsBadRequest(std::make_pair(true, 400));
				return ;
			}
			_method = vtmp[0];
			if (vtmp[1].find("?") == vtmp[1].npos)
				_uriPath = vtmp[1];
			else
			{
				_queryParams = vtmp[1].substr(vtmp[1].find("?") + 1);
				_uriPath = vtmp[1].substr(0, vtmp[1].find("?"));
			}
		}
		else
		{
			if (vtmp[0] == "Transfer-Encoding:" && vtmp[1] != "chunked\r")
				setIsBadRequest(std::make_pair(true, 501));
			if (vtmp[0] == "Transfer-Encoding:" && vtmp[1] == "chunked\r")
				_isChunked = true;
			else if (vtmp[0] == "Host:")
			{
				if (vtmp.size() != 2)
				{
					setIsBadRequest(std::make_pair(true, 400));
					return ;
				}
				_host = vtmp[1].substr(0, vtmp[1].find(":"));
				_port = atoi(vtmp[1].substr(vtmp[1].find(":") + 1, vtmp[1].find("\r")).c_str());
			}
			else if (vtmp[0] == "Connection:")
			{
				if (vtmp.size() > 1 && vtmp[1] == "keep-alive\r")
					_connection = true;
			}
			else if (vtmp[0] == "Content-Length:")
			{
				if (vtmp.size() > 1)
					_bodyFileLength = atoi(vtmp[1].c_str());
			}
			else if (vtmp[0] == "Content-Type:")
			{
				if (vtmp.size() > 1)
				{
					for (size_t i = 1; i < vtmp.size(); i++)
					{
						_contentType += vtmp[i];
						// _contentType += " ";
					}
				}
			}
			else if (vtmp[0] == "Cookie:")
			{
				if (vtmp.size() > 1)
				{
					for (size_t i = 1; i < vtmp.size(); i++)
					{
						_cookies.append(vtmp[i]);
						// _cookies.append(" ");
					}
				}
			}
		}
		start = end + 1;
		end = _header.find("\n", start);
	}
}

//	public

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
		_parseHeader();
	}
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
		write(readFd, _requestContent.c_str(), _requestContent.size());
	off_t size;
	size = lseek(readFd, 0, SEEK_END);
	if (((unsigned long)size > _bodyFileLength))
	{
		setIsBadRequest(std::make_pair(true, 400));
		close(readFd);
		return;
	}
	if (((unsigned long)size == _bodyFileLength) || !_bodyFileLength)
		_isRequestFinished = true;
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

bool	ReadRequest::getConnection(void) const
{
	return _connection;
}

std::string		ReadRequest::getContentType(void) const {
	return this->_contentType;
}

void	ReadRequest::handling_response_errors()
{
	std::size_t found = _uriPath.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%");
	if (!_is_bad_request.first)
	{
		if (found!=std::string::npos)
		{
			_is_bad_request.first = true;
			_is_bad_request.second = 400;
		}
		else if (!_isChunked && !_bodyFileLength && _method == "POST")
		{
			_is_bad_request.first = true;
			_is_bad_request.second = 400;
		}
		else if (_uriPath.length() > 2048)
		{
			_is_bad_request.first = true;
			_is_bad_request.second = 414;
		}
	}
}