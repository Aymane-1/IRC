/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 01:16:22 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/24 23:37:46 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Command.hpp"

/* Constructors & Distructors */

Command::Command(str_t &messgae) : message(messgae) { }

Command::Command(const char *messgae)
{
	this->message = str_t(messgae);
}

Command::~Command() { }

/* Getters & Setters */
const str_t	&Command::getMessage(void) const
{
	return (this->message);
}

const str_t	&Command::getCommand(void) const
{
	return (this->command);
}

const str_v	&Command::getParameters(void) const
{
	return (this->parameters);
}

/* Class funcionallities */
std::map<const str_t, Command::execmd> Command::allCommands = std::map<const str_t, Command::execmd>();

void	Command::tokenizeCommand(void)
{
	size_t	i;

	this->message = Helpers::trim(this->message, WHITESPACES);
	i = this->extractCommand();
	if (i != str_t::npos)
		this->extractParams(i);
}

size_t	Command::extractCommand(void)
{
	size_t	i;
	str_t	cmd;

	i = -1;
	i = this->message.find(' ');
	if (i != str_t::npos)
	{
		this->command = this->message.substr(0, i);
		return (i);
	}
	this->command = this->message;
	return (str_t::npos);
}

void	Command::extractParams(const size_t &start)
{
	size_t		i = 0;
	str_t	newMessage(this->message.c_str() + start);

	while (i != str_t::npos)
	{
		newMessage = Helpers::trim(newMessage, " ");
		i = newMessage.find_first_of(" ");
		if (i == str_t::npos)
		{
			this->parameters.push_back(newMessage);
			break ;
		}
		this->parameters.push_back(newMessage.substr(0, i));
		newMessage = newMessage.c_str() + i;
	}
}

void	(Command::*Command::commandRouting(void)) (Client &)
{
	void	(Command::*functionallity) (Client &);
	std::map<const str_t, execmd>::iterator	it;

	functionallity = NULL;
	it = Command::allCommands.find(this->command);
	if (it != Command::allCommands.end())
		functionallity = it->second;
	return (functionallity);
}

void	Command::passCmd(Client &client)
{
	client.getClientFd();
	this->getCommand();
}
