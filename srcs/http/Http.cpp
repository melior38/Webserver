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

void	Http::parse_input(std::string &request)
{
	std::string request_line = request.substr(0, request.find("\n", 0));
	cout << request_line << endl;
}

std::string	Http::getRequest() const
{
	return this->_request;
}