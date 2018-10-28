#include "http_server.h"






int main(int argc, char** argv)
{
	http_server app;
	return app.run(argc, argv);
}