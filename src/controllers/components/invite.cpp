/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:13:53 by aechafii          #+#    #+#             */
/*   Updated: 2023/09/06 05:16:26 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::invite(Client &client)
{
	std::vector<str_t>	tokenizer;
	str_t				channel;
	str_t				nickName;
	str_t				serverResponse;

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
		// CHECK IF USER IS OPERATOR + invite-only MODE
		client_n mods = channelIter->second.getMods();
		it =  mods.find(client.getNickname());
		if (it == mods.end()) // && +i IS ENABELED
			return(ERR_CHANOPRIVSNEEDED(this->server->getHost(), client.getNickname()));
		// CHECK IF TARGET IS ALREADY ON CHANNEL
		it = joinedClients.find(nickName);
		if (it != joinedClients.end())
			return (ERR_USERONCHANNEL(this->server->getHost(), client.getNickname()));
		std::string invitation = RPL_SENDINVITE(client.getNickname(), client.getUsername(), this->server->getHost(), nickName, channel);
		send(clientIter->second.getSocketFd(), invitation.c_str(), invitation.length(), 0);
		return (RPL_INVITING(this->server->getHost(), client.getNickname(), client.getHost(), client.getUsername(), nickName, channel));
	}
	else
		return (ERR_NOSUCHCHANNEL(this->server->getHost(), client.getNickname(), channel));
	return ("");
}