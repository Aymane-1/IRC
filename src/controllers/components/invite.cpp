/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:13:53 by aechafii          #+#    #+#             */
/*   Updated: 2023/09/04 01:23:26 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::invite(Client &client)
{
	std::vector<str_t>	tokenizer;
	str_t				

	tokenizer = Helpers::split(this->request, ' ');
	if (tokenizer.size() < 2)
		return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	
	return ("");
}