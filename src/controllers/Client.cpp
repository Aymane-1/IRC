/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 02:41:57 by sel-kham          #+#    #+#             */
/*   Updated: 2023/07/29 02:27:57 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Client.hpp"

const str_t	Client::forbiddenChars = " ,*?!@.#&";
const str_t	Client::forbiddenToStartWith = "#&$:";
unsigned long	Client::count = 0;
 
 /* Constructors & Distructors */
 Client::Client(const unsigned int &fd)
 {
	this->clientFd = fd;
	this->id = Client::count++;
 }

 Client::~Client(void) { }

 /* Getters & Setters */
 const unsigned int	&Client::getId(void) const
 {
	return (this->id);
 }

 const unsigned long	&Client::getClientFd(void) const
 {
	return (this->clientFd);
 }

 const str_t			&Client::getNickname(void) const
 {
	return (this->nickname);
 }

 const str_t			&Client::getUsername(void) const
 {
	return (this->username);
 }

void	Client::setId(const unsigned int &id)
{
	this->id = id;
}

void	Client::setClientFd(const long int &fd)
{
	this->clientFd = fd;
}

void	Client::setNickname(const str_t &nickname)
{
	int	i;

	i = -1;
	if (!nickname[0] || Client::forbiddenToStartWith.find(nickname[0]) < Client::forbiddenToStartWith.length())
		throw (std::runtime_error("Invalid nickname."));
	while (nickname[++i])
		if (Client::forbiddenChars.find(nickname[i]) < Client::forbiddenChars.length())
			throw (std::runtime_error("Invalid nickname."));
	this->nickname = nickname;
}

void	Client::setUsername(const str_t &username)
{
	this->username = username;
}
