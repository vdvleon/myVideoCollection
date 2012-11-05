#ifndef MyVideoCollection_DownloadStatus__
#define MyVideoCollection_DownloadStatus__

#include <iostream>

namespace MyVideoCollection
{
	struct DownloadStatus
	{
		// Types
		enum Status
		{
			STARTING = 0,
			ERROR = 1,
			BUSY = 2,
			PAUSED = 3,
			FINISHED = 4
		};
		
		// Vars
		Status status;
		std::size_t downloadSpeed; // bytes a second
		double progress; // progress in percentage
		std::size_t size; // loaded size in bytes
		std::size_t total; // total size in bytes
		
		// Functions
		DownloadStatus();
		void write(std::ostream & out);
		void read(std::istream & in);
	};
};

#endif
