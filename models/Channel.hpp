/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:02:46 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/18 02:32:49 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __CHANNEL_HPP__
# define __CHANNEL_HPP__

#include <iostream>
#include <map>
#include "Client.hpp"

class Client;

class Channel
{
    public:
        std::string                         name;
        std::string                         topic;
        std::map<std::string, Client *>     users;
        /*
        **  we don't need to add a user to the invited_users just add the inveted user to the user map
        **  and when he tries to join the channel he's already in the channel so he will have the access
        */
        std::set<std::string >              invited_users;  // !!!!!!!!!!
        
        bool                                i;
        bool                                t;
        std::string                         key;
        int                                 o;
        int                                 l;

    public:
        Channel(std::string name, std::string key, Client *opt);
        std::string u_list( void );
};


#endif