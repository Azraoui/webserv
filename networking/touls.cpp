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

std::string errRespone(int err, std::map<int, std::string> errs)
{
	std::string firstLine = "HTTP/1.1 " + std::to_string(err) + " " + errs[err] + "\n";
	std::string contentType = "Content-Type: text/html\n";
	std::string contentLength = "Content-Length: " + std::to_string(errorPage(std::to_string(err), errs[err]).size()) + "\n";
	std::string body = "\n" + errorPage(std::to_string(err), errs[err]);
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
	std::ifstream file;
	file.open(indexPath);
	std::string tmp;
	while(!file.eof())
	{
		file >> tmp;
		body.append(tmp);
	}
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

int	deleteFiles(const std::string &path, bool directory)
{
	if (directory)
	{
		if (system(("rm -rf " + path + "*").c_str()))
			return 0;
	}
	else if (system(("rm -rf " + path).c_str()))
		return 0;
	return 1;
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
	if (tmp.find("\n\n") != tmp.npos)
	{
		header.append(tmp.substr(0, tmp.find("\n\n")));
		bodyContent = tmp.substr(tmp.find("\n\n") + 2);
	}
	contentType = "Content-Type: text/html\n";
	contentLength = "Content-Length: " + std::to_string(bodyContent.size()) + "\n\n";
	header.append(contentType);
	header.append(contentLength);
	ret = header + bodyContent;
	return ret;
}