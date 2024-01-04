/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:02:46 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/04 12:03:41 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __CHANNEL_HPP__
# define __CHANNEL_HPP__

#include <iostream>
#include <map>
#include "Client.hpp"

class Channel
{
    public:
        std::string                         name;
        std::string                         key;
        std::string                         topic;
        std::map<std::string, Client *>     users;
        int                                 opts_nbr;
        bool                                i; // invite-only flag
        bool                                t; //the topic stters/removals is restricted to Op flag 
        std::string                         k; // passwd to join the channel
        int                                 o; // a flag to add a user to Ops of the channel
        size_t                              l; // set the nbr of user of a chennel

    public:
        Channel(std::string name, std::string key, Client *opt);
        std::string u_list( void );
};

#endif