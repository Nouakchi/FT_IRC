/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:57:44 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/22 22:05:08 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../irc.hpp"

class Client
{
private :
	std::string nick;
	std::string user;
	int			role;

public :
	int	AuthFlag;

	// Client();
	// ~Client();
};

#endif