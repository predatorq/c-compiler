VPATH = *.c samples
VPATH = *.lex src
out: tokens.txt

tokens.txt: clang.out 
	./$< < samples/numbers.c > $@

clang.out: lex.yy.c
	gcc -o $@ $<

lex.yy.c: clang.lex
	flex $<

clean: 
	rm clang.out lex.yy.c tokens.txt