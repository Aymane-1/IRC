/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 00:47:41 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/09 20:15:13 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::mode(Client &client)
{
	std::vector<str_t>	tokenizer;
	str_t				channel;
	str_t				modes;
	str_t				response;
	str_t				pos = "+";
	str_t				neg = "-";
	size_t				j;
	channel_m::iterator	it;
	str_t				clientNick = client.getNickname();
	str_t				serverHost = this->server->getHost();
	size_t				tokLen;

	tokenizer = Helpers::split(this->request, ' ');
	if (tokenizer.size() < 2)
		return (ERR_NEEDMOREPARAMS(serverHost, clientNick));
	channel = tokenizer[1];
	if (tokenizer.size() == 2)
		return (RPL_CHANNELMODEIS(serverHost, clientNick, channel, "tmp", "tmp 1"));
	it = this->server->channels.find(channel);
	if (it == this->server->channels.end())
		return (ERR_NOSUCHCHANNEL(serverHost, clientNick, channel));
	if (!it->second.isOperator(clientNick))
		return (ERR_CHANOPRIVSNEEDED(serverHost, clientNick, channel));
	tokLen = tokenizer.size();
	modes = tokenizer[2];
	j = 3;
	for (size_t i = 0; i < modes.size(); ++i)
	{
		char	sign = 0;
		char	oldMode;

		if (modes[i] == '+' || modes[i] == '-')
			sign = modes[i];
		else if (modes[i] == MODE_I)
		{
			oldMode = it->second.getMode(I_MODE);
			if (oldMode == MODE_DEFAULT && sign == '-')
				continue ;
			else if (oldMode == MODE_I && sign == '+')
				continue;
			else if (oldMode == MODE_I && sign == '-')
			{
				it->second.setMode(MODE_DEFAULT, I_MODE);
				neg += MODE_I;
			}
			else
			{
				it->second.setMode(MODE_I, I_MODE);
				pos += MODE_I;
			}
		}
		else if (modes[i] == MODE_T)
		{
			oldMode = it->second.getMode(T_MODE);
			if (oldMode == MODE_DEFAULT && sign == '-')
				continue ;
			else if (oldMode == MODE_T && sign == '+')
				continue;
			else if (oldMode == MODE_T && sign == '-')
			{
				it->second.setMode(MODE_DEFAULT, T_MODE);
				neg += MODE_T;
			}
			else
			{
				it->second.setMode(MODE_T, T_MODE);
				pos += MODE_T;
			}
		}
		else if (modes[i] == MODE_K)
		{
			oldMode = it->second.getMode(K_MODE);
			if (oldMode == MODE_DEFAULT && sign == '-')
				continue ;
			else if (oldMode == MODE_K && sign == '-')
			{
				it->second.setKey("");
				it->second.setMode(MODE_DEFAULT, K_MODE);
				neg += MODE_K;
			}
			else
			{
				if (j <= tokLen)
				{
					response += ERR_NEEDMOREPARAMS(serverHost, clientNick);
					continue ;
				}
				it->second.setKey(tokenizer[j]);
				it->second.setMode(MODE_K, K_MODE);
				pos += MODE_K;
			}
		}
		else if (modes[i] == MODE_O)
		{
			oldMode = it->second.getMode(O_MODE);
			if (oldMode == MODE_DEFAULT && sign == '-')
				continue ;
			else if (j <= tokLen)
			{
				response += ERR_NEEDMOREPARAMS(serverHost, clientNick);
				continue ;
			}
			else if (oldMode == MODE_O && sign == '-')
			{
				if (!it->second.isOperator(tokenizer[j]))
					continue ;
				it->second.removeMod(tokenizer[j]);
				neg += MODE_O;
			}
			else
			{
				if (it->second.isOperator(tokenizer[j]))
					continue ;
				if (!it->second.isJoined(tokenizer[j]))
				{
					response += ERR_USERNOTINCHANNEL(serverHost, clientNick, tokenizer[j], channel);
					continue ;
				}
				it->second.addMod(it->second.joinedClients.find(tokenizer[j])->second);
				it->second.setMode(MODE_O, O_MODE);
				pos += MODE_O;
			}
		}
		else if (modes[i] == MODE_L)
		{
			oldMode = it->second.getMode(L_MODE);
			if (oldMode == MODE_DEFAULT && sign == '-')
				continue ;
			else if (oldMode == MODE_L && sign == '-')
			{
				it->second.setLimit(-1);
				it->second.setMode(MODE_DEFAULT, L_MODE);
				neg += MODE_L;
			}
			else
			{
				if (j <= tokLen)
				{
					response += ERR_NEEDMOREPARAMS(serverHost, clientNick);
					continue ;
				}
				if (tokenizer[j].find_first_not_of("0123456789") != str_t::npos)
				{
					response += ERR_UNKNOWNMODE(serverHost, clientNick, channel, MODE_L, "Invalid channel user limit (non-numeric characters)");
					continue ;
				}
				std::stringstream sstream(tokenizer[j]);
				size_t result;
				sstream >> result;
				it->second.setLimit(result);
				it->second.setMode(MODE_L, L_MODE);
				pos += MODE_L;
			}
		}
		j++;
	}
	if (neg.size() > 1)
		pos += " " + neg;
	response += RPL_CHANNELMODEIS(serverHost, clientNick, channel, pos, "tmp 1");
	return (response);
}
