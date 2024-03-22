#include "Socket.hpp"

using std::cout;
using std::endl;

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
 	this->_kq = -1;
	this->_hint = (struct sockaddr_in) {};
	// this->_config = config;
	this->_socket.push_back(socket(AF_INET, SOCK_STREAM, 0));
	this->_hint.sin_family = AF_INET;
	this->_hint.sin_addr.s_addr = INADDR_ANY;
	for (size_t i = 0; i < port.size(); i++)
	{
		this->_socket.push_back(socket(AF_INET, SOCK_STREAM, 0));
		if (this->_socket.at(i) < 0)
			throw(Error::SocketException());
		this->_hint.sin_port = htons(port.at(i));
		if (bind(this->_socket.at(i), reinterpret_cast <struct sockaddr *> (&this->_hint),sizeof(this->_hint)) < 0)
			throw(Error::BindException());
		if (listen(this->_socket.at(i), getWorkerConnections()))
			throw(Error::BindException());
	}

}

void	Socket::addSocket(int index)
{
	int	 newSocket;
	struct kevent	newClient = {};

	newSocket = accept(this->_socket.at(index), NULL, NULL);
	if (newSocket < 0)
		return ;
	if (fcntl(newSocket, F_SETFL, O_NONBLOCK) == -1)
		return ;

	struct sockaddr_in	sockAddr = {};
	socklen_t len = sizeof(sockAddr);
	if (getsockname(this->_socket.at(index), reinterpret_cast <struct sockaddr *> (&sockAddr), &len))
		return ;

	this->_connections[newSocket] = false;
	EV_SET(&newClient, newSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
	if (kevent(this->getKqueue(), &newClient, 1, NULL, 0, NULL) != -1)
	{
		this->_rcv.insert(std::pair<int, std::string>(newSocket, ""));
		this->_snd.insert(std::pair<int, std::string>(newSocket, ""));
		cout << "from mainSocket: " << this->_socket.at(index) << " on port: " << ntohs(sockAddr.sin_port) << ", new socket: " << newSocket << endl;
	}
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

int	Socket::getWorkerConnections() const
{
	// normalement il get les workerconnection du fichier conf 
	// mais pour l'instant je met une valeur en dure
	return 1024;
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
	if ((this->_kq = kqueue()) == -1)
		throw(Error::SocketException());
}

int	Socket::isSocket(uintptr_t socket) const
{
	for (size_t i = 0; i < this->_socket.size(); i++)
		if (static_cast <int> (socket) == this->_socket.at(i))
			return static_cast <int> (i);
	return -1;
}

void	Socket::run()
{
	int				indexSocket;
	int				nbrRequests;
	struct kevent	newSocket = {};
	struct kevent	events[100];

	this->setKqueue();
	for (size_t j = 0; j < this->_socket.size(); j++)
	{
		fcntl(this->_socket[j], F_SETFL, O_NONBLOCK);
		EV_SET(&newSocket, this->_socket[j], EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
		if (kevent(this->getKqueue(), &newSocket, 1, NULL, 0, NULL) == -1)
			exit(1);
		cout << "adding mainSocket: " << j << " to kevent" << endl;
	}
	while (true)
	{
		nbrRequests = kevent(this->getKqueue(), NULL, 0, events, 100, NULL);
		if (nbrRequests < 0)
			throw(Error::KeventException());
		for (int i = 0; i < nbrRequests; i++)
		{
			indexSocket = this->isSocket(events[i].ident);
			if (events[i].flags & EV_ERROR)
				cout << "socket " << i << " removed because of an error" << endl; // une ft qui remove des socket
			if (indexSocket >= 0)
				this->addSocket(indexSocket);
		}
	}
}