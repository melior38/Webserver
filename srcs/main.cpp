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
#include "Conf.hpp"

int main(int ac, char *av[])
{
	Config	test;

	if (ac == 2)
	{
		test.set_name(av[1]);
		test.Check_conf_file();
	}
	else
	{
		std::cout << "Error: Too little or too many args!" << std::endl;
		return (1);
	}
	return (0);
}