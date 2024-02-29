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
	this->parse_input();
	for(std::map<std::string, std::string >::const_iterator it = this->_headers.begin(); \
	it != this->_headers.end(); ++it)
	{
	    std::cout << it->first << " " << it->second;
	}
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
	this->setCtrlData();
	cout << this->getRequest() << endl;
	size_t found_body = this->_request.find("\r\n\r\n");
	if (found_body != this->_request.length())
	{
		this->setHeader(this->_request.substr(0, found_body));
		this->_request.erase(0, found_body);
		this->_body = this->_request.substr(0);
	}
	else
	{
		this->setHeader(this->_request.substr(found_body));
		this->_body = "";
	}
}

void	Http::setHeader(std::string headers)
{
	std::string line;
	std::istream ss;
	size_t	startValue = headers.find(':');
	size_t	endValue = headers.find("\r\n");
    while (std::getline(ss, headers))
	{
		ss >> line;
		this->_headers[this->_request.substr(0 , startValue)] = this->_request.substr(startValue, endValue);
		this->_request.erase(endValue);
		line.clear();
    }
}

void	Http::setCtrlData()
{
	std::stringstream ss;
	std::string request_line = this->_request.substr(0, this->_request.find("\n", 0));
	this->_request.erase(this->_request.find('\n', 0));
	ss << request_line;
	for (int i = 0; i != 3; ++i)
		ss >> this->_ctrlData[i];
}

std::string	Http::getRequest() const
{
	return this->_request;
}