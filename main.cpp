/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:05:46 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/24 15:12:26 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/httpServer.hpp"

using namespace std;

void	test(void)
{
	int	server_fd;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd < 0)
		perror("cannot create socket");
	cout << server_fd << endl;
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		std::vector<Vserver>	servers;
		servers = parsingConfigFile(av[1]);

		HttpServer	httpServer(servers);
		

	}
	else if (ac == 1)
	{
		std::vector<Vserver>	servers;
		servers = parsingConfigFile("./config_files/siege.config");

		HttpServer	httpServer(servers);
		httpServer.runServers();

	}
	else
		cerr << "Error:\nMissing Configuration file!" << endl;
	return 0;
}
