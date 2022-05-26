VPATH = *.c samples
VPATH = *.lex src
out: RPN_correct.txt RPN_wrong.txt

RPN_correct.txt: LL1-semantic.out tokens1.txt
	./$< tokens1.txt grammar/LL-semantic_analysis/grammar.txt >> $@

RPN_wrong.txt: LL1-semantic.out tokens2.txt
	./$< tokens2.txt grammar/LL-semantic_analysis/grammar.txt >> $@

LL1-semantic.out: LL1-semantic.cpp
	g++ -o $@ $< -std=c++2a

tokens1.txt: clang.out
	./$< < samples/numbers_correct.c > $@

tokens2.txt: clang.out
	./$< < samples/numbers_wrong.c > $@

clang.out: lex.yy.c
	gcc -o $@ $<

lex.yy.c: clang.lex
	flex $<

clean: 
	rm clang.out lex.yy.c tokens1.txt tokens1.txt LL1-semantic.out RPN_correct.txt RPN_wrong.txt