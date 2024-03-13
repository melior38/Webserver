#include "Socket.hpp"

Socket::Socket() : _kq(-1), _hint((struct sockaddr_in){}), _config(NULL)
{
	this->_socket.push_back(socket(AF_INET, SOCK_STREAM, 0));
    if (this->_socket.at(0) < 0)
        throw(Error::SocketException());
    this->_hint.sin_family = AF_INET;
    this->_hint.sin_addr.s_addr = INADDR_ANY;
    this->_hint.sin_port = htons(8080);
    if (bind(this->_socket.at(0), reinterpret_cast<struct sockaddr *> (&this->_hint), sizeof(this->_hint)) < 0)
        throw(Error::BindException());
    if (listen(this->_socket.at(0), 1024))
        throw(Error::ListenException());
}

Socket::~Socket()
{
	for(size_t i = 0; i < this->_socket.size(); i++)
		close (this->_socket.at(i));
}

Socket::Socket(const Socket &ref)
{
    if (this != &ref)
        *this = ref;
}

Socket	&Socket::operator=(const Socket &ref)
{
	if (this != &ref)
    {
        this->_socket = ref.getSocket();
        this->_kq = ref.getKqueue();
        this->_hint = ref.getHint();
        this->_rcv = ref.getRcv();
        this->_snd = ref.getSnd();
        this->_config = ref.getConfig();
    }
	return *this;
}

Socket::Socket(/*Config config,*/ std::vector<int> port)
{
	(void) port;
}

void	Socket::addSocket(int index)
{
    (void) index;
}

std::vector<int>	Socket::getSocket() const
{
    return this->_socket;
}

int	Socket::getKqueue() const
{
    return this->_kq;
}

std::map<int, std::string>	Socket::getRcv() const
{
	return this->_rcv;
}

std::map<int, std::string>  Socket::getSnd() const
{
	return this->_snd;
}

Config	*Socket::getConfig() const
{
	return this->_config;
}

struct sockaddr_in	Socket::getHint() const
{
	return this->_hint;
}

void	addSocket(int index)
{
	(void) index;
}

void	Socket::readSocket(struct kevent &socket)
{
    (void) socket;
}

void	Socket::writeSocket(struct kevent &socket)
{
    (void) socket;
}

int	Socket::parseSocket(struct kevent &socket)
{
    (void) socket;
    return 0;
}

int	Socket::processSocket()
{
    return 0;
}

void	Socket::setKqueue()
{

}

int	Socket::isSocket(uintptr_t socket) const
{
    (void) socket;
    return 0;
}
