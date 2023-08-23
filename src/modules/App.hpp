/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgs <mgs@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:04:25 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/23 23:10:48 by mgs              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __APP_HPP__
# define __APP_HPP__

# include <map>
# include <vector>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "Server.hpp"
# include "Client.hpp"
# include "Command.hpp"
# include "macros.hpp"

typedef std::string	str_t;
typedef std::map<const int, Client> client_m;

class App
{
private:
	int			port;
	str_t		password;
	Server		server;
	client_m	clients;

	// Internal App functions!
	const int	&getPort(void);
	const str_t	&getPassword(void);
	void		setPort(const char *port);
	void		setPassword(const char *password);
public:
	App(const char *port, const char *pass);
	~App(void);
	void		init(void);
	void		run(void);
};

#endif