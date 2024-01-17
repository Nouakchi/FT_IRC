/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetRmMode.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:38:23 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/17 11:29:34 by aaoutem-         ###   ########.fr       */
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
			return(error_replay(server, ERR_USERNOTINCHANNEL, *clnt, chnlUser + " :is not on channel"));
		
	}
	else
		return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters"));

}

void	SetMode( t_server *server, Client *clnt, std::vector<std::string>& cmd,  char c, int i)
{
	std::string chnlName = cmd[1];

	if (c == 'k')
	{
		if (cmd.size() == 4)
			server->channels[chnlName]->key = cmd[i];
		else
			return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters"));
	}
	else if (cmd[2][0] == 'o')
		setChnlOp(server, clnt, cmd);
	else if (cmd[2][0] == 'l')
	{
		if (cmd.size() == 4 && (cmd[3].find_first_not_of("0123456789") == std::string::npos))
		{
			int limit = atoi(cmd[3].c_str());
			if (limit > 0)
			{
				server->channels[chnlName]->l = limit;
				std::string msg = ":" + server->host_name + " MODE " + chnlName + " +l " + cmd[3] + "\r\n";
				// error_replay(server, RPL_CHANNELMODEIS, *clnt, chnlName + " +l " + );
				// std::string msg = ":" + clnt->getNickName() + "!" + clnt->getLoginName() + "@" + server->host_name + " MODE " + chnlName + " +l\r\n";
				std::cout << "{" << msg << "}" << std::endl;
				send(clnt->getSocket(), msg.c_str(), msg.size(), 0);
			}
			else // not a valid arguement
				return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters"));
		}
		else // not a valid arguement
			return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters"));
	}
	while (!cmd[2].empty())
	{
		if (cmd[2][0] == 'i')
		{
			server->channels[chnlName]->i = true;
			// std::string msg = ":" + clnt->getNickName() + "!~" + clnt->getLoginName() + "@" + server->host_name + " MODE " + chnlName + " +i\r\n";
			std::string msg = ":" + server->host_name + " MODE " + chnlName + " +i\r\n";
			std::cout << "{" << msg << "}" << std::endl;
			send(clnt->getSocket(), msg.c_str(), msg.size(), 0);
		}
		else if (cmd[2][0] == 't')
		{
			// std::string msg = ":" + clnt->getNickName() + "!~" + clnt->getLoginName() + "@" + server->host_name + " MODE " + chnlName + " +i\r\n";
			std::string msg = ":" + server->host_name + " MODE " + chnlName + " +t\r\n";
			std::cout << "{" << msg << "}" << std::endl;
			send(clnt->getSocket(), msg.c_str(), msg.size(), 0);
			server->channels[chnlName]->t = true;
		}
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
			// to check
			std::string msg = ":" + clnt->getNickName() + "!" + clnt->getLoginName() + "@" + server->host_name + "MODE " + chnlName + " -o " + chnlUser + "\r\n";
			send(clnt->getSocket(), msg.c_str(), msg.size(), 0);
			//
		}
	}
	else
		return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));
}

void	RmMode(t_server *server, Client *clnt, std::vector<std::string>& cmd, char c, int i)
{
	std::string chnlName = cmd[1];

	// after setting a MODE succefully i reply with (:irc.server.com 324 <your_nick> #channel -k)
	if (cmd[2][0] == 'k')
	{
		if (cmd.size() == 3)
		{
			server->channels[chnlName]->key = "";
			std::string msg = ":" + clnt->getNickName() + "!" + clnt->getLoginName() + "@" + server->host_name + "MODE " + chnlName + " -k\r\n";
			send(clnt->getSocket(), msg.c_str(), msg.size(), 0);
		}
		else
			return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));
	}
	else if (cmd[2][0] == 'o')
		RmChnlOp(server, clnt, cmd);
	else if (cmd[2][0] == 'l')
	{
		if (cmd.size() == 3)
		{
			server->channels[chnlName]->l = -1;
			std::string msg = ":" + clnt->getNickName() + "!" + clnt->getLoginName() + "@" + server->host_name + "MODE " + chnlName + " -l\r\n";
			send(clnt->getSocket(), msg.c_str(), msg.size(), 0);
		}
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
