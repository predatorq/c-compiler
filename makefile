VPATH = *.c samples
VPATH = *.lex src
out: action_chart1.txt action_chart2.txt

action_chart1.txt: LL1.out tokens.txt
	./$< tokens.txt grammar/LL1/grammar.txt >> $@

action_chart2.txt: LR0.out tokens.txt
	./$< tokens.txt grammar/LR0/goto.txt grammar/LR0/shift.txt grammar/LR0/reduce.txt >> $@

LR0.out: LR0.cpp
	g++ -o $@ $< -std=c++2a

LL1.out: LL1.cpp
	g++ -o $@ $< -std=c++2a

tokens.txt: clang.out 
	./$< < samples/numbers.c > $@

clang.out: lex.yy.c
	gcc -o $@ $<

lex.yy.c: clang.lex
	flex $<

clean: 
	rm clang.out lex.yy.c tokens.txt LL1.out LL0.out action_chart1.txt action_chart2.txt