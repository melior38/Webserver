
#ifndef ERROR_HPP
#define ERROR_HPP

#include "Library.hpp"

class Error
{
	public:
		class SocketException : public std::exception {
			virtual const char	*what() const throw {return "SocketException: socket failed"};
		}
		class ListenException : public std::exception {
			virtual const char	*what() const throw {return "ListenException: listen failed"};
		}
		class AcceptException : public std::exception {
			virtual const char	*what() const throw {return "AcceptException: accept failed"};
		}
		class FcntlException : public std::exception {
			virtual const char	*what() const throw {return "SocketException: fcntl failed"};
		}	
		class BindException : public std::exception {
			virtual const char	*what() const throw {return "BindException: bind failed"};
		}
		class KeventException : public std::exception {
			virtual const char	*what() const throw {return "KeventException: kevent failed"};
		}
		class GetSockNameException : public std::exception {
			virtual const char	*what() const throw {return "GetSockNameException: getSockName failed"};
		}
		class GetNameInfoException : public std::exception {
			virtual const char	*what() const throw {return "GetNameInfoException: getNameInfo failed"};
		}
		class AccessException : public std::exception {
			virtual const char	*what() const throw {return "AccessException: access failed"};
		}
		class PipeException : public std::exception {
			virtual const char	*what() const throw {return "PipeException: pipe failed"};
		}
		class ForkException : public std::exception {
			virtual const char	*what() const throw {return "ForkException: fork failed"};
		}
};



#endif
