/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:51:49 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/28 04:51:45 by sel-kham         ###   ########.fr       */
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

str_t	(Command::*Command::routing(void)) (Client &client) // TODO: Update the function arguments later so it matches the type
{
	str_t	(Command::*fulfill) (Client &client);  // TODO: Update the function arguments later so it matches the type
	std::map<const str_t, functionallity>::iterator	it;

	it = Command::allCommands.find(this->command);
	fulfill = NULL;
	if (it != Command::allCommands.end())
		fulfill = it->second;
	return (fulfill);
}

void	Command::execute(Client &client)
{
	str_t	(Command::*fulfill) (Client &client);

	fulfill = this->routing();
	if (!fulfill)
		return ; // TODO: update the return type to match the error massges to client
	(this->*fulfill)(client);
}

str_t	Command::pass(Client &client)
{
	short	vAuth;
	str_t	password;
	size_t	index;

	vAuth = client.getVAuth();
	if ((vAuth == FULL_AUTH) || (vAuth == PASS_AUTH))
		return ("Already authenticated");
	index = this->request.find_first_of(" ");
	if (index == str_t::npos)
		return ("Not enought args");
	password = this->request.substr(index, this->request.size() - 1);
	password = Helpers::trim(password, "\n \r");
	if (password != this->server.getPassword())
		return ("Invalid password");
	vAuth = client.getVAuth() | PASS_AUTH;
	client.setVAuth(vAuth);
	return ("Passed");
}
