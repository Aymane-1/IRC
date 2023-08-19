// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   Helpers.cpp                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/18 22:59:42 by sel-kham          #+#    #+#             */
// /*   Updated: 2023/08/19 00:26:26 by sel-kham         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "Helpers.hpp"
// namespace Helpers

// {template<typename T>
// str_t	ltrim( str_t &str,  T c)
// {
// 	size_t	res;
// 	str_t	newstr;

// 	res = str.find_first_not_of(c);
// 	if (res != str_t::npos)
// 		return (str.substr(res));
// 	return (str);
// }

// template<typename T>
// str_t	rtrim( str_t &str,  T c)
// {
// 	size_t	res;
// 	str_t	newstr;

// 	res = str.find_last_not_of(c);
// 	if (res != str_t::npos)
// 		return (str.substr(0, res - 1));
// 	return (str);
// }

// template<typename T>
// str_t	trim( str_t &str,  T c)
// {
// 	return (Helpers::rtrim(Helpers::ltrim(str, c), c));
// }
// }