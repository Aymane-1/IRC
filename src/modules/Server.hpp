/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:01:30 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/01 20:56:18 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __SERVER_HPP__
# define __SERVER_HPP__

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <poll.h>
# include <map>
# include "macros.hpp"
# include "Client.hpp"

typedef std::map<const str_t, Client> client_m;

class Server
{
private:
	const int			port;
	const str_t			password;
	str_t				request;
	int					socketFd;
	struct pollfd		fds;
public:
	Server(int port, str_t password);
	~Server(void);
	// Getters and Setters
	const int		&getPort(void) const;
	const str_t		&getPassword(void) const;
	const int		&getSocketFd(void) const;
	const str_t		&getRequest(void) const;
	const client_m	&getClients(void) const;
	void			setRequest(const str_t &req);
	void			setSocketFd(const int fd);
	void			setClients(const client_m &clients);
	// Class functionallities
	int				init(void);
	int				run(void);
};

#endif