#ifndef CGI_PHP
# define CGI_PHP

#include <iostream>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../includes/readRequest.hpp"
#include "../includes/parser.hpp"
#include "../includes/touls.hpp"

extern char **environ;

class cgi 
{
    cgi();

    private:
        std::string     _cgiPath;
        int             _fd;
        std::string     _outputfile;
        std::string     _path;

    public:
        int fd_input;
        int fd_output;
        char *args[3];
        ReadRequest request;
        std::string file;
        int         cgi_error;
        std::string query_params;
        char **metaTest;
                
        cgi(ReadRequest request, std::string cgiPath, int fd, std::string path);
        ~cgi();
        void    setenvcgi(void);
        std::string concat(std::string const & s, int i);
        int    executecgi(void);
        std::string getCgiRetPath(void) const;

};
#endif