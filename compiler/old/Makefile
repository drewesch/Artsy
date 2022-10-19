all: clean artsy

lexer: lexer_standalone.l
	flex lexer_standalone.l
	gcc -o lexer_standalone lex.yy.c
	./lexer_standalone testProg.artsy

parser.tab.c parser.tab.h:	parser.y
	bison -t -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser: lex.yy.c parser.tab.c parser.tab.h symbolTable.h symbolTable.c AST.h semantic.c semantic.h ircode.c ircode.h codegen.c codegen.h
	gcc -o parser parser.tab.c lex.yy.c semantic.c symbolTable.c ircode.c codegen.c
	./parser testProg.artsy

ircode: lex.yy.c parser.tab.c parser.tab.h symbolTable.h symbolTable.c AST.c AST.h semantic.c semantic.h ircode.c ircode.h driver.c
	gcc -o driver parser.tab.c lex.yy.c semantic.c ircode.c driver.c AST.c symbolTable.c
	./driver testProg.artsy


artsy: lex.yy.c parser.tab.c parser.tab.h symbolTable.h symbolTable.c AST.c AST.h semantic.c semantic.h ircode.c ircode.h driver.c codegen.c codegen.h
	gcc -o driver parser.tab.c lex.yy.c semantic.c ircode.c driver.c AST.c symbolTable.c codegen.c
	./driver testProg.artsy

clean:
	rm -f parser lexer parser.tab.c lex.yy.c parser.tab.h parser.output
	rm -f parser lexer parser.gv parser.html parser.ps parser.xml lexer_standalone
	rm -f IRcode.ir IRcodeOptimized.ir MIPScode.asm
	ls -l