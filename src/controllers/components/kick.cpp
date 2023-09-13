/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:45:02 by mmeziani          #+#    #+#             */
/*   Updated: 2023/09/13 00:32:19 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::kick(Client &client)
{
    client.getNickname();
    std::string comment;
    str_t req = (request.substr((request.find("KICK") + 4) , (request.length() - request.find("KICK"))));
    req = Helpers::trim(req, ' ');
    if(req.find('#') == std::string::npos)
        return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
    req = req.substr(req.find('#'), req.length());
    std::string chann = req.substr(req.find('#'), req.find(' '));
    req = req.substr(chann.length(), req.length());
    req = Helpers::trim(req, ' ');
    if(req.find(' ') != std::string::npos)
        comment = req.substr(req.find(' '), req.length()) + TRAILING;
    std::vector<str_t> tok = Helpers::split(req.substr(0, req.find(' ')), ',');
    std::vector<str_t>::iterator itok = tok.begin();

    std::map<const str_t, Channel>::iterator channelIter = this->server->channels.find((chann));
    if (channelIter == this->server->channels.end())
        return (ERR_NOSUCHCHANNEL(this->server->getHost(), client.getNickname(), (chann)));
    
    if (!channelIter->second.isJoined(client.getNickname()))
        return (ERR_NOTONCHANNEL(this->server->getHost(), client.getNickname()));

    for (; itok != tok.end() ; itok++)
    {
        if (!channelIter->second.isJoined((*itok)))
            channelIter->second.broadcast(ERR_USERNOTINCHANNEL(this->server->getHost(), client.getNickname(), (*itok), chann), "");
        else
        {
            if (!channelIter->second.isOperator((*itok)))
                channelIter->second.broadcast(ERR_CHANOPRIVSNEEDED(this->server->getHost(), client.getNickname(), ""), "");
            else
            {
                if(comment.empty())
                    channelIter->second.broadcast(":" + client.getNickname() + "!" + client.getUsername() + "@" + this->server->getHost() +  " KICK " + chann + " " + (*itok) + client.getNickname() + TRAILING, "");
                else
                    channelIter->second.broadcast(":" + client.getNickname() + "!" + client.getUsername() + "@" + this->server->getHost() +  " KICK " + chann + " " + (*itok) + comment + TRAILING, "");
                channelIter->second.removeClient((*itok));
            }
        }
    }
    return ("");
}