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
    int         linenb = 1;
    std::string line;
    std::ifstream myfile (this->_conf_file_name.c_str());
    if (myfile.is_open())
    {
        while(std::getline(myfile, line))
        {
            if (linenb < 3)
                line = check_first_sec_line(line, linenb);
            else
                line = check_other_line(line, linenb);
            //std::cout << line << std::endl;
            linenb++;
        }
        myfile.close();
    }
    else
        std::cout << "Unable to open file";
}

std::string Config::check_first_sec_line(std::string line, int linenb)
{
    int size;

    size = line.length();
    switch (linenb)
    {
        case 1:
            line.erase(line.end() - 1);
            if (line == "<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
                return line;
            else
                return ("error");
        break;

        case 2:
            if (size == 1)
                return line;
            else
                return ("error");
    }
    return (line);
}

std::string Config::check_other_line(std::string line, int linenb)
{
    std::string line2;
    int size;
    int subpos = 0;
    int i = 0;
    int j = 0;

    size = line.length();

    for (i = 0; i < size; i++)
    {
        if (line[i] == '<' && linenb > 0)
        {
            for (j = i + 1; j < size; j++)
            {
                if (line[j] == '>')
                    break;
            }
            subpos = j - (i + 1);
            line2.replace(0, subpos, line, i + 1, subpos);
            std::cout << line2 << std::endl;
            j = 0;   
        }
    }
    return (line);
}