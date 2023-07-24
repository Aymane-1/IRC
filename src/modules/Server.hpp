/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:01:30 by sel-kham          #+#    #+#             */
/*   Updated: 2023/07/21 23:46:17 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __SERVER_HPP__
# define __SERVER_HPP__

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include "macros.hpp"

class Server
{
private:
	const int			port;
	const str_t			password;
	str_t				request;
	int					socketFd;
	int					newSocket;
	struct sockaddr_in	socketAddr;
public:
	Server(int port, str_t password);
	~Server(void);
	// Getters and Setters
	const int	&getPort(void) const;
	const str_t	&getPassword(void) const;
	const int	&getSocketFd(void) const;
	const int	&getNewSocket(void) const;
	const str_t	&getRequest(void) const;
	void		setRequest(const str_t &req);
	void		setSocketFd(const int fd);
	void		setNewSocket(const int &socket);
	// Class functionallities
	void	initSocket(void);
	void	bindSocket(void);
	void	listenSocket(void);
	void	acceptSocket(void);
	void	readRequest(void);
	void	closeSocket(void);
};

#endif