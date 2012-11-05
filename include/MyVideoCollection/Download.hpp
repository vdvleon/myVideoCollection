#ifndef MyVideoCollection_Download__
#define MyVideoCollection_Download__

#include "DownloadStatus.hpp"
#include <Poco/Mutex.h>
#include <Poco/PipeStream.h>
#include <Poco/Runnable.h>

namespace MyVideoCollection
{
	class Download : public Poco::Runnable
	{
		public:
			Download(const std::string & downloader, const std::string & download);
			
			const std::string & downloader() const;
			const std::string & download() const;
			const DownloadStatus & status();
			
			void run();
			
			void pauseDownload();
			void continueDownload();
			void stopDownload();
			
		private:
			Poco::Mutex mutex_;
			DownloadStatus status_;
			const std::string downloader_;
			const std::string download_;
			Poco::PipeOutputStream * out_;
	};
};

#endif
 