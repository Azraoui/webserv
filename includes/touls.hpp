#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "./parser.hpp"

std::string	 errorPage(std::string error, std::string msg);
int	matchLocationAndUri(std::vector<Location> location, std::string uriPath);
std::string errRespone(int err, std::map<int, std::string> errs);
std::string redirect(int err, std::map<int, std::string> errs, std::string link);
std::string sendGetResponse(std::string indexPath, std::string contentType);
std::string	getMimeType(std::string key, std::map<std::string, std::string> mimeMap);
std::string sendAutoIndexResponse(std::string body, std::string contentType);
std::string      readFileIntoString(const std::string& path);