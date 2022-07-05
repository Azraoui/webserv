#include "cgi.hpp"

cgi::cgi()
{
return ;
}

cgi::cgi(ReadRequest &request)
{
    this->request = &request;
    cgi_error = 0;
    setenvcgi();
    executecgi();
}


void    cgi::setenvcgi(void)
{
    setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
	setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
	setenv("SERVER_SOFTWARE", "Webserv", 1);
	setenv("REDIRECT_STATUS", "200", 1);
    setenv("REQUEST_METHOD", request->getMethod().c_str(), 1);
    setenv("SCRIPT_FILENAME", request->getRequestFileName().c_str() , 1);
    setenv("SERVER_PORT", std::to_string(request->getPort()).c_str(),1);
	setenv("SERVER_NAME", request->getHost().c_str(),1);
    if (request->getMethod() == "GET")
    {
        setenv("QUERY_STRING", request->getQueryParams().c_str(), 1);
    }
    if(request->getMethod().c_str() == "POST")
    {
        setenv("CONTENT_TYPE", request->getContentType().c_str(), 1);
		setenv("CONTENT_LENGTH", std::to_string(request->getBodyFileLength()).c_str(), 1);
    }
    args[0] = (char*)"/usr/local/bin/php-cgi";
	args[1] = NULL;
    fd_output = open("file.html", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    fd_input = open(request->getRequestFileName().c_str(), O_RDONLY);

}

void    cgi::executecgi(void)
{
    int pid;
    int wstatus;

    pid = fork();
    if (pid == -1)
    {
        cgi_error = 1;
    }
    if (pid == 0)
    {
        execve(args[0], args, environ);
        cgi_error = 1;
        exit(wstatus);
    }
    else
    {
        waitpid(pid, NULL, 0);
        if (WIFEXITED(wstatus))
            cgi_error = WEXITSTATUS(wstatus);
}
cgi::~cgi()
{
    close(fd_output);
    close(fd_input);
}