/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 00:47:41 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/09 03:44:19 by sel-kham         ###   ########.fr       */
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

	tokenizer = Helpers::split(this->request, " ");
	if (tokenizer.size() < 2)
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	channel = tokenizer[1];
	if (tokenizer.size() == 2)
		return (RPL_CHANNELMODEIS(this->server->getHost(), client.getNickname(), channel, "tmp", "tmp 1"));
	modes = tokenizer[2];
	it = this->server->channels.find(channel);
	if (it == this->server->channels.end())
		return (ERR_NOSUCHCHANNEL(this->server->getHost(), client.getNickname(), channel));
	j = 3;
	for (size_t i = 0; i < modes.size(); ++i)
	{
		int		index;
		int		mode;
		char	sign;
		char	oldMode;

		if (modes[i] == '+' || modes[i] == '-')
			sign = modes[i];
		else if (modes[i] == MODE_I)
		{
			oldMode = it->second.getMode(I_MODE);
			if (oldMode == MODE_I && sign == '+')
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
			if (oldMode == MODE_T && sign == '+')
				continue;
			else if (oldMode == MODE_T && sign == '-')
			{
				it->second.setMode(MODE_DEFAULT, T_MODE);
				//TODO:ACCUMELATE THE RESPONSE MESSAGE 
			}
			else
			{
				it->second.setMode(MODE_T, T_MODE);
				//TODO:ACCUMELATE THE RESPONSE MESSAGE
			}
		}
		else if (modes[i] == MODE_K)
		{
			oldMode = it->second.getMode(K_MODE);
			if (oldMode == MODE_K && sign == '+')
				continue;
			else if (oldMode == MODE_K && sign == '-')
			{
				it->second.setMode(MODE_DEFAULT, K_MODE);
				//TODO:ACCUMELATE THE RESPONSE MESSAGE 
			}
			else
			{
				it->second.setMode(MODE_K, K_MODE);
				//TODO:ACCUMELATE THE RESPONSE MESSAGE
			}
		}
		else if (modes[i] == MODE_O)
		{
			oldMode = it->second.getMode(O_MODE);
			if (oldMode == MODE_O && sign == '+')
				continue;
			else if (oldMode == MODE_O && sign == '-')
			{
				it->second.setMode(MODE_DEFAULT, O_MODE);
				//TODO:ACCUMELATE THE RESPONSE MESSAGE 
			}
			else
			{
				it->second.setMode(MODE_O, O_MODE);
				//TODO:ACCUMELATE THE RESPONSE MESSAGE
			}
		}
		else if (modes[i] == MODE_L)
		{
			oldMode = it->second.getMode(L_MODE);
			if (oldMode == MODE_L && sign == '+')
				continue;
			else if (oldMode == MODE_L && sign == '-')
			{
				it->second.setMode(MODE_DEFAULT, L_MODE);
				//TODO:ACCUMELATE THE RESPONSE MESSAGE 
			}
			else
			{
				it->second.setMode(MODE_L, L_MODE);
				//TODO:ACCUMELATE THE RESPONSE MESSAGE
			}
		}
		else
			response += RPL_CHANNELMODEIS(this->server->getHost(), client.getNickname(), channel, "tmp", "tmp 1");
		j++;
	}
	return (client.getNickname());
}
