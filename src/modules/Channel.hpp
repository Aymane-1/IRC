/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:17:11 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/06 03:43:54 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __CHANNEL_HPP__
# define __CHANNEL_HPP__

# include <map>
# include <sys/socket.h>
# include "Globals.hpp"
# include "Client.hpp"

typedef std::map<const str_t, Client > client_n;

class Channel
{
private:
	str_t		name;
	str_t		topic;
	str_t		key;
public:
	client_n	joinedClients;
	client_n	mods;
	/* Constructors & Destructors */
	Channel(void);
	Channel(const str_t &name);
	Channel(const str_t &name, const str_t &key);
	~Channel(void);

	/* Getters & Setters */
	const str_t		&getName(void) const;
	void			setName(const str_t &name);
	const str_t		&getTopic(void) const;
	void			setTopic(const str_t &topic);
	const client_n	&getJoinedclients(void) const;
	void			setJoinedclients(const client_n &topic);
	const client_n	&getMods(void) const;
	void			setMods(const client_n &mods);
	const str_t		&getKey(void) const;
	void			setKey(const str_t &key);

	/* Class functionalities */
	void	addClient(const Client &client);
	void	removeClient(const str_t &nick);
	void	addMod(const Client &client);
	void	removeMod(const str_t &nick);
	void	broadcast(const str_t &message);
};

#endif