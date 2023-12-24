/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:57:44 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/24 07:38:33 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../irc.hpp"

class Client
{
	private:
		int socket;
		bool authFlag;
		bool passChecked;

	public:
		Client( int _socket );

		/*_____KADIGH____*/
		std::string nickName;
		std::string userName;
		std::string realName;
		int AuthFlag;
		int sfd;
		std::string nick;
		/*_____KADIGH____*/

		//getters
		int getAuthFlag( void );
		bool getPassChecked( void );
		std::string getNickName( void );

		//setters
		void setNickName( std::string );
		void setLoginName( std::string );
		void setPassChecked( bool );
		
		// member functions
		int     check_authentification( );
		void    authenticate( void );
		int     reply( std::string serv_name, std::string code, std::string mssg);
};

#endif