/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kadigh.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 07:36:16 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/06 18:37:26 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

bool	parseChannelName( t_server *server, std::string& ChnlName)
{
	// return true;

	if ((ChnlName[0] != '#' && ChnlName[0] != '&')
		|| ChnlName.length() == 1)
	{
		return false;
	}

	std::string special_set = ", \r\n\a\0";
	for (size_t i = 1; i < ChnlName.length(); i++)
		if ((special_set.find(ChnlName[i]) != std::string::npos))
			return false;

	// check if there is  a channel with this name
	std::map<std::string, Channel*>::iterator it = server->channels.find(ChnlName);
	if (it == server->channels.end())
		return false;

	return true;
}

bool	OpExecCommand( t_server *server, Client *clnt, std::string chnlName)
{
	std::string nick("@" + clnt->getNickName());

	Channel*	chnl = server->channels[chnlName];
	std::map<std::string, Client*>::iterator it = chnl->users.find(nick);
	if (it == chnl->users.end())
		return false;

	return true;
}

void	ChannelOP(Channel *chnl, std::string* modes)
{
	bool chnHasOpFlag = false;

	std::map<std::string, Client *>::iterator it = chnl->users.begin();

	while (it != chnl->users.end())
	{
		if (it->first[0] == '@')
		{
			modes[1].append(" " + it->first);
			chnHasOpFlag = true;
		}
		it++;
	}
	if (chnHasOpFlag)
		modes[0].append("o");

	return ;
}

void	listCHmodes( t_server *server, Client *clnt , std::string ChnlName)
{
	std::string modes[2];

	Channel *chnl = server->channels[ChnlName];

	if (chnl->i)
		modes[0].append("i");
	if(chnl->t)
		modes[0].append("t");
	if (!chnl->key.empty())
	{
		modes[0].append("k");
		modes[1].append(" " + chnl->key);
	}
	if (chnl->l > 0)
	{
		modes[0].append("l");
		modes[1].append(" " + std::to_string(chnl->l));
	}
	ChannelOP(chnl, modes);
	
	//send replay 

	if (!modes[0].empty())
		modes[0].insert(0, "+");
	std::cout << ChnlName + " " + modes[0] + " " + modes[1] << std::endl;
	error_replay(server, RPL_CHANNELMODEIS, *clnt, ChnlName + " " + modes[0] + " " + modes[1]);// to be verified
}


void	ApplyMode( t_server *server, Client *clnt, std::vector<std::string>& cmd)
{
	int Set_RmModeSign = 0 + (cmd[2][0] == '+')*1 + (cmd[2][0] == '-')*(-1);

	cmd[2].erase(0,1);

	if (cmd[2].find_first_not_of("itkol") != std::string::npos)
		return(error_replay(server,ERR_UNKNOWNMODE, *clnt, cmd[2] + " :is unknown mode char to me"));

	if (cmd[2].length() == 0  || cmd[2].length() > 2  // bcz we could only apply one mode at a time the only allowed combination is the "it" one
		|| cmd[2][0] == cmd[2][1])
		return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters"));

	if (Set_RmModeSign > 0)
		SetMode(server, clnt, cmd);
	else
		RmMode(server, clnt, cmd);
}

int	ft_modeCmd( t_server *server, Client *clnt, std::string buff)
{

	std::vector<std::string> cmd;
	splitString(buff, cmd);

	if (cmd.size() < 2 || cmd.size() > 4)
	{
		error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters");
		return (0);
	}

	if (!parseChannelName(server, cmd[1])) //parse the channel name && if exist
	{
		error_replay(server, ERR_NOSUCHCHANNEL, *clnt, " :No such channel");
		return (0);
	}

	if (!OpExecCommand(server, clnt, cmd[1])) // if the user is not an operator he is not allowed to change the channel modes
		return (error_replay(server,ERR_CHANOPRIVSNEEDED, *clnt, cmd[1] + " :You're not channel operator"),0);

	if ( cmd.size() == 2 )
		listCHmodes(server, clnt, cmd[1]);
	else if (cmd[2][0] == '+' || cmd[2][0] == '-')
		ApplyMode(server, clnt, cmd);
	else 
		return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters"), 0);

	return 1;
}
