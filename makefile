VPATH = *.c samples
VPATH = *l src
out: tokens.txt

tokens.txt: clang.out 
	./$< < samples/demo.c > $@

clang.out: lex.yy.c
	gcc -o $@ $<

lex.yy.c: scanner.l
	flex $<

clean: 
	rm clang.out lex.yy.c tokens.txt