/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 02:31:19 by mmeziani          #+#    #+#             */
/*   Updated: 2023/09/15 10:37:28 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/CommandWorker.hpp"

str_t	CommandWorker::topic(Client &client)
{
    str_t chann , args, cmd;
    size_t pos;
    channel_m::iterator ch_it;

    cmd = Helpers::trim(this->request , ' ');
    pos = this->request.find_first_of(' ');   
    
    if (pos == str_t::npos)
        return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
    cmd = cmd.substr(pos, cmd.size());
    cmd = Helpers::trim(cmd , ' ');

    if (cmd.empty())
        return (ERR_NEEDMOREPARAMS(this->server->getHost(), client.getNickname()));
    chann = cmd.substr(0, pos);
    chann = Helpers::trim(chann , ' ');
    pos = cmd.find_first_of(' ');
    ch_it = this->server->channels.find(chann);
    if (ch_it == this->server->channels.end())
        return (ERR_NOSUCHCHANNEL(this->server->getHost(), client.getNickname(),  chann));

    if (!(ch_it->second.isJoined(client.getNickname())))
        return (ERR_NOTONCHANNEL(this->server->getHost(), client.getNickname()));

    if (ch_it->second.getMode(T_MODE) == MODE_T)
        if (!(ch_it->second.isOperator(client.getNickname())))
            return (ERR_CHANOPRIVSNEEDED(this->server->getHost(), client.getNickname(),  chann));

            
    if (pos == str_t::npos)
    {
        if (ch_it->second.getTopic().empty())
            return (RPL_NOTOPIC(this->server->getHost(), client.getUsername(), chann));

        std::time_t result = std::time(nullptr);
        unsigned long time = result;
        return (
            str_t(RPL_TOPIC(this->server->getHost(), client.getUsername(), chann, ch_it->second.getTopic())) + 
            str_t(RPL_TOPICWHOTIME(this->server->getHost(), client.getUsername(), chann, time))
        );
    }
    else
    {
        args = cmd.substr(pos , cmd.size());
        args = Helpers::trim(args, ' ');
        if (args[0] == ':')
            args = args.substr(1 , cmd.size());
        ch_it->second.setTopic(args);
        ch_it->second.broadcast(args, client.getNickname());
        return (TOPIC_SUCCESS(client.getNickname(), client.getUsername(), this->server->getHost(), chann, args));

    }
}