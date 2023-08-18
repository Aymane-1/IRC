/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:01:30 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/18 04:46:31 by sel-kham         ###   ########.fr       */
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

typedef std::vector<struct pollfd>	poll_v;
class Server
{
private:
	int							port;
	str_t						password;
	str_t						request;
	int							socketMaster;
	struct sockaddr_in			addr;
	poll_v						fds;
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
	poll_v			&getFds(void);
	void			setRequest(const str_t &req);
	void			setSocketMaster(const int fd);
	void			setFds(const poll_v &fds);
	void			setFd(const struct pollfd &fd);
	// Class functionallities
	void			initSocket(void);
	void			bindSocket(void);
	void			listenForConnections(void);
	void			initPoll(void);
	int				acceptConnection(void);
	
};

#endif