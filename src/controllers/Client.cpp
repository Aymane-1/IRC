/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 03:36:00 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/13 06:02:50 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Client.hpp"

/* Constructors & Destructors */
Client::Client(const int &fd) : message("")
{
	this->socketFd = fd;
	this->nickname = str_t("");
	this->username = str_t("");
	this->vAuth = 0;
	this->awayReason = str_t("");
	this->awayState = false;
}

Client::~Client(void) { }

/* Getters & Setters */
const int	&Client::getSocketFd(void) const
{
	return (this->socketFd);
}

void		Client::setSocketFd(const int &fd)
{
	this->socketFd = fd;
}

const str_t	&Client::getNickname(void) const
{
	return (this->nickname);
}

void		Client::setNickname(const str_t &nickname)
{
	this->nickname = nickname;
}

const str_t	&Client::getUsername(void) const
{
	return (this->username);
}

void		Client::setUsername(const str_t &username)
{
	this->username = username;
}

const short	&Client::getVAuth(void) const
{
	return (this->vAuth);
}

void		Client::setVAuth(const short &vAuth)
{
	this->vAuth = vAuth;
}

const str_t	&Client::getHost(void) const
{
	return (this->host);
}

void		Client::setHost(const str_t &host)
{
	this->host = host;
}

const int	&Client::getPort(void) const
{
	return (this->port);
}

void		Client::setPort(const int &port)
{
	this->port = port;
}

const str_t	&Client::getHostname(void) const
{
	return (this->hostname);
}

void		Client::setHostname(const str_t &hostname)
{
	this->hostname = hostname;
}

const str_t	&Client::getServerName(void) const
{
	return (this->serverName);
}

void		Client::setServerName(const str_t &servername)
{
	this->serverName = servername;
}

const str_t	&Client::getRealName(void) const
{
	return (this->realName);
}

void		Client::setRealName(const str_t &realName)
{
	this->realName = realName;
}

const str_t	&Client::getawayReason(void) const
{
	return (this->awayReason);
}

void		Client::setawayReason(const str_t &awayReason)
{
	this->awayReason = awayReason;
}

const bool	&Client::getawayState(void) const
{
	return (this->awayState);
}

void		Client::setawayState(const bool &awayState)
{
	this->awayState = awayState;
}

const str_t	&Client::getMessage(void)
{
	return (this->message);
}

void		Client::setMessage(const str_t &message)
{
	this->message = message;
}

void		Client::appendToMessage(const str_t &message)
{
	this->message += message;
}
