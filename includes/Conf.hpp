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
        std::map<std::string, std::string> _mp;
        std::string     _conf_file_name;
        std::string     check_first_sec_line(std::string line, int linenb);
        std::string     check_other_line(std::string line, int linenb);
        void            conf_error_handle(int error);

        //debug utils
        void            print_conf_map(void);
};
#endif