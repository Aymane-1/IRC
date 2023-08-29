/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:54:20 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/29 19:27:37 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Server.hpp"

/* Constructors & Destructors */
Server::Server(const int &port, const str_t &password)
{
	this->port = port;
	this->password = password;
	this->masterSocketFd = -1;
	memset(&addr, 0, sizeof(sockaddr_in_t));
}

Server::~Server(void) { }

/* Getters & Setters */
const int	&Server::getMasterSocketFd(void) const
{
	return (this->masterSocketFd);
}

void		Server::setMasterSocketFd(const int &fd)
{
	this->masterSocketFd = fd;
}

const int	&Server::getPort(void) const
{
	return (this->port);
}

void		Server::setPort(const int &port)
{
	this->port = port;
}

const str_t	&Server::getPassword(void) const
{
	return (this->password);
}

void		Server::setPassword(const str_t &pass)
{
	this->password = pass;
}

void		Server::initSocketMaster(void)
{
	int	optval;

	optval = 0;
	this->masterSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->masterSocketFd < 0)
		throw std::runtime_error("Couldn't initialize server's socket");
	if (setsockopt(this->masterSocketFd, SOL_SOCKET, SO_REUSEADDR,  (char *) &optval, sizeof(optval)) < 0)
		throw std::runtime_error("Error while setting socket options");
	if (fcntl(this->masterSocketFd, F_SETFL, fcntl(this->masterSocketFd, F_GETFL, 0) | O_NONBLOCK) < 0)
		throw std::runtime_error("Error while setting server's file socket to non-blocking");
}

void			Server::bindSocketMaster(void)
{
	int	res = 1;

	this->addr.sin_family = AF_INET;
	this->addr.sin_port = htons(this->port);
	this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	res = bind(this->masterSocketFd, (struct sockaddr *) &this->addr, sizeof(struct sockaddr));
	if (res < 0)
		throw std::runtime_error("Couldn't bind socket");
}

void			Server::listenForConnections(void)
{
	int	res;

	res = -1;
	res = listen(this->masterSocketFd, 5);
	if (res < 0)
		throw std::runtime_error("Error while listenning to connections");
}

int			Server::acceptConnections(Client &client)
{
	socklen_t		size;
	int				newFd;

	size = sizeof(this->addr);
	newFd = accept(this->masterSocketFd, (struct sockaddr *) &this->addr, &size);
	if (newFd < 0)
		return (perror("accept errot"), -1);
	client.setSocketFd(newFd);
	client.setHost(inet_ntoa(this->addr.sin_addr));
	client.setPort(ntohs(this->addr.sin_port));
	return (newFd);
}

int			Server::readRequest(Client &client)
{
	char	tmpbuff[1024];
	int	res;

	memset(tmpbuff, 0, sizeof(tmpbuff));
	res = recv(client.getSocketFd(), tmpbuff, sizeof(tmpbuff), 0);
	if (res < 0)
	{
		//TODO: Handle error case of read
	}
	else if (!res)
	{
		// TODO: Handle the case of 0 bites read
	}
	else
	{
		
	}
	tmpbuff[res] = 0;
	std::cout << tmpbuff;
	return (res);
}
