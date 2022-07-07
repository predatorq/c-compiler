TESTFILE = samples/demo.c
SCANNER  = src/scanner.l
PARSER   = src/parser.y
INC1      = src/macro.inc
INC2      = samples/demo.inc

CC       = gcc
FRONTOBJ = lex.yy.o y.tab.o
TESTOUT  = samples/demo.asm
FRONTEXE = tcc-front
OUTFILES = lex.yy.c y.tab.c y.tab.h y.output $(FRONTOBJ) $(TESTOUT) $(FRONTEXE) $(INC2) check.asm demo

demo: $(TESTOUT)
	nasm -f elf32 -P"$(INC1)" -P"$(INC2)" -o demo.o $(TESTOUT)
	ld -m elf_i386 -o $@ demo.o
	./demo

check: $(TESTOUT)
	nasm -P"$(INC1)" -P"$(INC2)" -e $(TESTOUT) -o check.asm 

$(TESTOUT): $(TESTFILE) $(FRONTEXE)
	./$(FRONTEXE) $< > $@

clean:
	rm -f *.o $(OUTFILES)

$(FRONTEXE): $(FRONTOBJ)
	$(CC) -w -o $(FRONTEXE) $(FRONTOBJ) 
	chmod u+x $(FRONTEXE) 

lex.yy.c: $(SCANNER) y.tab.c
	flex $<

y.tab.c: $(PARSER)
	bison -vdty $<