/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kadigh_util.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:27:48 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/06 12:02:05 by aaoutem-         ###   ########.fr       */
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
