/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 22:49:44 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/03 03:57:50 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::user(Client &client)
{
	size_t				i;
	str_t				user;
	short				vAuth;
	std::vector<str_t>	tokenizer;

	vAuth = client.getVAuth();
	if (vAuth < PASS_AUTH)
		return (ERR_NOTREGISTERED(this->server->getHost(), client.getNickname()));
	if (vAuth == FULL_AUTH || vAuth == (PASS_AUTH | USER_AUTH))
		return (ERR_ALREADYREGISTERED(this->server->getHost(), client.getNickname()));
	i = this->request.find_first_of(" ");
	if (i == str_t::npos)
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	user = this->request.substr(i, this->request.size() - 1);
	user = Helpers::trim(user, "\n \r");
	tokenizer = Helpers::split(user, ' ');
	if (tokenizer.size() < 4)
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	if (tokenizer[3][0] == ':')
	{
		for (size_t i = 3; i < tokenizer.size(); i++)
		{
			if (i == 3)
				continue ;
			tokenizer[3] += " " + tokenizer[i];
			tokenizer.erase(tokenizer.begin() + i, tokenizer.begin() + i);
		}
		tokenizer[3] = tokenizer[3].substr(1, tokenizer[3].size() - 1);
	}
	client.setUsername(tokenizer[0]);
	client.setHostname(tokenizer[1]);
	client.setServerName(tokenizer[2]);
	client.setRealName(tokenizer[3]);
	vAuth |= USER_AUTH;
	client.setVAuth(vAuth);
	return (RPL_WELCOME(this->server->getHost(), client.getNickname()));
}
