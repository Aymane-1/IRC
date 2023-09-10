/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:31:19 by mmeziani          #+#    #+#             */
/*   Updated: 2023/09/10 23:54:35 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::topic(Client &client)
{
    str_t topic;
    str_t chann;
    std::vector<str_t> tok = Helpers::split(this->request , ' ');
    chann = tok[1];
    topic = tok[2];
    
    if(tok.size() < 1)
        return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
    std::map<const str_t, Channel>::iterator channelIter = this->server->channels.find(chann);
    if (channelIter == this->server->channels.end())
        return (ERR_NOSUCHCHANNEL(this->server->getHost(), client.getNickname(), chann));
    topic = channelIter->second.getTopic();
    if (tok.size() == 2)
    {
        if (channelIter->second.getTopic() == "Costumizable channel")
            return (RPL_NOTOPIC(this->server->getHost(), client.getUsername(), chann));
        else
        {
            std::time_t result = std::time(nullptr);
            unsigned long time = result;
            return (RPL_TOPIC_SHOW(this->server->getHost(), client.getUsername(), chann, channelIter->second.getTopic(), time));
        }
    }
    channelIter->second.getTopic();
	if (channelIter != this->server->channels.end())
	{
        client_n joinedClients = channelIter->second.getJoinedclients();
		std::map<const str_t, Client >::iterator it = joinedClients.find(client.getNickname());
		if (it == joinedClients.end())
			return (ERR_NOTONCHANNEL(this->server->getHost(), client.getNickname()));
        client_n operators = channelIter->second.getoperators();
        it =  operators.find(client.getNickname());
		if (it == operators.end())
			return(ERR_CHANOPRIVSNEEDED(this->server->getHost(), client.getNickname(), ""));
        topic = request.substr( (request.find(chann) + chann.length()), request.length()) + TRAILING;
        channelIter->second.setTopic(topic);
        channelIter->second.broadcast(topic, client.getNickname());
        return (TOPIC_SUCCESS(client.getNickname(), client.getUsername(), this->server->getHost(), chann, topic));
	}
	else
		return (ERR_NOSUCHCHANNEL(this->server->getHost(), client.getNickname(), chann));
    return ("");
}