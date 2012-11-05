# Config
CC = g++
POCO_PATH = poco

# Poco
POCO_INCLUDES  = -I$(POCO_PATH)/Foundation/include
POCO_INCLUDES += -I$(POCO_PATH)/Net/include
POCO_INCLUDES += -I$(POCO_PATH)/Util/include
POCO_INCLUDES += -I$(POCO_PATH)/XML/include
POCO_LIBS_PATH = $(POCO_PATH)/lib/Linux/x86_64/

# Global
INCS = $(POCO_INCLUDES) -Iinclude
LIBS_PATH = -L$(POCO_LIBS_PATH)
BUILD_LIB_OBJECT = $(CC) $(INCS) -fPIC -c -o

# Build rules
all: lib server torrent nzb

build:
	mkdir -p build

lib: build
	$(BUILD_LIB_OBJECT) build/lib_DownloaderApplication.o source/lib/DownloaderApplication.cpp
	$(BUILD_LIB_OBJECT) build/lib_DownloadStatus.o source/lib/DownloadStatus.cpp
	$(BUILD_LIB_OBJECT) build/lib_Download.o source/lib/Download.cpp
	$(CC) -shared -o build/libMyVideoCollection.so build/lib_*.o

server: build
	$(CC) $(INCS) $(LIBS_PATH) -o build/MyVideoCollection source/server/main.cpp -lMyVideoCollection -lPocoFoundation -lPocoUtil -lPocoNet

torrent: build
	$(CC) $(INCS) $(LIBS_PATH) -o build/MyVideoCollection-torrent source/torrent/main.cpp

nzb: build
	$(CC) $(INCS) $(LIBS_PATH) -o build/MyVideoCollection-nzb source/nzb/main.cpp
