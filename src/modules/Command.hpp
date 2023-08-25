/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:59:08 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/25 02:27:14 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __COMMAND_HPP__
# define __COMMAND_HPP__

# include "macros.hpp"
# include "Client.hpp"
# include "../helpers/Helpers.hpp"
# include <vector>
# include <map>

typedef std::vector<str_t> str_v;

class Command
{
private:
	str_t	message;
	str_t	command;
	str_v	parameters;
public:
	/* Constructors & Distructors */
	Command(str_t &messgae);
	Command(const char *messgae);
	~Command();
	/* Getters & Setters */
	const str_t	&getMessage(void) const;
	const str_t	&getCommand(void) const;
	const str_v	&getParameters(void) const;
	/* Class funcionallities */
	typedef void (Command::*execmd)(Client &);
	static std::map<const str_t, Command::execmd> allCommands;
	static void	storeCommands(void);
	size_t	extractCommand(void);
	void	(Command::*commandRouting(void))(Client &);
	void	executeCommand(Client &client);
	void	pass(Client &client);
	void	nick(Client &client);
};

#endif