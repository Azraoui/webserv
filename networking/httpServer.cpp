/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:51:22 by ael-azra          #+#    #+#             */
/*   Updated: 2022/07/07 00:26:37 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/httpServer.hpp"

std::map<int, std::string> status_code; // first : key | second : string value of error 
std::map<std::string, std::string> mime_type;

HttpServer::HttpServer(const std::vector<Vserver> &servers) : _servers(servers) {
    this->_loadServers();
}

HttpServer::~HttpServer(){
}

// methods

void	HttpServer::_loadServers(void)
{
	for (size_t i = 0; i < _servers.size(); i++)
    {
        if (std::find(_open_ports.begin(), _open_ports.end(), _servers[i]._port) != _open_ports.end())
            continue;
        else
        {
            _serverSock.push_back(Socket());
            _serverSock.back().initSocket(_servers[i]._host, _servers[i]._port);
            _serverSock.back().bindSocket();
            _serverSock.back().listenSocket();
            _serverSock.back().addServer(i);
            _open_ports.push_back(_servers[i]._port);
        }
    }
};

void fill_map_error_value()
{
    status_code.insert(std::make_pair(200, "OK"));
    status_code.insert(std::make_pair(201, "Created"));
    status_code.insert(std::make_pair(204, "No Content"));
    
    status_code.insert(std::make_pair(301, "Moved Permanently"));
    
    status_code.insert(std::make_pair(400, "Bad Request"));
    status_code.insert(std::make_pair(403, "Forbidden"));
    status_code.insert(std::make_pair(404, "Not Found"));
    status_code.insert(std::make_pair(405, "Method Not Allowed"));
    status_code.insert(std::make_pair(409, "Conflict"));
    status_code.insert(std::make_pair(413, "Request Entity Too Large"));
    status_code.insert(std::make_pair(414, "Request-URI Too Long"));
    
    status_code.insert(std::make_pair(500, "Internal Server Error"));
    status_code.insert(std::make_pair(501, "Not Implemented"));
}

void fill_map_mime_type()
{
    mime_type.insert(std::make_pair("aac", "audio/aac"));
    mime_type.insert(std::make_pair("abw", "application/x-abiword"));
    mime_type.insert(std::make_pair("arc", "application/x-freearc"));
    mime_type.insert(std::make_pair("avi", "video/x-msvideo"));
    mime_type.insert(std::make_pair("azw", "Bad application/vnd.amazon.ebook"));
    mime_type.insert(std::make_pair("bin", "application/octet-stream"));
    mime_type.insert(std::make_pair("bmp", "application/x-bzip"));
    mime_type.insert(std::make_pair("bz", "application/x-bzip"));
    mime_type.insert(std::make_pair("bz2", "application/x-bzip2"));
    mime_type.insert(std::make_pair("csh", "application/x-csh"));
    mime_type.insert(std::make_pair("css", "text/css"));
    mime_type.insert(std::make_pair("csv", "text/csv"));
    mime_type.insert(std::make_pair("doc", "application/msword"));
    mime_type.insert(std::make_pair("docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"));
    mime_type.insert(std::make_pair("eot", "application/vnd.ms-fontobject"));
    mime_type.insert(std::make_pair("epub", "application/epub+zip"));
    mime_type.insert(std::make_pair("gz", "application/gzip"));
    mime_type.insert(std::make_pair("gif", "image/gif"));
    mime_type.insert(std::make_pair("htm", "text/html"));
    mime_type.insert(std::make_pair("html", "text/html"));
    mime_type.insert(std::make_pair("ico", "image/vnd.microsoft.icon"));
    mime_type.insert(std::make_pair("ics", "text/calendar"));
    mime_type.insert(std::make_pair("jar", "application/java-archive"));
    mime_type.insert(std::make_pair("jpeg", "image/jpeg"));
    mime_type.insert(std::make_pair("jpg", "image/jpeg"));
    mime_type.insert(std::make_pair("js", "text/javascript"));
    mime_type.insert(std::make_pair("json", "application/json"));
    mime_type.insert(std::make_pair("jsonld", "application/ld+json"));
    mime_type.insert(std::make_pair("mid", "audio/midi audio/x-midi"));
    mime_type.insert(std::make_pair("midi", "audio/midi audio/x-midi"));
    mime_type.insert(std::make_pair("mjs", "text/javascript"));
    mime_type.insert(std::make_pair("mp3", "audio/mpeg"));
    mime_type.insert(std::make_pair("mpeg", "video/mpeg"));
    mime_type.insert(std::make_pair("mpkg", "application/vnd.apple.installer+xml"));
    mime_type.insert(std::make_pair("odp", "application/vnd.oasis.opendocument.presentation"));
    mime_type.insert(std::make_pair("ods", "application/vnd.oasis.opendocument.spreadsheet"));
    mime_type.insert(std::make_pair("odt", "application/vnd.oasis.opendocument.text"));
    mime_type.insert(std::make_pair("oga", "audio/ogg"));
    mime_type.insert(std::make_pair("ogv", "video/ogg"));
    mime_type.insert(std::make_pair("ogx", "application/ogg"));
    mime_type.insert(std::make_pair("opus", "audio/opus"));
    mime_type.insert(std::make_pair("otf", "font/otf"));
    mime_type.insert(std::make_pair("png", "image/png"));
    mime_type.insert(std::make_pair("pdf", "application/pdf"));
    mime_type.insert(std::make_pair("php", "application/x-httpd-php"));
    mime_type.insert(std::make_pair("ppt", "application/vnd.ms-powerpoint"));
    mime_type.insert(std::make_pair("pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"));
    mime_type.insert(std::make_pair("rar", "application/vnd.rar"));
    mime_type.insert(std::make_pair("rtf", "application/rtf"));
    mime_type.insert(std::make_pair("sh", "application/x-sh"));
    mime_type.insert(std::make_pair("svg", "image/svg+xml"));
    mime_type.insert(std::make_pair("swf", "application/x-shockwave-flash"));
    mime_type.insert(std::make_pair("tar", "application/x-tar"));
    mime_type.insert(std::make_pair("tif", "image/tiff"));
    mime_type.insert(std::make_pair("tiff", "image/tiff"));
    mime_type.insert(std::make_pair("ts", "video/mp2t"));
    mime_type.insert(std::make_pair("ttf", "font/ttf"));
    mime_type.insert(std::make_pair("txt", "text/plain"));
    mime_type.insert(std::make_pair("vsd", "application/vnd.visio"));
    mime_type.insert(std::make_pair("wav", "audio/wav"));
    mime_type.insert(std::make_pair("weba", "audio/webm"));
    mime_type.insert(std::make_pair("webm", "video/webm"));
    mime_type.insert(std::make_pair("webp", "image/webp"));
    mime_type.insert(std::make_pair("woff", "font/woff"));
    mime_type.insert(std::make_pair("woff2", "font/woff2"));
    mime_type.insert(std::make_pair("xhtml", "application/xhtml+xml"));
    mime_type.insert(std::make_pair("xls", "application/vnd.ms-excel"));
    mime_type.insert(std::make_pair("xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"));
    mime_type.insert(std::make_pair("xml", "application/xml"));
    //  mime_type.insert(std::make_pair("xml", "text/xml"));
    mime_type.insert(std::make_pair("xul", "application/vnd.mozilla.xul+xml"));
    mime_type.insert(std::make_pair("zip", "application/zip"));
    mime_type.insert(std::make_pair("3gp", "video/3gpp"));
    mime_type.insert(std::make_pair("3gp2", "video/3gpp2"));
    mime_type.insert(std::make_pair("7z", "application/x-7z-compressed"));
}

void    HttpServer::runServers(void)
{
    fill_map_error_value(); // FILL STATUS_CODE MAP
    fill_map_mime_type();
    _selectUtility.clear();
    for (size_t i = 0; i < _serverSock.size(); i++)
    {
        _selectUtility.set_fd(_serverSock[i].getSocket());
        _selectUtility.set_maxFd(_serverSock[i].getSocket());
    }
    while (true)
    {
        _selectUtility.setReadAndWriteFD();
        if (!_selectUtility.selectFd())
            continue;
        for (size_t i = 0; i < _serverSock.size(); i++)
        {
            // accept requests
            if (_selectUtility.fd_isset(_serverSock[i].getSocket(), "read"))
                this->_acceptRequest(i);
        }
        for (size_t i = 0; i < _clientsSock.size(); i++)
        {
            // read
            if (_selectUtility.fd_isset(_clientsSock[i].getClientFd(), "read"))
            {
                if (!this->_readRequest(_clientsSock[i].getClientFd()))
                {
                    _clientsSock.erase(_clientsSock.begin() + i);
                    continue;
                }
            }
            // reponse
            if (_selectUtility.fd_isset(_clientsSock[i].getClientFd(), "write"))
            {
                int fd = _clientsSock[i].getClientFd();
                if (_selectUtility.getRequest(fd).getifrequestFinished())
                {
                    _responseServer(fd, i);
                }
                // reponse here
            }
        }
    }
}

bool	HttpServer::_readRequest(int clientFd)
{
    if (!_selectUtility.readData(clientFd))
        return false;
    return true;
}

void	HttpServer::_acceptRequest(int position)
{
    Socket tmp;
    int    option_value;

    tmp = _serverSock[position].accept_conncetion();
    if (tmp.getClientFd() < 0)
        return ;
    if (fcntl(tmp.getClientFd(), F_SETFL, O_NONBLOCK) < 0)
       return ;
    if (setsockopt(tmp.getClientFd(), SOL_SOCKET, SO_NOSIGPIPE, &option_value, sizeof(option_value)) < 0)
        return ;
    _clientsSock.push_back(tmp);
    _selectUtility.set_fd(tmp.getClientFd());
    _selectUtility.set_maxFd(tmp.getClientFd());
    _selectUtility.insertClient(tmp.getClientFd());
}
void    HttpServer::_handling_method_allowed_error(ReadRequest &request, Vserver &server)
{
    int pos_loc;
    Location loc;
    std::set<std::string>::iterator it;
    
    pos_loc = matchLocationAndUri(server._locations, request.getUriPath());
    loc = server._locations[pos_loc];   
    for (it = loc._allowed_methods.begin(); it != loc._allowed_methods.end(); it++)
    {
        if (*it == request.getMethod())
            return;
    }
    for (it = server._allowed_methods.begin(); it != server._allowed_methods.end(); it++)
    {
        if (*it == request.getMethod())
            return;
    }
    request.setIsBadRequest(std::make_pair(true, 405));
    // std::cout << "ERROR 405 !!" << request.getIsBadRequest().first << " | " << request.getIsBadRequest().second << std::endl;
}

void handling_upload(std::string request_file_name, std::string upload_path)
{
    // std::string new_str = "cgi_" + request_file_name;
    std::cout << request_file_name << std::endl;
    std::ifstream  src(request_file_name.c_str(), std::ios::binary);
    std::ofstream  dst(upload_path.c_str(), std::ios::binary);
    dst << src.rdbuf();

}

void	HttpServer::_responseServer(int clientFd, int i)
{
    std::string Method = _selectUtility.getRequest(clientFd).getMethod();
    std::string Path = _selectUtility.getRequest(clientFd).getUriPath();
    
    _selectUtility.getRequest(clientFd).handling_response_errors();
    _handling_method_allowed_error(_selectUtility.getRequest(clientFd), _servers[_clientsSock[i].getServerPosition()]);
    // _selectUtility.getRequest(clientFd).setIsBadRequest(std::make_pair(true, 405));
   // std::cout << "filename : " << _selectUtility.getRequest(clientFd).getRequestFileName() << std::endl;
    if ((Method == "GET" || Method == "POST") && Path.find(".php") != std::string::npos) // for testing
        cgi cgi(_selectUtility.getRequest(clientFd));
    // if (Method == "POST")
        // handling_upload(_selectUtility.getRequest(clientFd).getRequestFileName(), // upload_path);
    if (_selectUtility.getRequest(clientFd).getMethod() == "GET")
        _handleGetMethod(_selectUtility.getRequest(clientFd), _servers[_clientsSock[i].getServerPosition()], clientFd);
    // ServerResponse response(_selectUtility.getRequest(clientFd), _servers[_clientsSock[i].getServerPosition()]);
    // _selectUtility.getRequest(clientFd)
    FD_CLR(clientFd, &_selectUtility._master);
    close(clientFd);
    _clientsSock.erase(_clientsSock.begin() + i);
    _selectUtility.erase(clientFd);
}

void    HttpServer::_handleGetMethod(ReadRequest request, Vserver &server, int clientFd)
{
    int i;
    std::string rootAndUri, msg;
    struct stat	buf;

    i = matchLocationAndUri(server._locations, request.getUriPath());
    if (i != -1)
    {
        std::string temp = request.getUriPath();
        temp = temp.erase(0, server._locations[i]._locationPath.size());
        if (!server._locations[i]._rootPath.empty())
            rootAndUri = server._locations[i]._rootPath + temp;
        else // i should handle in config file if i don't find root in server and in location -> throw error
            rootAndUri = server._rootPath + temp;
        if (!lstat(rootAndUri.c_str(), &buf))
        {
            if (!(buf.st_mode & S_IREAD))
            {
                msg = errRespone(403, status_code);
                write(clientFd, msg.c_str(), msg.size());
            }
            else if (buf.st_mode & S_IFDIR)
            {
                if (rootAndUri[rootAndUri.size() - 1] != '/')
                {
                    msg = redirect(301, status_code, request.getUriPath() + '/');
                    write(clientFd, msg.c_str(), msg.size());
                }
                else
                {
                    std::string indexPath;
                    std::string extension;
                    for (size_t j = 0; j < server._locations[i]._index.size(); j++)
                    {
                        indexPath = rootAndUri + server._locations[i]._index[j];
                        if (!lstat(indexPath.c_str(), &buf) && !(buf.st_mode & S_IFDIR) && (buf.st_mode & S_IREAD))
                        {
                            extension = server._locations[i]._index[j].substr(server._locations[i]._index[j].find_last_of(".") + 1);
                            break;
                        }
                    }
                    if (extension.empty())
                    {
                        if (server._locations[i]._autoindex == "on")
                        {
                            // handle auto index
                        }
                        else
                        {
                            msg = errRespone(403, status_code);
                            write(clientFd, msg.c_str(), msg.size());
                        }
                    }
                    else
                    {
                        
                    }
                }
            }
        }
        else
        {
            msg = errRespone(404, status_code);
            write(clientFd, msg.c_str(), msg.size());
        }
    }
}
