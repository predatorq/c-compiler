VPATH = *.c samples
VPATH = *.lex src
out: action_chart.txt

action_chart.txt: LL1.out tokens.txt
	./$< tokens.txt grammar.txt >> $@

LL1.out: LL1.cpp
	g++ -o $@ $< -std=c++2a

tokens.txt: clang.out 
	./$< < samples/numbers.c > $@

clang.out: lex.yy.c
	gcc -o $@ $<

lex.yy.c: clang.lex
	flex $<

clean: 
	rm clang.out lex.yy.c tokens.txt LL1.out action_chart.txt