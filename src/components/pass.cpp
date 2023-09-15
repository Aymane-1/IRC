/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 02:29:49 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/03 01:47:48 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::pass(Client &client)
{
	short	vAuth;
	str_t	password;
	size_t	index;

	vAuth = client.getVAuth();
	if ((vAuth == FULL_AUTH) || (vAuth == PASS_AUTH))
		return (ERR_ALREADYREGISTERED(this->server->getHost(), client.getNickname()));
	index = this->request.find_first_of(" ");
	if (index == str_t::npos)
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	password = this->request.substr(index, this->request.size() - 1);
	password = Helpers::trim(password, "\n \r");
	if (password != this->server->getPassword())
		return (ERR_PASSWDMISMATCH(this->server->getHost(), client.getNickname()));
	vAuth = client.getVAuth() | PASS_AUTH;
	client.setVAuth(vAuth);
	return ("");
}
