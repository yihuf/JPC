//
// http_server.cpp
//

#include "http/http_server.h"


	
void MyPartHandler::handlePart(const MessageHeader& header, std::istream& stream)
{
	_type = header.get("Content-Type", "(unspecified)");
	if (header.has("Content-Disposition"))
	{
		std::string disp;
		NameValueCollection params;
		MessageHeader::splitParameters(header["Content-Disposition"], disp, params);
		_name = params.get("name", "(unnamed)");
		_fileName = params.get("filename", "(unnamed)");
	}
	
	CountingInputStream istr(stream);
	NullOutputStream ostr;
	StreamCopier::copyStream(istr, ostr);
	_length = istr.chars();
}
	
void FormRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
	Application& app = Application::instance();
	app.logger().information("Request from " + request.clientAddress().toString());

	MyPartHandler partHandler;
	HTMLForm form(request, request.stream(), partHandler);

	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html");

	std::ostream& ostr = response.send();
	
	ostr <<
		"<html>\n"
		"<head>\n"
		"<title>POCO Form Server Sample</title>\n"
		"</head>\n"
		"<body>\n"
		"<h1>POCO Form Server Sample</h1>\n"
		"<h2>GET Form</h2>\n"
		"<form method=\"GET\" action=\"/form\">\n"
		"<input type=\"text\" name=\"text\" size=\"31\">\n"
		"<input type=\"submit\" value=\"GET\">\n"
		"</form>\n"
		"<h2>POST Form</h2>\n"
		"<form method=\"POST\" action=\"/form\">\n"
		"<input type=\"text\" name=\"text\" size=\"31\">\n"
		"<input type=\"submit\" value=\"POST\">\n"
		"</form>\n"
		"<h2>File Upload</h2>\n"
		"<form method=\"POST\" action=\"/form\" enctype=\"multipart/form-data\">\n"
		"<input type=\"file\" name=\"file\" size=\"31\"> \n"
		"<input type=\"submit\" value=\"Upload\">\n"
		"</form>\n";
		
	ostr << "<h2>Request</h2><p>\n";
	ostr << "Method: " << request.getMethod() << "<br>\n";
	ostr << "URI: " << request.getURI() << "<br>\n";
	NameValueCollection::ConstIterator it = request.begin();
	NameValueCollection::ConstIterator end = request.end();
	for (; it != end; ++it)
	{
		ostr << it->first << ": " << it->second << "<br>\n";
	}
	ostr << "</p>";

	if (!form.empty())
	{
		ostr << "<h2>Form</h2><p>\n";
		it = form.begin();
		end = form.end();
		for (; it != end; ++it)
		{
			ostr << it->first << ": " << it->second << "<br>\n";
		}
		ostr << "</p>";
	}
	
	if (!partHandler.name().empty())
	{
		ostr << "<h2>Upload</h2><p>\n";
		ostr << "Name: " << partHandler.name() << "<br>\n";
		ostr << "File Name: " << partHandler.fileName() << "<br>\n";
		ostr << "Type: " << partHandler.contentType() << "<br>\n";
		ostr << "Size: " << partHandler.length() << "<br>\n";
		ostr << "</p>";
	}
	ostr << "</body>\n";
}

int http_server::main(const std::vector<std::string>& args)
{
	if (_helpRequested)
	{
		displayHelp();
	}
	else
	{
		unsigned short port = (unsigned short) config().getInt("httpServer.port", 9980);

		// set-up a server socket
		ServerSocket svs(port);
		// set-up a HTTPServer instance
		HTTPServer srv(new FormRequestHandlerFactory, svs, new HTTPServerParams);
		// start the HTTPServer
		srv.start();
		// wait for CTRL-C or kill
		waitForTerminationRequest();
		// Stop the HTTPServer
		srv.stop();
	}
	return Application::EXIT_OK;
}
