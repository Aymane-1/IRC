/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandWorker.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/15 06:42:51 by aechafii         ###   ########.fr       */
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
	str_t	execute(Client &client);
	str_t	pass(Client &client);
	str_t	nick(Client &client);
	str_t	user(Client &client);
	str_t	privmsg(Client &client);
	str_t	join(Client &client);
	str_t	invite(Client &client);
	str_t	topic(Client &client);
	str_t	quit(Client &client);
	str_t	mode(Client &client);
	str_t	kick(Client &client);
	str_t	pong(Client &client);
	str_t	bot(Client &client);
	str_t	away(Client &client);
	class CommandHelper
	{
	private:
		CommandHelper(void);
		~CommandHelper(void);
	public:
		static client_m::iterator	findClientByNickName(CommandWorker *worker, const str_t &nick);
	};
};

struct t_need // hady zadtha ana youlam
{
	std::vector<str_t>	tokenizer;
	str_t				channel;
	str_t				modes;
	str_t				response;
	size_t				j;
	channel_m::iterator	it;
	str_t				clientNick;
	str_t				serverHost;
	size_t				tokLen;
	char				sign;
};

#endif