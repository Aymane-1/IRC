/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:37:16 by sel-kham          #+#    #+#             */
/*   Updated: 2023/07/18 02:35:57 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __IRC_HPP__
# define __IRC_HPP__

# include "macros.hpp"

void	panic(const char *msg);
bool	is_valid_password(const char *pass);
int		is_valid_port(const char *p);
void	validate_args(char **args);

#endif