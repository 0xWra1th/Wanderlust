make:
	g++ -g -c *.cpp
	g++ *.o -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -o Wanderlust
	rm *.o

run: make
	./Wanderlust

debug: make
	gdb Wanderlust

clean:
	rm Wanderlust *.o *.gch
