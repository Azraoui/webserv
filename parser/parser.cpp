/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:00:33 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/13 16:19:55 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser/parser.hpp"

int	parsingConfigFile(std::string fileName)
{
	std::ifstream configFile(fileName);

	if (configFile)
	{
		std::string contents;
		configFile.seekg(0, std::ios::end);   
		contents.reserve(configFile.tellg());
		configFile.seekg(0, std::ios::beg);
		contents.assign((std::istreambuf_iterator<char>(configFile)),
            std::istreambuf_iterator<char>());
		
		//------------------------------------

		Lexer lex = Lexer(contents);
		t_token *token = NULL;
		while ((token = lex.get_next_token()) != NULL)
		{
			std::cout << "type = " << token->type << " value = " << token->value << std::endl;
		}
		// std::cout << contents << std::endl;
		configFile.close();
	}
	else
		std::cout << "Error\nFile doesn't exist" << std::endl;
	return (0);
}