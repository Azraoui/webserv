#include "cgi.hpp"
#include "../includes/parser.hpp"

cgi::cgi()
{
return ;
}

cgi::cgi(ReadRequest request)
{
    this->request = &request;
    query = std::string();
    std::string Path = request.getUriPath();
    std::vector<std::string> SplitPath = split(request.getUriPath(), '?');
    if (SplitPath.size() == 2)
        query = SplitPath[1];
    std::cout << "query-> " << query << std::endl;
    // file = SplitPath[0];
    file = "cgi/index.php";
    cgi_error = 0;
    setenvcgi();
    executecgi();
}


void    cgi::setenvcgi(void)
{
    if (request->getMethod().empty())
        return;
    std::cout << "request uri: " << request->getUriPath() << std::endl;
    std::cout << "method: " << request->getMethod() << std::endl;
    setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
	setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
	setenv("SERVER_SOFTWARE", "Webserv", 1);
	setenv("REDIRECT_STATUS", "200", 1);
    setenv("REQUEST_METHOD", request->getMethod().c_str(), 1);
    setenv("SCRIPT_FILENAME", file.c_str() , 1);
    setenv("SERVER_PORT", std::to_string(request->getPort()).c_str(),1);
	setenv("SERVER_NAME", request->getHost().c_str(),1);
    if (request->getMethod() == "GET")
    {
        setenv("QUERY_STRING", query.c_str(), 1);
    }
    if (request->getMethod() == "POST")
    {
        setenv("CONTENT_TYPE", request->getContentType().c_str(), 1);
		setenv("CONTENT_LENGTH", std::to_string(request->getBodyFileLength()).c_str(), 1);
    }
    args[0] = (char*)"bin/php-cgi";
    args[1] = (char*)file.c_str();
	args[2] = NULL;
    fd_output = open("file.html", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    fd_input = open(request->getRequestFileName().c_str(), O_RDONLY);

}

void    cgi::executecgi(void)
{
    int pid;
    int wstatus = 0;

    pid = fork();
    if (pid == -1)
    {
        cgi_error = 1;
    }
    if (pid == 0)
    {
        std::cout << "pid: " << getpid() << std::endl;
        std::cout << "wast child process " << std::endl;
        // if (request->getMethod() == "POST")
        dup2(fd_input, 0);
        dup2(fd_output, 1);
        execve(args[0], args, environ);
        std::cout << "execve failat" << std::endl;
        cgi_error = 1;
        exit(wstatus);
    }
    else
    {
        waitpid(pid, NULL, 0);
        if (WIFEXITED(wstatus))
            cgi_error = WEXITSTATUS(wstatus);
    }
}

cgi::~cgi()
{
    close(fd_output);
    close(fd_input);
}