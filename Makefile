# Config
CC = g++
POCO_PATH = $(pwd)/poco

# Poco
POCO_INCLUDES  = -I$(POCO_PATH)/Foundation/include
POCO_INCLUDES += -I$(POCO_PATH)/Net/include
POCO_INCLUDES += -I$(POCO_PATH)/Util/include
POCO_INCLUDES += -I$(POCO_PATH)/XML/include
POCO_LIBS_PATH = $(POCO_PATH)/lib/Linux/x86_64/

# Global
INCS = $(POCO_INCLUDES) -Iinclude
LIBS_PATH = -L$(POCO_LIBS_PATH)
BUILD_LIB_OBJECT = $(CC) $(INCS) -c -o

# Build rules
all: lib server torrent nzb

build:
	mkdir -p build

lib: build
	$(BUILD_LIB_OBJECT) build/lib_Downloader.o source/lib/Downloader.cpp

server: build
	$(CC) $(INCS) $(LIBS_PATH) -o build/myVideoCollection source/server/main.cpp

torrent: build
	$(CC) $(INCS) $(LIBS_PATH) -o build/myVideoCollection-torrent source/torrent/main.cpp

nzb: build
	$(CC) $(INCS) $(LIBS_PATH) -o build/myVideoCollection-nzb source/nzb/main.cpp
