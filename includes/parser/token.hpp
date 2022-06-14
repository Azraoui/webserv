/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:19:30 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/14 18:17:58 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

typedef struct s_token
{
	enum types
	{
		TOKEN_ID,
		TOKEN_SEMI,
		TOKEN_LBRACE,
		TOKEN_RBRACE,
		TOKEN_LSBRACE,
		TOKEN_RSBRACE,
		TOKEN_EOF
	} type;
	std::string value;
} t_token;

t_token	*init_token(enum s_token::types typ, std::string value);