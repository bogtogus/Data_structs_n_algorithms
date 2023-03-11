objects = main.o functionality.o menu.o hash.o tree.o list.o

all: main

main: $(objects)
	
#	@make -f Makefile clean

main.o: main.cpp $(ohdr)/functionality.h $(ohdr)/main.h $(ohdr)/menu.h $(ohdr)/hash.h $(ohdr)/tree.h $(ohdr)/list.h
	@echo "<...> main.o"
	@g++ -c main.cpp -g -I $(ohdr)

functionality.o: functionality.cpp
	@echo "<...> functionality.o"
	@g++ -c functionality.cpp -g -I $(ohdr) 

menu.o: menu.cpp $(ohdr)/functionality.h $(ohdr)/menu.h $(ohdr)/hash.h $(ohdr)/tree.h $(ohdr)/list.h
	@echo "<...> menu.o"
	@g++ -c menu.cpp -g -I $(ohdr) 

hash.o: hash.cpp $(ohdr)/hash.h
	@echo "<...> hash.o"
	@g++ -c hash.cpp -g -I $(ohdr) 

tree.o: tree.cpp $(ohdr)/tree.h
	@echo "<...> tree.o"
	@g++ -c tree.cpp -g -I $(ohdr) 

list.o: list.cpp $(ohdr)/list.h $(ohdr)/functionality.h
	@echo "<...> list.o"
	@g++ -c list.cpp -g -I $(ohdr) 

#clean:
#	@echo
#	@rm -rf $(mktrash)/*.o
