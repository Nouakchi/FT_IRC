/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:42:36 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/23 04:07:36 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "../includes/irc.h"

Client::Client( int _socket )
{
    this->socket = _socket;
    this->authFlag = 0;
    this->passChecked = false;
    this->nickName = "*";
    this->loginName = "*";
}

int Client::getAuthFlag( void )
{
    return this->authFlag;
}

bool Client::getPassChecked( void )
{
    return this->passChecked;
}

std::string Client::getNickName( void )
{
    return (this->nickName);
}

void    Client::setNickName( std::string _nickName )
{
    this->nickName = _nickName;
}

void    Client::setLoginName( std::string _loginName )
{
    this->loginName = _loginName;
}

void    Client::setPassChecked( bool checked )
{
    this->passChecked = checked;
}

void    Client::authenticate( void )
{
    this->authFlag = 1;
}

int Client::check_authentification( void )
{
    if (this->nickName == "*" || this->loginName == "*")
        return (1);
    if (!this->passChecked)
        return (this->reply(":localhost", std::to_string(ERR_PASSWDMISMATCH), ":Password Incorrect"), 1);
    this->authenticate();
    
    // sending mssg to the client to be informed 
    // that the connection has been accepted
    if (ft_send(this->socket, ":localhost", "001", "othman", ":Welcome to the IRC server!"))
        return (1);
    return (0);
}

int     Client::reply( std::string serv_name, std::string code, std::string mssg)
{
    if (ft_send(this->socket, serv_name, code, this->nickName, mssg))
        return (1);
    return (0);
}