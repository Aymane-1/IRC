/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:32:56 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/27 04:30:19 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __CLIENT_HPP__
# define __CLIENT_HPP__

# include "Globals.hpp"

class Client
{
private:
	/* Private class attributes */
	int		socketFd;
	str_t	nickname;
	str_t	username;
	short	vAuth;
public:
	/* Constructors & Destructors */
	Client(const int &fd);
	~Client(void);
	
	/* Getters & Setters */
	const int	&getSocketFd(void) const;
	void		setSocketFd(const int &fd);
	const str_t	&getNickname(void) const;
	void		setNickname(const str_t &nickname);
	const str_t	&getUsername(void) const;
	void		setUsername(const str_t &username);
	const short	&getVAuth(void) const;
	void		setVAuth(const short &vAuth);

	/* Class functionnallities */
};

#endif