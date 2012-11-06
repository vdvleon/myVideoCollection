#ifndef MyVideoCollection_DownloaderApplication__
#define MyVideoCollection_DownloaderApplication__

#include <Poco/Util/Application.h>
#include <Poco/Timer.h>
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
			
		protected:
			int main(const std::vector <std::string> & args);
			virtual void initDownload();
			virtual void deinitDownload();
			virtual void continueDownload();
			virtual void pauseDownload();
			virtual void stopDownload();
			virtual std::string description() const;
			virtual void updateStatus(DownloadStatus & status);
			std::string dataFolder() const;
			void defineOptions(Poco::Util::OptionSet & options);
			void onProgressTimer(Poco::Timer & timer);
		
		private:
			void handleHelp(const std::string& name, const std::string& value);
			void handleDownloadOption(const std::string& name, const std::string& value);
			
			Poco::Path dataFolder_;
			bool help_;
			Poco::Timer progressTimer_;
			DownloadStatus status_;
	};
};

#endif
