/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandWorker.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/10 23:39:17 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#pragma once
#ifndef __COMMAND_WORKER_HPP__
# define __COMMAND_WORKER_HPP__

# include "Globals.hpp"
# include "Client.hpp"
# include "Command.hpp"
# include "Server.hpp"
# include "Channel.hpp"

class Server;
typedef std::map<const int, Client>	client_m;
typedef std::map<const str_t, Channel>	channel_m;

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
	str_t	nick(Client &client);
	str_t	user(Client &client);
	str_t	privmsg(Client &client);
	str_t	join(Client &client);
	str_t	invite(Client &client);
	str_t	topic(Client &client);
	str_t	quit(Client &client);
	str_t	mode(Client &client);
	str_t	bot(Client &client);
	class CommandHelper
	{
	private:
		CommandHelper(void);
		~CommandHelper(void);
	public:
		static client_m::iterator	findClientByNickName(CommandWorker *worker, const str_t &nick);
	};
};

#endif