# FILE_PATH = ../test-programs/basic.artsy

%:
    @:

FILE_PATH = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`

all: clean lex.yy.c parser.tab.c parser.tab.h symbolTable.h symbolTable.c AST.c AST.h semantic.c semantic.h ircode.c ircode.h driver.c webgen.c webgen.h
	gcc -w -o driver parser.tab.c lex.yy.c semantic.c ircode.c driver.c AST.c symbolTable.c webgen.c
	./driver $(FILE_PATH)
	rm -f MAINcode.wat LOCALcode.wat VARScode.wat
	wat2wasm WATcode.wat -o WASMcode.wasm

wasm:
	wat2wasm WATcode.wat -o WASMcode.wasm

parser.tab.c parser.tab.h:	parser.y
	bison -t -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

artsy: lex.yy.c parser.tab.c parser.tab.h symbolTable.h symbolTable.c AST.c AST.h semantic.c semantic.h ircode.c ircode.h driver.c webgen.c webgen.h
	gcc -w -o driver parser.tab.c lex.yy.c semantic.c ircode.c driver.c AST.c symbolTable.c webgen.c
	./driver $(FILE_PATH)
	rm -f MAINcode.wat LOCALcode.wat VARScode.wat
	wat2wasm WATcode.wat -o WASMcode.wasm

clean:
	rm -f parser lexer parser.tab.c lex.yy.c parser.tab.h parser.output
	rm -f parser lexer parser.gv parser.html parser.ps parser.xml lexer_standalone
	rm -f IRcode.ir IRcodeOptimized.ir WATcode.wat WASMcode.wasm
	ls -l