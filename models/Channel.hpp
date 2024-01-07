/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:02:46 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/07 17:02:54 by heddahbi         ###   ########.fr       */
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
        int                                 i;
        int                                 t;
        int                                 k;
        int                                 o;
        int                                 l;

    public:
        Channel(std::string name, std::string key, Client *opt);
        std::string u_list( void );
};

#endif