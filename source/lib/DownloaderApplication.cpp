#include <MyVideoCollection/DownloaderApplication.hpp>
#include <Poco/Util/HelpFormatter.h>
#include <iostream>

namespace MyVideoCollection
{
	DownloaderApplication::DownloaderApplication() :
		Poco::Util::Application(),
		help_(false)
	{}
	
	int DownloaderApplication::main(const std::vector<std::string> & args)
	{
		Poco::Util::Application::main(args);
		
		// Stop because of help?
		if (help_)
		{
			// Show help
			Poco::Util::HelpFormatter help(options());
			help.setCommand(commandName());
			help.setUsage("OPTIONS");
			help.setHeader(description());
			help.format(std::cout);
			
			return EXIT_USAGE;
		}
		
		// Prepare data folder
		dataFolder_ = "data/" + config().getString("downloadID") + "/";
		if (!findFile(dataFolder_))
		{
			return EXIT_CONFIG;
		}
		
		// Init
		init();
		
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
		
		// Deinit
		deinit();
		
		return EXIT_OK;
	}
	
	void DownloaderApplication::defineOptions(Poco::Util::OptionSet & options)
	{
		Poco::Util::Application::defineOptions(options);
		
		std::cout << "A\n";
		
		// Download
		options.addOption(
			Poco::Util::Option("download", "d", "Download link (e.g. .nzb, .torrent, http://)", false, "download", true)
				.binding("download")
		);
		
		// ID
		options.addOption(
			Poco::Util::Option("downloadID", "i", "Download ID", true, "id", true)
				.binding("downloadID")
		);
		
		// Download option
		options.addOption(
			Poco::Util::Option("downloadOption", "o", "Download option (e.g. server=1.2.3.4)", false, "key=value", true)
				.repeatable(true)
				.callback(Poco::Util::OptionCallback<DownloaderApplication>(this, &DownloaderApplication::handleDownloadOption))
		);
		
		// Download rate
		options.addOption(
			Poco::Util::Option("downloadRate", "r", "Download rate in KB/s", true, "rate", true)
				.binding("downloadRate")
		);
		
		// Help
		options.addOption(
			Poco::Util::Option("help", "h", "display help information")
				.required(false)
				.repeatable(false)
				.callback(Poco::Util::OptionCallback<DownloaderApplication>(this, &DownloaderApplication::handleHelp))
		);
		
		std::cout << "B\n";
	}
	
	void DownloaderApplication::handleDownloadOption(const std::string& name, const std::string& value)
	{
		// Parse option
		std::size_t pos = value.find("=");
		if (pos != std::string::npos)
		{
			config().setString("options." + value.substr(0, pos), value.substr(pos + 1));
		}
		else
		{
			throw Poco::Exception("Invalid option: " + value);
		}
	}
	
	std::string DownloaderApplication::dataFolder() const
	{
		return dataFolder_.toString();
	}
	
	std::string DownloaderApplication::description() const
	{
		// Overwrite this function
		
		return "MyVideoCollection downloader";
	}
	
	void DownloaderApplication::handleHelp(const std::string& name, const std::string& value)
	{
		// In help mode
		help_ = true;
		
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
	
	void DownloaderApplication::init()
	{
		// Overwrite this function
	}
	
	void DownloaderApplication::deinit()
	{
		// Overwrite this function
	}
};
