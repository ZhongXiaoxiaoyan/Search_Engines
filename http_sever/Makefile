
FLAG=-I ../../cppjieba/include

http_server:http_server.cc  ../searcher/libsearcher.so
	g++ http_server.cc ../searcher/libsearcher.so -o http_server -std=c++11 -lpthread $(FLAG)
