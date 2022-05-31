/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:05:46 by ael-azra          #+#    #+#             */
/*   Updated: 2022/05/31 07:23:32 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/webserv.hpp"

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
		test();
		(void)av; 
	}
	else
		cerr << "Error:\nMissing Configuration file!" << endl;
	return 0;
}
