/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:34:15 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/27 19:21:36 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __SERVER_HP__
# define __SERVER_HP__

# include <sys/socket.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <poll.h>
# include <unistd.h>
# include "Globals.hpp"
# include "Client.hpp"

typedef struct sockaddr_in		sockaddr_in_t;

class Server
{
private:
	/* Class Attributes */
	int				masterSocketFd;
	int				port;
	str_t			password;
	sockaddr_in_t	addr;
public:
	/* Constructors & Destructors */
	Server(const int &port, const str_t &password);
	~Server(void);

	/* Getters & Setters */
	const int	&getMasterSocketFd(void) const;
	void		setMasterSocketFd(const int &fd);
	const int	&getPort(void) const;
	void		setPort(const int &port);
	const str_t	&getPassword(void) const;
	void		setPassword(const str_t &pass);

	/* External Class functionalities */
	void		initSocketMaster(void);
	void		bindSocketMaster(void);
	void		listenForConnections(void);
	int			acceptConnections(void);
	int			readRequest(Client &client);
};

#endif