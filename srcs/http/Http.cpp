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

Http::Http(std::string &request/*, uint_ptr socket*/) : _request(request)
{
	this->parse_input();
	cout << "\n               CTRL_DATA\n" << endl;
	cout << this->getCtrlData()[0] << " " << this->getCtrlData()[1] << " " << this->getCtrlData()[1] << endl;
	cout << "\n               HEADERS\n" << endl;
	for(std::map<std::string, std::string >::const_iterator it = this->_headers.begin(); \
	it != this->_headers.end(); ++it)
	{
	    std::cout << it->first << "  [" << it->second << "]" << endl;
	}
	cout << "\n               BODY";
	cout << this->getBody() << endl;
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
	size_t found_body = this->_request.find("\r\n\r\n");
	cout << "found_body == " << found_body << " length" << this->_request.length() << endl;
	if (found_body != this->_request.length() && found_body != std::string::npos)
	{
		this->setHeader(this->_request.substr(0, found_body + 2));
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
	size_t	startValue = headers.find(':');
	size_t	endValue;
	while ((endValue = headers.find("\r\n")) != std::string::npos)
	{
		if (startValue == std::string::npos)
			cout << "we have a problem !! (or im at the enb)" << endl;
		this->_headers[headers.substr(0, startValue)] = headers.substr(startValue + 2, endValue - startValue - 2);
		// cout << "{" << headers.substr(startValue + 2, endValue - startValue - 2) << "}" << endl;
		// cout << "{" << headers.substr(0, startValue + 1) << "}" << endl;
		headers.erase(0, endValue + 2);
		startValue = headers.find(':');
	}
}

void	Http::setCtrlData()
{
	std::stringstream ss;
	size_t endline = this->_request.find("\r\n", 0);
	if (endline != std::string::npos)
	{
		std::string request_line = this->_request.substr(0, endline);
		this->_request.erase(0, endline + 2);
		ss << request_line;
		for (int i = 0; i != 3; ++i)
			ss >> this->_ctrlData[i];
	}
}

std::string	Http::getRequest() const
{
	return this->_request;
}

std::string	*Http::getCtrlData()
{
	return this->_ctrlData;
}

std::string	Http::getBody() const
{
	return this->_body;
}

std::map<std::string, std::string>	Http::getHeaders() const
{
	return this->_headers;
}
