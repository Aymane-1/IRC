/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 06:02:02 by sel-kham          #+#    #+#             */
/*   Updated: 2023/07/21 23:58:09 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Server.hpp"

// Constructors & Distructors
Server::Server(int port, str_t password) : port(port), password(password) { }

Server::~Server(void) { }

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

void	Server::setSocketFd(const int fd)
{
	this->socketFd = fd;
}

const int	&Server::getNewSocket(void) const
{
	return (this->newSocket);
}

void		Server::setNewSocket(const int &socket)
{
	this->newSocket = socket;
}

const str_t	&Server::getRequest(void) const
{
	return (this->request);
}

void		Server::setRequest(const str_t &req)
{
	this->request = req;
}

// Class functionallities
void	Server::initSocket(void)
{
	this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketFd < 0)
		throw (std::runtime_error("Could not initialize socket."));
}
#include <errno.h>
void	Server::bindSocket(void)
{
	this->socketAddr.sin_family = AF_INET;
	this->socketAddr.sin_port = htons(this->port);
	this->socketAddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(this->getSocketFd(), (struct sockaddr *) &this->socketAddr, sizeof(this->socketAddr)) < 0)
	{
		std::cerr << errno << std::endl;
		throw (std::runtime_error("Could not bind socket."));
	}
}

void	Server::listenSocket(void)
{
	if (listen(this->getSocketFd(), 10) < 0)
		throw (std::runtime_error("Could not listen to incomming connections.")); 
}

void	Server::acceptSocket(void)
{
	socklen_t	sockLen = (socklen_t) sizeof(this->socketAddr);
	this->newSocket = accept(this->socketFd, (sockaddr *) &this->socketAddr, &sockLen);
	if (this->newSocket < 0)
		throw (std::runtime_error("Could not accept the current connection.")); 
}

void    Server::readRequest(void)
{
	char        buffer[1024];
    int            bytesRead;

    bytesRead = read(this->newSocket, buffer, 1024);
    if (bytesRead < 0)
        throw (std::runtime_error("Could not read the request."));
    buffer[bytesRead] = '\0';
    this->request = buffer;
}

void	Server::closeSocket(void)
{
	close(this->newSocket);
}
