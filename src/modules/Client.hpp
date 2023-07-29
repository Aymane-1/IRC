/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:04:05 by sel-kham          #+#    #+#             */
/*   Updated: 2023/07/29 02:07:01 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __CLIENT_HPP__
# define __CLIENT_HPP__

# include "macros.hpp"

class Client
{
private:
	unsigned int	id;
	unsigned long	clientFd;
	str_t			nickname;
	str_t			username;
public:
	/* Constructors & Distructors */
	Client(const unsigned int &fd);
	~Client(void);
	/* Class data */
	static const str_t forbiddenChars;
	static const str_t forbiddenToStartWith;
	static unsigned long	count;
	/* Getters & Setters */
	const unsigned int	&getId(void) const;
	const unsigned long	&getClientFd(void) const;
	const str_t			&getNickname(void) const;
	const str_t			&getUsername(void) const;
	
	void	setId(const unsigned int &id);
	void	setClientFd(const long int &fd);
	void	setNickname(const str_t &nickname);
	void	setUsername(const str_t &username);
};

#endif