#include "../includes/touls.hpp"

std::string	 errorPage(std::string error)
{
std::string htmlPage;
htmlPage = "<!DOCTYPE html>\n"\
"<html lang=\"en\">\n"\
"<head>\n"\
"	<style>\n"\
"		h1 {text-align: center; margin-top: 25%; color: red; font-size: 100px;}\n"\
"	</style>\n"\
"	<meta charset=\"UTF-8\">\n"\
"	<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"\
"	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"\
"	<title>Error</title>\n"\
"</head>\n"\
"<body>\n"\
"		<h1>Error " + error + "</h1>\n"\
"</body>\n"\
"</html>";
	return htmlPage;
}