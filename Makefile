CC=g++

release: main-release.o yaml_config-release.o expression_search-release.o
		$(CC)  -o bin/Release/sft obj/Release/main.o obj/Release/yaml_config.o obj/Release/expression_search.o\
			-lyaml-cpp \
			-lboost_system \
			-lboost_filesystem

main-release.o:
		$(CC) -Wall -std=c++11 -fexceptions -std=c++11 -g -std=c++11 \
			-I/usr/include \
			-I/usr/lib \
			-c main.cpp \
			-o obj/Release/main.o

yaml_config-release.o:
		$(CC) -Wall -std=c++11 -fexceptions -std=c++11 -g -std=c++11 \
			-I/usr/include \
			-I/usr/lib \
			-c yaml_config.cpp \
			-o obj/Release/yaml_config.o

expression_search-release.o:
		$(CC) -Wall -std=c++11 -fexceptions -std=c++11 -g -std=c++11 \
			-I/usr/include \
			-I/usr/lib \
			-c expression_search.cpp \
			-o obj/Release/expression_search.o

debug: main-debug.o yaml_config-debug.o expression_search-debug.o
		$(CC)  -o bin/Debug/sft obj/Debug/main.o obj/Debug/yaml_config.o  obj/Debug/expression_search.o\
			-lyaml-cpp \
			-lboost_system \
			-lboost_filesystem

main-debug.o:
		$(CC) -Wall -std=c++11 -fexceptions -std=c++11 -g -std=c++11 \
			-I/usr/include \
			-I/usr/lib \
			-c main.cpp \
			-o obj/Debug/main.o

yaml_config-debug.o:
		$(CC) -Wall -std=c++11 -fexceptions -std=c++11 -g -std=c++11 \
			-I/usr/include \
			-I/usr/lib \
			-c yaml_config.cpp \
			-o obj/Debug/yaml_config.o

expression_search-debug.o:
		$(CC) -Wall -std=c++11 -fexceptions -std=c++11 -g -std=c++11 \
			-I/usr/include \
			-I/usr/lib \
			-c expression_search.cpp \
			-o obj/Debug/expression_search.o
