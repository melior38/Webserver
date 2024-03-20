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
			std::vector<int>	port;
			port.push_back(80);
			Socket				webserver(port);
			webserver.run();
			cout << "Established connection !" << endl;
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