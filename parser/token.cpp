/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:29:28 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/13 16:03:54 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser/token.hpp"

t_token* init_token(enum s_token::types typ, std::string value)
{
	t_token *token;
	token = new t_token;
	token->type = typ;
	token->value = value;

	return token;
}