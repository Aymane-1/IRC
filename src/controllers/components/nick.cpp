/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:18:53 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/01 01:31:16 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::nick(Client &client)
{
	short		vAuth;
	size_t		index;
	str_t		nick;
	const str_t	forbiddenToStartWith = "# :";

	vAuth = client.getVAuth();
	if (vAuth < PASS_AUTH)
		return (ERR_NOTREGISTERED(this->server->getHost(), client.getNickname()));
	index = this->request.find_first_of(" ");
	if (index == str_t::npos)
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	nick = this->request.substr(index, this->request.size() - 1);
	nick = Helpers::trim(nick, "\n \r");
	if (nick.empty())
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	
}

