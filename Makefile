BASENAME := $(basename $(notdir $(ARGS)))

parser.tab.c parser.tab.h:	parser.y
	@bison -t -d parser.y

lex.yy.c: lexer.l parser.tab.h
	@flex lexer.l

artsy: lex.yy.c parser.tab.c parser.tab.h symbolTable.h symbolTable.c AST.c AST.h semantic.c semantic.h helper.h helper.c ircode.c ircode.h driver.c webgen.c webgen.h
	@rm -f ./in/$(ARGS).wasm
	# Enable this command if any modifications are made to the Artsy compiler to recompile the driver
	# gcc -w -o driver parser.tab.c lex.yy.c semantic.c ircode.c driver.c AST.c symbolTable.c webgen.c
	@./driver "$(ARGS)"
	@wat2wasm ./in/$(BASENAME)_WATcode.wat -o ./in/result.wasm
	@rm -f ./in/$(BASENAME)_IRcode.ir ./in/$(BASENAME)_IRcodeOptimized.ir ./in/$(BASENAME)_MAINcode.wat ./in/$(BASENAME)_LOCALcode.wat ./in/$(BASENAME)_VARScode.wat ./in/$(BASENAME)_WATcode.wat