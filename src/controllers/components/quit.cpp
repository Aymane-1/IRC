/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:32:15 by aechafii          #+#    #+#             */
/*   Updated: 2023/09/07 20:21:30 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::quit(Client &client)
{
	str_t	reason = "";
	size_t	index = 0;
	index = this->request.find_first_of(" ");
	if (index != str_t::npos)
		reason = this->request.substr(index, this->request.length());
	str_t	serverResponse = RPL_CLSLINK;
	send(client.getSocketFd(), serverResponse.c_str(), serverResponse.length(), 0);
	this->server->clean(client.getSocketFd());
	return (RPL_QUIT(client.getNickname(), this->server->getHost(), reason));
}