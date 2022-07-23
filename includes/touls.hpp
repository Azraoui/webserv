#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "./parser.hpp"
#include "dirent.h"
#include "sys/stat.h"
#include <unistd.h>

std::string		errorPage(std::string error, std::string msg);
int				matchLocationAndUri(std::vector<Location> location, std::string uriPath);
std::string		errRespone(int err, std::map<int, std::string> errs, Location &location, Vserver &server);
std::string		redirect(int err, std::map<int, std::string> errs, std::string link);
std::string		sendGetResponse(std::string indexPath, std::string contentType);
std::string		getMimeType(std::string key, std::map<std::string, std::string> mimeMap);
std::string		sendAutoIndexResponse(std::string body, std::string contentType);
void			readFileIntoString(const std::string& path, std::string *fileContent);
int    			deleteFiles(std::string path, bool isDir);
std::string		responseCgi(std::string cgiFilePath);