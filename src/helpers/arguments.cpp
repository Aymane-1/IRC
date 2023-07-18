/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 00:53:58 by sel-kham          #+#    #+#             */
/*   Updated: 2023/07/18 09:22:35 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/irc.hpp"

bool	is_valid_password(const char *pass)
{
	if (!pass)
		return (false);
	if (str_t(pass).length() < 8)
		return (false);
	return (true);
}

int		is_valid_port(const char *p)
{
	str_t	port = str_t(p);
	std::size_t	found;
	
	if (!p)
		return (-1);
	found = port.find_first_not_of("0123456789");
	if (found != std::string::npos)
		return (-2);
	found = atoi(p);
	if (found < 1024 || found > 65535)
		return (-3);
	return (found);
}

void	validate_args(char **args)
{
	if (!is_valid_password(args[1]))
		panic("Password must at least have 8 charachters.");
	else if (is_valid_port(args[0]) == -1)
		panic("Invalid port.");
	else if (is_valid_port(args[0]) == -2)
		panic("Port must contain only charachters.");
	else if (is_valid_port(args[0]) == -3)
		panic("Port must be a number betweeen 1024 and 65535.");
}
