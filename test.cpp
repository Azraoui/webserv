#include <iostream>

int main()
{
	std::string path = "/test//index.php/";
	std::string location = "/";

	std::cout << path.find_first_not_of("/") << std::endl;
	if (path.find_last_of("8") == path.npos)
		return 0;
	path.erase(path.find_last_of("/"));
	std::cout << path << std::endl;
	path.erase(path.find_last_of("/"));
	std::cout << path << std::endl;
	return 0;
}