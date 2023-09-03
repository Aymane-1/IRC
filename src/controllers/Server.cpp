/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:54:20 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/03 23:45:12 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Server.hpp"

/* Constructors & Destructors */
Server::Server(void) { }

Server::Server(const int &port, const str_t &password): host("irc.taza7akmal3alam.com")
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

const str_t	&Server::getHost(void) const
{
	return (this->host);
}

void		Server::initSocketMaster(void)
{
	int	optval;

	optval = 1;
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

int			Server::acceptConnections(void)
{
	socklen_t		size;
	int				newFd;
	Client	newClient = Client(-1);

	size = sizeof(this->addr);
	newFd = accept(this->masterSocketFd, (struct sockaddr *) &this->addr, &size);
	if (newFd < 0)
		return (perror("accept errot"), -1);
	newClient.setSocketFd(newFd);
	newClient.setHost(inet_ntoa(this->addr.sin_addr));
	newClient.setPort(ntohs(this->addr.sin_port));
	this->integrateNewConnect(newClient);
	return (newFd);
}

// const str_t	Server::welcomeMessage(const Client &client)
// {
// 	return (
// 		" Welcome to 7sn IRC server"
// 	);
// }

pollfd_t	Server::initPollFd(int fd, short event, short revent)
{
	pollfd_t	pfd;

	pfd.fd = fd;
	pfd.events = event;
	pfd.revents = revent;
	return (pfd);
}

void		Server::integrateNewConnect(Client &client)
{
	pollfd_t	pfd;

	memset(&pfd, 0, sizeof(pfd));
	pfd = this->initPollFd(client.getSocketFd(), POLLIN, 0);
	this->pfds.push_back(pfd);
	this->clients.insert(std::pair<const int, Client>(client.getSocketFd(), client));
}

void		Server::clean(const int &index)
{
	close(this->pfds[index].fd);
	this->clients.erase(this->pfds[index].fd);
	this->pfds.erase(pfds.begin() + index, pfds.begin() + index);
}

int			Server::readRequest(Client &client)
{
	char	tmpbuff[1024];
	CommandWorker	cw = CommandWorker(this);
	int	res;
	str_t	response;
	size_t	response_len;

	memset(tmpbuff, 0, sizeof(tmpbuff));
	res = recv(client.getSocketFd(), tmpbuff, sizeof(tmpbuff), 0);
	if (res <= 0)
		return (res);
	tmpbuff[res] = 0;
	cw.setRequest(tmpbuff);
	cw.extractCommand();
	response = cw.execute(client);
	response_len = strlen(response.c_str());
	std::cout << "ALL USERS	|";
	for (client_m::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
		std::cout << it->second.getNickname() + "; ";
	std::cout << "|" << std::endl;
	std::cout << response << std::endl;
	// std::cout << "________________________________" << std::endl;
	// std::cout << "request	: |" << tmpbuff << "|" << std::endl;
	// std::cout << "response	: |" << response << "|" << std::endl;
	// std::cout << "PASS		: |" << this->password << "|" << std::endl;
	// std::cout << "NICK		: |" << client.getNickname() << "|" << std::endl;
	// std::cout << "USER		: |" << client.getUsername() << "|" << std::endl;
	// std::cout << "ALL USERS	: |";
	// for (client_m::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
	// 	std::cout << it->second.getNickname() + "; ";
	// std::cout << std::endl;
	// std::cout << "________________________________" << std::endl;
	res = send(client.getSocketFd(), response.c_str(), response_len, 0);
	return (res);
}
