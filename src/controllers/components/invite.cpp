/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:13:53 by aechafii          #+#    #+#             */
/*   Updated: 2023/09/05 05:42:01 by aechafii         ###   ########.fr       */
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
	if (CommandHelper::findClientByNickName(this, (nickName)) == this->server->clients.end())
		return (ERR_NOSUCHNICK(this->server->getHost(), client.getNickname()));
	// client_m::iterator clientIter = CommandHelper::findClientByNickName(this, (nickName)); // SAVE FOUND USER
	channel = tokenizer[2];
	if (channel.empty())
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	Channel ch1, ch2, ch3;
	ch1.setName("#CHANNEL1");
	ch2.setName("#CHANNEL5");
	ch3.setName("#CHANNEL10");
	this->server->channels.insert(std::pair<const str_t, Channel>("#CHANNEL1", ch1));
	this->server->channels.insert(std::pair<const str_t, Channel>("#CHANNEL5", ch2));
	this->server->channels.insert(std::pair<const str_t, Channel>("#CHANNEL10", ch3));
	std::map<const str_t, Channel>::iterator channelIter = this->server->channels.find(channel);
	if (channelIter->first == channel)
	{
		client_n clt = channelIter->second.getJoinedclients(); // CHECK if user is on channel
		// client_m::iterator it = clt.find(clientIter->second.getNickname());
		return (RPL_INVITING(nickName, channel));
	}
	else
		return (ERR_NOSUCHCHANNEL(this->server->getHost(), channel));
	return ("");
}