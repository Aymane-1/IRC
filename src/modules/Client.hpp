/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:04:05 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/27 00:29:20 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __CLIENT_HPP__
# define __CLIENT_HPP__

# include "macros.hpp"
# include <poll.h>
typedef struct pollfd	pollfd_t;

class Client
{
private:
	int		clientFd;
	str_t	nickname;
	str_t	username;
	int		level;
	unsigned char vAuth;
	bool	isMod;
	pollfd_t	fd;
public:
	/* Constructors & Distructors */
	Client(void);
	Client(const int &fd);
	~Client(void);
	/* Class data */
	static const str_t forbiddenChars;
	static const str_t forbiddenToStartWith;
	/* Getters & Setters */
	const int	&getClientFd(void) const;
	const str_t	&getNickname(void) const;
	const str_t	&getUsername(void) const;
	const pollfd_t	&getFd(void) const;
	const bool	&getIsMod(void) const;
	const unsigned char &getVAuth(void) const;
	
	void	setClientFd(const int &fd);
	void	setNickname(const str_t &nickname);
	void	setUsername(const str_t &username);
	void	setIsMod(const bool &isMod);
	void	setVAuth(const unsigned char &vAuth);
	void	setPollFd(const pollfd_t &fd);
};

#endif