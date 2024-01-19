/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:20:47 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/19 02:13:59 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string _name, std::string _key, Client *_opt)
{
    this->name = _name;
    this->key = _key;
    this->topic = " :No topic is set";
    this->users.insert(std::pair<std::string, Client*>("@" + _opt->getNickName(), _opt));
    this->i = 0;
    this->t = 0;
    this->o = 0;
    this->l = 0;
}

std::string Channel::u_list( void )
{
    std::string list = "";
    std::map<std::string, Client*>::iterator it = this->users.begin();
    while (it != this->users.end())
    {
        list.append(it->first + " ");
        it++;
    }
    return (list);
}