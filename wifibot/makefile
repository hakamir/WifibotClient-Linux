prog: main.o WifibotClient.o
	gcc -o prog main.o WifibotClient.o -lncurses

main.o : main.cpp
	gcc -c -Wall main.cpp

WifibotClient.o : WifibotClient.cpp
	gcc -c -Wall WifibotClient.cpp
