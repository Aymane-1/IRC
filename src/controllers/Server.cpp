/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 06:02:02 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/02 00:01:45 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Server.hpp"

// Constructors & Distructors
Server::Server(void) : port(-1), password("") { }

Server::Server(int port, str_t password) : port(port), password(password) { }

Server::~Server(void) { }

Server			&Server::operator=(const Server &other)
{
	this->port = other.port;
	this->password = other.password;
	this->request = other.request;
	this->socketFd = other.socketFd;
	return (*this);
}

// Geters & Setters
const int	&Server::getPort(void) const
{
	return (this->port);
}

const str_t	&Server::getPassword(void) const
{
	return (this->password);
}

const int		&Server::getSocketFd(void) const
{
	return (this->socketFd);
}

const str_t	&Server::getRequest(void) const
{
	return (this->request);
}

void	Server::setSocketFd(const int fd)
{
	this->socketFd = fd;
}

void		Server::setRequest(const str_t &req)
{
	this->request = req;
}

// Class functionallities
