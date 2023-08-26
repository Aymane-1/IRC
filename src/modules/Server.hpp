/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:01:30 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/26 01:15:42 by sel-kham         ###   ########.fr       */
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

typedef std::vector<struct pollfd>	poll_v;
typedef std::map<const int, Client> client_m;
class Server
{
private:
	str_t						request;
	int							socketMaster;
	struct sockaddr_in			addr;
	poll_v						fds;
	client_m					clients;

public:
	Server(void);
	~Server(void);
	static str_t password;
	static int port;
	// Getters and Setters
	Server			&operator=(const Server &other);
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
	int				polling(void);
	int				readRequest(struct pollfd &fd, Client &client);
	
};

#endif