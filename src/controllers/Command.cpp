/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgs <mgs@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 01:16:22 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/23 23:04:52 by mgs              ###   ########.fr       */
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

// execmd	Command::commandRouting (void)
// {
// 	typedef void (Command::*execmd)(Client &, str_t &);
// 	execmd commands;


// 	if (commands.find(this->command) != commands.end())
// 		return commands[this->command];
// 	return (NULL);
// }
