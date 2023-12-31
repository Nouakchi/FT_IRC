/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:02:46 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/31 11:14:27 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __CHANNEL_HPP__
# define __CHANNEL_HPP__

#include <iostream>
#include <set>
#include "Client.hpp"

class Channel
{
    public:
        std::string             name;
        std::string             key;
        std::string             topic;
        std::string             u_names;
        Client                  *opt;
        std::set<Client *>      users;
        int                     i;
        int                     t;
        int                     k;
        int                     o;
        int                     l;

    public:
        Channel(std::string name, std::string key, Client *opt);
};

#endif