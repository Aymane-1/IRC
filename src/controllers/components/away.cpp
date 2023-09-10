/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:35:03 by aechafii          #+#    #+#             */
/*   Updated: 2023/09/10 22:17:09 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::away(Client &client)
{
	size_t				index;
	index = this->request.find_first_of(' ');
	if (index != str_t::npos)
	{
		client.setawayState(true);	
		client.setawayReason(this->request.substr(index, this->request.length()));	
		return (RPL_NOWAWAY(this->server->getHost(), client.getNickname()));
	}
	else
	{
		client.setawayState(false);	
		client.setawayReason("");	
		return (RPL_UNAWAY(this->server->getHost(), client.getNickname()));
	}
}