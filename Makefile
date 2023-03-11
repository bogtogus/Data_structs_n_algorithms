mkpath := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(patsubst %/,%,$(dir $(mkpath)))
hdr := $(current_dir)/include
src := $(current_dir)/src
objects = $(src)/main.o $(src)/functionality.o $(src)/menu.o $(src)/hash.o $(src)/tree.o $(src)/list.o

all: 
	@echo "Building..."
	@cd $(current_dir)/src && $(MAKE) all ohdr=$(hdr)
	@echo "Finishing..."
	@g++ -g $(objects) -I $(hdr) -o main

#clean:
#	@echo
#	@rm -rf $(mktrash)/*.o
