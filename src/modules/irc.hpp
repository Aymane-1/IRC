/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:37:16 by sel-kham          #+#    #+#             */
/*   Updated: 2023/07/18 01:13:56 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __IRC_HPP__
# define __IRC_HPP__

# include <iostream>
# include "macros.hpp"

typedef std::string	str_t;

void	panic(const char *msg);
bool	is_valid_password(const char *pass);
int		is_valid_port(const char *p);
void	validate_args(char **args);

#endif