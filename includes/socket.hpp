#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <netinet/in.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <cstring>
# include <arpa/inet.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <iostream>
# include "./parser.hpp"

class Socket
{
    private:
        int                 _socket;
        int                 _clientFd;
        struct sockaddr_in  _addr, _clientAddr;
        socklen_t           _clientLent;
        int                 _serverPosition;

    public:
        void    exitPrint(std::string err);
        int & getSocket() {
            return _socket;
        };
        void    addServer(int i){
            _serverPosition = i;
        };
        int    getServerPosition(void) const {
            return this->_serverPosition;
        };
        struct sockaddr_in & getAddr() {
            return _addr;
        };
        int getClientFd(void){
            return _clientFd;
        };
        int initSocket(std::string &host, size_t &port) {
            int opt = 1;
            // memset space for _addr
            memset((char *)&_addr, 0, sizeof(_addr));
            
            _addr.sin_family = AF_INET;
            if (host.empty()) {
                _addr.sin_addr.s_addr = htonl(INADDR_ANY);
            } else {
                if (host.compare("localhost") == 0) {
                    host = "127.0.0.1";
                }
                _addr.sin_addr.s_addr = inet_addr(host.c_str());
            }
            _addr.sin_port = htons(port);

            _socket = socket(AF_INET, SOCK_STREAM, 0);
            if (_socket == -1) {
                exitPrint("Error in Socket");
            }
            if ((setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0))
            {
                exitPrint("Error: setsockopt");
            }
            fcntl(_socket, F_SETFL, O_NONBLOCK);
            return (0);
        };

        int bindSocket() {
            //bin _addr to _socket
            if (bind(_socket, (struct sockaddr *)&_addr, sizeof(_addr)) == -1) {
                exitPrint("Error: bind() failed ");
            }
            return (0);
        };

        int listenSocket() {
            if (listen(_socket, 1024) == -1) {
                exitPrint("Error: listen() failed ");
            }
            return (0);
        };
        Socket    accept_conncetion(void);

        Socket() : _socket(-1), _addr(){};
        ~Socket() {};
};

#endif