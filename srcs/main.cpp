#include "Library.hpp"
#include "Http.hpp"
#include "Conf.hpp"

using std::cout;
using std::endl;

int main(void)
{
	{
		cout << "///////////////////////       HTTP      ///////////////////////" << endl;
		std::ifstream myfile("srcs/http/example.http");
		std::string http;
		std::string line;
		if (myfile.is_open())
			while (getline(myfile,line))
				http += (line + '\n');
		else
			cout << "couldn't open file" << endl;

		Http request(http);
		(void) request;
		cout << "///////////////////////////////////////////////////////////////" << endl;
	}
	{
		cout << "\n///////////////////////      SOCKET     ///////////////////////" << endl;
		try 
		{
			Socket				def;
			struct sockaddr_in	clientAddress = {};
			socklen_t			clientAddressLength = sizeof(clientAddress);
			int					clientSocket = accept(def.getSocket().at(0), reinterpret_cast<struct sockaddr*>(&clientAddress), &clientAddressLength);
			if (clientSocket < 0)
				throw(Error::AcceptException());
			cout << "Established connection !" << endl;
			close(clientSocket);
		}
		catch (std::exception &err)
		{
			std::cout << err.what() << std::endl;
			return 1;
		}
		cout << "///////////////////////////////////////////////////////////////" << endl;
	}
	{
		cout << "\n///////////////////////      CONFIG     ///////////////////////" << endl;
		Config test;

		test.Check_conf_file();
		cout << "///////////////////////////////////////////////////////////////" << endl;
	}
	return 0;
}