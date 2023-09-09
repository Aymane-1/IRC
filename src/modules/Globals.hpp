/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Globals.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/09 21:24:02 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __GLOBALS_HPP__
# define __GLOBALS_HPP__

# include <iostream>
# include <vector>
# include <string>

# define WHITESPACES " \t\r\n\b"
# define PASS_AUTH 1
# define USER_AUTH 2
# define NICK_AUTH 4
# define FULL_AUTH (PASS_AUTH | NICK_AUTH | USER_AUTH)

typedef std::string	str_t;

# define TRAILING "\r\n"
# define MODE_DEFAULT 0
# define MODE_I 'i'
# define MODE_T 't'
# define MODE_K 'k'
# define MODE_O 'o'
# define MODE_L 'l'

enum mode_e
{
	I_MODE,
	T_MODE,
	K_MODE,
	O_MODE,
	L_MODE
};

/* NUMERIC REPLIES */
# define RPL_WELCOME(server, nick)  ":" + server + " 001 " + nick + " :Welcome to ‘LKHEDMAOUI SERVER’ !" + TRAILING
# define RPL_JOIN(nick, user, clientHost, channel) ":" + nick + "!" + user + "@" +  clientHost  + " JOIN " + channel + TRAILING
# define RPL_JOIN_WATCH(nick, user, host, channel) ":" + nick + "!" + user + "@" +  host + " JOIN " + channel + TRAILING
# define RPL_MODE(nickname, channel, mode) ":" + nickname + " MODE " + channel + " " + mode + TRAILING;
# define RPL_TOPIC(server, nickname, channel, topic) ":" + server + " 332 " + nickname + " " + channel + " :" + topic + TRAILING
# define RPL_INVITING(server, nick , user, clientHost, targetClient, channel)  ":" + server + " 341 " + nick + "!" + user + "@" + clientHost + " " + targetClient + " " + channel + TRAILING
# define RPL_SENDINVITE(clientNickname, clientUsername, server, targetUser, channel) ":" + clientNickname + "!" + clientUsername + "@" + server + " INVITE " + targetUser + ": " + channel + TRAILING
# define RPL_CLSLINK "ERROR :Closing link: (~"
# define RPL_QUIT(nickname, server, reason) nickname + "@" + server + ") [Quit" + reason + "]" + TRAILING

/* ERROR REPLIES */
# define ERR_NEEDMOREPARAMS(server, nickname) ":" + server  + " 461 " + nickname + ": Need more parameters." + TRAILING
# define ERR_PASSWDMISMATCH(server, nickname) ":" + server  + " 464 " + nickname + ": Invalid password." + TRAILING
# define ERR_ALREADYREGISTERED(server, nickname) ":" + server  + " 462 " + nickname + ": Unauthorized command (already registered)." + TRAILING
# define ERR_NONICKNAMEGIVEN(server, nickname) ":" + server  + " 431 " + nickname + ": No nickname provided." + TRAILING
# define ERR_ERRONEUSNICKNAME(server, nickname) ":" + server  + " 432 " + nickname + ": Invalid nickname." + TRAILING
# define ERR_NICKNAMEINUSE(server, nickname) ":" + server  + " 433 " + nickname + ": Nickname already in use." + TRAILING
# define ERR_NOTREGISTERED(server, nickname) ":" + server + " 451 " + nickname + ": You have not registered." + TRAILING
# define ERR_UNKNOWNCOMMAND(server, request) ":" + server + " 421 " + request + " :Unknown command" + TRAILING
# define ERR_NOSUCHCHANNEL(server, nick, channel) ":" + server + " 403 " + nick + " " + channel + " :No such channel" + TRAILING
# define ERR_NOSUCHNICK(server, nickname) ":" + server + " 401 " + nickname + " :No such nick/channel" + TRAILING
# define ERR_BADCHANNELKEY(server, nickname, channel) ":" + server + " 475 " + nickname + " " + channel + " :Cannot join channel (+" + MODE_K + ") - Bad key" + TRAILING
# define ERR_NOTONCHANNEL(server, user) ":" + server + " 442 " + user + " :You're not on that channel" + TRAILING
# define ERR_USERONCHANNEL(server, user) ":" + server + " 443 " + user + " :is already on channel" + TRAILING
# define ERR_CHANOPRIVSNEEDED(server, user, channel) ":" + server + " 482 " + user + " " +  channel + " :You're not channel operator" + TRAILING

/* BOT REPLIES */
# define RPL_TIME(server, user, time) ":" + server + " 391 " + user + " :Current date and time: " + time + TRAILING
# define RPL_INFO(server) ":" + server + " 371 val "
# define RPL_MYINFO(server) ":" + server + " 004 "
# define RPL_ENDOFINFO(server) ":" + server + " 374 val "
# define RPL_HELPSTART(server ) ":" + server + " 704 val "
# define RPL_HELPTXT(server ) ":" + server + " 705 val "
# define RPL_ENDOFHELP(server ) ":" + server + " 706 val "
# define RPL_QUOTE(server, vec) RPL_MYINFO(server) + TRAILING + RPL_MYINFO(server) + vec + TRAILING + RPL_MYINFO(server) + TRAILING
# define RPL_INSULT(server, vec) RPL_MYINFO(server) + TRAILING + RPL_MYINFO(server) + vec + TRAILING + RPL_MYINFO(server) + TRAILING
# define RPL_JOKE(server, vec) RPL_MYINFO(server) + TRAILING + RPL_MYINFO(server) + vec + TRAILING + RPL_MYINFO(server) + TRAILING
# define ERR_SUGGCOMMAND_BOT(server, nickname) ":" + server  + " 461 " + nickname + ": [BOT SUGGEST] Command takes one of these parameters: [QUOTE | INSULT | JOKE]!" + TRAILING
# define ERR_UNKNOWNCOMMAND_BOT(server, command) ":" + server + " 421 " + command + ": Unknown command, use ‘BOT HELP’ command to see the available bot commands." + TRAILING
# define ERR_NEEDMOREPARAMS_BOT(server, nickname) ":" + server  + " 461 " + nickname + ": Invalid number of arguments!" + TRAILING

namespace Helpers
{
	template<typename T>
	str_t	ltrim(str_t str, T c)
	{
		size_t	res;
		str_t	newstr;

		res = str.find_first_not_of(c);
		if (res != str_t::npos)
			return (str.substr(res));
		return (str);
	}

	template<typename T>
	str_t	rtrim(str_t str,  T c)
	{
		size_t	res;
		str_t	newstr;

		res = str.find_last_not_of(c);
		if (res != str_t::npos)
			return (str.substr(0, res + 1));
		return (str);
	}

	template<typename T>
	str_t	trim(str_t str, T c)
	{
		return (rtrim(ltrim(str, c), c));
	}

	template<typename T>
	std::vector<str_t>	split(const str_t &target, T del)
	{
		std::vector<str_t>	result;
		str_t				current;

		for (size_t i = 0; i < target.length(); i++)
		{
			if (target[i] == del)
			{
				if (current.find_first_not_of(del) == str_t::npos)
					continue;
				result.push_back(current);
				current.clear();
			}
			else
				current += target[i];
		}
		if (!current.empty())
			result.push_back(current);
		return result;      
	}
}

#endif