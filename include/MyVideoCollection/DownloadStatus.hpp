#ifndef MyVideoCollection_DownloadStatus__
#define MyVideoCollection_DownloadStatus__

namespace MyVideoCollection
{
	struct DownloadStatus
	{
		std::size_t downloadSpeed; // bytes a second
		double progress; // progress in percentage
		std::size_t size; // loaded size in bytes
		std::size_t total; // total size in bytes
		
		// Init
		DownloadStatus() :
			downloadSpeed(0),
			progress(0.0)
		{}
	};
};

#endif
