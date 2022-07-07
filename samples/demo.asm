FUNC @main:
	main.var a, b
	push 1
	push 1
	add
	pop a
	push 3
	push 3
	mul
	pop a
	push 2
	push 2
	add
	pop b
	push 4
	push 4
	add
	pop b
_begWhile_1:
	push a
	push 80
	cmplt
	jz _endWhile_1
	push a
	push b
	add
	pop a
	print "INWHILE"
_begIf_1:
	push a
	push 60
	cmpgt
	jz _elIf_1
	print "BREAK"
	jmp _endWhile_1
	jmp _endIf_1
_elIf_1:
_endIf_1:
	jmp _begWhile_1
_endWhile_1:
	print "EXIT"
	push 0
	ret ~
ENDFUNC@main

