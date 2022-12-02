%{
    /* Declarations section */
#include <stdio.h>
#include "parser.tab.hpp"
#include "hw3_output.hpp"
#include "Stypes.h"
using namespace output;

%}

%option yylineno
%option noyywrap
void "void"
int "int"
byte "byte"
bool "bool"
and "and"
or "or"
not "not"
true "true"
false "false"
return "return"
if "if"
else "else"
while "while"
break "break"
continue "continue"
sc (\;)
comma (\,)
lparen (\()
rparen(\))
lbrace (\{)
rbrace (\})
assign (\=)
relop (<|>|<=|>=)
equal_relop (==|!=)
plus_minus ([\+\-])
mult_div ([\*\/])
comment (\/\/[^\r\n]*[\r|\n|\r\n]?)
digit ([0-9])
letter ([a-zA-Z])
whitespace ([ \t\n\r])
id ([a-zA-Z]+[a-zA-Z0-9]*)
num (0|([1-9]{digit}*))
space ([ ])
string (\"([^\n\r\"\\]|\\[rnt\"\\])+\")


%%
{void} yylval=new Node(yytext); return VOID;
{int} yylval=new Node(yytext); return INT;
{byte} yylval=new Node(yytext); return BYTE;
b return  yylval=new Node(yytext); B;
{bool} yylval=new Node(yytext); return BOOL;
{and} yylval=new Node(yytext); return AND;
{or} yylval=new Node(yytext); return OR;
{not} yylval=new Node(yytext); return NOT;
{true} yylval=new Node(yytext); return TRUE;
{false} yylval=new Node(yytext); return FALSE;
{return} yylval=new Node(yytext); return RETURN;
{if} yylval=new Node(yytext); return IF;
{else} yylval=new Node(yytext); return ELSE;
{while} yylval=new Node(yytext); return WHILE;
{break} yylval=new Node(yytext); return BREAK;
{continue} yylval=new Node(yytext); return CONTINUE;
{sc} yylval=new Node(yytext); return SC;
{comma} yylval=new Node(yytext); return COMMA;
{lparen} yylval=new Node(yytext); return LPAREN;
{rparen} yylval=new Node(yytext); return RPAREN;
{lbrace} yylval=new Node(yytext); return LBRACE;
{rbrace} yylval=new Node(yytext); return RBRACE;
{assign} yylval=new Node(yytext); return ASSIGN;
{relop} yylval=new Node(yytext); return RELOP;
{equal_relop} yylval=new Node(yytext); return EQUAL_RELOP;
{plus_minus} yylval=new Node(yytext); return PLUS_MINUS;
{mult_div} yylval=new Node(yytext); return MULT_DIV;
{num} yylval=new Node(yytext); return NUM;
{id} yylval=new Node(yytext); return ID;
{string} yylval=new Node(yytext); return STRING;
{comment}
{whitespace}

. {errorLex(yylineno);}
%%