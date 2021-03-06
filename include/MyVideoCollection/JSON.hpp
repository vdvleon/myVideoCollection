#ifndef MyVideoCollection_JSON__
#define MyVideoCollection_JSON__

#include <Poco/Dynamic/Var.h>

namespace MyVideoCollection
{
	class JSON
	{
		public:
			static Poco::Dynamic::Var parse(std::istream & stream);
			static Poco::Dynamic::Var parse(const std::string & str);
			static std::string stringify(const Poco::Dynamic::Var & any);
	};
};

#endif
