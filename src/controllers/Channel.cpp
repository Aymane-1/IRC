/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:17:08 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/05 00:28:31 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Channel.hpp"

/* Constructors & Destructors */
Channel::Channel(void)
{
	this->name = "";
	this->topic = "";
	this->joinedClients = client_n();
	this->mods = client_n();
	this->key = "";
}

Channel::Channel(const str_t &name)
{
	this->name = name;
	this->topic = "";
	this->joinedClients = client_n();
	this->mods = client_n();
	this->key = "";
}

Channel::Channel(const str_t &name, const str_t &key)
{
	this->name = name;
	this->topic = "";
	this->joinedClients = client_n();
	this->mods = client_n();
	this->key = key;
}

Channel::~Channel(void) { }

/* Getters & Setters */
const str_t	&Channel::getName(void) const
{
    return (this->name);
}

void		Channel::setName(const str_t &name)
{
    this->name = name;

}
const str_t	&Channel::getTopic(void) const
{
    return (this->topic);
}

void		Channel::setTopic(const str_t &topic)
{
    this->topic = topic;
}

const client_n	&Channel::getJoinedclients(void) const
{
    return (this->joinedClients);
}

void		Channel::setJoinedclients(const client_n &joinedClients)
{
    this->joinedClients = joinedClients;
}

const client_n	&Channel::getMods(void) const
{
    return (this->mods);
}

void		Channel::setMods(const client_n &mods)
{
    this->mods = mods;
}

const str_t	&Channel::getKey(void) const
{
    return (this->key);
}

void		Channel::setKey(const str_t &key)
{
    this->key = key;
}

/* Class functionalities */
void	Channel::addClient(const Client &client)
{
	this->joinedClients.insert(std::pair<const str_t, Client>(client.getNickname(), client));
}

void	Channel::removeClient(const str_t &nick)
{
	this->joinedClients.erase(nick);
}

void	Channel::addMod(const Client &client)
{
	this->mods.insert(std::pair<const str_t, Client>(client.getNickname(), client));
}

void	Channel::removeMod(const str_t &nick)
{
	this->mods.erase(nick);
}
