/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:27:48 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/20 03:15:26 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

void	error_replay( t_server* server ,int errNbr, Client clnt, std::string err)
{
	std::string errMsg;
	errMsg =  server->host_name + " " + std::to_string(errNbr) + " " + clnt.getNickName() + err + "\r\n";
	send(clnt.getSocket(), errMsg.c_str(), errMsg.size(), 0);
}

std::string skipSpaces(std::string input)
{
	std::istringstream iss(input);
	std::string output;
	std::string str;

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

void splitString(const std::string& cmd, std::vector<std::string>& substrs, char delim)
{
	std::istringstream iss(cmd);
	std::string token;
	std::string realname;

	while (std::getline(iss, token, delim)) {
		if (token[0] == ':' )
		{
			if (token.length() >= 1) 
				substrs.push_back(cmd.substr(1 + cmd.find(":")));
			return;
		}
		else if (!token.empty())
			substrs.push_back(token);
	}

	return ;
}

bool	ModesSyntaxe(std::string str)
{
	// to be optimized 
	if (str.find_first_not_of("+-itkol") != std::string::npos || str.length() > 10)
		return false;

	size_t lngth = str.length();
	for (size_t i = 1; i < lngth; i++)
		if((str[i] == '+' || str[i] == '-') &&
			(str[i - 1] == '+' || str[i - 1] == '-'))
				return false;

	std::set<char> stContainer(str.begin(), str.end()); // check duplicates
	if (stContainer.size() != str.length())
		return false;

	return true;
}

std::string	str_toupper(std::string flag)
{
	std::string tmp(flag);

	for (size_t i = 0; i < flag.length(); i++)
		tmp[i] = toupper(flag[i]);
	return tmp;
}
