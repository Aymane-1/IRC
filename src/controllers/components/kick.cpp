/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:45:02 by mmeziani          #+#    #+#             */
/*   Updated: 2023/09/11 05:26:03 by mmeziani         ###   ########.fr       */
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
    
    client_n joinedClients = channelIter->second.getJoinedclients();
    std::map<const str_t, Client >::iterator it = joinedClients.find(client.getNickname());
    if (it == joinedClients.end())
        return (ERR_NOTONCHANNEL(this->server->getHost(), client.getNickname()));
    for (; itok != tok.end() ; itok++)
    {
        std::map<const str_t, Client >::iterator it = joinedClients.find((*itok));
        if (it == joinedClients.end())
            channelIter->second.broadcast(ERR_USERNOTINCHANNEL(this->server->getHost(), client.getNickname(), (*itok), chann), "");
        else
        {
            client_n operators = channelIter->second.getoperators();
            it =  operators.find(client.getNickname());
            if (it == operators.end())
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