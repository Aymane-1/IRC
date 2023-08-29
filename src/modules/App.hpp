/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:28:22 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/29 21:20:08 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __APP_HPP__
# define __APP_HPP__

# include "Server.hpp"
# include "Client.hpp"
# include "Command.hpp"
# include "Globals.hpp"

class App
{
private:
	/* Class Attributes */
	int			port;
	str_t		password;
	Server		server;
	/* Internal class functionallities */
	void		setPort(const char *port);
	void		setPassword(const char *password);
public:
	/* Constructors & Destructors */
	App(const char *port, const char *password);
	~App(void);
	
	/* External Class functionalities */
	void	init(void);
	void	run(void);
};

#endif