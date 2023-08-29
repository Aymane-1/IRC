/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:37:35 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/29 01:50:13 by sel-kham         ###   ########.fr       */
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

void		App::integrateNewConnect(Client &client)
{
	pollfd_t	pfd;

	memset(&pfd, 0, sizeof(pfd));
	pfd = this->initPollFd(client.getSocketFd(), POLLIN, 0);
	this->pfds.push_back(pfd);
	this->clients.insert(std::pair<const int, Client>(client.getSocketFd(), client));
}

void		App::clean(const int &index)
{
	close(this->pfds[index].fd);
	this->clients.erase(this->pfds[index].fd);
	this->pfds.erase(pfds.begin() + index);
}

/* External Class functionalities */
void	App::init(void)
{
	try
	{
		this->server.initSocketMaster();
		this->server.bindSocketMaster();
		this->server.listenForConnections();
		this->server.getServerHost();
		Command::storeCommands();
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

	keepAlive = true;
	this->pfds.push_back(this->initPollFd(this->server.getMasterSocketFd(), POLLIN, 0));
	while (keepAlive)
	{
		res = -1;
		res = poll(&pfds[0], pfds.size(), 0);
		if (res < 0)
			throw std::runtime_error("poll() failed");
		if (pfds[0].revents & POLLIN)
		{
			Client	newClient = Client(-1);
	
			res = this->server.acceptConnections(newClient);
			if (res < 0)
				continue ;
			this->integrateNewConnect(newClient);
		}
		for (size_t i = 1; i < pfds.size(); i++)
		{
			if (pfds[i].revents & POLLIN)
			{
				res = this->server.readRequest(clients.at(pfds[i].fd));
				if (!res)
					this->clean(i);
			}
		}
	}
}
