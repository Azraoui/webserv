#include "../includes/serverResponse.hpp"

Vserver serverResponse::matchServer()
{
    for (std::vector<Vserver>::iterator it = _servers.begin(); it != _servers.end(); it++)
    {
        // chek ports 
        if (_request.getPort() == it->getPort())
        {
            std::vector<std::string>    serverNames = it->getServerNames();
            if (it->getHost().compare("localhost") == 0 || it->getHost().compare("127.0.0.1") == 0)
                if (_request.getHost().compare("localhost") == 0 || _request.getHost().compare("127.0.0.1") == 0)
                    return *it;
            for (std::vector<std::string>::iterator it2 = serverNames.begin(); it2 != serverNames.end(); it++)
            {
                if (it2->compare(_request.getHost()))
                    return *it;
            }
            if (_request.getHost().compare(it->getHost()))
                return *it;
        }
    }
    return {};
}

serverResponse::serverResponse(ReadRequest request, std::vector<Vserver> servers) : _request(request)
{
    _servers = servers;
    _method = "";
    _uriPath = "";
    _statusCode = "";
    _buffer = "";
    _connectionType = "";
    _autoIndex = "";
    _requestBodyFileFd = -1;
    _requestBodyFileName = _request.getRequestFileName();
    _isCgi = false;
    _isDirectory = false;
    _isResponseFinished = 0;
    _rootPath = "";
    _builtedPath = "";

    _matchedServer = matchServer();
}

serverResponse::~serverResponse()
{
    ;
}