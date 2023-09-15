#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::kick(Client &client)
{
	std::cout << this->request << std::endl;
	std::vector<str_t>	args, target;
	str_t				channel, targets, comment, response;
	if (client.getVAuth() != FULL_AUTH)
        return (ERR_NOTREGISTERED(this->server->getHost(), client.getNickname()));
	args = Helpers::split(this->request, ' ');
	if (args.size() < 4 || args[1].empty() || args[2].empty())
		return(ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
	channel = args[1];
	std::map<const str_t, Channel>::iterator channelIter = this->server->channels.find(channel); 
	if (channelIter->first == channel)
	{
		if (!channelIter->second.isJoined(client.getNickname()))
			return (ERR_NOTONCHANNEL(this->server->getHost(), client.getNickname()));
		if (!channelIter->second.isOperator(client.getNickname()))
			return(ERR_CHANOPRIVSNEEDED(this->server->getHost(), client.getNickname(), channel));
		targets = args[2];
		target = Helpers::split(targets, ',');
		if (target.empty())
			return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
		std::vector<str_t>::iterator targetIter = target.begin();
		size_t commentCheck = this->request.find(args[3]);
		if (commentCheck != str_t::npos)
			comment = this->request.substr(commentCheck, this->request.length());
		else
			comment = "";
		for (size_t i = 0; targetIter != target.end(); i++)
		{
			if (!channelIter->second.isJoined(target[i])) 
				response += ERR_USERNOTINCHANNEL(this->server->getHost(), client.getNickname(), target[i], channel);
			else
			{
				client_m::iterator clientIter = CommandHelper::findClientByNickName(this, target[i]);
				str_t res = RPL_KICK_SUCCESS(client.getNickname(), client.getUsername(), this->server->getHost(), channel, clientIter->second.getNickname(), comment);
				send(clientIter->second.getSocketFd(), res.c_str(), res.length(), 0);
				channelIter->second.removeClient(clientIter->second.getNickname());
			}
			targetIter++;
		}
		this->server->removeChannel(channel);
	}
	else
		response = ERR_NOSUCHCHANNEL(this->server->getHost(), client.getNickname(), channel);
	return (response);
}