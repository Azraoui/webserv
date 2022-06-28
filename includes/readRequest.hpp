#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>

class ReadRequest
{
	private:
		std::string                         _host;
		size_t                              _port;
		std::string                         _method;
		std::string                         _uriPath;
		std::string                         _version;
		std::string							_contentType;
		std::map<std::string, std::string>  _headerDirectives;
		std::string                         _queryParams;
		int                                 _bodyFileFd;
		size_t                              _bodyFileLength;
		bool                                _isRequestFinished;
		bool								_isChunked;
		size_t                              _statusCode;
		std::string							_requestFileName;
		std::string                         _requestContent;
		std::string							_header;
		size_t								_chunkSize;
		std::string							_chunkContent;

	public:
		ReadRequest();
		ReadRequest(ReadRequest const &obj);
		std::string		getRequestFileName(void) const;
		void			setRequestFileName(std::string fileName);
		void			generateFileName(int fd);
		void			parsing(char *content, int fd, ssize_t contentSize);
		std::string &getHost() {
			return _host;
		};

		size_t getPort() {
			return _port;
		};

		std::string &getMethod() {
			return _method;
		};

		std::string &getUriPath() {
			return _uriPath;
		};

		std::string &getVersion() {
			return _version;
		};

		std::map<std::string, std::string> &getHeaderDirectives() {
			return _headerDirectives;
		};

		std::string &getQueryParams() {
			return _queryParams;
		};

		int getBodyFileFd() {
			return _bodyFileFd;
		};

		size_t getBodyFileLength() {
			return _bodyFileLength;
		};

		size_t getStatusCode() {
			return _statusCode;
		};

		void setHost(std::string &host) {
			_host = host;
		};

		void setPort(size_t port) {
			_port = port;
		};

		void setMethod(std::string &method) {
			_method = method;
		};

		void setUriPath(std::string &uriPath) {
			_uriPath = uriPath;
		};

		void setVersion(std::string &version) {
			_version = version;
		};

		void setHeaderDirectives(std::map<std::string, std::string> &headerDirectives) {
			_headerDirectives = headerDirectives;
		};

		void setQueryParams(std::string &queryParams) {
			_queryParams = queryParams;
		};

		void setBodyFileFd(int bodyFileFd) {
			_bodyFileFd = bodyFileFd;
		};

		void setBodyFileLength(size_t bodyFileLength) {
			_bodyFileLength = bodyFileLength;
		};

		void setifrequestFinished(bool isRequestFinished) {
			_isRequestFinished = isRequestFinished;
		};

		bool getifrequestFinished() {
			return _isRequestFinished;
		};

		// methods
		~ReadRequest();
};