/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 00:50:07 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/26 01:23:36 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __MACROS_HPP__
# define __MACROS_HPP__

# include <iostream>
# include <stdio.h>

# define COLOR_RED "\033[0;31m"
# define COLOR_DEFAULT "\033[0;37m"

/* Message Macros */
# define WHITESPACES "\n\b\t "
# define CORRECT_PASSWORD 3

/* NUMERIC REPLIES */
// PASS
# define ERR_NEEDMOREPARAMS "461"
# define ERR_ALREADYREGISTERED "462"
# define ERR_PASSWDMISMATCH "464"

enum	Level {
	CLIENT,
	OPERATOR
};


typedef std::string	str_t;

#endif