#include "http/httpServer.h"
#include <map>
using namespace std;





int main(int argc, char** argv)
{
	map<int, int> a = ({1,2},{1,3});
	httpServer app;
	return app.run(argc, argv);
}