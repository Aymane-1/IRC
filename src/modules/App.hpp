/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 21:04:25 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/25 22:34:15 by sel-kham         ###   ########.fr       */
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

class App
{
private:
	int			port;
	str_t		password;
	Server		server;

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