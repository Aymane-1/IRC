/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Globals.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:42:30 by sel-kham          #+#    #+#             */
/*   Updated: 2023/09/01 00:28:13 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __GLOBALS_HPP__
# define __GLOBALS_HPP__

# include <iostream>
# include <string>

# define WHITESPACES " \t\r\n\b"
# define PASS_AUTH 1
# define NICK_AUTH 2
# define USER_AUTH 4
# define FULL_AUTH (PASS_AUTH | NICK_AUTH | USER_AUTH)

typedef std::string	str_t;

/* NUMERIC REPLIES */
# define RPL_WELCOME(server, nick) ":" + server + " 001 " + nick + " :Welcome to a7sn IRC server\r\n"

/* ERROR REPLIES */
# define ERR_NEEDMOREPARAMS(server, nickname) ":" + server  + " " + "461" + " " + nickname + ": Need more parameters\r\n"
# define ERR_PASSWDMISMATCH(server, nickname) ":" + server  + " " + "464" + " " + nickname + ": Invalid password\r\n"
# define ERR_ALREADYREGISTERED(server, nickname) ":" + server  + " " + "462" + " " + nickname + ": Already authenticated\r\n"
# define ERR_NONICKNAMEGIVEN "431"
# define ERR_ERRONEUSNICKNAME "432"
# define ERR_NICKNAMEINUSE "433"
# define ERR_NICKCOLLISION "436"
# define ERR_NOTREGISTERED(server, nickname) ":" + server + " " + "451" + " " + nickname + ": You have not registered.\r\n"

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
}

#endif