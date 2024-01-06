/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:20:47 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/06 11:29:53 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string _name, std::string _key, Client *_opt)
{
    (void )_opt;
    this->name = _name;
    this->key = _key;
    this->topic = "No topic is set";
    this->i = false; // at the creation, the channel is not invite-only
    this->t = true; //  at the creation, the topic stters/removals is restricted to Operators
    this->o = 0;    // at the moment i dont think i would use this flag
    this->l = -1; // at the creation, the max user of a channel are 100 
}