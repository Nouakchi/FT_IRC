/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetRmMode.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:38:23 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/06 09:57:16 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

void	setChnlOp( t_server *server, Client *clnt, std::vector<std::string>& cmd )
{
	if (cmd.size() == 4)
	{
		std::string chnlUser = cmd[3];
		std::string chnlName = cmd[1];

		Channel* Chnl = server->channels[chnlName];
		std::map<std::string, Client*>::iterator it = Chnl->users.find(chnlUser);
		std::map<std::string, Client*>::iterator it2 = Chnl->users.find("@" + chnlUser);
		if (it2 == Chnl->users.end() && it != Chnl->users.end())
		{
			Client* tmp = it->second;
			Chnl->users.erase(it);
			Chnl->users.insert(std::pair<std::string, Client*>("@" + chnlUser, tmp));
		}
		else if (it2 == Chnl->users.end())
			return(error_replay(server, ERR_USERNOTINCHANNEL, *clnt, chnlUser + " :is not on channel\r\n"));
		
	}
	else
		return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));

}

void	SetMode( t_server *server, Client *clnt, std::vector<std::string>& cmd )
{
	std::string chnlName = cmd[1];

	if (cmd[2][0] == 'k')
	{
		if (cmd.size() == 4)
			server->channels[chnlName]->k = cmd[3];
		else
			return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));
	}
	else if (cmd[2][0] == 'o')
		setChnlOp(server, clnt, cmd);
	else if (cmd[2][0] == 'l')
	{
		if (cmd.size() == 4 && (cmd[3].find_first_not_of("0123456789") == std::string::npos))
			server->channels[chnlName]->l = atoi(cmd[3].c_str());
		else // not a valid arguement
			return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));
	}
	while (!cmd[2].empty())
	{
		if (cmd[2][0] == 'i')
			server->channels[chnlName]->i = true;
		else if (cmd[2][0] == 't')
			server->channels[chnlName]->t = true;
		cmd[2].erase(0,1);
	}
}

void	RmChnlOp( t_server *server, Client *clnt, std::vector<std::string>& cmd )
{
	if (cmd.size() == 4)
	{
		std::string chnlName = cmd[1];
		std::string chnlUser = cmd[3];
		Channel* Chnl = server->channels[chnlName];
		
		std::map<std::string, Client*>::iterator it2 = Chnl->users.find("@" + chnlUser);
		if (it2 != Chnl->users.end()) // to be verified
		{
			Client* tmp = it2->second;
			Chnl->users.erase(it2);
			Chnl->users.insert(std::pair<std::string, Client*>(chnlUser, tmp));
		}
	}
	else
		return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));
}

void	RmMode(t_server *server, Client *clnt, std::vector<std::string>& cmd)
{
	std::string chnlName = cmd[1];


	// after setting a MODE succefully i reply with (:irc.server.com 324 <your_nick> #channel -k)
	if (cmd[2][0] == 'k')
	{
		if (cmd.size() == 3)
			server->channels[chnlName]->k = "";
		else
			return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));
	}
	else if (cmd[2][0] == 'o')
		RmChnlOp(server, clnt, cmd);
	else if (cmd[2][0] == 'l')
	{
		if (cmd.size() == 4 && (cmd[3].find_first_not_of("0123456789") == std::string::npos))
			server->channels[chnlName]->l = atoi(cmd[3].c_str());
		else // not a valid arguement
			return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));
	}
	while (!cmd[2].empty())
	{
		if (cmd[2][0] == 'i')
			server->channels[chnlName]->i = false;
		else if (cmd[2][0] == 't')
			server->channels[chnlName]->t = false;
		cmd[2].erase(0,1);
	}
	
}
