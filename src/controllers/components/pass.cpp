/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 02:29:49 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/31 22:36:44 by sel-kham         ###   ########.fr       */
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
		return (":" + this->server->getHost()  + " " + ERR_ALREADYREGISTERED + " " +client.getNickname() + ": Already authenticated\r\n");
	index = this->request.find_first_of(" ");
	if (index == str_t::npos)
		return (":" + this->server->getHost()  + " " + ERR_NEEDMOREPARAMS + " " +client.getNickname() + ": Need more parameters\r\n");
	password = this->request.substr(index, this->request.size() - 1);
	password = Helpers::trim(password, "\n \r");
	if (password != this->server->getPassword())
		return (":" + this->server->getHost()  + " " + ERR_PASSWDMISMATCH + " " +client.getNickname() + ": Invalid password\r\n");
	vAuth = client.getVAuth() | PASS_AUTH;
	client.setVAuth(vAuth);
	return (":" + this->server->getHost()  + " 001 " + client.getNickname() + " :Welcome to 7sn IRC server\r\n");
}
