/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:20:47 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/02 09:34:51 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string _name, std::string _key, Client *_opt)
{
    this->name = _name;
    this->key = _key;
    this->opt = _opt;
    this->topic = "No topic is set";
    this->u_names = " :@" + _opt->getNickName() + " ";
    this->users.insert(opt);
    this->i = 0;
    this->t = 0;
    this->k = 0;
    this->o = 0;
    this->l = 0;
}