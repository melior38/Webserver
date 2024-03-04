# ifndef CONF_HPP
# define CONF_HPP

#include "Library.hpp"

class Config
{
    public:
        Config();
        Config(Config const &ref);
        Config	&operator=(Config const &ref);
        ~Config();
        void    Check_conf_file(void);
        void    set_name(std::string name);

    private:
        std::map<std::string, std::string> _mp;
        std::string     _conf_file_name;
        std::string     check_first_sec_line(std::string line, int linenb);
        std::string     check_other_line(std::string line, int linenb);
        void            conf_error_handle(int error, int linenb);

        //debug utils
        void            print_conf_map(void);
};
#endif