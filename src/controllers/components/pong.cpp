/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 06:17:59 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/05 06:24:41 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::pong(Client &client)
{
	size_t	i;

	if (client.getVAuth() != FULL_AUTH)
		return (ERR_NOTREGISTERED(this->server->getHost(), client.getNickname()));
	i = this->request.find_first_of(" ");
	if (i == str_t::npos)
		return ("ERR_NOORIGIN(this->server->getHost(), client.getNickname())");
	return ("");
}
