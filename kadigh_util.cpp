/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kadigh_util.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:27:48 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/03 17:33:21 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/irc.h"

void	error_replay( t_server* server ,int errNbr, Client clnt, std::string err)
{
	std::string errMsg;
	errMsg =  server->host_name + " " + std::to_string(errNbr) + " " + clnt.getNickName() + err;
	send(clnt.getSocket(), errMsg.c_str(), errMsg.size(), 0);
}
