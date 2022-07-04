#ifndef SERVERRESPONSE_HPP
#define SERVERRESPONSE_HPP

#include "httpServer.hpp"


class ServerResponse
{
    private:
        ReadRequest             _request;
        std::string             _method;
        std::string             _uriPath;
        std::string             _statusCode;
        std::string             _buffer;
        std::string             _connectionType;
        std::string             _autoIndex;
        std::string             _rootPath;
        std::string             _builtedPath;
        int                     _requestBodyFileFd;
        std::string             _requestBodyFileName;
        bool                    _isCgi;
        bool                    _isDirectory;
        size_t                  _isResponseFinished;

    public:
        ServerResponse();
        ~ServerResponse();
};

#endif