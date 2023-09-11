/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:07:32 by aechafii          #+#    #+#             */
/*   Updated: 2023/09/11 01:44:05 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	suggest(str_t server, str_t parameter)
{
	srand(time(NULL));
	int RandomNumber = rand() % 4;
	if (parameter == "QUOTE")
	{
		std::vector<str_t> quoteVec;
		quoteVec.push_back("* - Impossible is for the unwilling. ~ John Keats");
		quoteVec.push_back("* - Every man dies. Not every man lives. ~ William Wallace");
		quoteVec.push_back("* - Life shrinks or expands in proportion to one’s courage. ~ Anais Nin");
		quoteVec.push_back("* - If you’re going through hell, keep going.” ~ Winston Churchill");
		if (RandomNumber == 0)
			return (RPL_QUOTE(server, quoteVec[0]));
		else if (RandomNumber == 1)
			return (RPL_QUOTE(server, quoteVec[1]));
		else if (RandomNumber == 2)
			return (RPL_QUOTE(server, quoteVec[2]));
		else
			return (RPL_QUOTE(server, quoteVec[3]));
	}
	else if (parameter == "INSULT")
	{	
		std::vector<str_t> insultVec;
		insultVec.push_back("* - Can I have the name of your hair salon? I need to know where not to go.");
		insultVec.push_back("* - You are the human equivalent of a participation trophy.");
		insultVec.push_back("* - You’re as useless as the “ueue” in “queue.");
		insultVec.push_back("* - You don’t need to fear success. You have nothing to worry about.");
		if (RandomNumber == 0)
			return (RPL_QUOTE(server, insultVec[0]));
		else if (RandomNumber == 1)
			return (RPL_QUOTE(server, insultVec[1]));
		else if (RandomNumber == 2)
			return (RPL_QUOTE(server, insultVec[2]));
		else
			return (RPL_QUOTE(server, insultVec[3]));
	}
	else if (parameter == "JOKE")
	{
		std::vector<str_t> jokeVec;
		jokeVec.push_back("* - Where do most horses live? In neighhh-borhoods!");
		jokeVec.push_back("* - What do you call an old snowman? A glass of water!");
		jokeVec.push_back("* - What did the bathtub say to the toilet? “You look flushed!");
		jokeVec.push_back("* - How does a scientist freshen her breath? With experi-mints.");
		if (RandomNumber == 0)
			return (RPL_QUOTE(server, jokeVec[0]));
		else if (RandomNumber == 1)
			return (RPL_QUOTE(server, jokeVec[1]));
		else if (RandomNumber == 2)
			return (RPL_QUOTE(server, jokeVec[2]));
		else
			return (RPL_QUOTE(server, jokeVec[3]));
	}
	return (ERR_SUGGCOMMAND_BOT(server, "."));
}

str_t	CommandWorker::bot(Client &client)
{
	str_t				command;
	std::vector<str_t>	tokenizer;
	if (client.getVAuth() != FULL_AUTH)
        return (ERR_NOTREGISTERED(this->server->getHost(), client.getNickname()));
	if (this->request.find_first_of(' ') == str_t::npos)
		return (ERR_UNKNOWNCOMMAND_BOT(this->server->getHost(), "."));
	tokenizer = Helpers::split(this->request, ' ');
	command   = tokenizer[1];
	if (tokenizer.size() < 2 || tokenizer.size() > 3)
		return (ERR_NEEDMOREPARAMS_BOT(this->server->getHost(), client.getNickname()));
	if (command == "TIME" && tokenizer.size() == 2)
	{
		time_t tmNow = time(0);
		str_t dt = ctime(&tmNow);
		send(client.getSocketFd(), dt.c_str(), dt.length(), 0);
		return (RPL_TIME(this->server->getHost(), client.getNickname(), dt));
	}
	else if (command == "INFO" && tokenizer.size() == 2)
		return (RPL_INFO_BOT(this->server->getHost())); 
	else if (command == "HELP" && tokenizer.size() == 2)
		return (RPL_HELP_BOT(this->server->getHost()));
	else if (command == "SUGGEST")
		return(suggest(this->server->getHost(), tokenizer[2]));
	return (ERR_UNKNOWNCOMMAND_BOT(this->server->getHost(), command));
}