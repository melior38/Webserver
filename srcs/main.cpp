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

using std::cout;
using std::endl;

int main(void)
{
	Config test;

	test.Check_conf_file();
	return (1);
}