/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:17:08 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/13 23:37:18 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Channel.hpp"

/* Constructors & Destructors */
Channel::Channel(void)
{
	this->name = "";
	this->topic = "Costumizable channel";
	this->joinedClients = client_n();
	this->operators = client_n();
	this->key = "";
	invitedClients = std::vector<str_t>();
	this->setMode(MODE_DEFAULT, I_MODE);
	this->setMode(MODE_DEFAULT, T_MODE);
	this->setMode(MODE_DEFAULT, K_MODE);
	this->setMode(MODE_O, O_MODE);
	this->setMode(MODE_DEFAULT, L_MODE);
}

Channel::Channel(const str_t &name)
{
	this->name = name;
	this->topic = "Costumizable channel";
	this->joinedClients = client_n();
	this->operators = client_n();
	this->key = "";
	invitedClients = std::vector<str_t>();
	this->setMode(MODE_DEFAULT, I_MODE);
	this->setMode(MODE_DEFAULT, T_MODE);
	this->setMode(MODE_DEFAULT, K_MODE);
	this->setMode(MODE_O, O_MODE);
	this->setMode(MODE_DEFAULT, L_MODE);
}

Channel::Channel(const str_t &name, const str_t &key)
{
	this->name = name;
	this->topic = "Costumizable channel";
	this->joinedClients = client_n();
	this->operators = client_n();
	this->key = key;
	invitedClients = std::vector<str_t>();
	this->setMode(MODE_DEFAULT, I_MODE);
	this->setMode(MODE_DEFAULT, T_MODE);
	this->setMode(MODE_DEFAULT, K_MODE);
	this->setMode(MODE_O, O_MODE);
	this->setMode(MODE_DEFAULT, L_MODE);
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

const client_n	&Channel::getoperators(void) const
{
    return (this->operators);
}

void		Channel::setoperators(const client_n &operators)
{
    this->operators = operators;
}

const str_t	&Channel::getKey(void) const
{
    return (this->key);
}

void		Channel::setKey(const str_t &key)
{
    this->key = key;
}

const char		&Channel::getMode(const int &mode) const
{
	return (this->mods[mode]);
}

void			Channel::setMode(const char &mode, const int &index)
{
	this->mods[index] = mode;
}

const size_t	&Channel::getLimit(void) const
{
	return (this->limit);
}

void			Channel::setLimit(const size_t &limit)
{
	if (limit < 1)
		this->limit = 1;
	else
		this->limit = limit;
}

const str_t		Channel::getCurrentModes(void) const
{
	int		i;
	str_t	modes;

	i = -1;
	modes = "+";
	while (++i < 5)
		if (this->mods[i] != MODE_DEFAULT)
			modes += this->mods[i];
	return (modes);
}

const std::vector<str_t>	&Channel::getInvitedTo(void)
{
	return (this->invitedClients);
}

void			Channel::setInvitedTo(const std::vector<str_t> &invitedTo)
{
	this->invitedClients = invitedTo;
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
	this->operators.insert(std::pair<const str_t, Client>(client.getNickname(), client));
}

void	Channel::removeMod(const str_t &nick)
{
	this->operators.erase(nick);
}

bool	Channel::isOperator(const str_t &nick)
{
	const client_n::iterator it = this->operators.find(nick);
	if (it != this->operators.end())
        return (true);
	return (false);
}

bool	Channel::isJoined(const str_t &nick)
{
	const client_n::iterator it = this->joinedClients.find(nick);
	if (it != this->joinedClients.end())
        return (true);
	return (false);
}

void	Channel::broadcast(const str_t &message, str_t nick)
{
	client_n::iterator	it;

	it = this->joinedClients.begin();
	for ( ; it != this->joinedClients.end(); it++)
	{
		if (it->second.getNickname() == nick)
			continue;
		send(it->second.getSocketFd(), message.c_str(), message.size(), 0);
	}
}

void	Channel::addToInvitedClients(const str_t &channel)
{
	this->invitedClients.push_back(channel);
}

bool	Channel::isInvited(const str_t &client)
{
	std::vector<str_t>::iterator	it;

	it = std::find(this->invitedClients.begin(), this->invitedClients.end(), client);
	if (it!= this->invitedClients.end())
		return (true);
	return (false);
}

void    Channel::removeFromInvitedClient(const str_t &client)
{
	std::vector<str_t>::iterator	it;

	it = std::find(this->invitedClients.begin(), this->invitedClients.end(), client);
	if (it!= this->invitedClients.end())
		this->invitedClients.erase(it);
}

const str_t	Channel::getAllUsers(void)
{
	str_t	users;

	users = "";
	for (client_n::iterator it = this->joinedClients.begin(); it != this->joinedClients.end(); it++)
	{
		if (this->operators.find(it->second.getNickname()) != this->operators.end())
			users += "@" + it->second.getNickname();
		else
			users += it->second.getNickname();
		users += " ";
	}
	users = users.substr(0, users.size() - 1);
	return (users);
}

client_n::iterator	Channel::getClientByNickname(const str_t &nickname)
{
	const client_n::iterator it = this->joinedClients.find(nickname);
	return (it);
}
