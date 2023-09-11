/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/11 03:07:36 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::invite(Client &client)
{
	std::vector<str_t>	tokenizer;
	str_t				channel;
	str_t				nickName;
	str_t				serverResponse;
	
	if (client.getVAuth() != FULL_AUTH)
        return (ERR_NOTREGISTERED(this->server->getHost(), client.getNickname()));
	tokenizer = Helpers::split(this->request, ' ');
	if (tokenizer.size() != 3)
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	nickName = tokenizer[1];
	client_m::iterator clientIter = CommandHelper::findClientByNickName(this, (nickName)); // SAVE TARGET USER
	if (clientIter == this->server->clients.end())
		return (ERR_NOSUCHNICK(this->server->getHost(), client.getNickname()));
	channel = tokenizer[2];
	if (channel.empty())
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	std::map<const str_t, Channel>::iterator channelIter = this->server->channels.find(channel); // SAVE TARGET CHANNEL
	if (channelIter->first == channel)
	{
		client_n joinedClients = channelIter->second.getJoinedclients();
		std::map<const str_t, Client >::iterator it = joinedClients.find(client.getNickname());
		if (it == joinedClients.end()) // CHECK IF USER IS ON CHANNEL
			return (ERR_NOTONCHANNEL(this->server->getHost(), client.getNickname()));
		client_n operators = channelIter->second.getoperators();
		it =  operators.find(client.getNickname());
		if (it == operators.end() && channelIter->second.getMode(I_MODE) == MODE_I) // // CHECK IF USER IS OPERATOR + invite-only MODE
			return(ERR_CHANOPRIVSNEEDED(this->server->getHost(), client.getNickname(), channel));
		it = joinedClients.find(nickName);
		if (it != joinedClients.end()) // CHECK IF TARGET IS ALREADY ON CHANNEL
			return (ERR_USERONCHANNEL(this->server->getHost(), client.getNickname()));
		if (!channelIter->second.isInvited(nickName))
			channelIter->second.addToInvitedClients(nickName);
		std::string invitation = RPL_SENDINVITE(client.getNickname(), client.getUsername(), this->server->getHost(), nickName, channel);
		send(clientIter->second.getSocketFd(), invitation.c_str(), invitation.length(), 0);
		return (RPL_INVITING(this->server->getHost(), client.getNickname(), client.getHost(), client.getUsername(), nickName, channel));
	}
	return (ERR_NOSUCHCHANNEL(this->server->getHost(), client.getNickname(), channel));
}