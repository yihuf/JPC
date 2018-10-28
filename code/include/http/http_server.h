#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/CountingStream.h"
#include "Poco/NullStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Exception.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include <iostream>


using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Net::MessageHeader;
using Poco::Net::HTMLForm;
using Poco::Net::NameValueCollection;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::CountingInputStream;
using Poco::NullOutputStream;
using Poco::StreamCopier;


class MyPartHandler: public Poco::Net::PartHandler
{
public:
	MyPartHandler():
		_length(0)
	{
	}
	
	void handlePart(const MessageHeader& header, std::istream& stream);
	
	int length() const
	{
		return _length;
	}
	
	const std::string& name() const
	{
		return _name;
	}

	const std::string& fileName() const
	{
		return _fileName;
	}
	
	const std::string& contentType() const
	{
		return _type;
	}
	
private:
	int _length;
	std::string _type;
	std::string _name;
	std::string _fileName;
};


class FormRequestHandler: public HTTPRequestHandler
	/// Return a HTML document with the current date and time.
{
public:
	FormRequestHandler() 
	{
	}
	
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};


class FormRequestHandlerFactory: public HTTPRequestHandlerFactory
{
public:
	FormRequestHandlerFactory()
	{
	}

	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
	{
		return new FormRequestHandler;
	}
};


class httpServer: public Poco::Util::ServerApplication
	/// The main application class.
	///
	/// This class handles command-line arguments and
	/// configuration files.
	/// Start the httpServer executable with the help
	/// option (/help on Windows, --help on Unix) for
	/// the available command line options.
	///
	/// To use the sample configuration file (httpServer.properties),
	/// copy the file to the directory where the httpServer executable
	/// resides. If you start the debug version of the httpServer
	/// (httpServer[.exe]), you must also create a copy of the configuration
	/// file named httpServer.properties. In the configuration file, you
	/// can specify the port on which the server is listening (default
	/// 9980) and the format of the date/Form string sent back to the client.
	///
	/// To test the FormServer you can use any web browser (http://localhost:9980/).
{
public:
	httpServer(): _helpRequested(false)
	{
	}
	
	~httpServer()
	{
	}

protected:
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
	}
		
	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);
		
		options.addOption(
			Option("help", "h", "display help information on command line arguments")
				.required(false)
				.repeatable(false));
	}

	void handleOption(const std::string& name, const std::string& value)
	{
		ServerApplication::handleOption(name, value);

		if (name == "help")
			_helpRequested = true;
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A web server that shows how to work with HTML forms.");
		helpFormatter.format(std::cout);
	}

	int main(const std::vector<std::string>& args);
	
private:
	bool _helpRequested;
};