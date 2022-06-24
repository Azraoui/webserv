#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP


# include "../includes/parser.hpp" // AbdAllah Vserver struct


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

	public:
		HttpServer(const std::vector<Vserver> &servers);
		~HttpServer();

		// methods
		void	loadServers(void);

};

#endif