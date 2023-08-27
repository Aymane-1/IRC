/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 01:27:04 by sel-kham          #+#    #+#             */
/*   Updated: 2023/08/27 04:06:23 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modules/IRC.hpp"

static void	panic(const char *msg)
{
	std::cerr << msg << std::endl;
	exit(EXIT_FAILURE);
}

int	main(int c, char **v)
{
	if (c != 3)
		panic("Not enough arguments.");
	App app = App(v[1], v[2]);
	app.init();
	try
	{
		app.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}
