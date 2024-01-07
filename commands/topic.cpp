#include "../includes/irc.h"
#include "../models/Client.hpp"
#include "../models/Channel.hpp"

#define ERR_NEEDMOREPARAMS 461
#define ERR_NOSUCHCHANNEL 403
#define ERR_NOTONCHANNEL 442
#define ERR_USERNOTINCHANNEL 441
#define ERR_CHANOPRIVSNEEDED 482
#define ERR_BADCHANMASK   476
#define RPL_NOTOPIC 331
#define RPL_TOPIC 332

int ft_topicCmd(t_server *server, Client *clt, std::vector<std::string> &items)
{
    size_t size = items.size();
    std::string ch = items[1];
    if (size < 2)
        return (
            clt->reply(server->host_name, ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters"),
            EXIT_FAILURE
        );
    if (!is_valid_channel_name(ch))
        return (
            clt->reply(server->host_name, ERR_BADCHANMASK, ch + " :Bad Channel Mask"),
            EXIT_FAILURE
        );
    std::map<std::string, Channel*>::iterator it = server->channels.find(ch);
    if (it == server->channels.end())
        return (
            clt->reply(server->host_name, ERR_NOSUCHCHANNEL, ch + " :No such channel"),
            EXIT_FAILURE
        );
    std::map<std::string, Client *>::iterator is_opt = it->second->users.find("@" + clt->getNickName());
    if (it->second->users.find(clt->getNickName()) == it->second->users.end() 
        && is_opt == it->second->users.end())
        return (
            clt->reply(server->host_name, ERR_NOTONCHANNEL, ch + " :You're not on that channel"),
            EXIT_FAILURE
        );
    if (size == 2)
    {
        if (it->second->topic == "")
            return (
                clt->reply(server->host_name, RPL_NOTOPIC, ch + " :No topic is set"),
                EXIT_SUCCESS
            );
        return (
            clt->reply(server->host_name, RPL_TOPIC, ch + " :" + it->second->topic),
            EXIT_SUCCESS
        );
    }
    if (is_opt == it->second->users.end())
        return (
            clt->reply(server->host_name, ERR_CHANOPRIVSNEEDED, items[1] + " :You're not channel operator"),
            EXIT_FAILURE
        );
    return (EXIT_SUCCESS);

}