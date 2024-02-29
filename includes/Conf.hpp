# ifndef CONF_HPP
# define CONF_HPP

#include "Library.hpp"

class Config
{
    public:
        Config();
        Config(Config const &ref);
        Config	&operator=(Config const &ref);
    private:
        std::string     _server_names;
        unsigned int    _port;
};

#endif