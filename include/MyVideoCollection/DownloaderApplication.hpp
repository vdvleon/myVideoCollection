#ifndef MyVideoCollection_DownloaderApplication__
#define MyVideoCollection_DownloaderApplication__

#include <Poco/Util/Application.h>

namespace MyVideoCollection
{
	class DownloaderApplication : public Poco::Util::Application
	{
		public:
			int main(const std::vector <std::string> & args);
			
		protected:
			virtual void updateStatus(DownloadStatus & status);
	};
};

#endif
