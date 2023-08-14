/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:01:30 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/13 22:01:52 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __SERVER_HPP__
# define __SERVER_HPP__

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <vector>
# include "macros.hpp"
# include "Client.hpp"

class Server
{
private:
	int							port;
	str_t						password;
	str_t						request;
	int							socketMaster;
	struct sockaddr_in			addr;
	std::vector<struct pollfd>	fds;
public:
	Server(void);
	Server(int port, str_t password);
	~Server(void);
	// Getters and Setters
	Server			&operator=(const Server &other);
	const int		&getPort(void) const;
	const str_t		&getPassword(void) const;
	const int		&getSocketMaster(void) const;
	const str_t		&getRequest(void) const;
	void			setRequest(const str_t &req);
	void			setSocketMaster(const int fd);
	// Class functionallities
	void			initSocket(void);
	//TODO: Set FD to non-blocking: fcntrl()
	void			bindSocket(void);
	void			listenForConnections(void);
	int				acceptConnection(void);
	
};

#endif