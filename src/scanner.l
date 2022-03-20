%{
typedef enum {
    T_Le = 256, T_Ge, T_Eq, T_Ne, T_And, T_Or, T_IntConstant,
    T_StringConstant, T_Identifier, T_Void, T_Int, T_While,
    T_If, T_Else, T_Return, T_Break, T_Continue, T_Print,
    T_ReadInt, T_Science, T_Binary, T_Hex, T_Octal, T_Lshift,
    T_Rshift, T_AddAssign, T_SubAssign, T_QuoAssign, T_MulAssign,
    T_Sizeof

} TokenType;

static void print_token(int token) {
    static char* token_strs[] = {
        "T_Le", "T_Ge", "T_Eq", "T_Ne", "T_And", "T_Or", "T_IntConstant",
        "T_StringConstant", "T_Identifier", "T_Void", "T_Int", "T_While",
        "T_If", "T_Else", "T_Return", "T_Break", "T_Continue", "T_Print",
        "T_ReadInt", "T_Science", "T_Binary", "T_Hex", "T_Octal", "T_Lshift",
        "T_Rshift", "T_AddAssign", "T_SubAssign", "T_QuoAssign", "T_MulAssign",
        "T_Sizeof"
    };

    if (token < 256) {
        printf("%-20c", token);
    } else {
        printf("%-20s", token_strs[token-256]);
    }
}

int cur_line_num = 1;
void init_scanner();
void lex_error(char* msg, int line);
%}

/* Definitions, note: \042 is '"' */
INTEGER             ([0-9]+)
SCIENCE             ({INTEGER}(\.[0-9]+)?([Ee][-+]?[0-9]+))
BINARY              (0[bB][01]+)
HEX                 (0[xX][a-fA-F0-9]+)
OCTAL               (0[0-7]+)
SPACE               ([ \t\r\a\f\v]+)

UNTERM_STRING       (\042[^\042\n]*)
STRING              (\042[^\042\n]*\042)
IDENTIFIER          ([_a-zA-Z][_a-zA-Z0-9]*)
OPERATOR            ([+*-/%=,;!<>(){}])
SINGLE_COMMENT     ("//"[^\n]*)

%%

[\n]                { cur_line_num++;                       }

{SPACE}             { /* ignore all spaces */               }

{SINGLE_COMMENT}   { /* skip for single line comment */    }

{OPERATOR}          { return yytext[0];         }   

"<="                { return T_Le;              }
">="                { return T_Ge;              }
"=="                { return T_Eq;              }
"!="                { return T_Ne;              }
"&&"                { return T_And;             }
"||"                { return T_Or;              }
"void"              { return T_Void;            }
"int"               { return T_Int;             }
"sizeof"            { return T_Sizeof;          }
"while"             { return T_While;           }
"if"                { return T_If;              }
"else"              { return T_Else;            }
"return"            { return T_Return;          }
"break"             { return T_Break;           }
"continue"          { return T_Continue;        }
"print"             { return T_Print;           }
"readint"           { return T_ReadInt;         }
"<<"                { return T_Lshift;          }
">>"                { return T_Rshift;          }
"\+="               { return T_AddAssign;       }
"\-="               { return T_SubAssign;       }
"\/="               { return T_QuoAssign;       }
"\*="               { return T_MulAssign;       }


{INTEGER}           { return T_IntConstant;     }
{STRING}            { return T_StringConstant;  }
{IDENTIFIER}        { return T_Identifier;      }
{SCIENCE}           { return T_Science;         }
{BINARY}            { return T_Binary;          }
{HEX}               { return T_Hex;             }
{OCTAL}             { return T_Octal;           }

<<EOF>>             { return 0; }

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