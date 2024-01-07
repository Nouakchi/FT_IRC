/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:20:47 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/03 18:16:56 by onouakch         ###   ########.fr       */
=======
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:20:47 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/06 15:40:10 by heddahbi         ###   ########.fr       */
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string _name, std::string _key, Client *_opt)
{
    this->name = _name;
    this->key = _key;
    this->topic = "No topic is set";
    this->users.insert(std::pair<std::string, Client*>("@" + _opt->getNickName(), _opt));
    this->i = 0;
    this->t = 0;
    this->k = 0;
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
<<<<<<< HEAD
=======
}

std::string Channel::getmode( void )
{
    std::string mode = "+";
    if (this->i == 1)
        mode.append("i");
    if (this->t == 1)
        mode.append("t");
    if (this->k == 1)
        mode.append("k");
    if (this->o == 1)
        mode.append("o");
    if (this->l == 1)
        mode.append("l");
    return (mode);
}
std::string Channel::gettopic( void )
{
    return (this->topic);
}
void Channel::settopic( std::string topic )
{
    this->topic = topic;
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)
}