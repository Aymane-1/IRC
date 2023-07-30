/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 01:16:22 by sel-kham          #+#    #+#             */
/*   Updated: 2023/07/30 01:29:08 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Command.hpp"

/* Constructors & Distructors */
Command::Command(const str_t &messgae) : message(messgae) { }

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
