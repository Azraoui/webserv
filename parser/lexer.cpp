/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:53:11 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/14 18:17:51 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser/lexer.hpp"

Lexer::Lexer(std::string contents)
{
	this->_lexer = new struct s_lexer;
	this->_lexer->contents = contents;
	this->_lexer->i = 0;
	this->_lexer->c = contents[this->_lexer->i];
}

Lexer::~Lexer()
{}

// implement Lexer methods

void	Lexer::advance(void)
{
	if (_lexer->i < _lexer->contents.length())
	{
		_lexer->i += 1;
		_lexer->c = _lexer->contents[_lexer->i];
	}
}

void	Lexer::skip_whitespace(void)
{
	while (_lexer->c == ' ' || _lexer->c == '\n')
		this->advance();
}

t_token*	Lexer::collect_id(void)
{
	std::string	value;

	while (ft_isString(_lexer->c))
	{
		value += _lexer->c;
		this->advance();
	}
	return init_token(s_token::TOKEN_ID, value);
}

t_token*	Lexer::advance_with_token(t_token *token)
{
	this->advance();
	return token;
}

t_token*	Lexer::get_next_token(void)
{
	while (_lexer->i < _lexer->contents.length())
	{
		if (_lexer->c == ' ' || _lexer->c == '\n')
			this->skip_whitespace();
		if (ft_isString(_lexer->c))
			return this->collect_id();
		switch (_lexer->c)
		{
			case ';':
				return this->advance_with_token(init_token(s_token::TOKEN_SEMI, this->char_to_string()));
				break;
			case '{':
				return this->advance_with_token(init_token(s_token::TOKEN_LBRACE, this->char_to_string()));
				break;
			case '}':
				return this->advance_with_token(init_token(s_token::TOKEN_RBRACE, this->char_to_string()));
				break;
			case '[':
				return this->advance_with_token(init_token(s_token::TOKEN_LSBRACE, this->char_to_string()));
				break;
			case ']':
				return this->advance_with_token(init_token(s_token::TOKEN_RSBRACE, this->char_to_string()));
				break;
		}
	}
	return NULL;
}

std::string	Lexer::char_to_string(void)
{
	std::string s(1, _lexer->c);
	return s;
}

bool	ft_isString(char c)
{
	if (c == '{' || c == '}')
		return false;
	else if (c == '[' || c == ']')
		return false;
	else if (c == ';' || c == ' ')
		return false;
	else
		return true;
}
