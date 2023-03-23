mkpath := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(patsubst %/,%,$(dir $(mkpath)))
hdr := $(current_dir)/include
src := $(current_dir)/src
enc = "-finput-charset=UTF-8 -fexec-charset=cp1251"
objects = $(src)/main.o $(src)/functionality.o $(src)/menu.o $(src)/hash.o $(src)/tree.o $(src)/list.o $(src)/sqlite3.o

all: 
	@echo "Building..."
	@cd $(current_dir)/src && $(MAKE) all ohdr=$(hdr) oenc=$(enc)
	@echo "Finishing..."
	@g++ -g $(objects) $(enc) -I $(hdr) -o main

#clean:
#	@echo
#	@rm -rf $(mktrash)/*.o
