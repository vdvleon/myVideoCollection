# Config
CC = g++
POCO_PATH = poco

# Poco
POCO_INCLUDES  = -I$(POCO_PATH)/Foundation/include
POCO_INCLUDES += -I$(POCO_PATH)/Net/include
POCO_INCLUDES += -I$(POCO_PATH)/Util/include
POCO_INCLUDES += -I$(POCO_PATH)/XML/include
POCO_INCLUDES += -I$(POCO_PATH)/JSON/include
POCO_INCLUDES += -I$(POCO_PATH)/Crypto/include
POCO_LIBS_PATH = $(POCO_PATH)/lib/Linux/x86_64/

# Global
INCS = $(POCO_INCLUDES) -Iinclude
LIBS_PATH = -L$(POCO_LIBS_PATH) -Lbuild
BUILD_LIB_OBJECT = $(CC) $(INCS) -fPIC -c -o

# Build rules
all: lib server torrent nzb

build:
	mkdir -p build

lib: build
	$(BUILD_LIB_OBJECT) build/lib_DownloaderApplication.o source/lib/DownloaderApplication.cpp
	$(BUILD_LIB_OBJECT) build/lib_DownloadStatus.o source/lib/DownloadStatus.cpp
	$(BUILD_LIB_OBJECT) build/lib_Download.o source/lib/Download.cpp
	$(BUILD_LIB_OBJECT) build/lib_JSON.o source/lib/JSON.cpp
	$(CC) -shared -o build/libMyVideoCollection.so build/lib_*.o

server: build
	$(CC) $(INCS) $(LIBS_PATH) -o build/MyVideoCollection source/server/main.cpp -lMyVideoCollection -lPocoFoundation -lPocoUtil -lPocoNet -lPocoXML -lPocoCrypto -lPocoJSON

torrent: build
	$(CC) $(INCS) $(LIBS_PATH) -o build/MyVideoCollection-torrent source/torrent/main.cpp -lMyVideoCollection -lPocoFoundation -lPocoUtil -lPocoNet -lPocoXML -lPocoCrypto -lPocoJSON

nzb: build
	$(CC) $(INCS) $(LIBS_PATH) -o build/MyVideoCollection-nzb source/nzb/main.cpp -lMyVideoCollection -lPocoFoundation -lPocoUtil -lPocoNet -lPocoXML -lPocoCrypto -lPocoJSON

nzb-test1:
	rm -R -f data/test1
	LD_LIBRARY_PATH=:poco/lib/Linux/x86_64:build valgrind ./build/MyVideoCollection-nzb -itest1 -r600 -oserver=newsreader100.eweka.nl -ousername=538209 -opassword=4xqn6w -dtest1.nzb

nzb-test2:
	rm -R -f data/test2
	LD_LIBRARY_PATH=:poco/lib/Linux/x86_64:build valgrind ./build/MyVideoCollection-nzb -itest2 -r600 -oserver=newsreader100.eweka.nl -ousername=538209 -opassword=4xqn6w -dtest2.nzb

nzb-test3:
	rm -R -f data/test3
	LD_LIBRARY_PATH=:poco/lib/Linux/x86_64:build valgrind ./build/MyVideoCollection-nzb -itest3 -r600 -oserver=newsreader100.eweka.nl -ousername=538209 -opassword=4xqn6w -dtest3.nzb
