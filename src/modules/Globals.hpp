/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Globals.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:42:30 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/04 02:32:19 by aechafii         ###   ########.fr       */
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

/* NUMERIC REPLIES */
# define RPL_WELCOME(server, nick)  ":" + server + " 001 " + nick + " :Welcome to a7sn IRCserver Network" + TRAILING

/* ERROR REPLIES */
# define ERR_NEEDMOREPARAMS(server, nickname) ":" + server  + " 461 " + nickname + ": Need more parameters." + TRAILING
# define ERR_PASSWDMISMATCH(server, nickname) ":" + server  + " 464 " + nickname + ": Invalid password." + TRAILING
# define ERR_ALREADYREGISTERED(server, nickname) ":" + server  + " 462 " + nickname + ": Unauthorized command (already registered)." + TRAILING
# define ERR_NONICKNAMEGIVEN(server, nickname) ":" + server  + " 431 " + nickname + ": No nickname provided." + TRAILING
# define ERR_ERRONEUSNICKNAME(server, nickname) ":" + server  + " 432 " + nickname + ": Invalid nickname." + TRAILING
# define ERR_NICKNAMEINUSE(server, nickname) ":" + server  + " 433 " + nickname + ": Nickname already in use." + TRAILING
# define ERR_NOTREGISTERED(server, nickname) ":" + server + " 451 " + nickname + ": You have not registered." + TRAILING
# define ERR_UNKNOWNCOMMAND(server, request) ":" + server + " 421 " + request + " :Unknown command" + TRAILING

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