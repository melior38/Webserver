/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Http.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:30:05 by marvin            #+#    #+#             */
/*   Updated: 2024/02/17 13:30:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Http.hpp"

using std::cout;
using std::endl;

Http::Http()
{

}

Http::Http(std::string &request) : _request(request)
{
	this->parse_input(request);
}

Http::Http(Http const &ref)
{
	*this = ref;
}

Http	&Http::operator=(Http const &ref)
{
	this->_request = ref.getRequest();
	return *this;
}

void	Http::parse_input(void)
{
	int line;
	if (this->_request.find("\n\n", ))
	for (int i = 0; this->_request[i]; i++)
	{

	}
}

void	Http::setCtrlData()
{
	std::stringstream ss;
	std::string request_line = request.substr(0, request.find("\n", 0));
	ss << request_line;
	for (int i = 0; i != 3; ++i)
		ss >> this->_ctrlData[i];
}

std::string	Http::getRequest() const
{
	return this->_request;
}