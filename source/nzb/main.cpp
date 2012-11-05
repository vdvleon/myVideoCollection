#include <MyVideoCollection/DownloaderApplication.hpp>

class Application : public MyVideoCollection::DownloaderApplication
{
	protected:
		std::string description() const
		{
			return "MyVideoCollection NZB downloader";
		}
		
		void continueDownload()
		{
			// TODO
		}
		
		void pauseDownload()
		{
			// TODO
		}
		
		void stopDownload()
		{
			// TODO
		}
		
		void updateStatus(DownloadStatus & status)
		{
			// TODO
		}
};
