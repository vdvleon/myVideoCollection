#include <MyVideoCollection/DownloadStatus.hpp>

namespace MyVideoCollection
{
	DownloadStatus::DownloadStatus() :
		status(STARTING),
		downloadSpeed(0),
		progress(0.0),
		size(0),
		total(0)
	{}
	
	void DownloadStatus::write(std::ostream & out)
	{
		out << (short)status << downloadSpeed << progress << size << total << std::endl;
	}
	
	void DownloadStatus::read(std::istream & in)
	{
		short status_;
		in >> status_ >> downloadSpeed >> progress >> size >> total;
		switch (status_)
		{
			default:
			case STARTING:	status = STARTING; break;
			case ERROR:		status = ERROR; break;
			case BUSY:		status = BUSY; break;
			case PAUSED:	status = PAUSED; break;
			case FINISHED:	status = FINISHED; break;
		}
	}
};
