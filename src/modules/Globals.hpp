/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Globals.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/09/14 00:34:49 by aechafii         ###   ########.fr       */
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
# define MODE_DEFAULT '0'
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
# define RPL_QUIT(serverRes, nickname, server, reason) serverRes + nickname + "@" + server + ") [" + reason + "]" + TRAILING
# define RPL_NOTOPIC(server, username, chann) ":" + server + " 331 " + username + " " + chann + " :No topic is set." + TRAILING
# define RPL_TOPIC_SHOW(server, username, chann, topic, time) ":" + server + " 332 " + username + " " + chann + " " + topic + ":" + server + " 333 " + username + " " + chann + " " + username + " " + std::to_string(time) + TRAILING
# define TOPIC_SUCCESS(nickName, userName, server, chann, topic) ":" + nickName + "!" + userName + "@" + server + " TOPIC " + chann + " :" + topic + TRAILING
# define RPL_TOPICWHOTIME(server, nickname, channel, time) ":" + server + " 333 " + nickname + " " + channel + " " + nickname + " " + std::to_string(time) + TRAILING
# define RPL_NAMREPLY(server, nickname, channel, members) ":" + server + " 353 " + nickname + " = " + channel + " :" + members + TRAILING
# define RPL_ENDOFNAMES(server, nickname, channel) ":" + server + " 366 " + nickname + " " + channel + " ::End of /NAMES list." + TRAILING
# define RPL_YOUREOPER(server, nickname, targetNick, channel) ":" + server + " 381 " + nickname + " " + targetNick + " " + channel + " :You are now the channel operator." + TRAILING

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
# define RPL_CHANNELMODEIS(server, user, channel, modestring, modeparams) ":" + server + " 324 " + user + " " + channel + " " + modestring + " " + modeparams + TRAILING
# define ERR_USERNOTINCHANNEL(server, nickname, target, channel) ":" + server + " 441 " + nickname + " " + target + " " + channel + " :this user is not on the channel." + TRAILING
# define ERR_UNKNOWNMODE(server, nickname, channel, mode, message) ":" + server + " 472 " + nickname + " " + channel + " " + mode + " :" + message + TRAILING
# define RPL_UNAWAY(server, nick) ":" + server + " 305 " + nick + ":You are no longer marked as being away" + TRAILING
# define RPL_NOWAWAY(server, nick) ":" + server + " 306 " + nick + ":You have been marked as being away" + TRAILING
# define ERR_INVITEONLYCHAN(server, nickname, channel) ":" + server + " 473 " + nickname + " " + channel + " :Cannot join channel (+i)" + TRAILING
# define ERR_NOPRIVILEGES(server, nickname, channel) ":" + server + " 473 " + nickname + " " + channel + ":Permission Denied - You're not an operator" + TRAILING
# define ERR_CHANNELISFULL(server, nickname, channel) ":" + server + " 471 " + nickname + " " + channel + " :Cannot join channel (+l) - Channel is full" + TRAILING
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
# define ERR_SUGGCOMMAND_BOT(server, nickname) ":" + server  + " 461 " + nickname + ": <BOT SUGGEST> Command takes one of these parameters: [QUOTE | INSULT | JOKE]!" + TRAILING
# define ERR_UNKNOWNCOMMAND_BOT(server, command) ":" + server + " 421 " + command + ": Unknown command, use ‘BOT HELP’ command to see the available bot commands." + TRAILING
# define ERR_NEEDMOREPARAMS_BOT(server, nickname) ":" + server  + " 461 " + nickname + ": Invalid number of arguments!" + TRAILING
# define RPL_INFO_BOT(server) RPL_MYINFO(server) + TRAILING \
	+ RPL_INFO(server) + "*************************************  LKHEDMAOUI SERVER  *******************************************" + TRAILING \
	+ RPL_INFO(server) +  "*** --------------------------------- CORE DEVELOPERS ---------------------------------------------" + TRAILING \
	+ RPL_INFO(server) +  "***      -     Soufiane Khamlichi  :: <https://github.com/MGS15>                                 " + TRAILING \
	+ RPL_INFO(server) +  "***      -     Aeymne Echafii      :: <https://github.com/Aymane-1>                               " + TRAILING \
	+ RPL_INFO(server) +  "***      -     Mahmoud Meziani    :: <https://github.com/7ach7ouch101>                         " + TRAILING \
	+ RPL_INFO(server) +  "*** --------------------------------- GENERAL SERVER COMMANDS -------------------------------------" + TRAILING \
	+ RPL_INFO(server) +  "***      -     PASS  :: Set a ‘connection password’.                                             " + TRAILING \
	+ RPL_INFO(server) +  "***      -     NICK  :: Set client's nickname or change the previous one.                        " + TRAILING \
	+ RPL_INFO(server) +  "***      -     USER  :: Specify the username and realname of a new user at the beginning of a connection.  " + TRAILING \
	+ RPL_INFO(server) +  "***      -     JOIN  :: Join a given channel.                                      " + TRAILING \
	+ RPL_INFO(server) +  "***      -     PRIVMSG :: Send private messages between users/channels.           " + TRAILING \
	+ RPL_INFO(server) +  "*** --------------------------------- CHANNEL OP COMMANDS -----------------------------------------" + TRAILING \
	+ RPL_INFO(server) +  "***      -     KICK    :: Eject a client from the channel .                        " + TRAILING \
	+ RPL_INFO(server) +  "***      -     INVITE  :: Invite a client to a channel.                            " + TRAILING \
	+ RPL_INFO(server) +  "***      -     TOPIC   :: Change or view the channel topic.                        " + TRAILING \
	+ RPL_INFO(server) +  "***      -     MODE    :: Change the channel’s mode.                               " + TRAILING \
	+ RPL_ENDOFINFO(server) + "***************************************************************************************************" + TRAILING \
	+ RPL_MYINFO(server) + TRAILING
	
# define RPL_HELP_BOT(server) RPL_MYINFO(server) + TRAILING \
	+ RPL_HELPSTART(server) + "**********************************         BOT COMMANDS        ********************************" + TRAILING \
	+ RPL_HELPTXT(server) + "********************************************************************************" + TRAILING \
	+ RPL_HELPTXT(server) + "***             • BOT TIME    [    NO parameters    ]:    :DISPLAY THE CURRENT TIME AND DATE.         ***" + TRAILING \
	+ RPL_HELPTXT(server) + "***             • BOT INFO    [    NO parameters    ]:    :DISPLAY SERVER INFO.                       ***" + TRAILING \
	+ RPL_HELPTXT(server) + "***             • BOT SUGGEST [QUOTE | INSULT | JOKE]:    :SUGGEST REQUESTED PARAMETER.      ***" + TRAILING \
	+ RPL_ENDOFHELP(server) + "********************************************************************************" + TRAILING \
	+ RPL_MYINFO(server) + TRAILING

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