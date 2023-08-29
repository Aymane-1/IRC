/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:17:11 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/29 22:20:49 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __CHANNEL_HPP__
# define __CHANNEL_HPP__

# include <map>
# include "Globals.hpp"
# include "Client.hpp"

typedef std::map<const str_t, Client > client_n;

class Channel
{
private:
	str_t		name;
	str_t		topic;
	client_n	joinedClients;
	client_n	mods;
};

#endif