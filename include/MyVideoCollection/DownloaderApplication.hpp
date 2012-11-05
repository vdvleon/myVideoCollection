#ifndef MyVideoCollection_DownloaderApplication__
#define MyVideoCollection_DownloaderApplication__

#include <Poco/Util/Application.h>
#include "DownloadStatus.hpp"

namespace MyVideoCollection
{
	class DownloaderApplication : public Poco::Util::Application
	{
		public:
			enum Action
			{
				CONTINUE = 1,
				PAUSE = 2,
				STOP = 3
			};
			
			DownloaderApplication();
			int main(const std::vector <std::string> & args);
			
		protected:
			virtual void continueDownload();
			virtual void pauseDownload();
			virtual void stopDownload();
			virtual std::string description() const;
			virtual void updateStatus(DownloadStatus & status);
		
		private:
			void defineOptions(Poco::Util::OptionSet & options);
			void handleHelp(const std::string& name, const std::string& value);
			
			bool help_;
	};
};

#endif
