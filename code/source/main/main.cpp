#include "http/httpServer.h"





int main(int argc, char** argv)
{
	httpServer app;
	return app.run(argc, argv);
}