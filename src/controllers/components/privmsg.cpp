/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:55:07 by mmeziani          #+#    #+#             */
/*   Updated: 2023/09/13 03:24:08 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::privmsg(Client &client)
{
    std::vector<str_t> error;
    std::vector<str_t> chann;
    std::vector<str_t> nick;
    str_t req = (request.substr((request.find("PRIVMSG") + 7) , (request.length() - request.find("PRIVMSG"))));
    req = Helpers::trim(req, ' ');
    str_t mess = req.substr(req.find(' '), req.length()) + TRAILING;
    std::vector<str_t> tok = Helpers::split(req.substr(0, req.find(' ')), ',');
    std::vector<str_t>::iterator it = tok.begin();
    
    for ( ;it != tok.end(); it++)
    {
        if ((*it).find('#') != std::string::npos)
            chann.push_back(Helpers::trim((*it) , ' '));
        else
            nick.push_back(Helpers::trim((*it) , ' '));
    }

    std::vector<str_t>::iterator it1 = chann.begin();
    while(it1 != chann.end())
    {
        std::map<const str_t, Channel>::iterator channelIter = this->server->channels.find((*it1));
        if (channelIter == this->server->channels.end())
            return (ERR_NOSUCHCHANNEL(this->server->getHost(), client.getNickname(), (*it1)));
		if (!channelIter->second.isJoined(client.getNickname()))
			return (ERR_NOTONCHANNEL(this->server->getHost(), client.getNickname()));
        channelIter->second.broadcast(":" + client.getNickname() + "!" + client.getUsername() + "@" + this->server->getHost() + " PRIVMSG " + (*it1) + " :" + mess + TRAILING , client.getNickname());
        it1++;
    }

    std::vector<str_t>::iterator it2 = nick.begin();
    str_t rep;
    str_t tr;
    while(it2 != nick.end())
    {
        client_m::iterator clientIter = CommandHelper::findClientByNickName(this, (*it2));
	    if (clientIter == this->server->clients.end())
		    return (ERR_NOSUCHNICK(this->server->getHost(), client.getNickname()));
        if (Helpers::ltrim(mess, ' ')[0] == ':')
            tr = "";
        else
            tr = " :";
        rep = (":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHost() + " PRIVMSG " + (*it2) + tr  + mess + TRAILING );
        if ((*it2) == client.getNickname())
            continue ;
        else
            send(clientIter->second.getSocketFd(), rep.c_str(), rep.length(), 0);
        it2++;
    }
    return ("");
}