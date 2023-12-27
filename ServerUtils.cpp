/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 23:02:51 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/27 03:00:36 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string    displayTimestamp()
{
	std::string time_;

	std::time_t currentTime = std::time(0);

	std::tm* timeInfo = std::localtime(&currentTime);

	char buffer[23];
	std::strftime(buffer, 23, "%Y/%m/%d %H:%M:%S", timeInfo);
	time_ = buffer;

	return (time_);
}

bool	nickInUse(std::string nickname)
{
	// check in the container for the nick
	return true;
}
void user_cmd(std::vector<std::string>& cmd)
{
	
}

bool valid_nickname(std::string nickname)
{
	std::string special_set = "-|[]|\\`^{}";

	if (nickname.empty() || isdigit(nickname[0]))
		return false;
	for (int i = 0; i < nickname.length(); i++)
		if (!isalnum(nickname[i]) && (special_set.find(nickname[i]) == std::string::npos))
			return false;
	return true;
}

void Server::wlcmMsg(Client clnt)
{
	std::string wlcmMsg;
	std::string RPL_urhost;
	std::string RPL_created;

	wlcmMsg = this->hostname + " 001 Welcome to the Internet Relay Network " 
			+ clnt.nickName + "!" + clnt.userName + "\r\n";
	send(clnt.sfd, wlcmMsg.c_str(), wlcmMsg.size(), 0);

	RPL_urhost = this->hostname + " 002 Your host is " + this->hostname + "\r\n";
	send(clnt.sfd, RPL_urhost.c_str(), RPL_urhost.size(), 0);

	RPL_created = this->hostname + " 003 This server was created "
			+ this->creation_time  + "\r\n";
	send(clnt.sfd, RPL_created.c_str(), RPL_created.size(), 0);
}

void	Server::checkAuth(Client& clnt)
{
	std::string tosend;

	if (clnt.clnt_entred_passwd != this->passwd)
	{
		error_replay(ERR_PASSWDMISMATCH, clnt, " :Password incorrect");
		close (clnt.sfd);
	}
	else if (!valid_nickname(clnt.nickName))
	{
		error_replay(ERR_ERRONEUSNICKNAME, clnt, " :Erroneus nickname");
	}
	// else if (nickInUse(clnt.nickName)) //
	// {
	//	error_replay(ERR_NICKNAMEINUSE, clnt, " :Nickname is already in use\r\n");
	// }
	else  // Valid Authentif  send a wlcm msg
		return;

	clnt.AuthFlag--;
}

void	Server::error_replay(int errNbr, Client& clnt, std::string err)
{
	std::string errMsg;

	errMsg = this->hostname + " " + std::to_string(errNbr) + " " + clnt.nickName + err;
	std::cout << err;
	send(clnt.sfd, errMsg.c_str(), errMsg.size(), 0);
}
