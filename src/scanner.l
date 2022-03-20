%{
#include "token.h"
int cur_line_num = 1;
void init_scanner();
void lex_error(char* msg, int line);
%}

/* Definitions, note: \042 is '"' */
INTEGER             ([0-9]+)
SCIENCE             ({INTEGER}(\.[0-9]+)?([Ee][-+]?[0-9]+))
UNTERM_STRING       (\042[^\042\n]*)
STRING              (\042[^\042\n]*\042)
IDENTIFIER          ([_a-zA-Z][_a-zA-Z0-9]*)
OPERATOR            ([+*-/%=,;!<>(){}])
SINGLE_COMMENT1     ("//"[^\n]*)
SINGLE_COMMENT2     ("#"[^\n]*)
BINARY              (0[bB][01]+)
HEX                 (0[xX][a-fA-F0-9]+)
OCTAL               (0[0-7]+)
SPACE               ([ \t\r\a\f\v]+)

%%

// line number 
[\n]                { cur_line_num++;                       }

// ignore space
{SPACE}             { /* ignore all spaces */               }

// ignore comment
{SINGLE_COMMENT1}   { /* skip for single line comment */    }
{SINGLE_COMMENT2}   { /* skip for single line commnet */    }

// operator in ASCII
{OPERATOR}          { return yytext[0];         }   

// compare
"<="                { return T_Le;              }
">="                { return T_Ge;              }
"=="                { return T_Eq;              }
"!="                { return T_Ne;              }
// logic
"&&"                { return T_And;             }
"||"                { return T_Or;              }
// type declare
"void"              { return T_Void;            }
"int"               { return T_Int;             }
// case
"while"             { return T_While;           }
"if"                { return T_If;              }
"else"              { return T_Else;            }
"return"            { return T_Return;          }
"break"             { return T_Break;           }
"continue"          { return T_Continue;        }
// read
"print"             { return T_Print;           }
"readint"           { return T_ReadInt;         }
// shift
"<<"                { return T_Lshift;          }
">>"                { return T_Rshift;          }
// assign
"\+="               { return T_AddAssign;       }
"\-="               { return T_SubAssign;       }
"\/="               { return T_QuoAssign;       }
"\*="               { return T_MulAssign;       }

// type
{INTEGER}           { return T_IntConstant;     }
{STRING}            { return T_StringConstant;  }
{IDENTIFIER}        { return T_Identifier;      }
{SCIENCE}           { return T_Science;         }
{BINARY}            { return T_Binary;          }
{HEX}               { return T_Hex;             }
{OCTAL}             { return T_Octal;           }

// EOF
<<EOF>>             { return 0; }

// ERROR
{UNTERM_STRING}     { lex_error("Unterminated string constant", cur_line_num);  }
.                   { lex_error("Unrecognized character", cur_line_num);        }

%%

int main(int argc, char* argv[]) {
    int token;
    init_scanner();
    while (token = yylex()) {
        print_token(token);
        puts(yytext);
    }
    return 0;
}

void init_scanner() {
    printf("%-20s%s\n", "TOKEN-TYPE", "TOKEN-VALUE");
    printf("-------------------------------------------------\n");
}

void lex_error(char* msg, int line) {
    printf("\nError at line %-3d: %s\n\n", line, msg);
}

int yywrap(void) {
    return 1;
}