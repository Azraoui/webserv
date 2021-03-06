#include "cgi.hpp"

cgi::cgi() {

}

std::string cgi::concat(std::string const & s, int i)
{
    std::stringstream ss;
    ss << i;
    return (s + ss.str());
}

cgi::cgi(ReadRequest request, std::string cgiPath, int fd, std::string path): _cgiPath(cgiPath), _fd(fd), _path(path)
{
    // bedel dak path li generiti b _cgiPath
    this->request = request;
    // std::string path = request.getUriPath();

    query_params = request.getQueryParams();
    file = path;
    cgi_error = 0;
    _outputfile = concat("file_", _fd);
    setenvcgi();
}


void    cgi::setenvcgi(void)
{
    setenv("SERVER_SOFTWARE","webserv", 1);
    setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
	setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
	setenv("REDIRECT_STATUS", "200", 1);
    setenv("REQUEST_METHOD", request.getMethod().c_str(), 1);
    setenv("SCRIPT_FILENAME", file.c_str() , 1);
    setenv("SERVER_PORT", std::to_string(request.getPort()).c_str(),1);
	setenv("SERVER_NAME", request.getHost().c_str(),1);
    setenv("HTTP_COOKIE",request.getCookies().c_str(),1);
    setenv("CONTENT_TYPE", request.getContentType().c_str(), 1);
	setenv("CONTENT_LENGTH", std::to_string(request.getBodyFileLength()).c_str(), 1);
    setenv("PATH_INFO", request.getUriPath().c_str(), 1);
    // setenv("PATH_TRANSLATED", "", 1);
    if (request.getMethod() == "GET")
    {
        setenv("QUERY_STRING", query_params.c_str(), 1);
    }
    if(request.getMethod() == "POST")
    {
        // setenv("CONTENT_TYPE", request.getContentType().c_str(), 1);
		// setenv("CONTENT_LENGTH", std::to_string(request.getBodyFileLength()).c_str(), 1);
    }
    args[0] = (char*)_cgiPath.c_str();
	args[1] = (char*)file.c_str();
    args[2] = NULL;
    fd_output = open(_outputfile.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0666);
}

int    cgi::executecgi(void)
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
        fd_input = open(request.getRequestFileName().c_str(), O_RDONLY);
        if (fd_input < 0)
            std::cerr << strerror(errno) << std::endl;
        dup2(fd_input, 0);
        dup2(fd_output, 1);
        execve(args[0], args, environ);
        exit(wstatus);
    }
    else
    {
        waitpid(pid, NULL, 0);
        if (WIFEXITED(wstatus))
            cgi_error = WEXITSTATUS(wstatus);
    }
    return (cgi_error);
}

cgi::~cgi()
{
    close(fd_output);
    close(fd_input);
}

std::string cgi::getCgiRetPath(void) const
{
    return this->_outputfile;
}