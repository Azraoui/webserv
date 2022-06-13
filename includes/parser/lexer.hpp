/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:45:00 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/13 15:40:55 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "token.hpp"
#include "ctype.h"

typedef	struct s_lexer
{
	char	c;
	size_t	i;
	std::string	contents;

}	t_lexer;

class Lexer
{
	private:
		t_lexer *_lexer;

	public:
		Lexer(std::string contents);
		~Lexer();
		// lexer methods
		void		advance(void);
		void		skip_whitespace(void);
		t_token*	get_next_token(void);
		t_token*	collect_id(void);
		t_token*	advance_with_token(t_token *token);
		std::string	char_to_string(void);
};

bool	ft_isString(char c);