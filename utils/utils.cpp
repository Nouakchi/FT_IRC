/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:12:57 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/31 11:36:29 by onouakch         ###   ########.fr       */
=======
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:12:57 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/03 20:09:40 by heddahbi         ###   ########.fr       */
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

int ft_error( std::string err_msg )
{
    std::cerr << err_msg << std::endl;
    return (EXIT_FAILURE);
}

int ft_send(int socket, std::string serv_name, std::string code, std::string nickname, std::string message)
{
    std::string resp = "";
    resp.append(serv_name.append(" "));
    resp.append(code.append(" "));
    resp.append(nickname.append(" "));
    resp.append(message.append("\r\n"));
<<<<<<< HEAD
    std::cout << "-*- " << resp;
=======
    // std::cout << "-*- " << resp;
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)
    if (send(socket, resp.c_str(), resp.size(), 0) == -1)
        return (1);
    return (0);
}    