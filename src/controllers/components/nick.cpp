/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:18:53 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/15 01:34:29 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::nick(Client &client)
{
	short		vAuth;
	size_t		index;
	const str_t	forbiddenToStartWith = "# :";
	const str_t	specialCharacheters = "[]{}\\|:";
	std::vector<str_t>	tokenizer;
	str_t		oldNick;

	vAuth = client.getVAuth();
	oldNick = client.getNickname();
	if (vAuth < PASS_AUTH)
		return (ERR_NOTREGISTERED(this->server->getHost(), client.getNickname()));
	tokenizer = Helpers::split(this->request, ' ');
	if (tokenizer.size() < 2)
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	if (tokenizer[1][0] == ':')
	{
		for (size_t i = 1; i < tokenizer.size(); i++)
		{
			if (i == 1)
				continue ;
			tokenizer[1] += " " + tokenizer[i];
			tokenizer.erase(tokenizer.begin() + i, tokenizer.begin() + i);
		}
		tokenizer[1] = tokenizer[1].substr(1, tokenizer[1].size() - 1);
	}
	if (tokenizer[1].empty())
		return (ERR_NONICKNAMEGIVEN(this->server->getHost(), client.getNickname()));
	index = forbiddenToStartWith.find(tokenizer[1][0]);
	if (index != str_t::npos)
		return (ERR_ERRONEUSNICKNAME(this->server->getHost(), client.getNickname()));
	index = -1;
	while (tokenizer[1][++index])
		if (!isalnum(tokenizer[1][index]) && specialCharacheters.find(tokenizer[1][index]) != str_t::npos)
			return (ERR_ERRONEUSNICKNAME(this->server->getHost(), client.getNickname()));
	if (CommandHelper::findClientByNickName(this, tokenizer[1]) != this->server->clients.end())
		return (ERR_NICKNAMEINUSE(this->server->getHost(), client.getNickname()));
	for (channel_m::iterator ch_it = this->server->channels.begin(); ch_it != this->server->channels.end(); ch_it++)
    {
        client_n::iterator cl_it = ch_it->second.getClientByNickname(oldNick);
        if (cl_it != ch_it->second.joinedClients.end())
        {
            Client tmp = cl_it->second;
            tmp.setNickname(tokenizer[1]);
            ch_it->second.removeClient(cl_it->second.getNickname());
            ch_it->second.addClient(tmp);
            if (ch_it->second.isOperator(cl_it->second.getNickname()))
            {
                ch_it->second.removeMod(cl_it->second.getNickname());
                ch_it->second.addMod(tmp);
            }
        }
    }
	vAuth |= NICK_AUTH;
	client.setVAuth(vAuth);
	client.setNickname(tokenizer[1]);
	return (":" + oldNick + " NICK :" + client.getNickname() + TRAILING);
}

