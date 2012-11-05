#include <MyVideoCollection/DownloaderApplication.hpp>
#include <Poco/Util/HelpFormatter.h>
#include <iostream>

namespace MyVideoCollection
{
	DownloaderApplication::DownloaderApplication() :
		help_(false)
	{}
	
	int DownloaderApplication::main(const std::vector<std::string> & args)
	{
		// Stop because of help?
		if (help_)
		{
			return EXIT_USAGE;
		}
		
		// Read commands
		while (true)
		{
			short command;
			std::cin >> command;
			switch (command)
			{
				case CONTINUE:	continueDownload(); break;
				case PAUSE:		pauseDownload(); break;
				case STOP:		stopDownload(); break;
			}
		}
		
		return EXIT_OK;
	}
	
	void DownloaderApplication::defineOptions(Poco::Util::OptionSet & options)
	{
		Poco::Util::Application::defineOptions(options);
		
		// Download
		options.addOption(
			Poco::Util::Option("download", "d", "Download link (e.g. .nzb, .torrent, http://)", true, "download", true)
		);
		
		// Help
		options.addOption(
			Poco::Util::Option("help", "h", "display help information")
				.required(false)
				.repeatable(false)
				.callback(Poco::Util::OptionCallback<DownloaderApplication>(this, &DownloaderApplication::handleHelp))
		);
	}
	
	std::string DownloaderApplication::description() const
	{
		// Overwrite this function
		
		return "myVideoCollection downloader";
	}
	
	void DownloaderApplication::handleHelp(const std::string& name, const std::string& value)
	{
		// In help mode
		help_ = true;
		
		// Show help
		Poco::Util::HelpFormatter help(options());
		help.setCommand(commandName());
		help.setUsage("OPTIONS");
		help.setHeader(description());
		help.format(std::cout);
		
		// Stop
		stopOptionsProcessing();
	}

	void DownloaderApplication::updateStatus(DownloadStatus & status)
	{
		// Overwrite this function
	}
	
	void DownloaderApplication::continueDownload()
	{
		// Overwrite this function
	}
	
	void DownloaderApplication::pauseDownload()
	{
		// Overwrite this function
	}
	
	void DownloaderApplication::stopDownload()
	{
		// Overwrite this function
	}
};
