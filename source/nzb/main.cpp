#include <MyVideoCollection/DownloaderApplication.hpp>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Process.h>
#include <Poco/NumberFormatter.h>

class Application : public MyVideoCollection::DownloaderApplication
{
	protected:
		void init()
		{
			// Find server port
			std::size_t port = 6800;
			for (; port < 7800; ++port)
			{
				try
				{
					// Can bind to IP?
					Poco::Net::ServerSocket socket(Poco::Net::SocketAddress("127.0.0.1", port));
					socket.close();
					
					// Stop, found port
					break;
				}
				catch (...)
				{}
			}
			
			// Build arguments
			Poco::Process::Args arguments;
			arguments.push_back("-n");
			arguments.push_back("-o"); arguments.push_back("ParCheck=yes");
			arguments.push_back("-o"); arguments.push_back("ParRepair=yes");
			arguments.push_back("-o"); arguments.push_back("LockFile=" + dataFolder() + "nzbget.lock");
			arguments.push_back("-o"); arguments.push_back("LogFile=" + dataFolder() + "nzbget.log");
			arguments.push_back("-o"); arguments.push_back("NzbDir=" + dataFolder() + "nzb");
			arguments.push_back("-o"); arguments.push_back("QueueDir=" + dataFolder() + "queue");
			arguments.push_back("-o"); arguments.push_back("DestDir=" + dataFolder() + "done");
			arguments.push_back("-o"); arguments.push_back("TempDir=" + dataFolder() + "temp");
			arguments.push_back("-o"); arguments.push_back("ServerIp=127.0.0.1");
			arguments.push_back("-o"); arguments.push_back("ServerPort=" + Poco::NumberFormatter::format(port));
			arguments.push_back("-o"); arguments.push_back("RenameIMG=yes");
			arguments.push_back("-o"); arguments.push_back("OutputMode=loggable");
			arguments.push_back("-o"); arguments.push_back("Server1.Level=0");
			arguments.push_back("-o"); arguments.push_back("Server1.Host=" + config().getString("options.server", "server"));
			arguments.push_back("-o"); arguments.push_back("Server1.Port=" + config().getString("options.port", "119"));
			arguments.push_back("-o"); arguments.push_back("Server1.Username=" + config().getString("options.username", "username"));
			arguments.push_back("-o"); arguments.push_back("Server1.Password=" + config().getString("options.password", ""));
			arguments.push_back("-o"); arguments.push_back("Server1.Encryption=" + config().getString("options.encryption", "no"));
			arguments.push_back("-o"); arguments.push_back("Server1.Connections=" + config().getString("options.connections", "1"));
			arguments.push_back("-s");
			
			// Start download server
			Poco::Process::launch(config().getString("options.nzbgetBin", "/usr/bin/nzbget"), arguments, 0, 0, 0);
			
			// Add download?
			if (config().getString("download", "-") != "-")
			{
				// Build arguments
				Poco::Process::Args arguments;
				arguments.push_back("-n");
				arguments.push_back("-o"); arguments.push_back("ServerIp=127.0.0.1");
				arguments.push_back("-o"); arguments.push_back("ServerPort=" + Poco::NumberFormatter::format(port));				
				arguments.push_back("-o"); arguments.push_back("OutputMode=loggable");
				arguments.push_back("-A"); arguments.push_back(config().getString("download"));
				
				// Run
				Poco::Process::launch(config().getString("options.nzbgetBin", "/usr/bin/nzbget"), arguments, 0, 0, 0);
			}
		}
		
		void deinit()
		{
			// TODO
		}
		
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

		void updateStatus(MyVideoCollection::DownloadStatus & status)
		{
			// TODO
		}
};

POCO_APP_MAIN(Application)
