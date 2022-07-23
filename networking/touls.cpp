#include "../includes/touls.hpp"

std::string	 errorPage(std::string error, std::string msg)
{
std::string htmlPage;
htmlPage = "<!DOCTYPE html>\n"\
"<html lang=\"en\">\n"\
"<head>\n"\
"	<style>\n"\
"		h1 {text-align: center; margin-top: 10%; color: red; font-size: 70px;}\n"\
"		h2 {text-align: center; margin-top: 3%; color: black; font-size: 50px;}\n"\
"	</style>\n"\
"	<meta charset=\"UTF-8\">\n"\
"	<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"\
"	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"\
"	<title>Error</title>\n"\
"</head>\n"\
"<body>\n"\
"		<h1>Error " + error + "</h1>\n"\
"		<h2>" + msg + "</h2>\n"\
"</body>\n"\
"</html>";
	return htmlPage;
}

int	matchLocationAndUri(std::vector<Location> location, std::string uriPath)
{
	std::string temp;
	int			count = INT_MAX, j;
	int			index = -1;

	for (size_t i = 0; i < location.size(); i++)
	{
		temp = uriPath;
		j = 0;
		if (location[i]._locationPath == uriPath)
			return i;
		while (!temp.empty())
		{
			if (temp.find_last_of("/") == temp.npos)
				break;
			if (temp.find_last_of("/") + 1 != temp.size())
				temp.erase(temp.find_last_of("/") + 1);
			else
				temp.erase(temp.find_last_of("/"));
			j++;
			if (temp == location[i]._locationPath)
				break;
		}
		if (j && !temp.empty())
		{
			if (j < count)
			{
				count = j;
				index = i;
			}
		}
	}
	return index;
}

std::string errRespone(int err, std::map<int, std::string> errs, Location &location, Vserver &server)
{
	struct stat	buf;
	std::string body;
	std::string contentLength;
	if (!location._errorPage[std::to_string(err)].empty() && !lstat(location._errorPage[std::to_string(err)].c_str(), &buf))
	{
		std::string path = location._errorPage[std::to_string(err)];
		if (!(buf.st_mode & S_IFDIR) && (buf.st_mode & S_IREAD))
		{
			readFileIntoString(path, &body);
			contentLength = "Content-Length: " + std::to_string(body.size()) + "\n\n";
		}
		else
		{
			body = "\n" + errorPage(std::to_string(err), errs[err]);
			contentLength = "Content-Length: " + std::to_string(errorPage(std::to_string(err), errs[err]).size()) + "\n";
		}
	}
	else if (!server._errorPage[std::to_string(err)].empty() && !lstat(server._errorPage[std::to_string(err)].c_str(), &buf))
	{
		std::string path = server._errorPage[std::to_string(err)];
		if (!(buf.st_mode & S_IFDIR) && (buf.st_mode & S_IREAD))
		{
			readFileIntoString(path, &body);
			contentLength = "Content-Length: " + std::to_string(body.size()) + "\n\n";
		}
		else
		{
			body = "\n" + errorPage(std::to_string(err), errs[err]);
			contentLength = "Content-Length: " + std::to_string(errorPage(std::to_string(err), errs[err]).size()) + "\n";
		}
	}
	else
	{
		body = "\n" + errorPage(std::to_string(err), errs[err]);
		contentLength = "Content-Length: " + std::to_string(errorPage(std::to_string(err), errs[err]).size()) + "\n";
	}
	std::string firstLine = "HTTP/1.1 " + std::to_string(err) + " " + errs[err] + "\n";
	std::string contentType = "Content-Type: text/html\n";
	return firstLine + contentType + contentLength + body;
}

std::string redirect(int err, std::map<int, std::string> errs, std::string link)
{
	std::string firstLine = "HTTP/1.1 " + std::to_string(err) + " " + errs[err] + "\n";
	std::string location = "Location: " + link + "\n\n";
	return firstLine + location;
}

std::string sendGetResponse(std::string indexPath, std::string contentType)
{
	std::string body;
	std::string firstLine = "HTTP/1.1 200 OK\n";
	std::string _contentType = "Content-Type: " + contentType + "\n";
	readFileIntoString(indexPath, &body);
	std::string contentLength = "Content-Length: " + std::to_string(body.size()) + "\n\n";
	return firstLine + _contentType + contentLength + body;
}

std::string sendAutoIndexResponse(std::string body, std::string contentType)
{
	std::string firstLine = "HTTP/1.1 200 OK\n";
	std::string _contentType = "Content-Type: " + contentType + "\n";
	std::string contentLength = "Content-Length: " + std::to_string(body.size()) + "\n\n";
	return firstLine + _contentType + contentLength + body;
}

std::string	getMimeType(std::string key, std::map<std::string, std::string> mimeMap)
{
	if (mimeMap.find(key) != mimeMap.end())
		return mimeMap[key];
	else
		return "application/octet-stream";
}

void	readFileIntoString(const std::string& path, std::string *fileContent) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    *fileContent =  std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
	input_file.close();
}

// int	deleteFiles(const std::string &path, bool directory)
// {
// 	std::cout << "i was here " << directory << std::endl;
// 	if (directory)
// 	{
// 		int i = system(("rm -rf " + path + "*").c_str());
// 		i = WEXITSTATUS(i);
// 		std::cout << " i = " << i << std::endl;
// 		if (i != 1)
// 			return 0;
// 	}
// 	else if (system(("rm -rf " + path).c_str()) != -1)
// 		return 0;
// 	return 1;
// }

int    deleteFiles(std::string path, bool isDir)
{
    DIR *dir = NULL;
    struct stat s;
    struct dirent *dirIterator;
    std::string filePath;
	std::cout << "here " << std::endl;
	if (!isDir)
	{
		if (unlink(path.c_str()) < 0)
        {
            if (errno == EACCES)
                return 403;
            else if (errno == EEXIST)
                return 500;
        }
		return 0;
	}
    dir = opendir(path.c_str());
    if (!dir)
        return 500;
    while ((dirIterator = readdir(dir)) != NULL)
    {
        if (!strcmp(dirIterator->d_name, ".") || !strcmp(dirIterator->d_name, ".."))
            continue;
        filePath = path + dirIterator->d_name;
        if (stat(filePath.c_str(), &s) < 0)
            return 500; 
        if (S_ISDIR(s.st_mode))
        {
            deleteFiles(filePath + "/", true);
            continue;
                
        }
        if (unlink(filePath.c_str()) < 0)
        {
            if (errno == EACCES)
                return 403;
            else if (errno == EEXIST)
                return 500;
        }
    }
    if (rmdir(path.c_str()) < 0)
        return 500;
    closedir(dir);
	return 0;
}

std::string	responseCgi(std::string cgiFilePath)
{
	std::string firstLine;
	std::string contentType;
	std::string contentLength;
	std::string	ret;
	std::string bodyContent;
	std::string tmp;
	std::string header;

	readFileIntoString(cgiFilePath, &tmp);
	firstLine = "HTTP/1.1 200 OK\n";
	header = firstLine;
	if (tmp.find("\r\n\r\n") != tmp.npos)
	{
		header.append(tmp.substr(0, tmp.find("\r\n\r\n")));
		header += "\n";
		bodyContent = tmp.substr(tmp.find("\r\n\r\n") + 4); 
	}
	contentType = "Content-Type: text/html\n";
	contentLength = "Content-Length: " + std::to_string(bodyContent.size()) + "\n\n";
	header.append(contentType);
	header.append(contentLength);
	ret = header + bodyContent;
	system(("rm -f " + cgiFilePath).c_str());
	return ret;
}