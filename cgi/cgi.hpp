#ifndef CGI_PHP
# define CGI_PHP

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../includes/readRequest.hpp"

extern char **environ;

class cgi 
{
    public:
        int fd_input;
        int fd_output;
        char *args[2];
        ReadRequest *request;
        std::string file;
        int         cgi_error;
        
        cgi();
        cgi(ReadRequest &request);
        ~cgi();
        void    setenvcgi(void);
        void    executecgi(void);

};
#endif