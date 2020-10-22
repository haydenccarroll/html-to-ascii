a.out: parser.o tag.o main.o
	g++ parser.o tag.o main.o

parser.o: parser.cpp parser.hpp tag.hpp
	g++ -c -g parser.cpp

tag.o: tag.cpp tag.hpp
	g++ -c -g tag.cpp

main.o: main.cpp parser.hpp
	g++ -c -g main.cpp