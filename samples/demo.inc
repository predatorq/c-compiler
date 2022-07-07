; ==== begin function `main` ====
%define main.argc 0

%MACRO $main 0
   CALL @main
   ADD ESP, 4*main.argc
   PUSH EAX
%ENDMACRO

%define main.varc 2

%MACRO main.var main.varc
	%define a [EBP - 4*1]
	%define b [EBP - 4*2]
	SUB ESP, 4*main.varc
%ENDMACRO

%MACRO ENDFUNC@main 0
	LEAVE
	RET
	%undef a
	%undef b
%ENDMACRO
; ==== end function `main`   ====

