/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-azra <ael-azra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:55:45 by ael-azra          #+#    #+#             */
/*   Updated: 2022/06/13 15:57:09 by ael-azra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "lexer.hpp"
#include <fstream>
#include <streambuf>
#include <string>

int	parsingConfigFile(std::string fileName);