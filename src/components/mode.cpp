/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 00:47:41 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/15 04:39:58 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

// str_t	CommandWorker::mode(Client &client)
// {
// 	std::vector<str_t>	tokenizer;
// 	str_t				channel;
// 	str_t				modes;
// 	str_t				response;
// 	size_t				j;
// 	channel_m::iterator	it;
// 	str_t				clientNick = client.getNickname();
// 	str_t				serverHost = this->server->getHost();
// 	size_t				tokLen;
// 	char				sign = 0;

// 	tokenizer = Helpers::split(this->request, ' ');
// 	if (tokenizer.size() < 2)
// 		return (ERR_NEEDMOREPARAMS(serverHost, clientNick));
// 	channel = tokenizer[1];
// 	if (tokenizer.size() == 2)
// 		return (RPL_CHANNELMODEIS(serverHost, clientNick, channel, it->second.getCurrentModes(), ""));
// 	it = this->server->channels.find(channel);
// 	if (it == this->server->channels.end())
// 		return (ERR_NOSUCHCHANNEL(serverHost, clientNick, channel));
// 	if (!it->second.isOperator(clientNick))
// 		return (ERR_CHANOPRIVSNEEDED(serverHost, clientNick, channel));
// 	tokLen = tokenizer.size();
// 	modes = tokenizer[2];
// 	j = 2;
// 	for (size_t i = 0; i < modes.size(); ++i)
// 	{
// 		char	oldMode;

// 		if (modes[i] == '+' || modes[i] == '-')
// 			sign = modes[i];
// 		else if (modes[i] == MODE_I)
// 		{
// 			oldMode = it->second.getMode(I_MODE);
// 			if (oldMode == MODE_DEFAULT && sign == '-')
// 				continue ;
// 			else if (oldMode == MODE_I && sign == '+')
// 				continue;
// 			else if (oldMode == MODE_I && sign == '-')
// 				it->second.setMode(MODE_DEFAULT, I_MODE);
// 			else
// 				it->second.setMode(MODE_I, I_MODE);
// 		}
// 		else if (modes[i] == MODE_T)
// 		{
// 			oldMode = it->second.getMode(T_MODE);
// 			if (oldMode == MODE_DEFAULT && sign == '-')
// 				continue ;
// 			else if (oldMode == MODE_T && sign == '+')
// 				continue;
// 			else if (oldMode == MODE_T && sign == '-')
// 				it->second.setMode(MODE_DEFAULT, T_MODE);
// 			else
// 				it->second.setMode(MODE_T, T_MODE);
// 		}
// 		else if (modes[i] == MODE_K)
// 		{
// 			oldMode = it->second.getMode(K_MODE);
// 			if (oldMode == MODE_DEFAULT && sign == '-')
// 				continue ;
// 			else if (oldMode == MODE_K && sign == '-')
// 			{
// 				it->second.setKey("");
// 				it->second.setMode(MODE_DEFAULT, K_MODE);
// 			}
// 			else
// 			{
// 				if (j >= tokLen)
// 				{
// 					response += ERR_NEEDMOREPARAMS(serverHost, clientNick);
// 					continue ;
// 				}
// 				it->second.setKey(tokenizer[j]);
// 				it->second.setMode(MODE_K, K_MODE);
// 			}
// 		}
// 		else if (modes[i] == MODE_O)
// 		{
// 			oldMode = it->second.getMode(O_MODE);
// 			if (oldMode == MODE_DEFAULT && sign == '-')
// 				continue ;
// 			else if (j >= tokLen)
// 			{
// 				response += ERR_NEEDMOREPARAMS(serverHost, clientNick);
// 				continue ;
// 			}
// 			else if (oldMode == MODE_O && sign == '-')
// 			{
// 				if (!it->second.isOperator(tokenizer[j]))
// 					continue ;
// 				it->second.removeMod(tokenizer[j]);
// 			}
// 			else
// 			{
// 				if (it->second.isOperator(tokenizer[j]))
// 					continue ;
// 				if (!it->second.isJoined(tokenizer[j]))
// 				{
// 					response += ERR_USERNOTINCHANNEL(serverHost, clientNick, tokenizer[j], channel);
// 					continue ;
// 				}
// 				it->second.addMod(it->second.joinedClients.find(tokenizer[j])->second);
// 				it->second.setMode(MODE_O, O_MODE);
// 			}
// 		}
// 		else if (modes[i] == MODE_L)
// 		{
// 			oldMode = it->second.getMode(L_MODE);
// 			if (oldMode == MODE_DEFAULT && sign == '-')
// 				continue ;
// 			else if (oldMode == MODE_L && sign == '-')
// 			{
// 				it->second.setLimit(-1);
// 				it->second.setMode(MODE_DEFAULT, L_MODE);
// 			}
// 			else
// 			{
// 				if (j >= tokLen)
// 				{
// 					response += ERR_NEEDMOREPARAMS(serverHost, clientNick);
// 					continue ;
// 				}
// 				if (tokenizer[j].find_first_not_of("0123456789") != str_t::npos)
// 				{
// 					response += ERR_UNKNOWNMODE(serverHost, clientNick, channel, MODE_L, "Invalid channel user limit (non-numeric characters)");
// 					continue ;
// 				}
// 				std::stringstream sstream(tokenizer[j]);
// 				size_t result;
// 				sstream >> result;
// 				it->second.setLimit(result);
// 				it->second.setMode(MODE_L, L_MODE);
// 			}
// 		}
// 		j++;
// 	}
// 	response += RPL_CHANNELMODEIS(serverHost, clientNick, channel, it->second.getCurrentModes(), "tmp 1");
// 	return (response);
// }


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
	