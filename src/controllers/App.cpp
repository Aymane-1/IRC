/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:37:35 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/27 04:42:31 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/App.hpp"

/* Constructors & Destructors */
App::App(const char *port, const char *password) : server(Server(this->port, this->password))
{
	try
	{
		this->setPort(port);
		this->setPassword(password);
		this->server = Server(this->port, this->password);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		exit(EXIT_FAILURE);
	}
	
}

App::~App(void) { }

/* Internal class functionallities */
void		App::setPort(const char *port)
{
	unsigned long	found;

	if (!port)
		throw std::runtime_error("Port is required.");
	found = str_t(port).find_first_not_of("0123456789");
	if (found != std::string::npos)
		throw std::runtime_error("Port must contain only charachters.");
	found = atoi(port);
	if (found < 1024 || found > 65535)
		throw std::runtime_error("Port must be a number betweeen 1024 and 65535.");
	this->port = found;
}

void		App::setPassword(const char *password)
{
	if (!password)
		throw std::runtime_error("Password is required.");
	this->password = str_t(password);
}

pollfd_t	App::initPollFd(int fd, short event, short revent)
{
	pollfd_t	pfd;

	pfd.fd = fd;
	pfd.events = event;
	pfd.revents = revent;
	return (pfd);
}

/* External Class functionalities */
void	App::init(void)
{
	try
	{
		this->server.initSocketMaster();
		this->server.bindSocketMaster();
		this->server.listenForConnections();
	}
	catch(const std::exception& e)
	{
		perror(e.what());
		exit(EXIT_FAILURE);
	}
}

void	App::run(void)
{
	int			res;
	bool		keepAlive;
	pollfd_t	pfd;

	keepAlive = true;
	memset(&pfd, 0, sizeof(pollfd_t));
	pfd = this->initPollFd(this->server.getMasterSocketFd(), POLLIN, 0);
	this->pfds.push_back(pfd);
	while (keepAlive)
	{
		res = -1;
		res = poll(&pfds[0], pfds.size(), 0);
		if (res < 0)
			throw std::runtime_error("poll() failed");
		if (pfds[0].revents & POLLIN)
		{
			memset(&pfd, 0, sizeof(pollfd_t));
			res = this->server.acceptConnections();
			if (res < 0)
				continue ;
			pfd = this->initPollFd(res, POLLIN, 0);
			pfds.push_back(pfd);
			clients.insert(std::pair<const int, Client>(res, Client(res)));
		}
		for (size_t i = 1; i < pfds.size(); i++)
		{
			if (pfds[i].revents & POLLIN)
			{
				char buf[513] = { 0 };

				res = read(pfds[i].fd, buf, sizeof(buf));
				std::cout << buf;
			}
		}
	}
}
