/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:51:49 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/28 02:13:41 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Command.hpp"

/* Static Class Elements */
std::map<const str_t, Command::functionallity> Command::allCommands = std::map<const str_t, Command::functionallity>();

void	Command::storeCommands(void)
{
	Command::allCommands.insert(std::pair<const str_t, Command::functionallity>("PASS", &Command::pass));
}

/* Constructors & Destructors */
Command::Command(void) { }

Command::~Command(void) { }

/* Getters & Setters */
const str_t	&Command::getRequest(void) const
{
	return (this->request);
}

void		Command::setRequest(const str_t &request)
{
	this->request = request;
}

const str_t	&Command::getCommand(void) const
{
	return (this->command);
}

void		Command::setCommand(const str_t &command)
{
	this->command = command;
}

const str_t	&Command::getResponse(void) const
{
	return (this->response);
}

void		Command::setResponse(const str_t &response)
{
	this->response = response;
}

/* Class  functionallities */
void	Command::extractCommand(void)
{
	size_t	res;

	this->request = Helpers::trim(this->request, WHITESPACES);
	res = this->request.find_first_of(" ");
	if (res != str_t::npos)
		this->command = this->request.substr(0, res);
	else
		this->command = this->request;
}

str_t	Command::pass(void)
{
	return ("");
}
