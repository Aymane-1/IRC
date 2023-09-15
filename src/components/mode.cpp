/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 00:47:41 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/15 11:05:07 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/CommandWorker.hpp"

bool mode_i(char &oldMode, t_need &c)
{
	oldMode = c.it->second.getMode(I_MODE);
	if (oldMode == MODE_DEFAULT && c.sign == '-')
		return true;
	else if (oldMode == MODE_I && c.sign == '+')
		return true;
	else if (oldMode == MODE_I && c.sign == '-')
		c.it->second.setMode(MODE_DEFAULT, I_MODE);
	else
		c.it->second.setMode(MODE_I, I_MODE);
	return true;
}

bool t_mode_t(char &oldMode, t_need &c)
{
	oldMode = c.it->second.getMode(T_MODE);
	if (oldMode == MODE_DEFAULT && c.sign == '-')
		return true;
	else if (oldMode == MODE_T && c.sign == '+')
		return true;
	else if (oldMode == MODE_T && c.sign == '-')
		c.it->second.setMode(MODE_DEFAULT, T_MODE);
	else
		c.it->second.setMode(MODE_T, T_MODE);
	return(false);
}

bool mode_k(char &oldMode, t_need &c)
{
	oldMode = c.it->second.getMode(K_MODE);
	if (oldMode == MODE_DEFAULT && c.sign == '-')
		return true;
	else if (oldMode == MODE_K && c.sign == '-')
	{
		c.it->second.setKey("");
		c.it->second.setMode(MODE_DEFAULT, K_MODE);
	}
	else
	{
		if (c.j >= c.tokLen)
		{
			c.response += ERR_NEEDMOREPARAMS(c.serverHost, c.clientNick);
			return true;
		}
		c.it->second.setKey(c.tokenizer[c.j]);
		c.it->second.setMode(MODE_K, K_MODE);
	}
	return false;
}

bool mode_o(char &oldMode, t_need &c)
{
	int	fd;
	str_t	tmpResponse;
	oldMode = c.it->second.getMode(O_MODE);
	if (c.j >= c.tokLen)
	{
		c.response += ERR_NEEDMOREPARAMS(c.serverHost, c.clientNick);
		return true ;
	}
	else if (oldMode == MODE_O && c.sign == '-')
	{
		if (!c.it->second.isOperator(c.tokenizer[c.j]))
			return true ;
		c.it->second.removeMod(c.tokenizer[c.j]);
	}
	else
	{
		if (c.it->second.isOperator(c.tokenizer[c.j]))
			return true;
		if (!c.it->second.isJoined(c.tokenizer[c.j]))
		{
			c.response += ERR_USERNOTINCHANNEL(c.serverHost, c.clientNick, c.tokenizer[c.j], c.channel);
			return true;
		}
		c.it->second.addMod(c.it->second.joinedClients.find(c.tokenizer[c.j])->second);
		c.it->second.setMode(MODE_O, O_MODE);
		tmpResponse = RPL_YOUREOPER(c.serverHost, c.clientNick, c.tokenizer[c.j], c.channel);
		fd = c.it->second.getClientByNickname(c.tokenizer[c.j])->second.getSocketFd();
		send(fd, tmpResponse.c_str(), tmpResponse.size(), 0);
	}
	c.it->second.broadcast(
		RPL_NAMREPLY(c.serverHost, c.clientNick, c.channel, c.it->second.getAllUsers()) +
		RPL_ENDOFNAMES(c.serverHost, c.clientNick, c.channel), ""
	);
	return false;
}

bool mode_l(char &oldMode, t_need &c)
{
	oldMode = c.it->second.getMode(L_MODE);
	if (oldMode == MODE_DEFAULT && c.sign == '-')
		return true;
	else if (oldMode == MODE_L && c.sign == '-')
	{
		c.it->second.setLimit(-1);
		c.it->second.setMode(MODE_DEFAULT, L_MODE);
		return true;
	}
	else
	{
		if (c.j >= c.tokLen)
		{
			c.response += ERR_NEEDMOREPARAMS(c.serverHost, c.clientNick);
			return true;
		}
		if (c.tokenizer[c.j].find_first_not_of("0123456789") != str_t::npos)
		{
			c.response += ERR_NEEDMOREPARAMS(c.serverHost, c.clientNick);
			return true;
		}
		std::stringstream sstream(c.tokenizer[c.j]);
		size_t result;
		sstream >> result;
		c.it->second.setLimit(result);
		c.it->second.setMode(MODE_L, L_MODE);
	}
	return false;
}


str_t	CommandWorker::mode(Client &client)
{
	t_need c;
	str_t mode;
	
	c.clientNick = client.getNickname();
	c.serverHost = this->server->getHost();
	c.sign = 0;

	if (client.getVAuth() != FULL_AUTH)
        return (ERR_NOTREGISTERED(this->server->getHost(), client.getNickname()));
	c.tokenizer = Helpers::split(this->request, ' ');
	if (c.tokenizer.size() < 2)
		return (ERR_NEEDMOREPARAMS(c.serverHost, c.clientNick));
	c.channel = c.tokenizer[1];
	c.it = this->server->channels.find(c.channel);
	if (c.it == this->server->channels.end())
		return (ERR_NOSUCHCHANNEL(c.serverHost, c.clientNick, c.channel));
	if (c.tokenizer.size() == 2)
		return (RPL_CHANNELMODEIS(c.serverHost, c.clientNick, c.channel, c.it->second.getCurrentModes(), ""));
	if (!c.it->second.isOperator(c.clientNick))
		return (ERR_CHANOPRIVSNEEDED(c.serverHost, c.clientNick, c.channel));
	c.tokLen = c.tokenizer.size();
	c.modes = c.tokenizer[2];
	c.j = 2;

	if(!mode.empty())
		return (mode);
	for (size_t i = 0; i < c.modes.size(); ++i)
	{
		char	oldMode;
		if (c.modes[i] == '+' || c.modes[i] == '-')
			c.sign = c.modes[i];
		else
		{
			switch(c.modes[i])
			{
				case (MODE_I):
					if(mode_i(oldMode, c))
						continue;
					break;
				case (MODE_T):
					if(t_mode_t(oldMode, c))
						continue;
					break;
				case (MODE_K):
					if(mode_k(oldMode, c))
						continue;
					break;
				case (MODE_O):
					if(mode_o(oldMode, c))
						continue;
					break;
				case(MODE_L):
					if(mode_l(oldMode, c))
						continue;
					break;
				default:
					response += ERR_UNKNOWNMODE(c.serverHost, c.clientNick, c.channel, c.sign + c.modes[i], "Invalid channel mode.");
					continue ;
			}
		}
		c.j++;
	}
	c.it->second.broadcast(RPL_CHANNELMODEIS(c.serverHost, c.clientNick, c.channel, c.it->second.getCurrentModes(), ""), "");
	return (c.response);
}
	