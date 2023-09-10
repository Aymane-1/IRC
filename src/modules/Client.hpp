/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:32:56 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/11 00:26:11 by aechafii         ###   ########.fr       */
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
	str_t	hostname;
	str_t	serverName;
	str_t	realName;
	str_t	host;
	str_t	awayReason;
	bool	awayState;
	int		port;
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
	const str_t	&getHost(void) const;
	void		setHost(const str_t &host);
	const int	&getPort(void) const;
	void		setPort(const int &port);
	const str_t	&getHostname(void) const;
	void		setHostname(const str_t &hostname);
	const str_t	&getServerName(void) const;
	void		setServerName(const str_t &servername);
	const str_t	&getRealName(void) const;
	void		setRealName(const str_t &servername);
	const str_t	&getawayReason(void) const;
	void		setawayReason(const str_t &awayReason);
	const bool	&getawayState(void) const;
	void		setawayState(const bool &awayState);

	/* Class functionnallities */
};

#endif