#include <MyVideoCollection/DownloaderApplication.hpp>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/File.h>
#include <iostream>

namespace MyVideoCollection
{
	DownloaderApplication::DownloaderApplication() :
		Poco::Util::Application(),
		help_(false),
		progressTimer_(10000, 10000)
	{
		// Start timer
		progressTimer_.start(Poco::TimerCallback<DownloaderApplication>(*this, &DownloaderApplication::onProgressTimer));
	}
	
	void DownloaderApplication::onProgressTimer(Poco::Timer & timer)
	{
		// Update status
		updateStatus(status_);
		
		// Write status
		status_.write(std::cout);
	}
	
	int DownloaderApplication::main(const std::vector<std::string> & args)
	{
		Poco::Util::Application::main(args);
		
		// Stop because of help?
		if (help_)
		{
			// Show help
			Poco::Util::HelpFormatter help(options());
			help.setCommand(commandName());
			help.setUsage("(-i<id> | --downloadID<id>) OPTIONS");
			help.setWidth(100);
			help.setHeader("\n" + description() + "\n\nOPTIONS:");
			help.format(std::cout);
			
			return EXIT_USAGE;
		}
		
		// Prepare data folder
		dataFolder_ = "data/";
		if (!findFile(dataFolder_))
		{
			throw Poco::Exception("Can not find data folder");
		}
		dataFolder_.append(config().getString("downloadID") + "/");
		if (Poco::File(dataFolder_).exists())
		{
			if (config().getString("download", "-") != "-")
			{
				throw Poco::Exception("Can not append a download '" + config().getString("download") + "' to an already initialized downloader");
			}
		}
		else
		{
			Poco::File(dataFolder_).createDirectory();
		}
		
		// Init
		initDownload();
		
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
		deinitDownload();
		
		return EXIT_OK;
	}
	
	void DownloaderApplication::defineOptions(Poco::Util::OptionSet & options)
	{
		Poco::Util::Application::defineOptions(options);
		
		// Download
		options.addOption(
			Poco::Util::Option("download", "d", "Download link (e.g. .nzb, .torrent, http://)", false, "<download>", true)
				.binding("download")
		);
		
		// ID
		options.addOption(
			Poco::Util::Option("downloadID", "i", "Download ID", true, "<id>", true)
				.binding("downloadID")
		);
		
		// Download option
		options.addOption(
			Poco::Util::Option("downloadOption", "o", "Download option (e.g. server=1.2.3.4)", false, "<key>=<value>", true)
				.repeatable(true)
				.callback(Poco::Util::OptionCallback<DownloaderApplication>(this, &DownloaderApplication::handleDownloadOption))
		);
		
		// Download rate
		options.addOption(
			Poco::Util::Option("downloadRate", "r", "Download rate in KB/s", false, "<rate>", true)
				.binding("downloadRate")
		);
		
		// Help
		options.addOption(
			Poco::Util::Option("help", "h", "display help information")
				.required(false)
				.repeatable(false)
				.callback(Poco::Util::OptionCallback<DownloaderApplication>(this, &DownloaderApplication::handleHelp))
		);
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
	
	void DownloaderApplication::initDownload()
	{
		// Overwrite this function
	}
	
	void DownloaderApplication::deinitDownload()
	{
		// Overwrite this function
	}
};
