/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:59:08 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/24 23:37:27 by sel-kham         ###   ########.fr       */
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

class Command;



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
	void	tokenizeCommand(void);
	size_t	extractCommand(void);
	void	extractParams(const size_t &start);
	void	(Command::*commandRouting(void))(Client &);
	void	passCmd(Client &client);
};

#endif