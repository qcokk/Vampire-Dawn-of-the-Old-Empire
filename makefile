FLAG = -pedantic-errors -std=c++11

main.o: main.cpp main.h In_game_user_interface.h index_calculator.h check_index.h User_Interface.h opportunity_card.h file_io.h
	g++ $(FLAG) -c $<

file_io.o: file_io.cpp file_io.h User_Interface.h check_index.h In_game_user_interface.h index_calculator.h opportunity_card.h main.h
	g++ $(FLAG) -c $<
	
In_game_user_interface.o: In_game_user_interface.cpp In_game_user_interface.h main.h
	g++ $(FLAG) -c $<

opportunity_card.o: opportunity_card.cpp opportunity_card.h main.h 
	g++ $(FLAG) -c $<

index_calculator.o: index_calculator.cpp index_calculator.h main.h
	g++ $(FLAG) -c $<

check_index.o: check_index.cpp check_index.h
	g++ $(FLAG) -c $<

User_Interface.o: User_Interface.cpp User_Interface.h main.h
	g++ $(FLAG) -c $<

main: main.o file_io.o In_game_user_interface.o index_calculator.o opportunity_card.o check_index.o User_Interface.o
	g++ $(FLAG) $^ -o $@

clean:
	rm -f *.o

.PHONY:
	clean
