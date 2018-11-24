CC=g++
LIBS=-lyaml-cpp -lboost_system -lboost_filesystem -lpthread -lcryptopp
CFLAGS=-Wall -std=c++11 -fexceptions -std=c++11
INC=-I/usr/include -I/usr/lib
OBJECTS=yaml_config.o expression_search.o match_context.o match.o file_matches.o interaction.o match_candidate.o ignore_file.o
BIN=sft
OUTPUTDIR=Release

BINDIR=bin/$(OUTPUTDIR)/$(BIN)
OBJDIR=obj/$(OUTPUTDIR)

.PHONY: debug
debug: OUTPUTDIR=Debug
debug: CFLAGS+= -g -std=c++11
debug: all

.PHONY: test
test: CFLAGS+= -g -std=c++11
test: all
test: OUTPUTDIR=Test
test: LIBS+= -lgtest
test: BIN=test_runner
test: 
		$(CC) $(CFLAGS) $(INC) -o $(BINDIR) test/main.cpp $(addprefix obj/$(OUTPUTDIR)/,$(OBJECTS)) $(LIBS)

all: SRCDIR=src
all: main.o
all: $(OBJECTS)
	$(CC) -o $(BINDIR) $(addprefix obj/$(OUTPUTDIR)/,$^) \
	$(LIBS)

%.o:
		$(CC) $(CFLAGS) $(INC)\
			-c $(subst .o,.cpp,$(addprefix $(SRCDIR)/,$@)) \
			-o $(OBJDIR)/$@
