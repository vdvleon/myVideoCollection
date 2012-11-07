#include <MyVideoCollection/DownloadStatus.hpp>
#include <Poco/RegularExpression.h>
#include <Poco/NumberParser.h>

namespace MyVideoCollection
{
	DownloadStatus::DownloadStatus() :
		status(STARTING),
		downloadSpeed(0),
		progress(0.0),
		size(0),
		total(0),
		remainingTime(0)
	{}
	
	void DownloadStatus::write(std::ostream & out)
	{
		out.precision(2);
		out << (short)status << " " << downloadSpeed << " " << std::showpoint << std::fixed << progress << " " << size << " " << total << " " << remainingTime << std::endl << std::flush;
	}
	
	void DownloadStatus::read(std::istream & in)
	{
		// Read line
		std::string line;
		std::getline(in, line);
		
		// Parse status
		Poco::RegularExpression regex("^(\\d+) (\\d+) (\\d+\\.\\d+) (\\d+) (\\d+) (\\d+)$");
		Poco::RegularExpression::MatchVec m;
		regex.match(line, 0, m);
		if (m.size() == 7)
		{
			// Status
			switch (Poco::NumberParser::parse(line.substr(m[1].offset, m[1].length)))
			{
				default:
				case STARTING:	status = STARTING; break;
				case ERROR:		status = ERROR; break;
				case BUSY:		status = BUSY; break;
				case PAUSED:	status = PAUSED; break;
				case FINISHED:	status = FINISHED; break;
			}
			
			// Download speed
			downloadSpeed = Poco::NumberParser::parseUnsigned64(line.substr(m[2].offset, m[2].length));
			
			// Progress
			progress = Poco::NumberParser::parseFloat(line.substr(m[3].offset, m[3].length));
			
			// Size
			size = Poco::NumberParser::parse64(line.substr(m[4].offset, m[4].length));
			
			// Total
			total = Poco::NumberParser::parse64(line.substr(m[5].offset, m[5].length));
			
			// Total
			remainingTime = Poco::NumberParser::parseUnsigned64(line.substr(m[6].offset, m[6].length));
		}
	}
};
