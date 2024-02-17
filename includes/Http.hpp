/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Http.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:08:09 by marvin            #+#    #+#             */
/*   Updated: 2024/02/17 13:08:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_HPP
# define HTTP_HPP

#include "Library.hpp"

class Http
{
	public:
		Http();
		Http(std::string const &request);
		Http(Http const &ref);
		Http	&operator=(Http const &ref);
	private:
		std::string							_request;
		std::string 						_ctrlData[3]; //[0] = GET ; [1] = /path ; [2] = HTTP/1.1
		std::map<std::string, std::string>	_headers;
		std::string 						_body;

}

#endif