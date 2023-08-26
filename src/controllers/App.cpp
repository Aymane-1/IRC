/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:10:35 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/26 01:14:39 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/App.hpp"

App::App(const char *port, const char *pass)
{
	try
	{
		this->setPort(port);
		this->setPassword(pass);
	}
	catch (std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	this->server = Server();
}

App::~App(void) { }

const int	&App::getPort(void)
{
	return (this->port);
}

const str_t	&App::getPassword(void)
{
	return (this->password);
}

void		App::setPort(const char *p)
{
	unsigned long	found;

	if (!p)
		throw std::runtime_error("Port is required.");
	found = str_t(p).find_first_not_of("0123456789");
	if (found != std::string::npos)
		throw std::runtime_error("Port must contain only charachters.");
	found = atoi(p);
	if (found < 1024 || found > 65535)
		throw std::runtime_error("Port must be a number betweeen 1024 and 65535.");
	this->port = found;
}

void		App::setPassword(const char *pass)
{
	if (!pass)
		throw std::runtime_error("Password is required.");
	if (str_t(pass).length() < 8)
		throw std::runtime_error("Password must at least have 8 charachters.");
	this->password = pass;
}
#include <stdio.h>

void	App::init(void)
{
	try
	{
		Server::password = this->password;
		Server::port = this->port;
		this->server.initSocket();
		this->server.bindSocket();
		this->server.listenForConnections();
		Command::storeCommands();
	}
	catch (std::exception &e)
	{
		perror(e.what());
		exit(EXIT_FAILURE);
	}
}

void	App::run(void)
{
	bool	keep_running = true;
	poll_v	&pfds = this->server.getFds();
	int				res;
	unsigned int	i;
	Client	client;

	res = -1;
	this->server.initPoll();
	while (keep_running)
	{
		if (this->server.polling() < 0)
			break ;
		if (pfds[0].revents == POLLIN)
		{
			res = this->server.acceptConnection();
			if (res < 0)
				continue ;
			client = Client(res);
		}
		for (i = 1; i < pfds.size(); i++)
		{
			if (pfds[i].revents == POLLIN)
			{
				this->server.readRequest(pfds[i], client);
			}
		}
	}
}
