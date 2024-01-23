/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 02:27:45 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/23 08:46:31 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __CLIENT_HPP__
# define __CLIENT_HPP__

#include <iostream>
#include <set>
#include "Channel.hpp"

class Channel;

class Client
{
    private:
        int                     socket;
        bool                    authFlag;
        bool                    passChecked;
        std::string             nickName;
        std::string             loginName;
        std::string             realName;
        std::string             cmd;
        std::set<Channel *>     joined_channels;
        
        std::time_t srvrJointime;
        

    public:
        Client( int _socket );
        
        //getters
        int         getAuthFlag( void );
        int         getSocket( void );
        bool        getPassChecked( void );
        std::string getNickName( void );
        std::string getLoginName( void );
        std::string getRealName( void );
        std::time_t getcltsrvrJointime( void );
        std::string getCmd( void );

        //setters
        void        setNickName( std::string );
        void        setLoginName( std::string );
        void        setCmd( std::string );
        void        setPassChecked( bool );
        void        setRealName( std::string realname );
        void        addChannel( Channel * );
        
        // member functions
        int         check_authentification( void );
        void        authenticate( void );
        int         reply( std::string serv_name, int code, std::string mssg);
        void        clearHistory( void );
};

#endif