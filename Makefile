all: Test1.cpp example.hpp
	g++ Test1.cpp example.hpp -o res

deb: lexer.l
	flex -+ -o lexer.cpp lexer.l
	g++ lexer.cpp parser.hpp -g -o out/lexer

#interpretator: lexer.l parser.y

lex: lexer.l
	flex -+ -o lexer.cpp lexer.l
	g++ lexer.cpp parser.hpp -g -o lexer
	#rm lexer.cpp

symbols: parser.y
	bison parser.y --defines=parser.hpp -L C++
	rm parser.tab.cc

tests: tests/LexerTests.cpp lexer.l parser.y
	flex -+ -o lexer.cpp lexer.l
	g++ tests/LexerTests.cpp lexer.cpp parser.hpp -o out/test
