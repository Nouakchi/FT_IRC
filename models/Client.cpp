/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:42:36 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/18 01:54:03 by heddahbi         ###   ########.fr       */
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
    srvrJointime = std::time(NULL);
}

/************************************************************/
/*                  # -*- GETTERS -*- #                     */
/************************************************************/

int Client::getSocket( void )
{
    return this->socket;
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

std::string Client::getLoginName( void )
{
    return (this->loginName);
}

std::string Client::getRealName( void )
{
    return (this->realName);
}
std::time_t  Client::getclntsrvrJointime( void )
{
    return (this->srvrJointime);
}

/************************************************************/
/*                  # -*- SETTERS -*- #                     */
/************************************************************/

void    Client::setNickName( std::string _nickName )
{
    this->nickName = _nickName;
}

void    Client::setLoginName( std::string _loginName )
{
    this->loginName = _loginName;
}

void    Client::setRealName( std::string _realName )
{
    this->realName = _realName;
}

void    Client::setPassChecked( bool checked )
{
    this->passChecked = checked;
}

void    Client::authenticate( void )
{
    this->authFlag = 1;
}

/************************************************************/
/*                  # -*- M_FUNCT -*- #                     */
/************************************************************/

int Client::check_authentification( void )
{
    if (this->nickName == "*" || this->loginName == "*")
        return (-1);
    if (!this->passChecked)
        return (this->reply(":localhost", ERR_PASSWDMISMATCH, ":Password Incorrect"), EXIT_FAILURE);

    return (EXIT_SUCCESS);
}

int     Client::reply( std::string serv_name, int code, std::string mssg)
{
    std::string s_code = std::to_string(code);
    if (code == -1)
        s_code = "";
    if (ft_send(this->socket, serv_name, s_code, this->nickName, mssg))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}