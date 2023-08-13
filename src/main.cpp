/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:51:19 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/02 00:07:50 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/App.hpp"

void	panic(const char *msg)
{
	std::cerr << COLOR_RED << msg << COLOR_DEFAULT << std::endl;
	exit(1);
}

int	main(int c, char **v)
{

	if (c != 3)
		panic("Invalid number of arguments.");
	App	app(v[1], v[2]);
	app.init();
	app.run();
	return (0);
}
