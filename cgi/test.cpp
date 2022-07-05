#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

 
void cgiexecute(std::string sriptname, char **env)
{
    int cgi_error;

    // setenv("SERVER_PROTOCOL", "HTTP/1.1", 1);
    // setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
    // setenv("SERVER_SOFTWARE", "Webserv", 1);
    setenv("REDIRECT_STATUS", "200", 1);
    setenv("REQUEST_METHOD", "POST", 1);
    setenv("SCRIPT_FILENAME", sriptname.c_str() , 1);
     //setenv("QUERY_STRING", "user=hamadafhgfhgfhgfhgfhgfghfghhfg", 1);
    setenv("CONTENT_LENGTH", "35", 1);
    setenv("CONTENT_TYPE", "application/x-www-form-urlencoded;charset=utf-8", 1);
    int fd_output = open("file.html", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    int fd_input = open("body.txt",  O_RDONLY);

    char *args[2] = {(char*)"/usr/local/bin/php-cgi", NULL};
    
    int wstatus;
    int pid = fork();
    if (pid == 0)
    {
        dup2(fd_input, 0);
        dup2(fd_output, 1);
        execve(args[0], args, environ);
        exit(wstatus);
    }
    else
    {
        close(fd_output);
        waitpid(pid, &wstatus, 0);
        if (WIFEXITED(wstatus))
            cgi_error = WEXITSTATUS(wstatus);
        std::cout << cgi_error << std::endl;
    }
}


int main(int av, char **ac, char **env)
{
    cgiexecute("index.php", env);
}