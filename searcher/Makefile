FLAG=-std=c++11 -lboost_filesystem -lboost_system \
	 -I ../../cppjieba/include -I /home/mmc/workpress/jsoncpp
TAGET= /home/mmc/workpress/qq/lib/libjsoncpp.a
.PHONY:all
all:test libsearcher.so

test:test.cc searcher.hpp searcher.cpp
	g++ test.cc searcher.cpp  -o test $(FLAG) $(TAGET)

libsearcher.so:searcher.hpp searcher.cpp
	g++ searcher.cpp -shared -fPIC -o libsearcher.so $(FLAG) $(TAGET)
