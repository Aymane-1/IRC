/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 03:36:00 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/27 04:30:28 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Client.hpp"

/* Constructors & Destructors */
Client::Client(const int &fd)
{
	this->socketFd = fd;
	this->nickname = str_t("");
	this->username = str_t("");
	this->vAuth = 0;
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


