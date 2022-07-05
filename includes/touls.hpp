#pragma once

#include <iostream>
#include <string>
#include "./parser.hpp"

std::string	 errorPage(std::string error);
int	matchLocationAndUri(std::vector<Location> location, std::string uriPath);