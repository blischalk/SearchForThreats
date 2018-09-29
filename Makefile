CC=g++
LIBS=-lyaml-cpp -lboost_system -lboost_filesystem
CFLAGS=-Wall -std=c++11 -fexceptions -std=c++11 -g -std=c++11
INC=-I/usr/include -I/usr/lib
OBJECTS=main.o yaml_config.o expression_search.o

release: $(OBJECTS)
		$(CC)  -o bin/Release/sft $(addprefix obj/Release/, $(OBJECTS))\
		$(LIBS)

main.o:
		$(CC) $(CFLAGS) $(INC)\
			-c main.cpp \
			-o obj/Release/main.o

yaml_config.o:
		$(CC) $(CFLAGS) $(INC)\
			-c yaml_config.cpp \
			-o obj/Release/yaml_config.o

expression_search.o:
		$(CC) $(CFLAGS) $(INC)\
			-c expression_search.cpp \
			-o obj/Release/expression_search.o

debug: main-debug.o yaml_config-debug.o expression_search-debug.o
		$(CC)  -o bin/Debug/sft $(addprefix obj/Debug/, $(OBJECTS))\
		$(LIBS)

main-debug.o:
		$(CC) $(CFLAGS) $(INC)\
			-c main.cpp \
			-o obj/Debug/main.o

yaml_config-debug.o:
		$(CC) $(CFLAGS) $(INC)\
			-c yaml_config.cpp \
			-o obj/Debug/yaml_config.o

expression_search-debug.o:
		$(CC) $(CFLAGS) $(INC)\
			-c expression_search.cpp \
			-o obj/Debug/expression_search.o
