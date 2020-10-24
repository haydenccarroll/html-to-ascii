a.out: parser.o tag.o main.o tagList.o
	g++ parser.o tag.o main.o tagList.o

parser.o: parser.cpp parser.hpp tag.hpp
	g++ -c -g parser.cpp

tag.o: tag.cpp tag.hpp tagList.hpp
	g++ -c -g tag.cpp

tagList.o: tagList.cpp tagList.hpp
	g++ -c -g tagList.cpp

main.o: main.cpp parser.hpp
	g++ -c -g main.cpp