/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 02:27:45 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/22 05:40:37 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __CLIENT_HPP__
# define __CLIENT_HPP__

#include <iostream>

class Client
{
    private:
        int socket;
        int authFlag;
        std::string nickName;
        std::string loginName;
        
    public:
        Client( int _socket );
        
        //getters
        int getAuthFlag( void );

        //setters
        void setNickName( std::string _nickName );
        void setLoginName( std::string _loginName );
        
        // member functions
        int     check_authentification();
        void    authenticate( void );
};

#endif