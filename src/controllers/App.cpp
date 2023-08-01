/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:10:35 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/01 22:41:54 by sel-kham         ###   ########.fr       */
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
	catch (std::exception &e)
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
		std::runtime_error("Port is required.");
	found = str_t(p).find_first_not_of("0123456789");
	if (found != std::string::npos)
		std::runtime_error("Port must contain only charachters.");
	found = atoi(p);
	if (found < 1024 || found > 65535)
		std::runtime_error("Port must be a number betweeen 1024 and 65535.");
	this->port = found;
}

void		App::setPassword(const char *pass)
{
	if (!pass)
		std::runtime_error("Password is required.");
	if (str_t(pass).length() < 8)
		std::runtime_error("Password must at least have 8 charachters.");
	this->password = pass;
}

void	App::init(void)
{
	
}

void	App::run(void)
{
	
}
