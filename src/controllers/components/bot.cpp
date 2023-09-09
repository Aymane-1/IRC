/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 02:07:32 by aechafii          #+#    #+#             */
/*   Updated: 2023/09/09 05:43:19 by aechafii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::bot(Client &client)
{
	str_t				command;
	std::vector<str_t>	tokenizer;
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
	{
		return (RPL_MYINFO(this->server->getHost()) + TRAILING
		+ RPL_INFO(this->server->getHost()) + "*************************************  LKHEDMAOUI SERVER  *******************************************" + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "*** --------------------------------- CORE DEVELOPERS ---------------------------------------------" + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     Soufiane Khamlichi  :: <https://github.com/MGS15>                                 " + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     Aeymne Echafii      :: <https://github.com/Aymane-1>                               " + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     Mahmoud Meziani    :: <https://github.com/7ach7ouch101>                         " + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "*** --------------------------------- GENERAL SERVER COMMANDS -------------------------------------" + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     PASS  :: Set a ‘connection password’.                                             " + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     NICK  :: Set client's nickname or change the previous one.                        " + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     USER  :: Specify the username and realname of a new user at the beginning of a connection.  " + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     JOIN  :: Join a given channel.                                      " + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     PRIVMSG :: Send private messages between users/channels.           " + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "*** --------------------------------- CHANNEL OP COMMANDS -----------------------------------------" + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     KICK    :: Eject a client from the channel .                        " + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     INVITE  :: Invite a client to a channel.                            " + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     TOPIC   :: Change or view the channel topic.                        " + TRAILING
		+ RPL_INFO(this->server->getHost()) +  "***      -     MODE    :: Change the channel’s mode.                               " + TRAILING
		+ RPL_ENDOFINFO(this->server->getHost()) + "***************************************************************************************************" + TRAILING
		+ RPL_MYINFO(this->server->getHost()) + TRAILING); 
	}
	else if (command == "HELP" && tokenizer.size() == 2)
	{
		return (RPL_MYINFO(this->server->getHost()) + TRAILING
		+ RPL_HELPSTART(this->server->getHost()) + "**********************************         BOT COMMANDS        ********************************" + TRAILING 
		+ RPL_HELPTXT(this->server->getHost()) + "********************************************************************************" + TRAILING
		+ RPL_HELPTXT(this->server->getHost()) + "***             • TIME    [    NO parameters    ]:    :DISPLAY THE CURRENT TIME AND DATE.             ***" + TRAILING
		+ RPL_HELPTXT(this->server->getHost()) + "***             • INFO    [    NO parameters    ]:    :DISPLAY SERVER INFO.                           ***" + TRAILING
		+ RPL_HELPTXT(this->server->getHost()) + "***             • SUGGEST [QUOTE | INSULT | JOKE]:    :SUGGEST REQUESTED PARAMETER.          ***" + TRAILING
		+ RPL_ENDOFHELP(this->server->getHost()) + "********************************************************************************" + TRAILING
		+ RPL_MYINFO(this->server->getHost()) + TRAILING);
	}
	else if (command == "SUGGEST")
	{
		str_t	parameter = tokenizer[2];
		srand(time(NULL));
		int RandomNumber = rand() % 3;
		if (parameter == "QUOTE")
		{
			std::vector<str_t> quoteVec;
			quoteVec.push_back("* - Impossible is for the unwilling. ~ John Keats");
			quoteVec.push_back("* - Every man dies. Not every man lives. ~ William Wallace");
			quoteVec.push_back("* - Life shrinks or expands in proportion to one’s courage. ~ Anais Nin");
			if (RandomNumber == 0)
				return (RPL_QUOTE(this->server->getHost(), quoteVec[0]));
			else if (RandomNumber == 1)
				return (RPL_QUOTE(this->server->getHost(), quoteVec[1]));
			else if (RandomNumber == 2)
				return (RPL_QUOTE(this->server->getHost(), quoteVec[2]));
		}
		else if (parameter == "INSULT")
		{	
			std::vector<str_t> insultVec;
			insultVec.push_back("* - Can I have the name of your hair salon? I need to know where not to go.");
			insultVec.push_back("* - You are the human equivalent of a participation trophy.");
			insultVec.push_back("*  -You’re as useless as the “ueue” in “queue.”");
			if (RandomNumber == 0)
				return (RPL_QUOTE(this->server->getHost(), insultVec[0]));
			else if (RandomNumber == 1)
				return (RPL_QUOTE(this->server->getHost(), insultVec[1]));
			else if (RandomNumber == 2)
				return (RPL_QUOTE(this->server->getHost(), insultVec[2]));
		}
		else if (parameter == "JOKE")
		{
			std::vector<str_t> jokeVec;
			jokeVec.push_back("* - Where do most horses live? In neighhh-borhoods!");
			jokeVec.push_back("* - What do you call an old snowman? A glass of water!");
			jokeVec.push_back("* - What did the bathtub say to the toilet? “You look flushed!”");
			if (RandomNumber == 0)
				return (RPL_QUOTE(this->server->getHost(), jokeVec[0]));
			else if (RandomNumber == 1)
				return (RPL_QUOTE(this->server->getHost(), jokeVec[0]));
			else if (RandomNumber == 2)
				return (RPL_QUOTE(this->server->getHost(), jokeVec[0]));
		}
		return (ERR_SUGGCOMMAND_BOT(this->server->getHost(), "."));
	}
	return (ERR_UNKNOWNCOMMAND_BOT(this->server->getHost(), command));
}