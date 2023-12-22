/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:42:36 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/22 05:41:47 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "../includes/irc.h"

Client::Client( int _socket )
{
    this->socket = _socket;
    this->authFlag = 0;
    this->nickName = "";
    this->loginName = "";
}

int Client::getAuthFlag( void )
{
    return this->authFlag;
}

void    Client::setNickName( std::string _nickName )
{
    this->nickName = _nickName;
}

void    Client::setLoginName( std::string _loginName )
{
    this->loginName = _loginName;
}

void    Client::authenticate( void )
{
    this->authFlag = 1;
}

int Client::check_authentification( void )
{
    if (this->nickName.empty() || this->loginName.empty())
        return (1);
    this->authenticate();
    
    // sending mssg to the client to be informed 
    // that the connection has been accepted
    std::string resp = ":localhost 001 othman :Welcome to the IRC server!\r\n";
    send(this->socket, resp.c_str(), resp.size(), 0);
    return (0);
}