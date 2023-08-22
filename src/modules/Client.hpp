/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:04:05 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/18 20:15:35 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __CLIENT_HPP__
# define __CLIENT_HPP__

# include "macros.hpp"

class Client
{
private:
	int		clientFd;
	str_t	nickname;
	str_t	username;
	bool	isAuthentecated;
	bool	isMod;
public:
	/* Constructors & Distructors */
	Client(void);
	~Client(void);
	/* Class data */
	static const str_t forbiddenChars;
	static const str_t forbiddenToStartWith;
	/* Getters & Setters */
	const int	&getClientFd(void) const;
	const str_t	&getNickname(void) const;
	const str_t	&getUsername(void) const;
	const bool	&getIsAuthentecated(void) const;
	const bool	&getIsMod(void) const;
	
	void	setClientFd(const int &fd);
	void	setNickname(const str_t &nickname);
	void	setUsername(const str_t &username);
	void	setIsAuthentecated(const bool &isAuth);
	void	setIsMod(const bool &isMod);
};

#endif