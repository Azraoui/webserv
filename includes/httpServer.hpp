#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP


# include "./parser.hpp" // AbdAllah Vserver struct
# include "./socket.hpp"
# include "./serverRequest.hpp"
# include "./serverResponse.hpp"
# include "./touls.hpp"
#include "../cgi/cgi.hpp"

# include <string>
# include <vector>
# include <map>
# include <sys/select.h>
# include <iostream>
# include <sys/stat.h>
# include <unistd.h>

# define BUFFER_LENGTH 1024

class HttpServer
{
	private:
		std::vector<Vserver >           _servers;
		std::vector<int>				_open_ports;
		std::vector<Socket>				_serverSock;
		std::vector<Socket>				_clientsSock;
		ServerRequest					_selectUtility;
		// ServerResponse					_response;

		//methods
		void	_loadServers(void);
		bool	_readRequest(int clientFd);
		void	_acceptRequest(int position);
		void	_handleGetMethod(ReadRequest request, Vserver &server, int clientFd);
		void	_handlePost(ReadRequest request, Vserver &server, int clientFd);
		void	_handleDelete(ReadRequest request, Vserver &server, int clientFd);
		void	_responseServer(int clientFd, int i);
		void	_handling_method_allowed_error(ReadRequest &request, Vserver &server);
	public:
		HttpServer(const std::vector<Vserver> &servers);
		~HttpServer();

		// methods
		void	runServers(void);
};

#endif