#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP


# include "./parser.hpp" // AbdAllah Vserver struct
# include "./socket.hpp"
# include "./serverRequest.hpp"

# include <string>
# include <vector>
# include <map>
# include <sys/select.h>
# include <iostream>

# define BUFFER_LENGTH 1024

class HttpServer
{
	private:
		std::vector<Vserver >           _servers;
		std::vector<int>				_open_ports;
		std::vector<Socket>				_serverSock;
		ServerRequest					_selectUtility;

		//methods
		void	_loadServers(void);

	public:
		HttpServer(const std::vector<Vserver> &servers);
		~HttpServer();

		// methods
		void	runServers(void);
};

#endif