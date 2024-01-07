/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:02:46 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/03 18:00:10 by onouakch         ###   ########.fr       */
=======
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:02:46 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/06 16:16:21 by heddahbi         ###   ########.fr       */
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)
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
<<<<<<< HEAD

    public:
        Channel(std::string name, std::string key, Client *opt);
=======
    public:
        Channel(std::string name, std::string key, Client *opt);
        ~Channel();
        
        // hossine 's methods
        std::string getmode( void );
        std::string gettopic( void );
        void settopic( std::string topic );
        
        //end hossine 's methods
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)
        std::string u_list( void );
};

#endif