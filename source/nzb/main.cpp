#include <MyVideoCollection/DownloaderApplication.hpp>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Process.h>
#include <Poco/Pipe.h>
#include <Poco/PipeStream.h>
#include <Poco/StreamCopier.h>
#include <Poco/NumberFormatter.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/RegularExpression.h>
#include <Poco/NumberParser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Dynamic/Struct.h>
#include <sstream>
#include <algorithm>
#include <MyVideoCollection/JSON.hpp>

class NZBApp : public MyVideoCollection::DownloaderApplication
{
	protected:
		void initDownload()
		{
			// Find server port
			for (port_ = 6800; port_ < 7800; ++port_)
			{
				try
				{
					// Can bind to IP?
					Poco::Net::ServerSocket socket(Poco::Net::SocketAddress("127.0.0.1", port_));
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
			arguments.push_back("-o"); arguments.push_back("ServerIp=0.0.0.0"); // 127.0.0.1");
			arguments.push_back("-o"); arguments.push_back("ServerPort=" + Poco::NumberFormatter::format(port_));
			arguments.push_back("-o"); arguments.push_back("OutputMode=loggable");
			arguments.push_back("-o"); arguments.push_back("DownloadRate=" + config().getString("downloadRate", "0"));
			arguments.push_back("-o"); arguments.push_back("Server1.Level=0");
			arguments.push_back("-o"); arguments.push_back("Server1.Host=" + config().getString("options.server", "usenet.server"));
			arguments.push_back("-o"); arguments.push_back("Server1.Port=" + config().getString("options.port", "119"));
			arguments.push_back("-o"); arguments.push_back("Server1.Username=" + config().getString("options.username", "username"));
			arguments.push_back("-o"); arguments.push_back("Server1.Password=" + config().getString("options.password", ""));
			arguments.push_back("-o"); arguments.push_back("Server1.Encryption=" + config().getString("options.encryption", "no"));
			arguments.push_back("-o"); arguments.push_back("Server1.Connections=" + config().getString("options.connections", "1"));
			arguments.push_back("-s");
			
			// Start download server
			Poco::Pipe p1, p2;
			Poco::Process::launch(config().getString("options.nzbgetBin", "/usr/bin/nzbget"), arguments, 0, &p1, &p2);
			
			// Add download?
			if (config().getString("download", "-") != "-")
			{
				// Start download
				Poco::Process::Args arguments; arguments.push_back("-A"); arguments.push_back(config().getString("download"));
				sendCommand(arguments);
			}
		}
		
		inline bool sendCommand(const Poco::Process::Args & extraArguments)
		{
			std::string str;
			return sendCommand(extraArguments, str);
		}
		
		bool sendCommand(const Poco::Process::Args & extraArguments, std::string & output)
		{
			// Build arguments
			Poco::Process::Args arguments;
			arguments.push_back("-n");
			arguments.push_back("-o"); arguments.push_back("ServerIp=127.0.0.1");
			arguments.push_back("-o"); arguments.push_back("ServerPort=" + Poco::NumberFormatter::format(port_));
			arguments.push_back("-o"); arguments.push_back("OutputMode=loggable");
			for (Poco::Process::Args::const_iterator it = extraArguments.begin(); it != extraArguments.end(); ++it)
			{
				arguments.push_back(*it);
			}
			
			// Run
			Poco::Pipe out, err;
			if (Poco::Process::launch(config().getString("options.nzbgetBin", "/usr/bin/nzbget"), arguments, 0, &out, &err).wait() != 0)
			{
				// Read error
				Poco::PipeInputStream stream(err);
				Poco::StreamCopier::copyToString(stream, output);
				
				return false;
			}
			else
			{
				// Read out
				Poco::PipeInputStream stream(out);
				Poco::StreamCopier::copyToString(stream, output);
				
				return true;
			}
		}
		
		inline bool sendCommandJSON(const std::string & method, const std::vector<Poco::Dynamic::Var> & params = std::vector<Poco::Dynamic::Var>())
		{
			Poco::Dynamic::Var output;
			return sendCommandJSON(method, output, params);
		}
		
		bool sendCommandJSON(const std::string & method, Poco::Dynamic::Var & output, const std::vector<Poco::Dynamic::Var> & params = std::vector<Poco::Dynamic::Var>())
		{
			// Create request
			Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, "/jsonrpc");
			
			// Authorization
			request.set("Authorization", "Basic bnpiZ2V0OnRlZ2J6bg==");
			
			// Create body
			Poco::Dynamic::Var body = Poco::Dynamic::Struct<std::string>();
			body["method"] = method;
			body["id"] = "sendCommandJSON";
			std::vector<Poco::Dynamic::Var> params_;
			params_.push_back("callback");
			for (std::vector<Poco::Dynamic::Var>::const_iterator it = params.begin(); it != params.end(); ++it)
			{
				params_.push_back(*it);
			}
			body["params"] = params_;
			std::string body_ = MyVideoCollection::JSON::stringify(body);
			request.setContentLength(body_.length());
			
			// Send request
			Poco::Net::HTTPClientSession session("127.0.0.1", port_);
			session.sendRequest(request) << body_ << std::flush;
			
			// Receive response
			Poco::Net::HTTPResponse response;
			std::istream & responseStream = session.receiveResponse(response);
			std::size_t bytes = response.getContentLength();
			std::stringstream response_;
			while (bytes > 0 && responseStream.good())
			{
				char buf[4096];
				responseStream.read(buf, std::min(bytes, (std::size_t)4096));
				std::size_t gcount = responseStream.gcount();
				bytes -= gcount;
				response_ << std::string(buf, gcount);
			}
			
			// Parse JSON
			output = MyVideoCollection::JSON::parse(response_);
			
			// Result?
			if (!output.isStruct())
			{
				output.empty();
				return false;
			}
			output = output["result"];
			
			return true;
		}
		
		void deinitDownload()
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
		
		static Poco::Int64 int64PartsGlue(Poco::Int64 low, Poco::Int64 high)
		{
			return low + (high * (Poco::Int64)4294967296);
		}
		
		void updateStatus(MyVideoCollection::DownloadStatus & status)
		{
			// Get status
			Poco::Dynamic::Var result, result2;
			sendCommandJSON("status", result);
			sendCommandJSON("listgroups", result2);
			if (!result.isStruct() || !result2.isArray())
			{
				// Error
				status.status = MyVideoCollection::DownloadStatus::ERROR;
				
				return;
			}
			
			// Vars
			status.downloadSpeed = result["DownloadRate"];
			if (result2.extract< std::vector<Poco::Dynamic::Var> >().size() > 0)
			{
				status.total = int64PartsGlue(result2[0]["FileSizeLo"], result2[0]["FileSizeHi"]);
				status.size = status.total - int64PartsGlue(result2[0]["RemainingSizeLo"], result2[0]["RemainingSizeHi"]);
			}
			if (status.total == 0)
			{
				status.progress = 100.0;
				status.remainingTime = 0;
			}
			else
			{
				status.progress = ((double)status.size / (double)status.total) * 100.0;
				status.remainingTime = (status.total * result["DownloadTimeSec"]) / status.size;
			}
			
			// Status
			if (result["ServerPaused"])
			{
				status.status = MyVideoCollection::DownloadStatus::PAUSED;
			}
			else
			{
				status.status = MyVideoCollection::DownloadStatus::BUSY;
			}
			if (result["ServerStandBy"])
			{
				status.size = status.total;
				status.progress = 100.0;
				status.status = MyVideoCollection::DownloadStatus::FINISHED;
				if (result["ParJobCount"] > 0)
				{
					status.status = MyVideoCollection::DownloadStatus::PROCESSING;
				}
			}
		}
		
		std::size_t port_;
};

POCO_APP_MAIN(NZBApp)
