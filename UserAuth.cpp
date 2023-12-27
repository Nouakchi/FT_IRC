/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserAuth.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 02:44:16 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/27 09:10:18 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void chof_vct(std::vector<std::string>& vct)
{
	std::cout << vct.size() << std::endl;
	std::cout << "-----------------------------------\n";
	for (int i = 0;i< vct.size(); i++)
		std::cout <<"'"<< vct[i] <<"'" << std::endl;
	std::cout << "-----------------------------------\n";
}

int Server::processPass(Client& clnt, std::vector<std::string>& cmd)
{
	chof_vct(cmd);
	if (cmd.size() != 2)
	{
		error_replay(ERR_NEEDMOREPARAMS, clnt, " PASS :Not enough parametres\r\n");
		// return 0;
	}
	clnt.AuthFlag = 1;
	clnt.clnt_entred_passwd = cmd[1];
	return 0;
}

int Server::processNick(Client& clnt, std::vector<std::string>& cmd)
{
	chof_vct(cmd);
	if ( (cmd.size() != 2) || !valid_nickname(cmd[1]))
	{
		error_replay(ERR_ERRONEUSNICKNAME, clnt, " :Erroneus nickname\r\n");
		return 0;
	}
	else {
		if ( clnt.nickName.empty() ) // || !valid_nickname(clnt.nickName))
			clnt.AuthFlag++ ;
		clnt.nickName = cmd[1];
	}
	return 0;
}

int Server::processUser(Client& clnt, std::vector<std::string>& cmd)
{
	
	chof_vct(cmd);
	if (cmd.size() != 5){
		error_replay(ERR_NEEDMOREPARAMS, clnt, " USER :Not enough parametres\r\n");
		return 0;
	}
	// user_cmd(cmd);
	if ( clnt.userName.empty() )
		clnt.AuthFlag++ ;
	clnt.userName = cmd[1];
	clnt.realName = cmd[4];
	return 0;
}
