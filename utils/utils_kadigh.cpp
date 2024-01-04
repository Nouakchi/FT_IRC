/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_kadigh.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 07:35:00 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/03 07:36:48 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"


std::string skipSpaces(std::string input)
{
	std::istringstream iss(input);
	std::string output;
	std::string str;
	int i = 0;

	while (getline(iss, str, ' ')) {
		if (!str.empty())
		{
			output += str;
			if (!iss.eof()) {
				output += " ";
			}
		}
	}
	return output;
}

void splitString(const std::string& cmd, std::vector<std::string>& substrs)
{
	std::istringstream iss(cmd);
	std::string token;
	std::string realname;

	while (std::getline(iss, token, ' ')) {
		if (token[0] == ':')
		{
			break;
		}
		else if (!token.empty())
			substrs.push_back(token);
	}
	if (token[0] == ':')
	{
		std::getline(iss, realname,'\n');// /r
		token = skipSpaces(token.substr(1) + realname);
		if (token.empty())
		{
			std::cout << substrs.size() << std::endl;
			return ;
		}
		substrs.push_back(token);
	}
	return ;
}