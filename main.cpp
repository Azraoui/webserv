/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:05:46 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/24 10:47:53 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/parser.hpp"

using namespace std;

int	main(int ac, char **av)
{
	if (ac == 2)
		parsingConfigFile(av[1]);
	else
		cerr << "Error:\nMissing Configuration file!" << endl;
	return 0;
}
