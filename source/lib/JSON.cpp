#include <MyVideoCollection/JSON.hpp>
#include <Poco/JSON/DefaultHandler.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Stringifier.h>

namespace MyVideoCollection
{
	Poco::Dynamic::Var JSON::parse(const std::istream & stream)
	{
		// Init parser
		Poco::JSON::DefaultHandler handler;
		Poco::JSON::Parser parser;
		parser.setHandler(&handler);
		
		// Parse
		parser.parse(stream);
		
		// Return result
		return handler.result();
	}
	
	Poco::Dynamic::Var JSON::parse(const std::string & str)
	{
		// Init parser
		Poco::JSON::DefaultHandler handler;
		Poco::JSON::Parser parser;
		parser.setHandler(&handler);
		
		// Parse
		parser.parse(str);
		
		// Return result
		return handler.result();
	}
	
	std::string JSON::stringify(const Dynamic::Var & any, std::size_t indent)
	{
		// Stringify
		std::ostringstream ss;
		Poco::JSON::Stringifier::stringify(any, ss, indent);
		
		return ss.str();
	}
};
