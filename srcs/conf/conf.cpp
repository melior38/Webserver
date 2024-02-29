/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:53:04 by marvin            #+#    #+#             */
/*   Updated: 2024/02/17 13:53:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#include "../../includes/Library.hpp"
#include "../../includes/Conf.hpp"

Config::Config(void)
{
    this->_conf_file_name = "srcs/conf/config.xml";
    this->_listen = 0;
    this->_server_name = "default";
    this->_error_404_page = "default";
    this->_error_500_page = "default";
    this->_max_body_size = "default";
    this->_root = "default";
    this->_autoindex = false;
    this->_upload_store = "default";
}

void   Config::Check_conf_file(void)
{
    bool firstline = true;
    std::string line;
    std::ifstream myfile (this->_conf_file_name.c_str());
    if (myfile.is_open())
    {
        while(std::getline(myfile, line))
        {
            line = check_line(line, firstline);
            firstline = false;
            if (line == "error")
            {
                std::cout << line << std::endl;
                exit (1);
            }
            else
                std::cout << line << std::endl;
        }
    myfile.close();
    }
    else
        std::cout << "Unable to open file";
}

std::string check_line(std::string line, bool firstline)
{
    if (firstline == true)
    {
        line.erase(line.end() - 1);
        if (line == "<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
            return line;
        else
            return ("error");
    }
    return (line);
}