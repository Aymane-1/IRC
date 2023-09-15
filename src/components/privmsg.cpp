/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:55:07 by mmeziani          #+#    #+#             */
/*   Updated: 2023/09/15 11:58:31 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/CommandWorker.hpp"

str_t	CommandWorker::privmsg(Client &client)
{
	
	size_t	pos;
	str_t	params;
	str_t	message;
	const str_t serverHost = this->server->getHost();
	const str_t clientNick = client.getNickname();
	std::vector<str_t>	tokenizer;
	str_t	response = "";

	if (client.getVAuth() != FULL_AUTH)
        return (ERR_NOTREGISTERED(this->server->getHost(), client.getNickname()));
	params = this->getRequest();
	pos = params.find_first_of(" ");
	if (pos == str_t::npos)
		return (ERR_NEEDMOREPARAMS(serverHost, clientNick));
	params = params.substr(pos, params.size() - 1);
	params = Helpers::trim(params, ' ');
	if (params.empty())
		return (ERR_NEEDMOREPARAMS(serverHost, clientNick));
	pos = params.find_first_of(":");
	if (pos == str_t::npos)
	{
		pos = params.find_last_of(" ");
		if (pos == str_t::npos)
			return (ERR_NOTEXTTOSEND(serverHost, clientNick));
		message = params.substr(pos, params.size() - pos);
		params = params.substr(0, pos);
	}
	else
	{
		message = params.substr(pos + 1, params.size() - pos);
		params = params.substr(0, pos);
	}
	message = Helpers::trim(message, ' ');
	params = Helpers::trim(params, ' ');
	if (message.empty())
		return (ERR_NOTEXTTOSEND(serverHost, clientNick));
	if (params.empty())
		return (ERR_NORECIPIENT(serverHost, clientNick));
	tokenizer = Helpers::split(params, ',');
	for (std::vector<str_t>::iterator it = tokenizer.begin(); it != tokenizer.end(); it++)
	{
		if (it->at(0) == '#')
		{
			channel_m::iterator	target = this->server->channels.begin();
			if (target == this->server->channels.end())
				response += ERR_NOSUCHCHANNEL(serverHost, clientNick, *it);
			else
			{
				if (target->second.isJoined(clientNick))
				{
					str_t	toSend = PRIVMSG_TO_CHANNEL(clientNick, client.getUsername(), serverHost, (*it), message);
					target->second.broadcast(toSend, clientNick);
				}
				else
					response += ERR_NOTONCHANNEL(serverHost, clientNick);
			}
		}
		else
		{
			client_m::iterator target = this->server->getClientByNickname(*it);
			if (target == this->server->clients.end())
				response += ERR_NOSUCHNICK_PRIVMSG(serverHost, clientNick, *it);
			else
			{
				if (target->second.getawayState())
                    response += RPL_AWAY(serverHost, clientNick, *it, target->second.getawayReason());
				if (Helpers::ltrim(message, ' ')[0] != ':')
					message = " :" + message;
				str_t	toSend = PRIVMSG_TO_USER(clientNick, client.getUsername(), client.getHost(), *it, message);
				send(target->second.getSocketFd(), toSend.c_str(), toSend.size(), 0);
			}
		}
	}
	return (response);
}