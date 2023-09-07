/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 00:47:41 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/07 02:01:21 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

static void	i_modeHandler(const char &pm, channel_m::iterator &ch_it)
{
	if (pm == '-')
		ch_it->second.setMode();
}

str_t	CommandWorker::mode(Client &client)
{
	return (client.getNickname());
}
