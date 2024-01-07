/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 02:27:45 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/07 17:03:06 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __CLIENT_HPP__
# define __CLIENT_HPP__

#include <iostream>

class Client
{
    private:
        int socket;
        bool authFlag;
        bool passChecked;
        std::string nickName;
        std::string loginName;
        std::string realName;
        
    public:
        Client( int _socket );
        
        //getters
        int         getAuthFlag( void );
        int         getSocket( void );
        bool        getPassChecked( void );
        std::string getNickName( void );
        std::string getLoginName( void );
        std::string getRealName( void );

        //setters
        void        setNickName( std::string );
        void        setLoginName( std::string );
        void        setPassChecked( bool );
        void        setRealName( std::string realname );
        
        // member functions
        int         check_authentification( void );
        void        authenticate( void );
        int         reply( std::string serv_name, int code, std::string mssg);
};

#endif