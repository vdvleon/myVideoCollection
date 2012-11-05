#include <MyVideoCollection/Download.hpp>
#include <MyVideoCollection/DownloaderApplication.hpp>
#include <Poco/Process.h>

namespace MyVideoCollection
{
	Download::Download(const std::string & downloader, const std::string & download) :
		Poco::Runnable(),
		downloader_(downloader),
		download_(download),
		out_(0)
	{}
	
	const std::string & Download::downloader() const
	{
		return downloader_;
	}
	
	const std::string & Download::download() const
	{
		return download_;
	}
	
	const DownloadStatus & Download::status()
	{
		Poco::Mutex::ScopedLock lock(mutex_);
		
		return status_;
	}
	
	void Download::pauseDownload()
	{
		Poco::Mutex::ScopedLock lock(mutex_);
		
		if (!out_)
		{
			throw Poco::Exception("Can not pause a not started download thread");
		}
		
		*out_ << (short)DownloaderApplication::PAUSE << std::endl;
	}
	
	void Download::continueDownload()
	{
		Poco::Mutex::ScopedLock lock(mutex_);
		
		if (!out_)
		{
			throw Poco::Exception("Can not continue a not started download thread");
		}
		
		*out_ << (short)DownloaderApplication::CONTINUE << std::endl;
	}
	
	void Download::stopDownload()
	{
		Poco::Mutex::ScopedLock lock(mutex_);
		
		if (!out_)
		{
			throw Poco::Exception("Can not stop a not started download thread");
		}
		
		*out_ << (short)DownloaderApplication::STOP << std::endl;
	}
	
	void Download::run()
	{
		// Pipes
		Poco::Pipe inPipe;
		Poco::Pipe outPipe;
		
		// Arguments
		Poco::Process::Args arguments;
		
		// Start process
		Poco::ProcessHandle ph(Poco::Process::launch(downloader_, arguments, &inPipe, &outPipe, 0));
		
		// Open streams
		Poco::PipeInputStream in(outPipe);
		out_ = new Poco::PipeOutputStream(inPipe);
		
		// Read status
		while (true)
		{
			// Locked
			{
				Poco::Mutex::ScopedLock lock(mutex_);
				
				
			}
		}
	}
};
