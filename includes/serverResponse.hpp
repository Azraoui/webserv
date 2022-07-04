#ifndef SERVERRESPONSE_HPP
#define SERVERRESPONSE_HPP

#include "httpServer.hpp"

class serverResponse
{
    private:
        Vserver                 _matchedServer; // we can remove it after finishing i guess
        std::vector<Vserver>    _servers;
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

        Vserver matchServer();
        Vserver getMatchedServer() {
            return _matchedServer;
        };
        serverResponse(ReadRequest request, std::vector<Vserver> servers);
        ~serverResponse();
        void handling_errors();
};

#endif