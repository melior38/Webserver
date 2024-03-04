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
    this->_conf_file_name = "0";
    this->_mp["listen"] = "1";
    this->_mp["server_name"] = "1";
    this->_mp["error_page_404"] = "1";
    this->_mp["error_page_500"] = "1";
    this->_mp["client_max_body_size"] = "1";
    this->_mp["root"] = "1";
    this->_mp["autoindex"] = "1";
    this->_mp["upload_store"] = "1";
    this->_mp["worker_connections"] = "1";
}

void    Config::set_name(std::string name)
{
    this->_conf_file_name = name;
}

Config::~Config(void)
{
    for (std::map<std::string, std::string>::iterator it = _mp.begin(); it != _mp.end();)
    {
        _mp.erase(it++);
    }
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
            else if (myfile.eof())
                line = check_first_sec_line(line, 0);
            else
                line = check_other_line(line, linenb);
            linenb++;
        }
        myfile.close();
    }
    else
        conf_error_handle(3, linenb);
    print_conf_map();
}

std::string Config::check_first_sec_line(std::string line, int linenb)
{
    int size;

    size = line.length();
    switch (linenb)
    {
        case 1:
            line.erase(line.end() - 1);
            if (line != "<?xml version=\"1.0\" encoding=\"UTF-8\"?>")
                conf_error_handle(1, linenb);
        break;
        case 2:
            if (size != 1)
                conf_error_handle(1, linenb);
        break;
        case 3:
            if (line != "config")
                conf_error_handle(1, linenb);
        break;
        case 0 :
            if (line != "</config>")
                conf_error_handle(1, linenb);
        break;
    }
    return (line);
}

std::string Config::check_other_line(std::string line, int linenb)
{
    std::string tag;
    std::string tag2;
    std::string arg;
    std::string templine = "test";
    int size;
    int subpos = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    size = line.length();

    for (i = 0; i < size; i++)
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '<')
            conf_error_handle(1, linenb);
        else if (line[i] == '<')
            break;
    }

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
            tag.replace(0, subpos, line, i + 1, subpos);
            check_first_sec_line(tag, linenb);
            if (linenb > 3)
            {
                for (k = j + 1; k < size; k++)
                {
                    if (line[k] == '<')
                        break;
                }
                arg.replace(0, k - (j + 1), line, j + 1, k - (j + 1));
                for (l = k + 1; l < size; l++)
                {
                    if (line[l] == '>')
                        break;
                }
                if (tag != "server_1" && tag != "/server_1" && tag != "/config")
                {
                    templine = line;
                    templine.erase(templine.end() - 1);
                    if (templine.c_str()[l + 1] != '\0')
                        conf_error_handle(1, linenb);
                    tag2.replace(0, l - (k + 1), line, k + 1, l - (k + 1));
                    if (tag2[0] != '/')
                        conf_error_handle(1, linenb);
                    if (tag2.compare(1, l - k, tag) == 0)
                    {
                        if (this->_mp[tag] == "1")
                        {
                            this->_mp[tag] = arg;
                        }
                        else
                            conf_error_handle(2, linenb);
                    }
                    else
                        conf_error_handle(1, linenb);
                    return (line);
                }
            }
        }
    }
    return (line);
}

void    Config::conf_error_handle(int error, int linenb)
{
    switch(error)
    {
        case 1:
            std::cout << "Error in config at line " << linenb << "!" << std::endl;
            exit (1);
        break;
        case 2:
            std::cout << "Error in tags! Please verify the names and check for any doubles!" << std::endl;
            exit (1);
        break;
        case 3:
            std::cout << "Wasn't able to open the file!" << std::endl;
            exit (1);
        break;
    }
}

void    Config::print_conf_map(void)
{
    std::map<std::string, std::string>::iterator it = this->_mp.begin();

     while (it != this->_mp.end())
     {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
        ++it;
    }
}