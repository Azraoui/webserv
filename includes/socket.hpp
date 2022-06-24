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

class Socket
{
    private:
        int                 _socket;
        struct sockaddr_in  _addr;
    public:
        
        int & getSocket() {
            return _socket;
        };

        struct sockaddr_in & getAddr() {
            return _addr;
        };

        int initSocket(std::string &host, size_t &port) {
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
                std::cerr << "Error: socket() failed " << std::endl;
                return (-1);
            }

            fcntl(_socket, F_SETFL, O_NONBLOCK);
            return (0);
        };

        int bindSocket() {
            //bin _addr to _socket
            if (bind(_socket, (struct sockaddr *)&_addr, sizeof(_addr)) == -1) {
                std::cerr << "Error: bind() failed " << std::endl;
                return (-1);
            }
            return (0);
        };

        int listenSocket() {
            if (listen(_socket, 1024) == -1) {
                std::cerr << "Error: listen() failed " << std::endl;
                return (-1);
            }
            return (0);
        };

        Socket() : _socket(-1), _addr() {};
        ~Socket() {};
};

#endif