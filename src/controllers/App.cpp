/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:10:35 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/18 02:51:36 by sel-kham         ###   ########.fr       */
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
	this->server = Server(this->port, this->password);
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
		this->server.initSocket();
		this->server.bindSocket();
		this->server.listenForConnections();
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

	res = -1;
	this->server.initPoll();
	while (keep_running)
	{
		res = poll(&pfds[0], pfds.size(), 0);
		if (res < 0)
		{
			perror("poll error");
			break ;
		}
		if (pfds[0].revents == POLLIN)
		{
			res = this->server.acceptConnection();
			if (res < 0)
				continue ;
		}
		for (i = 1; i < pfds.size(); i++)
		{
			if (pfds[i].revents == POLLIN)
			{
				char tempbuf[1024] = {0};
				res = read(pfds[i].fd, tempbuf, sizeof(tempbuf) - 1);
				if (res < 0)
				{
				}
				else if (!res)
				{
					close(pfds[i].fd);
					pfds[i].fd = 0;
					pfds[i].revents = 0;
				}
				else
				{
					std::cout << tempbuf;
				}
			}
		}
	}
}
