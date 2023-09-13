/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:32:15 by aechafii          #+#    #+#             */
/*   Updated: 2023/09/14 00:35:25 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::quit(Client &client)
{
	str_t	reason = "";
	str_t	serverResponse = "";
	size_t	index = 0;
	index = this->request.find_first_of(" ");
	if (index != str_t::npos)
		reason = this->request.substr(index + 1, this->request.length());
	if (reason.empty())
		serverResponse = RPL_QUIT(RPL_CLSLINK, client.getNickname(), this->server->getHost(), "Client exited");
	else
		serverResponse = RPL_QUIT(RPL_CLSLINK, client.getNickname(), this->server->getHost(), "Quit: " + reason);
	send(client.getSocketFd(), serverResponse.c_str(), serverResponse.length(), 0);
	return ("QUIT");
}