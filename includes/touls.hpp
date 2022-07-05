#pragma once

#include <iostream>
#include <string>
#include "./parser.hpp"

std::string	 errorPage(std::string error, std::string msg);
int	matchLocationAndUri(std::vector<Location> location, std::string uriPath);
std::string errRespone(int err, std::map<int, std::string> errs);
std::string redirect(int err, std::map<int, std::string> errs, std::string link);