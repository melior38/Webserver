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
		cout << "\n///////////////////////      CONFIG     ///////////////////////" << endl;
		Config test;

		test.Check_conf_file();
		cout << "///////////////////////////////////////////////////////////////" << endl;
	}
	return 0;
}