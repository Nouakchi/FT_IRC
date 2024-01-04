/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kadigh.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 07:36:16 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/04 14:54:20 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/irc.h"

bool	parseChannelName( t_server *server, std::string& ChnlName)
{
	if (ChnlName[0] == '#' || ChnlName[0] == '&')
		return false;
	for (int i = 1; i < ChnlName.length(); i++)	/* if i could find a more optimized way*/
		if (!isalpha(ChnlName[i]))
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

void	listCHmodes()
{
	std::cout << "need to be Implemented\n";
}



void	ApplyMode( t_server *server, Client *clnt, std::vector<std::string>& cmd)
{
	int Set_RmModeSign = 0 + (cmd[2][0] == '+')*1 + (cmd[2][0] == '-')*(-1);

	cmd[2].erase(0,1);

	if (cmd[2].find_first_not_of("itkol") != std::string::npos)
		return(error_replay(server,ERR_UNKNOWNMODE, *clnt, cmd[2] + " :is unknown mode char to me"));

	if (Set_RmModeSign > 0)
		SetMode(server, clnt, cmd);
	else
		RmMode(server, clnt, cmd);


}

int ft_modeCmd( t_server *server, Client *clnt, std::string buff)
{

	std::vector<std::string> cmd;
	splitString(buff, cmd);

	if (cmd.size() < 2 || cmd.size() > 4)
	{
		error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n");
		return 0;
	}

	if (!parseChannelName(server, cmd[1]))
	{
		error_replay(server, ERR_NOSUCHCHANNEL, *clnt, " :No such channel\r\n");
		return 0;
	}

	if (!OpExecCommand(server, clnt, cmd[1])) // if the user is not an operator he is not allowed to change the channel modes
	{
		error_replay(server,ERR_CHANOPRIVSNEEDED, *clnt, cmd[1] + " :You're not channel operator\r\n");
		return 0;
	}

	if ( cmd.size() == 2 )
		listCHmodes();
	else if (cmd[2][0] == '+' || cmd[2][0] == '-')
	{
		ApplyMode(server, clnt, cmd);
	}
	else 
		return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"),
				0);
	return 1;
}
