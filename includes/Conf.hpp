# ifndef CONF_HPP
# define CONF_HPP

#include "Library.hpp"

class Config
{
    public:
        Config();
        Config(Config const &ref);
        Config	&operator=(Config const &ref);
        void    Check_conf_file(void);

    private:
        std::string     _conf_file_name;
        std::string     _server_name;
        unsigned int    _listen;
        std::string     _error_404_page;
        std::string     _error_500_page;
        std::string     _max_body_size;
        std::string     _root;
        bool            _autoindex;
        std::string     _upload_store;
};

std::string  check_line(std::string line, bool firstline);
#endif