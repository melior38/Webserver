/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:31:07 by marvin            #+#    #+#             */
/*   Updated: 2024/02/17 14:31:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Library.hpp"
#include "Http.hpp"

using std::cout;
using std::endl;

int main(void)
{
	std::ifstream myfile("srcs/http/example.http");
	std::string http;
	std::string line;
	if (myfile.is_open())
		while (getline(myfile,line))
			http += (line + '\n');
	else
		cout << "couldn't open file" << endl;

	Http request(http);
	(void) request;
	return 0;
}