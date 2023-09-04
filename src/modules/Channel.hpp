/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:17:11 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/04 01:18:28 by mmeziani         ###   ########.fr       */
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
		str_t		key;
	public:
		const str_t	&getName(void) const;
		void		setName(const str_t &name);
		const str_t	&getTopic(void) const;
		void		setTopic(const str_t &topic);
		const client_n	&getJoinedclients(void) const;
		void		setJoinedclients(const client_n &topic);
		const client_n	&getMods(void) const;
		void		setMods(const client_n &mods);
		const str_t	&getKey(void) const;
		void		setKey(const str_t &key);

};

#endif