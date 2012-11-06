#include <MyVideoCollection/JSON.hpp>
#include <Poco/StreamCopier.h>

namespace MyVideoCollection
{
	Poco::Dynamic::Var JSON::parse(std::istream & stream)
	{
		std::string str;
		Poco::StreamCopier::copyToString(stream, str);
		return parse(str);
	}
	
	Poco::Dynamic::Var JSON::parse(const std::string & str)
	{
		return Poco::Dynamic::Var::parse(str);
	}
	
	std::string JSON::stringify(const Poco::Dynamic::Var & any)
	{
		return Poco::Dynamic::Var::toString(any);
	}
};
