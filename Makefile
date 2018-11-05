CC=g++
LIBS=-lyaml-cpp -lboost_system -lboost_filesystem
CFLAGS=-Wall -std=c++11 -fexceptions -std=c++11
INC=-I/usr/include -I/usr/lib
OBJECTS=main.o yaml_config.o expression_search.o match_context.o match.o file_matches.o interaction.o match_candidate.o
BIN=sft
OUTPUTDIR=Release

ifeq ($(mode),debug)
	OUTPUTDIR=Debug
	CFLAGS=-Wall -std=c++11 -fexceptions -std=c++11 -g -std=c++11
endif

BINDIR=bin/$(OUTPUTDIR)/$(BIN)
OBJDIR=obj/$(OUTPUTDIR)

all: $(OBJECTS)
		$(CC)  -o $(BINDIR) $(addprefix obj/$(OUTPUTDIR)/,$^)\
		$(LIBS)

%.o:
		$(CC) $(CFLAGS) $(INC)\
			-c $(subst .o,.cpp,$@) \
			-o $(OBJDIR)/$@
