/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/14 00:46:30 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::invite(Client &client)
{
	std::vector<str_t>	tokenizer;
	str_t				channel, nickName, serverResponse;
	
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
		if (!channelIter->second.isJoined(client.getNickname())) // CHECK IF USER IS ON CHANNEL
			return (ERR_NOTONCHANNEL(this->server->getHost(), client.getNickname()));
		if (!channelIter->second.isOperator(client.getNickname()) && channelIter->second.getMode(I_MODE) == MODE_I) // // CHECK IF USER IS OPERATOR + invite-only MODE
			return(ERR_CHANOPRIVSNEEDED(this->server->getHost(), client.getNickname(), channel));
		if (channelIter->second.isJoined(nickName)) // CHECK IF TARGET IS ALREADY ON CHANNEL
			return (ERR_USERONCHANNEL(this->server->getHost(), client.getNickname()));
		if (!channelIter->second.isInvited(nickName)) // TARGET IS ADDED TO INVITED CLIENTS
			channelIter->second.addToInvitedClients(nickName);
		str_t invitation = RPL_SENDINVITE(client.getNickname(), client.getUsername(), this->server->getHost(), nickName, channel);
		send(clientIter->second.getSocketFd(), invitation.c_str(), invitation.length(), 0);
		return (RPL_INVITING(this->server->getHost(), client.getNickname(), client.getHost(), client.getUsername(), nickName, channel));
	}
	return (ERR_NOSUCHCHANNEL(this->server->getHost(), client.getNickname(), channel));
}