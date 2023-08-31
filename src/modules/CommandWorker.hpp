/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandWorker.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:29:47 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/31 02:52:51 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __COMMAND_WORKER_HPP__
# define __COMMAND_WORKER_HPP__

# include "Globals.hpp"
# include "Client.hpp"
# include "Command.hpp"
# include "Server.hpp"

class Server;

class CommandWorker : public Command
{
public:
	Server *server;
	CommandWorker(Server *server);
	typedef str_t (CommandWorker::*functionallity)(Client &client);
	static std::map<const str_t, CommandWorker::functionallity> allCommands;
	static void	storeCommands(void);
	str_t	(CommandWorker::*routing(void)) (Client &client);
	str_t	execute(Client &client); // TODO: update the return type to match the error massges to client
	str_t	pass(Client &client);
};

#endif