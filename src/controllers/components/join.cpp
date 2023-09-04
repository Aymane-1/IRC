/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:14:01 by mmeziani          #+#    #+#             */
/*   Updated: 2023/09/03 23:59:30 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../modules/CommandWorker.hpp"

str_t	CommandWorker::join(Client &client)
{
    std::string asdas = client.getNickname();
    std::string req = this->getRequest();
    // channel_m mapp;
    // Channel chann;
    // channel_m::iterator it;
    // mapp.insert(std::make_pair("test", chann));
    //std::cout << (*it)->first << std::endl;
    size_t pos1 = find('#');
    size_t pos2 = find('&');
    
    std::istringstream ss(req);
    std::string channel;
    if (req.find('#') != std::string::npos)
    {
        while (std::getline(ss , channel , '#'))
        {
            std::cout << channel << std::endl;
        }
    }
    
    if (req.find('&') != std::string::npos)
    {
        while (std::getline(ss , channel , '&'))
        {
            std::cout << channel << std::endl;
        }
    }
    return ("");
}