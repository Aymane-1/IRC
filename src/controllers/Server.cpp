/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 06:02:02 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/13 20:06:24 by sel-kham         ###   ########.fr       */
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
	this->socketMaster = other.socketMaster;
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

const int		&Server::getSocketMaster(void) const
{
	return (this->socketMaster);
}

const str_t	&Server::getRequest(void) const
{
	return (this->request);
}

void	Server::setSocketMaster(const int fd)
{
	this->socketMaster = fd;
}

void		Server::setRequest(const str_t &req)
{
	this->request = req;
}

// Class functionallities
void			Server::initSocket(void)
{
	int	optval = 1;

	this->socketMaster = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->socketMaster < 0)
		throw std::runtime_error("Couldn't create socket.");
	if (setsockopt(this->socketMaster, SOL_SOCKET, SO_REUSEADDR,  (char *) &optval, sizeof(optval)) < 0)
		throw std::runtime_error("Error while setting socket options.");
}

void			Server::bindSocket(void)
{
	int	res = 1;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	res = bind(this->socketMaster, (struct sockaddr *) &this->addr, sizeof(struct sockaddr));
	if (res < 0)
		throw std::runtime_error("Couldn't bind socket.");
}

void			Server::listenForConnections(void)
{
	int	res;

	res = -1;
	res = listen(this->socketMaster, 5);
	if (res < 0)
		throw std::runtime_error("Error while listenning to connections.");
}

int			Server::acceptConnection(void)
{
	socklen_t	size;

	size = sizeof(struct sockaddr);
	return accept(this->socketMaster, (struct sockaddr *) &this->addr, &size);
}
