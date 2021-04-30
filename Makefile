all:1 2 3 main libmake

1: home/1_arithmetic.cpp
	mkdir -p bin
	g++ home/1_arithmetic.cpp -o bin/1_arithmetic

2: home/2_assign.cpp
	mkdir -p bin
	g++ home/2_assign.cpp -o bin/2_assign

3: home/3_logic.cpp
	mkdir -p bin	
	g++ home/3_logic.cpp -o bin/3_logic

main: bin/const.o bin/utility.o bin/lexem.o bin/lexical.o bin/semantic.o bin/syntax.o
	g++ src/main.cpp bin/const.o bin/utility.o bin/lexem.o bin/lexical.o bin/semantic.o bin/syntax.o -I./include -o main -fsanitize=address,leak

bin/const.o: src/const.cpp
	mkdir -p bin
	g++ -c src/const.cpp -I./include -o bin/const.o

bin/utility.o: src/utility.cpp
	g++ -c src/utility.cpp -I./include -o bin/utility.o

bin/lexem.o: src/lexem.cpp
	g++ -c src/lexem.cpp -I./include -o bin/lexem.o

bin/lexical.o: src/lexical.cpp
	g++ -c src/lexical.cpp -I./include -o bin/lexical.o

bin/semantic.o: src/semantic.cpp
	g++ -c src/semantic.cpp -I./include -o bin/semantic.o

bin/syntax.o: src/syntax.cpp
	g++ -c src/syntax.cpp -I./include -o bin/syntax.o

clean: 
	rm -r bin
	rm -r lib
	rm main
libmake: lib/libconst.so lib/libutility.so lib/liblexem.so lib/liblexical.so lib/libsemantic.so lib/libsyntax.so
	g++ src/main.cpp -I./include -L./lib -lconst -lutility -llexem -llexical -lsemantic -lsyntax -o main

lib/libconst.so: src/const.cpp
	mkdir -p lib
	g++ src/const.cpp -I./include -fpic -shared -o lib/libconst.so

lib/libutility.so: src/utility.cpp
	g++ src/utility.cpp -I./include -fpic -shared -o lib/libutility.so

lib/liblexem.so: src/lexem.cpp
	g++ src/lexem.cpp -I./include -fpic -shared -o lib/liblexem.so

lib/liblexical.so: src/lexical.cpp
	g++ src/lexical.cpp -I./include -fpic -shared -o lib/liblexical.so

lib/libsemantic.so: src/semantic.cpp
	g++ src/semantic.cpp -I./include -fpic -shared -o lib/libsemantic.so

lib/libsyntax.so: src/syntax.cpp
	g++ src/syntax.cpp -I./include -fpic -shared -o lib/libsyntax.so

