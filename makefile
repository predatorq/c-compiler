VPATH = *.c samples
VPATH = *.lex src
out: RPN.txt

RPN.txt: LL1-semantic.out tokens.txt
	./$< tokens.txt grammar/LL-semantic_analysis/grammar.txt >> $@

LL1-semantic.out: LL1-semantic.cpp
	g++ -o $@ $< -std=c++2a

tokens.txt: clang.out
	./$< < samples/numbers.c > $@

clang.out: lex.yy.c
	gcc -o $@ $<

lex.yy.c: clang.lex
	flex $<

clean: 
	rm clang.out lex.yy.c tokens.txt LL1-semantic.out RPN.txt