/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 02:29:49 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/31 03:14:34 by sel-kham         ###   ########.fr       */
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
		return ("Already authed");
	index = this->request.find_first_of(" ");
	if (index == str_t::npos)
		return (":" + this->server->getHost()  + " " + ERR_NEEDMOREPARAMS + " " +client.getNickname() + ": Need more parameters");
	password = this->request.substr(index, this->request.size() - 1);
	password = Helpers::trim(password, "\n \r");
	// std::cout << "1 => {" << password << "}" << std::endl;
	// std::cout << "2 => {" << this->server->getPassword() << "}" << std::endl;
	
	if (password != this->server->getPassword())
		return (":" + this->server->getHost()  + " " + ERR_PASSWDMISMATCH + " " +client.getNickname() + ": Invalid password");
	vAuth = client.getVAuth() | PASS_AUTH;
	client.setVAuth(vAuth);
	return (":" + this->server->getHost()  + " 001 " + client.getNickname() + " :Welcome to 7sn IRC server");
}
