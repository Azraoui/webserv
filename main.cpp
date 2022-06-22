/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:05:46 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/16 21:41:35 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/webserv.hpp"
#include "./includes/parser/parser.hpp"

using namespace std;

void	test(void)
{
	int	server_fd;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd < 0)
		perror("can't create socket");
	cout << server_fd << endl;
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		parsingConfigFile(av[1]);
	}
	else
		cerr << "Error:\nMissing Configuration file!" << endl;
	return 0;
}
