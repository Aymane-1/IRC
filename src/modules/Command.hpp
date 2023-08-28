/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:51:57 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/28 04:51:51 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __COMMAND_HPP__
# define __COMMAND_HPP__

# include <map>
# include "Globals.hpp"
# include "Client.hpp"
# include "Server.hpp"

class Command
{
private:
	/* Private class attributes */
	str_t	request;
	str_t	command;
	str_t	response;
	Server	server;
public:
	/* Constructors & Destructors */
	Command(void);
	~Command(void);

	/* Getters & Setters */
	const str_t	&getRequest(void) const;
	void		setRequest(const str_t &request);
	const str_t	&getCommand(void) const;
	void		setCommand(const str_t &command);
	const str_t	&getResponse(void) const;
	void		setResponse(const str_t &response);

	/* Static Class Elements */
	typedef str_t (Command::*functionallity)(Client &client);
	static std::map<const str_t, Command::functionallity> allCommands;
	static void	storeCommands(void);
	
	/* Class  functionallities */
	void	extractCommand(void);
	str_t	(Command::*routing(void)) (Client &client);
	void	execute(Client &client); // TODO: update the return type to match the error massges to client
	str_t	pass(Client &client);
};

#endif