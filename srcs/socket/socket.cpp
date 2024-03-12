#include "Socket.hpp"

Socket::Socket()
{

}

Socket::~Socket()
{

}

Socket::Socket(const Socket &ref)
{

}

Socket	&Socket::operator=(const Socket &ref)
{

}

Socket::Socket(/*Config config,*/ std::vector<int> port)
{
	(void) port;
}

void	Socket::addSocket(int index)
{

}

std::vector<int>	Socket::getSocket() const
{

}

int	Socket::getKqueue() const
{

}

std::map<int, std::string>	Socket::getRcv() const
{
	return this->_rcv;
}

std::map<int, std::string>  Socket::getSnd() const
{
	return this->_snd;
}

Parser	Socket::getConfig() const
{
	return this->_config;
}

void	addSocket(int index)
{

}

void	readSocket(struct kevent &socket)
{

}

void	writeSocket(struct kevent &socket)
{

}

int	parseSocket(struct kevent &socket)
{

}
 // renvoie un code parseCase 
int	processSocket()
{

}

void	setKqueue()
{

}

int	isSocket(uintptr_t socket) const
{

}
