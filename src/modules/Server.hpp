/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:01:30 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/27 00:32:07 by sel-kham         ###   ########.fr       */
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
# include <map>
# include "macros.hpp"
# include "Client.hpp"
# include "Command.hpp"

class Server
{
private:
	str_t						request;
	int							socketMaster;
	struct sockaddr_in			addr;

public:
	Server(void);
	~Server(void);
	static str_t password;
	static int port;
	// Getters and Setters
	Server			&operator=(const Server &other);
	const int		&getSocketMaster(void) const;
	const str_t		&getRequest(void) const;
	void			setRequest(const str_t &req);
	void			setSocketMaster(const int fd);
	// Class functionallities
	void			initSocket(void);
	void			bindSocket(void);
	void			listenForConnections(void);
	// void			initPoll(void);
	int				acceptConnection(void);
	int				polling(void);
	char			*readRequest(struct pollfd &fd);
	
};

#endif