/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 02:41:57 by sel-kham          #+#    #+#             */
/*   Updated: 2023/07/18 02:47:27 by sel-kham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../modules/Client.hpp"

const str_t	Client::forbiddenChars = " ,*?!@.#&";
const str_t	Client::forbiddenToStartWith = "#&$:";
