%{
#define YYSTYPE char *
#include "y.tab.h"
int cur_line = 1;
void yyerror(const char *msg);
void unrecognized_char(char c);
int yylex();
%}

/* note \042 is '"' */
SPACE               ([ \t\r\a]+)
COMMENT             ("//"[^\n]*)
OPERATOR            ([+*-/%=,;!<>(){}])
INTEGER             ([0-9]+)
IDENTIFIER          ([_a-zA-Z][_a-zA-Z0-9]*)
UNTERM_STRING       (\042[^\042\n]*)
STRING              (\042[^\042\n]*\042)

%%

\n                  { cur_line++; }
{SPACE}             { /* ignore */ }
{COMMENT}           { /* skip */    }

{OPERATOR}          { return yytext[0]; }
"int"               { return T_Int; }
"void"              { return T_Void; }
"return"            { return T_Return; }
"print"             { return T_Print; }
"readint"           { return T_ReadInt; }
"while"             { return T_While; }
"if"                { return T_If; }
"else"              { return T_Else; }
"break"             { return T_Break; }
"continue"          { return T_Continue; }
"<="                { return T_Le; }
">="                { return T_Ge; }
"=="                { return T_Eq; }
"!="                { return T_Ne; }
"&&"                { return T_And; }
"||"                { return T_Or; }

{INTEGER}           { yylval = strdup(yytext); return T_IntConstant; }
{STRING}            { yylval = strdup(yytext); return T_StringConstant; }
{IDENTIFIER}        { yylval = strdup(yytext); return T_Identifier; }

{UNTERM_STRING}     { yyerror("Unterminate string constant"); }
.                   { unrecognized_char(yytext[0]); }

%%

int yywrap(void) { 
    return 1;
}

void unrecognized_char(char c) {
    char buf[32] = "Unrecognized character: ?";
    buf[24] = c;
    yyerror(buf);
}


void yyerror(const char *msg) {
    fprintf(stderr, "Error at line %d:\n\t%s\n", cur_line, msg);
    exit(-1);
}