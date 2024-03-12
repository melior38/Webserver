#include "Library.hpp"
#include "Http.hpp"

using std::cout;
using std::endl;

int main(void)
{
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
	return 0;
}