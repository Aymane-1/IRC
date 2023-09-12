/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:14:01 by mmeziani          #+#    #+#             */
/*   Updated: 2023/09/12 05:59:07 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

static std::vector<Channel>	composeChannelList(const std::vector<str_t> &channels, const std::vector<str_t> &keys)
{
	std::vector<Channel>	channelList = std::vector<Channel>();

	for (size_t i = 0; i < channels.size(); ++i)
	{
		if (i >= keys.size())
			channelList.push_back(Channel(channels[i]));
		else
			channelList.push_back(Channel(channels[i], keys[i]));
	}
	return (channelList);
}

static std::vector<Channel>	joinParser(str_t params)
{
	std::vector<str_t>	channels;
	std::vector<str_t>	keys;
	size_t				i;
	std::vector<Channel>	channelsList;

	i = params.find_first_of(" ");
	if (i == str_t::npos)
		channels = Helpers::split(params, ',');
	else
	{
		str_t	tmp1;

		tmp1 = params.substr(0, i);
		channels = Helpers::split(tmp1, ',');
		tmp1 = params.substr(i + 1, params.size());
		tmp1 = Helpers::trim(tmp1, ' ');
		if (!tmp1.empty())
		{
			if (tmp1[0] == ':')
				keys.push_back(tmp1.substr(1, tmp1.size()));
			else
				keys = Helpers::split(tmp1, ',');
		}
	}
	channelsList = composeChannelList(channels, keys);
	return (channelsList);
}

str_t	CommandWorker::join(Client &client)
{
	str_t				params;
	size_t				i;
	channel_m			&allChannels = this->server->channels;
	std::vector<Channel>	channelsList;
	str_t				response;

	if (client.getVAuth() != FULL_AUTH)
		return (ERR_NOTREGISTERED(this->server->getHost(), client.getNickname()));
	i = this->request.find_first_of(" ");
	if (i == str_t::npos)
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	params = this->request.substr(i, this->request.size());
	params = Helpers::trim(params, " \n\r");
	if (params.empty() || params.size() < 2)
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	channelsList = joinParser(params);
	response = "";
	for (std::vector<Channel>::iterator it = channelsList.begin(); it != channelsList.end(); it++)
	{
		client_m::iterator	c_it;
		str_t				name;

		name = it->getName();
		if (name[0] != '#' && name[0] != '&')
		{
			std::cout << name << std::endl;
			response += ERR_NOSUCHCHANNEL(this->server->getHost(), client.getNickname(), name);
			continue ;
		}
		channel_m::iterator	ch_it = allChannels.find(it->getName());
		if (ch_it == allChannels.end())
		{
			name = it->getName();
			it->addMod(client);
			it->addClient(client);
			allChannels.insert(std::pair<const str_t, Channel>(name, *it));
			response += RPL_JOIN(client.getNickname(), client.getUsername(), client.getHost(), name);
			response += RPL_MODE(client.getNickname(), name, it->getCurrentModes());
			// response += RPL_CHANNELMODEIS(this->server->getHost(), client.getNickname(), it->getName(), it->getCurrentModes(), "");
			response += RPL_NAMREPLY(this->server->getHost(), client.getNickname(), it->getName(), it->getAllUsers());
			response += RPL_ENDOFNAMES(this->server->getHost(), client.getNickname(), it->getName());
		}
		else
		{
			const char	isI = ch_it->second.getMode(I_MODE);
			if (isI == MODE_I)
			{
				if (ch_it->second.isInvited(client.getNickname()))
				{
					response += ERR_INVITEONLYCHAN(this->server->getHost(), client.getNickname(), ch_it->second.getName());
					continue ;
				}
			}
			str_t	ch_key = ch_it->second.getKey();
			if (ch_key == it->getKey())
			{
				ch_it->second.addClient(client);
				response += RPL_JOIN(client.getNickname(), client.getUsername(), client.getHost(), ch_it->second.getName());
				response += RPL_CHANNELMODEIS(this->server->getHost(), client.getNickname(), it->getName(), it->getCurrentModes(), "");
				response += RPL_TOPIC(this->server->getHost(), client.getNickname(), ch_it->second.getName(), ch_it->second.getTopic());
				response += RPL_NAMREPLY(this->server->getHost(), client.getNickname(), ch_it->second.getName(), ch_it->second.getAllUsers());
				response += RPL_ENDOFNAMES(this->server->getHost(), client.getNickname(), ch_it->second.getName());
				ch_it->second.broadcast(
					str_t(RPL_JOIN_WATCH(client.getNickname(), client.getUsername(), client.getHost(), ch_it->second.getName())) + 
					RPL_NAMREPLY(this->server->getHost(), client.getNickname(), ch_it->second.getName(), ch_it->second.getAllUsers()) + 
					RPL_ENDOFNAMES(this->server->getHost(), client.getNickname(), ch_it->second.getName()), client.getNickname());
			}
			else
				response += ERR_BADCHANNELKEY(this->server->getHost(), client.getNickname(), ch_it->second.getName());
		}
	}
    return (response);
}
