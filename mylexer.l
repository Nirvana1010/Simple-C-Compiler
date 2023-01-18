%{
/****************************************************************************
mylexer.l
ParserWizard generated Lex file.

Date: 2019.11.10
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myparser.h"

extern YYSTYPE yylval;
extern int line;
char id[20];
char hash1[1000][20];

typedef enum {StmtK, ExpK, DeclK} NodeK;
typedef enum {IfK, WhileK, AssignK, ForK, CompK, InputK, PrintK} StmtKind;
typedef enum {OpK, ConstK, IdK, TypeK} ExpKind;
typedef enum {VarK} DeclKind;
typedef enum {Integer, Char, Void} Type;

struct TreeNode
{
	struct TreeNode * child[100];
	struct TreeNode * sibling;
	int lineno;
	int nodekind;
	int kind;
	union
	{
		int op;
		int val;
		char *name;
	} attr;
	int type;
	int index;
};

int getid(char* text, int leng);

int getHash(char* text, int leng);

int getNum(char* text, int leng);

char getChar(char* text, int leng);
%}

/////////////////////////////////////////////////////////////////////////////
// declarations section

// place any declarations here

INT			"int"
CHAR		"char"
MAIN		"main"
ASSIGN		"="
IF			"if"
WHILE		"while"
FOR			"for"
BREAK		"break"
ELSE		"else"
INPUT		"input"
OUTPUT		"output"

ID			[A-Za-z_][A-Za-z0-9_]*
NUMBER		(0|[1-9][0-9]*)
WHILTESPACE [[:blank:]]
ENTER		(\r\n|\n|\r)
CHARACTER	'[^'\n]'

PLUS		"+"
SUB			"-"
MUL			"*"
DIV			"/"
MOD			"%"
INC			"++"
DEC			"--"
B_AND		"&"
B_OR		"|"
B_NOT		"~"
B_XOR		"^"
SHIFT_L		"<<"
SHIFT_R		">>"
AND			"&&"
OR			"||"
NOT			"!"
EQ			"=="
GREATER		">"
LESS		"<"
G_EQ		">="
L_EQ		"<="
NEQ			"!="
SEMICOLON	";"
LPAREN		"("
RPAREN		")"
LBRACE		"{"
RBRACE		"}"
LBRAC		"["
RBRAC		"]"
ANNO		(\/\*([^\*^\/]*|[\*^\/*]*|[^\**\/]*)*\*\/)|(\/\/[^\n]*)
COMMA		","

%%

/////////////////////////////////////////////////////////////////////////////
// rules section

// place your Lex rules here

// Keyword
{MAIN}		{return MAIN;}
{INT}		{return INT;}
{CHAR}		{return CHAR;}
{FOR}		{return FOR;}
{IF}		{return IF;}
{WHILE} 	{return WHILE;}
{ASSIGN} 	{return ASSIGN;}
{BREAK} 	{return BREAK;}
{ELSE} 		{return ELSE;}
{INPUT} 	{return INPUT;}
{OUTPUT}	{return OUTPUT;}

// Operators

{PLUS}		{return PLUS;}
{SUB}		{return SUB;}
{MUL}		{return MUL;}
{DIV}		{return DIV;}
{MOD}		{return MOD;}
{INC}		{return INC;}
{DEC}		{return DEC;}
{B_AND}		{return B_AND;}
{B_OR}		{return B_OR;}
{B_NOT}		{return B_NOT;}
{B_XOR}		{return B_XOR;}
{SHIFT_L}	{return SHIFT_L;}
{SHIFT_R}	{return SHIFT_R;}
{AND}		{return AND;}
{OR}		{return OR;}
{NOT}		{return NOT;}
{EQ}		{return EQ;}
{GREATER}	{return GREATER;}
{LESS}		{return LESS;}
{G_EQ}		{return G_EQ;}
{L_EQ}		{return L_EQ;}
{NEQ}		{return NEQ;}

// Brackets
{LBRACE}	{return LBRACE;}
{RBRACE}	{return RBRACE;}
{LPAREN}	{return LPAREN;}
{RPAREN}	{return RPAREN;}
{LBRAC}		{return LBRAC;}
{RBRAC}		{return RBRAC;}

// Separators
{SEMICOLON}	{return SEMICOLON;}
{COMMA}		{return COMMA;}

// Comments
{ANNO}		{}


{ID}		{
				int i;
				struct TreeNode * t  = (struct TreeNode*) malloc(sizeof(struct TreeNode));
				for(i = 0; i < 100; i++)
					t->child[i] = NULL;
				t->sibling = NULL;
				t->nodekind = ExpK;
				t->kind = IdK;
				t->lineno = line++;
				t->attr.name = hash1[getid(yytext, yyleng)];
				t->type = Char;
				t->index = getid(yytext, yyleng);
				yylval = t;
				return ID;
			}
			
{NUMBER}	{
				int i;
				struct TreeNode * t  = (struct TreeNode*) malloc(sizeof(struct TreeNode));
				for(i = 0; i < 100; i++)
					t->child[i] = NULL;
				t->sibling = NULL;
				t->nodekind = ExpK;
				t->kind = ConstK;
				t->lineno = line++;
				t->attr.val = getNum(yytext, yyleng);
				t->type = Integer;
				yylval = t;
				return NUMBER;
			}
{CHARACTER}	{
				int i;
				struct TreeNode * t  = (struct TreeNode*) malloc(sizeof(struct TreeNode));
				for(i = 0; i < 100; i++)
					t->child[i] = NULL;
				t->sibling = NULL;
				t->nodekind = ExpK;
				t->kind = ConstK;
				t->lineno = line++;
				t->attr.val = getChar(yytext, yyleng);
				t->type = Char;
				yylval = t;
				return CHARACTER;
			}

{WHILTESPACE}	{}
{ENTER}		{}


%%

/////////////////////////////////////////////////////////////////////////////
// programs section
int getid(char* text, int leng)
{
	int i = 0;
	int index;
	for(i = 0; i < leng; i++)
	{
		id[i] = *text;
		text++;
	}
	id[i] = '\0';
	index = getHash(id, leng)%1000;
	if(hash1[index][0] == '\0')
		strcpy(hash1[index], id);
	else
	{
		while(hash1[index][0] != '\0' && strcmp(id, hash1[index]) != 0)
			index++;
		strcpy(hash1[index], id);
	}
	return index;
}

int getHash(char* text, int leng)
{
	int hash = 0;
	int i = 0;
	for(i = 0; text[i] != '\0'; i++)
		hash = 31 * hash + text[i];
	if(hash < 0)
		hash = -hash;
	return hash;
}

int getNum(char* text, int leng)
{
	int value = 0;
	int i;
	for(i = 0; i < leng; i++)
	{
		value = value*10 + *text - '0';
		text++;
	}
	return value;
}

char getChar(char* text, int leng)
{
	char value;
	value = text[1];
	return value;
}