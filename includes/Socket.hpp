#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "Library.hpp"

enum parseCase {
	badRequest = 0,
	methodeNotAllowed = 1,
	done = 2,
	keepreading = 3,	
};

class Config;

class Socket
{
	public:
		///////////////							CONSTRUCTOR								///////////////
		Socket();
		Socket(const Socket &ref);
		Socket	&operator=(const Socket &ref);
		Socket(/*Config config,*/ std::vector<int> port);
		~Socket();
		///////////////////////////////////////////////////////////////////////////////////////////////

		///////////////								GETERS								///////////////
		std::vector<int>			getSocket() const;
		int							getKqueue() const;
		std::map<int, std::string>	getRcv() const;
		std::map<int, std::string>  getSnd() const;
		Config						*getConfig() const;
		struct sockaddr_in			getHint() const;
		///////////////////////////////////////////////////////////////////////////////////////////////
		
		///////////////								RUN									///////////////
		void						run();
		void						addSocket(int index);
		void						readSocket(struct kevent &socket);
		void						writeSocket(struct kevent &socket);
		int							parseSocket(struct kevent &socket); // renvoie un code parseCase 
		int							processSocket(); // renvoie un code parseCase 
		///////////////////////////////////////////////////////////////////////////////////////////////

		///////////////								UTILS								///////////////
		void						setKqueue();
		int							isSocket(uintptr_t socket) const;
		///////////////////////////////////////////////////////////////////////////////////////////////

	private:
		int							_kq;
		std::map<int, std::string>	_rcv; // la liste de requetes reçu  
		std::map<int, std::string>	_snd; // la liste de requetes (reponse) envoyer
		std::map<uintptr_t, bool>	_connection; // la liste de state de connexion
		struct sockaddr_in			_hint;
		Config						*_config;
		std::vector<int>			_socket;
};

#endif