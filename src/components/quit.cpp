/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:32:15 by aechafii          #+#    #+#             */
/*   Updated: 2023/09/15 10:37:33 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/CommandWorker.hpp"

str_t	CommandWorker::quit(Client &client)
{
	str_t	reason = "";
	str_t	serverResponse = "";
	size_t	index = 0;
	
	index = this->request.find_first_of(" ");
	if (index != str_t::npos)
		reason = this->request.substr(index, this->request.length());
	if (reason.empty())
		serverResponse = RPL_QUIT(RPL_CLSLINK, client.getNickname(), this->server->getHost(), "Client exited");
	else
	{
		reason = Helpers::trim(reason, ' ');
		if (reason[0] == ':')
			reason = reason.substr(1, reason.length());
		serverResponse = RPL_QUIT(RPL_CLSLINK, client.getNickname(), this->server->getHost(), "Quit: " + reason);
	}
	send(client.getSocketFd(), serverResponse.c_str(), serverResponse.length(), 0);
	this->server->clean(client.getSocketFd());
	return ("");
}