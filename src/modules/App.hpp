/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:28:22 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/28 00:24:18 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __APP_HPP__
# define __APP_HPP__

# include <vector>
# include <map>
# include "Server.hpp"
# include "Client.hpp"
# include "Globals.hpp"

typedef struct pollfd					pollfd_t;
typedef std::vector<pollfd_t>			pollfd_v;
typedef std::map<const int, Client>		client_m;

class App
{
private:
	/* Class Attributes */
	int			port;
	str_t		password;
	Server		server;
	pollfd_v	pfds;
	client_m	clients;
	/* Internal class functionallities */
	void		setPort(const char *port);
	void		setPassword(const char *password);
	pollfd_t	initPollFd(int fd, short event, short revent);
	void		integrateNewConnect(const int &res);
	void		clean(const int &index);
public:
	/* Constructors & Destructors */
	App(const char *port, const char *password);
	~App(void);
	
	/* External Class functionalities */
	void	init(void);
	void	run(void);
};

#endif