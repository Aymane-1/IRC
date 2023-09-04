/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:55:07 by mmeziani          #+#    #+#             */
/*   Updated: 2023/09/04 02:41:35 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"
#include <sstream>

str_t	CommandWorker::privmsg(Client &client)
{
    // size_t pos1 = req.find('#');
    // size_t pos2 = req.find('&');
    std::vector<std::string> v;
    std::string nick;
    std::string message;
    std::string req = getRequest();
    size_t cmd = req.find("PRIVMSG");
    while(req[cmd] >= 'A' && req[cmd] <= 'Z')
        cmd++;
    req = req.substr(cmd, req.length());
    std::istringstream ss(req);
    while(std::getline(ss , nick , ','))
    {
        nick = Helpers::trim(nick, WHITESPACES);
        if(nick.find(':') != std::string::npos)
        {
            message = nick.substr(nick.find(':') + 1, nick.length());
            v.push_back(nick.substr(0 , nick.find(':')));
        }
        else if(nick.find(':') == std::string::npos && nick.find(' ') != std::string::npos)
        {
            message = nick.substr(nick.find(' ') + 1, nick.length());
            v.push_back(nick.substr(0 , nick.find(' ')));
        }
        else
            v.push_back(nick);
    }
    message = (message + '\n');
    client_m::iterator it_m;
    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) 
    {
        (*it) = Helpers::trim((*it), WHITESPACES);
        std::cout << (*it) << std::endl;
        if (CommandHelper::findClientByNickName(this, (*it)) == this->server->clients.end())
            return (ERR_NICKNAMEINUSE(this->server->getHost(), client.getNickname()));
        it_m = CommandHelper::findClientByNickName(this, (*it));
        send(it_m->second.getSocketFd(), message.c_str(), message.length() , 0);
    }
    return ("");
}