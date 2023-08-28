/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:51:57 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/28 02:09:01 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __COMMAND_HPP__
# define __COMMAND_HPP__

# include <map>
# include "Globals.hpp"

class Command
{
private:
	/* Private class attributes */
	str_t	request;
	str_t	command;
	str_t	response;
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
	typedef str_t (Command::*functionallity)(void);
	static std::map<const str_t, Command::functionallity> allCommands;
	static void	storeCommands(void);
	
	/* Class  functionallities */
	void	extractCommand(void);
	str_t	pass(void);
};

#endif