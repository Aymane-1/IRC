/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 06:02:02 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/18 20:16:12 by sel-kham         ###   ########.fr       */
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

poll_v	&Server::getFds(void)
{
	return (this->fds);
}

void	Server::setSocketMaster(const int fd)
{
	this->socketMaster = fd;
}

void		Server::setRequest(const str_t &req)
{
	this->request = req;
}

void			Server::setFds(const poll_v &fds)
{
	this->fds = fds;
}

void			Server::setFd(const struct pollfd &fd)
{
	this->fds.push_back(fd);
}

// Class functionallities
void			Server::initSocket(void)
{
	int	optval = 1;

	this->socketMaster = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->socketMaster < 0)
		throw std::runtime_error("Couldn't create socket");
	if (setsockopt(this->socketMaster, SOL_SOCKET, SO_REUSEADDR,  (char *) &optval, sizeof(optval)) < 0)
		throw std::runtime_error("Error while setting socket options");
	if (fcntl(this->socketMaster, F_SETFL, fcntl(this->socketMaster, F_GETFL, 0) | O_NONBLOCK) < 0)
		throw std::runtime_error("Error while setting server's file socket to non-blocking");
}

void			Server::bindSocket(void)
{
	int	res = 1;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	res = bind(this->socketMaster, (struct sockaddr *) &this->addr, sizeof(struct sockaddr));
	if (res < 0)
		throw std::runtime_error("Couldn't bind socket");
}

void			Server::listenForConnections(void)
{
	int	res;

	res = -1;
	res = listen(this->socketMaster, 5);
	if (res < 0)
		throw std::runtime_error("Error while listenning to connections");
}

int			Server::acceptConnection(void)
{
	socklen_t		size;
	int				newFd;
	struct pollfd	fd;

	size = sizeof(this->addr);
	newFd = accept(this->socketMaster, (struct sockaddr *) &this->addr, &size);
	if (newFd < 0)
		return (perror("accept errot"), -1);
	fd.fd = newFd;
	fd.events = POLLIN;
	fd.revents = 0;
	this->setFd(fd);
	return (newFd);
}

void			Server::initPoll(void)
{
	struct pollfd	fd;

	fd.fd = this->getSocketMaster();
	fd.events = POLLIN;
	fd.revents = 0;
	this->setFd(fd);
}

int				Server::polling(void)
{
	int	res;

	res = -1;
	res = poll(&this->fds[0], fds.size(), 0);
	if (res < 0)
		perror("poll error");
	return (res);
}

int				Server::readRequest(struct pollfd &fd)
{
	char	tempbuf[513] = {0};
	int		res = -1;

	res = read(fd.fd, tempbuf, sizeof(tempbuf) - 1);
	tempbuf[res] = 0;
	if (res < 0)
	{
		
	}
	else if (!res)
	{
		close(fd.fd);
		fd.fd = 0;
		fd.revents = 0;
	}
	else
	{
		std::cout << tempbuf;
	}
	return (res);
}
