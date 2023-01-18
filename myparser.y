%{
/****************************************************************************
myparser.y
ParserWizard generated YACC file.

Date: 2019.11.10
****************************************************************************/

#include "mylexer.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {StmtK, ExpK, DeclK} NodeK;
typedef enum {IfK, WhileK, ForK, CompK, InputK, OutputK, NullK} StmtKind;
typedef enum {OpK, ConstK, IdK, TypeK} ExpKind;
typedef enum {VarK} DeclKind;
typedef enum {Integer, Char, Void, Bool} Type;

int line = 0;
int num = 0;
static int d = 0;

FILE * fp = NULL;

int label = 0;
int labeln = 1;
int cur_t = 0;
int temp_var_seq = 1;

struct symbol
{
	char id[20];//id
	char id_type;//type
};

struct symbol table[1000];

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
	int tid;//$t1-9
	int begin_label;
	int next_label;
	int true_label;
	int false_label;
};

struct TreeNode * newStmtNode(int kind)
{
	struct TreeNode * t = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	int i;
	if(t == NULL)
		printf("out of memory error at linr %d\n", line);
	else
	{
		for(i = 0; i < 100; i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = StmtK;
		t->kind = kind;
		t->lineno = line++;
	}
	return t;
}

struct TreeNode * newExpNode(int kind)
{
	struct TreeNode * t = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	int i;
	if(t == NULL)
		printf("out of memory error at linr %d\n", line);
	else
	{
		for(i = 0; i < 100; i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = ExpK;
		t->kind = kind;
		t->lineno = line++;
	}
	return t;
}

struct TreeNode * newDeclNode(int kind)
{
	struct TreeNode * t = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	int i;
	if(t == NULL)
		printf("out of memory error at line %d\n", line);
	else
	{
		for(i = 0; i < 100; i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = DeclK;
		t->kind = kind;
		t->lineno = line++;
	}
	return t;
}

struct symbol * newSymbolItem(char* id, char type)
{
	struct symbol * s = (struct symbol*) malloc(sizeof(struct symbol));
	strcpy(s->id, id);
	s->id_type = type;
	return s;
}

int ShowNode(struct TreeNode *p);

void Display(struct TreeNode *p);

void gen_header();

void gen_var(struct TreeNode *r);

void gen_asm(struct TreeNode *r);

void gen_label(struct TreeNode *r);

void recursive_gen_label(struct TreeNode *r);

void gen_data(struct TreeNode *r);

void gen_code(struct TreeNode *r);

void gen_stmt_code(struct TreeNode *r);

void gen_exp_code(struct TreeNode *r);

void get_temp_var(struct TreeNode *r);

void get_label(struct TreeNode *r);

void get_expr_label(struct TreeNode *r);

void get_stmt_label(struct TreeNode *r);

struct TreeNode* root;
%}

/////////////////////////////////////////////////////////////////////////////
// declarations section

// attribute type
%include {
#ifndef YYSTYPE
#define YYSTYPE struct TreeNode*
#endif
}

// place any declarations here
%token MAIN IF WHILE FOR BREAK INPUT OUTPUT
%token INT CHAR ASSIGN
%token ID NUMBER CHARACTER
%token PLUS SUB 
%token MUL DIV MOD 
%token INC DEC
%token B_AND B_OR B_NOT B_XOR
%token SHIFT_L SHIFT_R
%token AND OR NOT EQ GREATER LESS G_EQ L_EQ NEQ
%token SEMICOLON LPAREN RPAREN LBRACE RBRACE
%token COMMA
%token ELSE

%left	COMMA
%right	ASSIGN
%left	AND OR
%left	B_AND B_OR B_XOR
%left	EQ NEQ
%left	GREATER LESS G_EQ L_EQ
%left	SHIFT_L SHIFT_R
%left	PLUS SUB
%left	MUL DIV MOD 
%left	INC DEC NOT B_NOT
%left	LPAREN RPAREN LBRACE RBRACE LBRAC RBRAC
%right	ELSE

%%

/////////////////////////////////////////////////////////////////////////////
// rules section

// place your YACC rules here (there must be at least one)

start		:MAIN LPAREN RPAREN compStmt
			{
				$$ = $4;
				Display($4);
				root  = $4;
			}
			;
compStmt	:LBRACE stmtList RBRACE
			{
				$$ = newStmtNode(CompK);
				$$->child[0] = $2;
				$$->type = Void;
			}
			;
stmtList	:stmt stmtList
			{
				$$->sibling = $2;
				$$ = $1;
			}
			|stmt
			{
				$$ = $1;
			}
			;
stmt		:decStmt
			{
				$$ = $1;
			}
			|exprStmt
			{
				$$ = $1;
			}
			|ifStmt
			{
				$$ = $1;
			}
			|whileStmt
			{
				$$ = $1;
			}
			|forStmt
			{
				$$ = $1;
			}
			|compStmt
			{
				$$ = $1;
			}
			|inputStmt SEMICOLON
			{
				$$ = $1;
			}
			|outputStmt SEMICOLON
			{
				$$ = $1;
			}
			|nullStmt
			{
				$$ = $1;
			}
			;
nullStmt	:SEMICOLON
			{
				$$ = newStmtNode(NullK);
				$$->type = Void;
			}
			;
typeDecp	:INT
			{
				$$ = newExpNode(TypeK);
				$$->type = Integer;
			}
			|CHAR
			{
				$$ = newExpNode(TypeK);
				$$->type = Char;
			}
			;
idList		:expr COMMA idList
			{
				$$ = $1;
				$$->sibling = $3;
			}
			|expr
			{
				$$ = $1;
			}
			;
decStmt		:typeDecp idList SEMICOLON
			{
				char *type1[3] = {"Integer", "Char", "Void"};
				struct TreeNode * temp = (struct TreeNode*) malloc(sizeof(struct TreeNode));
				struct symbol * sym = (struct symbol*) malloc(sizeof(struct symbol));
				char typeDec;
				$$ = newDeclNode(VarK);
				$$->child[0] = $1;
				$$->child[2] = $2;
				$$->child[2]->type = $1->type;
				temp = $$->child[2]->sibling;
				if(type1[$1->type] == "Integer")
					typeDec = 'I';
				else if(type1[$1->type] == "Char")
					typeDec = 'C';
				while(temp != NULL)
				{
					temp->type = $1->type;
					sym = newSymbolItem(temp->attr.name, typeDec);
					table[temp->index] = *sym;
					temp = temp->sibling;
				}
				sym = newSymbolItem($$->child[2]->attr.name, typeDec);
				table[$$->child[2]->index] = *sym;
				$$->type = Void;
			}
			;
inputStmt	:INPUT LPAREN expr RPAREN //input(a)
			{
				$$ = newStmtNode(InputK);
				$$->child[0] = $3;
				$$->type = Void;
			}
			;
outputStmt	:OUTPUT LPAREN expr RPAREN //output(a)
			{
				$$ = newStmtNode(OutputK);
				$$->child[0] = $3;
				$$->type = Void;
			}
			;
ifStmt		:IF LPAREN expr RPAREN stmt //if(expr) stmt
			{
				$$ = newStmtNode(IfK);
				$$->child[0] = $3;
				$$->child[1] = $5;
				$$->type = Void;
			}
			|IF LPAREN expr RPAREN stmt ELSE stmt //if(expr) stmt else stmt
			{
				$$ = newStmtNode(IfK);
				$$->child[0] = $3;
				$$->child[1] = $5;
				$$->child[2] = $7;
				$$->type = Void;
			}
			;
forStmt		:FOR LPAREN expr SEMICOLON expr SEMICOLON expr RPAREN stmt //for(expr;expr;expr)
			{
				$$ = newStmtNode(ForK);
				$$->child[0] = $3;
				$$->child[1] = $5;
				$$->child[2] = $7;
				$$->child[3] = $9;
				$$->type = Void;
			}
			|FOR LPAREN SEMICOLON expr SEMICOLON expr RPAREN stmt //for(;expr;expr)
			{
				$$ = newStmtNode(ForK);
				$$->child[0] = NULL;
				$$->child[1] = $4;
                $$->child[2] = $6;
                $$->child[3] = $8;
                $$->type = Void;
			}
			|FOR LPAREN expr SEMICOLON SEMICOLON expr RPAREN stmt //for(expr;;expr)
			{
				$$ = newStmtNode(ForK);
				$$->child[0] = $3;
				$$->child[1] = NULL;
                $$->child[2] = $6;
                $$->child[3] = $8;
                $$->type = Void;
			}
			|FOR LPAREN expr SEMICOLON expr SEMICOLON RPAREN stmt //for(expr;expr;)
			{
				$$ = newStmtNode(ForK);
				$$->child[0] = $3;
				$$->child[1] = $5;
                $$->child[2] = NULL;
                $$->child[3] = $8;
                $$->type = Void;
			}
			|FOR LPAREN SEMICOLON SEMICOLON expr RPAREN stmt //for(;;expr)
			{
				$$ = newStmtNode(ForK);
				$$->child[0] = NULL;
				$$->child[1] = NULL;
                $$->child[2] = $5;
                $$->child[3] = $7;
                $$->type = Void;
			}
			|FOR LPAREN SEMICOLON expr SEMICOLON RPAREN stmt //for(;expr;;)
			{
				$$ = newStmtNode(ForK);
				$$->child[0] = NULL;
				$$->child[1] = $4;
                $$->child[2] = NULL;
                $$->child[3] = $7;
                $$->type = Void;
			}
			|FOR LPAREN expr SEMICOLON SEMICOLON RPAREN stmt //for(expr;;)
			{
				$$ = newStmtNode(ForK);
				$$->child[0] = $3;
				$$->child[1] = NULL;
                $$->child[2] = NULL;
                $$->child[3] = $7;
                $$->type = Void;
			}
			|FOR LPAREN SEMICOLON SEMICOLON RPAREN stmt //for(;;)
			{
				$$ = newStmtNode(ForK);
				$$->child[0] = NULL;
				$$->child[1] = NULL;
                $$->child[2] = NULL;
                $$->child[3] = $6;
                $$->type = Void;
			}
			;
whileStmt	:WHILE LPAREN expr RPAREN stmt //while(expr) stmt
			{
				$$ = newStmtNode(WhileK);
				$$->child[0] = $3;
				$$->child[1] = $5;
				$$->type = Void;
			}
			;
exprStmt	:expr SEMICOLON
			{
				$$ = $1;
			}
			;
expr		:expr ASSIGN expr //expr = expr
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = ASSIGN;
				$$->type = Void;
			}
			|orExpr
			{
				$$ = $1;
			}
			;
orExpr		:orExpr OR andExpr
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = OR;
				$$->type = Void;
				get_temp_var($$);
			}
			|andExpr
			{
				$$ = $1;
			}
			;
andExpr		:andExpr AND eqExpr
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = AND;
				$$->type = Void;
				get_temp_var($$);
			}
			|eqExpr
			{
				$$ = $1;
			}
			;
eqExpr		:eqExpr EQ simpleExpr
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = EQ;
				$$->type = Void;
				get_temp_var($$);
			}
			|eqExpr GREATER simpleExpr
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = GREATER;
				$$->type = Void;
				get_temp_var($$);
			}
			|eqExpr LESS simpleExpr
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = LESS;
				$$->type = Void;
				get_temp_var($$);
			}
			|eqExpr G_EQ simpleExpr
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = G_EQ;
				$$->type = Void;
				get_temp_var($$);
			}
			|eqExpr L_EQ simpleExpr
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = L_EQ;
				$$->type = Void;
				get_temp_var($$);
			}
			|eqExpr NEQ simpleExpr
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = NEQ;
				$$->type = Void;
				get_temp_var($$);
			}
			|simpleExpr
			{
				$$ = $1;
			}
			;
simpleExpr	:simpleExpr PLUS factor
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = PLUS;
				$$->type = Void;
				get_temp_var($$);
			}
			|simpleExpr SUB factor
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = SUB;
				$$->type = Void;
				get_temp_var($$);
			}
			|factor
			{
				$$ = $1;
			}
			;
factor		:factor MUL term
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = MUL;
				$$->type = Integer;
				get_temp_var($$);
			}
			|factor DIV term
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = DIV;
				$$->type = Integer;
				get_temp_var($$);
			}
			|factor MOD term
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = MOD;
				$$->type = Integer;
				get_temp_var($$);
			}
			|factor B_AND term
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = B_AND;
				$$->type = Integer;
				get_temp_var($$);
			}
			|factor B_OR term
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = B_OR;
				$$->type = Integer;
				get_temp_var($$);
			}
			|factor B_XOR term
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = B_XOR;
				$$->type = Integer;
				get_temp_var($$);
			}
			|factor INC
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->attr.op = INC;
				$$->type = Integer;
			}
			|factor DEC
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->attr.op = DEC;
				$$->type = Integer;
			}
			|factor SHIFT_L term
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = SHIFT_L;
				$$->type = Integer;
				get_temp_var($$);
			}
			|factor SHIFT_R term
			{
				$$ = newExpNode(OpK);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = SHIFT_R;
				$$->type = Integer;
				get_temp_var($$);
			}
			|term
			{
				$$ = $1;
			}
			;
term		:LPAREN expr RPAREN
			{
				$$ = $2;
			}
			|ID
			{
				$$ = $1;
			}
			|NUMBER
			{
				$$ = $1;
			}
			|NOT term
			{
			   $$ = newExpNode(OpK);
			   $$ -> attr.op = NOT;
			   $$ -> child[0] =$2;
			   $$->type = Void;
			}
			|B_NOT term
			{
			   $$ = newExpNode(OpK);
			   $$ -> attr.op = B_NOT;
			   $$ -> child[0] =$2;
			   $$->type = Void;
			}
			|CHARACTER
			{
				$$ = $1;
			}
			;
%%

/////////////////////////////////////////////////////////////////////////////
// programs section
int ShowNode(struct TreeNode *p)
{	
	struct TreeNode * temp = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	int i;
	char *type[4] = {"Integer", "Char", "Void", "Bool"};
	p->lineno = num++;
	printf("%d: ", p->lineno);

	switch(p->nodekind)
	{
		case StmtK:
		{
			char *name[7] = {"if statement:", "while statement:", "for statement:", "compound statement:","input statement:","output statement:","null statement:"};
			switch(p->kind)
			{
				case IfK:
				{
					if(strcmp(type[p->child[0]->type], "Integer") == 0 || strcmp(type[p->child[0]->type], "Bool") == 0)
						p->type = Void;
					else
					{
						printf("\nTYPE ERROR: if statement: node %d is not bool/interger!\n", p->child[0]->lineno);
						return -1;
					}
					break;
				}
				case WhileK:
				{
					if(strcmp(type[p->child[0]->type], "Integer") == 0 || strcmp(type[p->child[0]->type], "Bool") == 0)
						p->type = Void;
					else
					{
						printf("\nTYPE ERROR: while statement: node %d is not bool/interger!\n", p->child[0]->lineno);
						return -1;
					}
					break;
					
				}
				case ForK:
				{
					if(p->child[1] != NULL)
					{
						if(strcmp(type[p->child[1]->type], "Bool") == 0)
							p->type = Void;
						else
						{
							printf("\nTYPE ERROR: for statement: node %d is not bool!\n", p->child[1]->lineno);
							return -1;
						}
					}
					break;
				}
				case InputK:
				{
					if(p->child[0]->type == Bool)
					{
						printf("\nTYPE ERROR: Input statement: node %d can not be a bool!\n", p->child[0]->lineno);
						return -1;
					}
					break;
				}
				case OutputK:
				{
					if(p->child[0]->type == Bool)
					{
						printf("\nTYPE ERROR: Output statement: node %d can not be a bool!\n", p->child[0]->lineno);
						return -1;
					}
					break;
				}
			}
			printf("%s\t\t\t", name[p->kind]);
			break;
		}
		case ExpK:
		{
			char *name[4] = {"expr:", "const declaration:", "ID declaration:", "type specifier:"};
			printf("%s\t", name[p->kind]);
			
			switch(p->kind)
			{
				case OpK:
				{
				   switch(p->attr.op)
				   {
				       case PLUS:
				       {
				           printf("\top:+\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case SUB:
				       {
				           printf("\top:-\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
							   return -1;
						   }
					       break;
				       }
				       case MUL:
				       {
				           printf("\top:*\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case DIV:
				       {
				           printf("\top:/\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case MOD:
				       {
				           printf("\top:%\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case INC:
				       {
				           printf("\top:++\t\t");
				           if(strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   printf("\nTYPE ERROR: node %d is not integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case DEC:
				       {
				           printf("\top:--\t\t");
				           if(strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   printf("\nTYPE ERROR: node %d is not integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case LESS:
				       {
				           printf("\top:<\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = Bool;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case L_EQ:
				       {
				           printf("\top:<=\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = Bool;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case GREATER:
				       {
				           printf("\top:>\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = Bool;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case G_EQ:
				       {
				           printf("\top:>=\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = Bool;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }	
				       case EQ:
				       {
				           printf("\top:==\t\t");
				           if(p->child[0]->type == p->child[1]->type)
						       p->type = Bool;
						   else
						   {
							   printf("\nTYPE ERROR: node %d and node %d not match!\n", p->child[0]->lineno, p->child[1]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case NEQ:
				       {
				           printf("\top:!=\t\t");
				           if(p->child[0]->type == p->child[1]->type)
						       p->type = Bool;
						   else
						   {
							   printf("\nTYPE ERROR: node %d and node %d not match!\n", p->child[0]->lineno, p->child[1]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case OR:
				       {
				           printf("\top:||\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Bool") == 0)
						       p->type = Bool;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Bool") != 0)
							       printf("\nTYPE ERROR: node %d is not Bool!\n", p->child[0]->lineno);
							   if(strcmp(type[p->child[1]->type], "Bool") != 0)
							       printf("\nTYPE ERROR: node %d is not Bool!\n", p->child[1]->lineno);
							   
							   return -1;
						   }
				           break;
				       }
				       case AND:
				       {
				           printf("\top:&&\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Bool") == 0)
						       p->type = Bool;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Bool") != 0)
							       printf("\nTYPE ERROR: node %d is not Bool!\n", p->child[0]->lineno);
							   if(strcmp(type[p->child[1]->type], "Bool") != 0)
							       printf("\nTYPE ERROR: node %d is not Bool!\n", p->child[1]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case NOT:
				       {
				           printf("\top:!\t\t");
				           if(strcmp(type[p->child[0]->type], "Bool") == 0)
						       p->type = Bool;
						   else
						   {
							   printf("\nTYPE ERROR: node %d is not Bool!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case B_AND://a & b
				       {
				           printf("\top:&\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
						   } 
				           break;
				       }
				       case B_OR://a | b
				       {
				           printf("\top:|\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
						   } 
				           break;
				       }
				       case B_XOR://a ^ b
				       {
				           printf("\top:^\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
						   }
				           break;
				       }
				       case B_NOT:// ~a
				       {
				           printf("\top:~\t\t");
				           if(strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   printf("\nTYPE ERROR: node %d is not integer!\n", p->child[0]->lineno);
						   }
				           break;
				       }
				       case SHIFT_L://a << b
				       {
				           printf("\top:<<\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           break;
				       }
				       case SHIFT_R://a >> b
				       {
				           printf("\top:>>\t\t");
				           if(p->child[0]->type == p->child[1]->type && strcmp(type[p->child[0]->type], "Integer") == 0)
						       p->type = p->child[0]->type;
						   else
						   {
							   if(strcmp(type[p->child[0]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[1]->lineno);
							   if(strcmp(type[p->child[1]->type], "Integer") == 0)
							       printf("\nTYPE ERROR: node %d is not a integer!\n", p->child[0]->lineno);
							   return -1;
						   }
				           
				           break;
				       }
				       case ASSIGN:
				       {
				           printf("\top:=\t\t");
				           if(p->child[0]->type == p->child[1]->type)
						       p->type = p->child[0]->type;
						   else
						   {
							   printf("\nTYPE ERROR: node %d and node %d not match!\n", p->child[0]->lineno, p->child[1]->lineno);
							   return -1;
						   }
				           break;
				       }
				   }
				   break;
				}
				case ConstK:
				{
					printf("values: %d\t",p->attr.val);
					break;
				}
				case IdK:
				{
					//printf("\nindex: %d  \n", p->index);
					if(table[p->index].id_type == 'I')
						p->type = Integer;
					else if(table[p->index].id_type == 'C')
						p->type = Char;
					else if(table[p->index].id_type == NULL)
					{
						printf("\nERROR: node %d : symbol %s has not been declared!\n", p->lineno, p->attr.name);
						return -1;
					}
					printf("symbol: %s\t",p->attr.name);
					break;
				}
				case TypeK:
				{
					printf("%s\t\t", type[p->type]);
					break;
				}
			}
			break;
		}
		case DeclK:
		{
			printf("%s\t\t\t", "Var Declaration:");
			break;
		}
		break;
	}
	printf("type:%s\t", type[p->type]);
	printf("children:");
	for(i = 0; i < 100; i++)
	{
		if(p->child[i] != NULL)
		{
			printf("%d  ", p->child[i]->lineno);
			temp = p->child[i]->sibling;
			while(temp != NULL)
			{
				printf("%d\t", temp->lineno);
				temp = temp->sibling;
			}
		}
	}
	printf("\n");
	return 0;
}

void Display(struct TreeNode *p)
{
	//gen_header();
	struct TreeNode *temp = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	int i;
	int r = 0;
	for(i = 0; i < 100; i++)
	{
		if(p->child[i] != NULL)
			Display(p->child[i]);
		
	}
	if(d == -1)
		return ;
	r = ShowNode(p);
	
	if(r == -1)
	{
		d = -1;
	}
	if(d == -1)
		return ;
	temp = p->sibling;
	if(temp != NULL)
		Display(temp);
	return ;
}

void gen_asm(struct TreeNode *r)
{
	int i;
	gen_header();
	
	fprintf(fp, "\n\n\t.data\n");
	fprintf(fp, "\ttype0 db '%s', 0\n", "%d");
	fprintf(fp, "\ttype1 db '%s', 0\n", "%d");
	fprintf(fp, "\tindata DWORD ?\n");

	gen_var(r);

	for(i = 1; i < temp_var_seq; i++)
	{
		fprintf(fp, "\tt%d\tDWORD 0\t\n", i);
	}
	fprintf(fp, "\tnewline BYTE    13, 10, 0\n");
	//gen_data(r);
	//cur_t = 0;

	fprintf(fp, "\n\n\t.code\n");
	fprintf(fp, "_start:\n");
	get_label(r);

	gen_code(r);

	fprintf(fp, "\tinvoke crt_scanf, addr type0, indata\n");
	fprintf(fp, "\tinvoke ExitProcess, 0\n");
	fprintf(fp, "end _start\n");
}

void gen_header()
{ 
	fprintf(fp,"\t.586\n");
	fprintf(fp,"\t.model flat, stdcall\n");
	fprintf(fp,"\toption casemap :none\n\n");
	fprintf(fp,"\tinclude \\masm32\\include\\windows.inc\n");
	fprintf(fp,"\tinclude \\masm32\\include\\user32.inc\n");
	fprintf(fp,"\tinclude \\masm32\\include\\kernel32.inc\n");
	fprintf(fp,"\tinclude \\masm32\\include\\masm32.inc\n\n");
	fprintf(fp,"\tincludelib \\masm32\\lib\\user32.lib\n");
	fprintf(fp,"\tincludelib \\masm32\\lib\\kernel32.lib\n");
	fprintf(fp,"\tincludelib \\masm32\\lib\\masm32.lib\n\n");
	fprintf(fp,"\tinclude \\masm32\\macros\\macros.asm\n");
	fprintf(fp,"\tinclude \\masm32\\include\\msvcrt.inc\n");
	fprintf(fp,"\tincludelib \\masm32\\lib\\msvcrt.lib\n");
	
}

void gen_var(struct TreeNode *r)
{
	struct TreeNode *temp = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	int i;
	for(i = 0; i < 100; i++)
	{
		if(r->child[i] != NULL)
			gen_var(r->child[i]);
		
	}
	if(r->nodekind == DeclK)
		recursive_gen_label(r);

	temp = r->sibling;
	if(temp != NULL)
		gen_var(temp);
	return ;
}

void recursive_gen_label(struct TreeNode *r)
{
	struct TreeNode *temp = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	for(temp = r->child[2]; temp != NULL; temp = temp->sibling)
	{
		if(temp->type == Integer)
			fprintf(fp, "\t_%s\tDWORD 0\n", temp->attr.name);
		else if(temp->type ==Char)
			fprintf(fp, "\t_%s\tDWORD 0\n", temp->attr.name);
	}
}

void get_temp_var(struct TreeNode *t)
{
	struct TreeNode *child1 = t->child[0];
	struct TreeNode *child2 = t->child[1];
	if (t->nodekind != ExpK)
		return;
	if (child1->kind == OpK)
		temp_var_seq--;
	if (child2 && child2->kind == OpK)
		temp_var_seq--;
	t->tid = temp_var_seq;
	temp_var_seq++;
}

void gen_data(struct TreeNode *r)
{
	struct TreeNode *t = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	t = r;
	for( ; t != NULL; t = t->sibling)
	{
		switch(t->nodekind)
		{
			case StmtK:
			{
				//fprintf(fp,"StmtK\n");
				switch(t->kind)
				{
					case IfK:
					{
						if(t->child[1])
							gen_data(t->child[1]);
						if(t->child[2])
							gen_data(t->child[2]);
						break;
					}
					case WhileK:
					{
						if(t->child[1])
							gen_data(t->child[1]);
						break;
					}
					case ForK:
					{
						if(t->child[0])
							gen_data(t->child[0]);
						if(t->child[3])
							gen_data(t->child[3]);
						break;
					}
					case CompK:
					{
						if(t->child[0])
							gen_data(t->child[0]);
						break;
					}
					case InputK:
					{
						break;
					}
					case OutputK:
					{
						break;
					}
				}
				break;
			}
			case ExpK:
			{
				switch(t->kind)
				{
					//fprintf(fp,"ExpK\n");
					case OpK:
					{
						break;
					}
					case ConstK:
					{
						break;
					}
					case IdK:
					{
						fprintf(fp, "\t_%s\tDWORD 0\n", t->attr.name);
						break;
					}
					case TypeK:
					{
						break;
					}
				}
				break;
			}
			case DeclK:
			{
				//fprintf(fp,"DeclK\n");
				gen_data(t->child[2]);
				break;
			}
		}
	}
}

void gen_code(struct TreeNode *r)
{
	struct TreeNode *t = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	t = r;
	switch(t->nodekind)
	{
		case StmtK:
		{
			gen_stmt_code(t);
			break;
		}
		case ExpK:
		{
			//printf("gen_exp_code\n");
			gen_exp_code(t);
			break;
		}
		case DeclK:
		{
			//gen_decl_code(t);
			break;
		}
	}
}

void gen_stmt_code(struct TreeNode *r)
{
	struct TreeNode *t = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	int m1;
	int m2;
	t = r;
	switch(t->kind)
	{
		case IfK:
		{
			if(r->child[2] == NULL)
			{
				if(r->begin_label > 0)
					fprintf(fp, "label%d:\n", r->begin_label);
				gen_code(r->child[0]);
				if(r->child[0]->true_label > 0)
					fprintf(fp, "label%d:\n", r->child[0]->true_label);
				gen_code(r->child[1]);
				//if(r->next_label+1 == labeln)
					fprintf(fp, "label%d:\n", r->next_label	);
			}
			else
			{
				if(r->begin_label > 0)
					fprintf(fp, "label%d:\n", r->begin_label);
				gen_code(r->child[0]);
				if(r->child[0]->true_label > 0)
					fprintf(fp, "label%d:\n", r->child[0]->true_label);
				gen_code(r->child[1]);
				fprintf(fp, "\tjmp label%d\n", r->next_label);
				fprintf(fp, "label%d:\n", r->child[0]->false_label);
				gen_code(r->child[2]);
				//if(r->next_label+1 == labeln)
					fprintf(fp, "label%d:\n", r->next_label	);
			}
			break;
		}
		case WhileK:
		{
			if(r->begin_label > 0)
				fprintf(fp, "label%d:\n", r->begin_label);
			gen_code(r->child[0]);
			if(r->child[0]->true_label > 0)
				fprintf(fp, "label%d:\n", r->child[0]->true_label);
			gen_code(r->child[1]);
			fprintf(fp, "\tjmp label%d\n", r->begin_label);
			//if(r->next_label+1 == labeln)
				fprintf(fp, "label%d:\n", r->next_label	);
			break;
		}
		case ForK:
		{
			if(r->begin_label > 0)
				//fprintf(fp, "label%d:\n", r->begin_label);
			if(r->child[0] != NULL)
				gen_code(r->child[0]);

			if(r->true_label > 0)
				fprintf(fp, "label%d:\n", r->true_label);

			if(r->child[1] != NULL)
				gen_code(r->child[1]);
			if(r->child[1] != NULL && r->child[1]->true_label > 0)
				fprintf(fp, "label%d:\n", r->child[1]->true_label);

			gen_code(r->child[3]);
			if(r->child[2] != NULL)
				gen_code(r->child[2]);

			fprintf(fp, "\tjmp label%d\n", r->true_label);
			//if(r->next_label+1 == labeln)
				fprintf(fp, "label%d:\n", r->next_label	);
			break;
		}
		case CompK:
		{
			struct TreeNode* temp;
			int i;
			for(i = 0; r->child[i] != NULL; i++)
			{
				gen_code(r->child[i]);
				for(temp = r->child[i]->sibling; temp != NULL; temp = temp->sibling)
					gen_code(temp);
			}
			break;
		}
		case InputK:
		{
			fprintf(fp, "\tmov eax, sval(input(\"Enter a number : \"))\n");
			fprintf(fp, "\tmov _%s, eax\n", t->child[0]->attr.name);
			break;
		}
		case OutputK:
		{
			fprintf(fp, "\tinvoke crt_printf, addr type1, _%s\n", t->child[0]->attr.name);
			fprintf(fp, "\tinvoke crt_printf, OFFSET newline\n");
			break;
		}
	}
}

void gen_exp_code(struct TreeNode *r)
{
	struct TreeNode* temp;
	int i;
	struct TreeNode *c1;		
	struct TreeNode *c2;
	struct TreeNode *t = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	t = r;

	c1 = r->child[0];
	if(r->child[1]!=NULL)		
		c2 = r->child[1];

	switch(t->kind)
	{
		case OpK:
		{
			if(t->child[0] != NULL && t->child[0]->kind == OpK)
			{
				if(t->child[0]->begin_label > 0)
					fprintf(fp, "label%d:\n", t->child[0]->begin_label);
				gen_code(t->child[0]);
			}
			if(t->child[1] != NULL && t->child[1]->kind == OpK)
			{
				if(t->child[1]->begin_label > 0)
					fprintf(fp, "label%d:\n", t->child[1]->begin_label);
				gen_code(t->child[1]);
			}
			switch(t->attr.op)
			{
				case PLUS:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tadd eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tadd eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tadd eax, t%d\n", c2->tid);
					fprintf(fp, "\tmov t%d, eax\n", r->tid);
					break;
				}
				case SUB:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tsub eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tsub eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tsub eax, t%d\n", c2->tid);
					fprintf(fp, "\tmov t%d, eax\n", r->tid);
					break;
				}
				case MUL:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\timul eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\timul eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\timul eax, t%d\n", c2->tid);
					fprintf(fp, "\tmov t%d, eax\n", r->tid);
					break;
				}
				case DIV:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tdiv eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tdiv eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tdiv eax, t%d\n", c2->tid);
					fprintf(fp, "\tmov t%d, eax\n", r->tid);
					break;
				}
				case MOD:
				{
					fprintf(fp, "\tmov edx, 0\n");
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tmov ecx, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tmov ecx, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tmov ecx, t%d\n", c2->tid);
					fprintf(fp, "\tdiv ecx\n");
					fprintf(fp, "\tmov t%d, edx\n", cur_t);
					break;
				}
				case INC:
				{
					fprintf(fp, "\tinc _%s\n", c1->attr.name);
					break;
				}
				case DEC:
				{
					fprintf(fp, "\tdec _%s\n", c1->attr.name);
					break;
				}
				case B_AND:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tand eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tand eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tand eax, t%d\n", c2->tid);
					fprintf(fp, "\tmov t%d, eax\n", r->tid);
					break;
				}
				case B_OR:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tor eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tor eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tor eax, t%d\n", c2->tid);
					fprintf(fp, "\tmov t%d, eax\n", r->tid);
					break;
				}
				case B_NOT:
				{
					break;
				}
				case B_XOR:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\txor eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\txor eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\txor eax, t%d\n", c2->tid);
					fprintf(fp, "\tmov t%d, eax\n", r->tid);
					break;
				}
				case SHIFT_R:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tshl eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tshl eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tshl eax, t%d\n", c2->tid);
					fprintf(fp, "\tmov t%d, eax\n", r->tid);
					break;
				}
				case SHIFT_L:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tshr eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tshr eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tshr eax, t%d\n", c2->tid);
					fprintf(fp, "\tmov t%d, eax\n", r->tid);
					break;
				}
				case AND:
				{
					//fprintf(fp,"label%d:\n",c2->begin_label);
					break;
				}
				case OR:
				{
					//printf("OR:begin_label c2 %d\n", c2->begin_label);
					//fprintf(fp,"label%d:\n",c2->begin_label);
					break;
				}
				case NOT:
				{
					//fprintf(fp,"label%d:\n",r->begin_label);
					break;
				}
				case EQ:
				{
					//fprintf(fp,"label%d:\n",r->begin_label);
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tcmp eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tcmp eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tcmp eax, t%d\n", c2->tid);
					fprintf(fp, "\tje label%d\n", r->true_label);
					fprintf(fp, "\tjmp label%d\n", r->false_label);
					//fprintf(fp, "label%d:\n", r->true_label);
					break;
				}
				case GREATER:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tcmp eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tcmp eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tcmp eax, t%d\n", c2->tid);
					fprintf(fp, "\tjg label%d\n", r->true_label);
					fprintf(fp, "\tjmp label%d\n", r->false_label);
					//fprintf(fp, "label%d:\n", r->true_label);
					break;
				}
				case LESS:
				{
					//fprintf(fp,"label%d:\n",r->begin_label);
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tcmp eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tcmp eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tcmp eax, t%d\n", c2->tid);
					fprintf(fp, "\tjl label%d\n", r->true_label);
					fprintf(fp, "\tjmp label%d\n", r->false_label);
					//fprintf(fp, "label%d:\n", r->true_label);
					break;
				}
				case G_EQ:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tcmp eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tcmp eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tcmp eax, t%d\n", c2->tid);
					fprintf(fp, "\tjge label%d\n", r->true_label);
					fprintf(fp, "\tjmp label%d\n", r->false_label);
					//fprintf(fp, "label%d:\n", r->true_label);
					break;
				}
				case L_EQ:
				{
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tcmp eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tcmp eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tcmp eax, t%d\n", c2->tid);
					fprintf(fp, "\tjle label%d\n", r->true_label);
					fprintf(fp, "\tjmp label%d\n", r->false_label);
					//fprintf(fp, "label%d:\n", r->true_label);
					break;
				}
				case NEQ:
				{
					//fprintf(fp,"label%d:\n",r->begin_label);
					if(c1->kind == ConstK)
						fprintf(fp, "\tmov eax, %d\n", c1->attr.val);
					else if(c1->kind == IdK)
						fprintf(fp, "\tmov eax, _%s\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov eax, t%d\n", c1->tid);
					if(c2->kind == ConstK)
						fprintf(fp, "\tcmp eax, %d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "\tcmp eax, _%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "\tcmp eax, t%d\n", c2->tid);
					fprintf(fp, "\tjne label%d\n", r->true_label);
					fprintf(fp, "\tjmp label%d\n", r->false_label);
					//fprintf(fp, "label%d:\n", r->true_label);
					break;
				}
				case ASSIGN:
				{
					fprintf(fp, "\tmov eax, ");
					
					if(c2->kind == ConstK)
						fprintf(fp, "%d\n", c2->attr.val);
					else if(c2->kind == IdK)
						fprintf(fp, "_%s\n", c2->attr.name);
					else if(c2->kind == OpK)
						fprintf(fp, "t%d\n", c2->tid);

					if(c1->kind == IdK)
						fprintf(fp, "\tmov _%s, eax\n", c1->attr.name);
					else if(c1->kind == OpK)
						fprintf(fp, "\tmov t%d, eax\n", c1->tid);
					break;
				}
			}
			break;
		}
		case ConstK:
		{
			//fprintf(fp, "\tmov eax, %d\n", t->attr.val);
			break;
		}
		case IdK:
		{
			//fprintf(fp, "\tmov eax, _%s\n", t->attr.name);
			break;
		}
		case TypeK:
		{
			break;
		}
	}
}

void get_label(struct TreeNode *p)
{
	struct TreeNode* temp;
	int i;
	if(p == NULL)
		return;
	for(i = 0; p->child[i] != NULL; i++)
		get_label(p->child[i]);
		
	if (p->nodekind == StmtK)
		get_stmt_label(p);

	else if (p->nodekind == ExpK)
		get_expr_label(p);		
	
	temp = p->sibling;
	if(temp!=NULL)
    	get_label(temp);
	return;	
}

void get_expr_label(struct TreeNode *t)
{
	struct TreeNode *e1;		
	struct TreeNode *e2;
	if (t->type != Bool)	
		return;
	e1 = t->child[0];		
	e2 = t->child[1];	
	switch (t->attr.op)
	{
		
		case AND:
			e1->true_label = labeln++;
			e2->begin_label = e1->true_label;
			e2->true_label = t->true_label;  
			e1->false_label = e2->false_label = t->false_label;  
		break;		
		case OR:
			e1->false_label = labeln++;
			e2->begin_label = e1->false_label;
			e2->false_label = t->false_label;
			e1->true_label = e2->true_label = t->true_label;
		break;
		case NOT:
			e1->true_label = t->false_label;
			e1->false_label = t->true_label;
		break;

	}
	if (e1)  
		get_label(e1);
	if (e2)  
		get_label(e2);
}

void get_stmt_label(struct TreeNode *t)
{
	struct TreeNode *e;		
	struct TreeNode *s;
	struct TreeNode *s1;		
	struct TreeNode *s2 ;
	switch (t->kind)
	{ 
	case IfK:
    {
		if(t->child[2]==NULL){
			e = t->child[0];	
			s = t->child[1];
			if (t->begin_label <= 0)
				t->begin_label = labeln++;
			s->begin_label = e->true_label = labeln++;  		
			if (t->next_label <=0)
				t->next_label = labeln++;	
			s->next_label =e->false_label = t->next_label;
			if (t->sibling)
				t->sibling->begin_label = t->next_label;  
			get_label(e);		
			get_label(s);
		}
		else if(t->child[2]!=NULL){
			e = t->child[0];	
			s1 = t->child[1];
			s2 = t->child[2];
			if (t->begin_label <= 0)
				t->begin_label = labeln++;
			s1->begin_label = e->true_label = labeln++; 
			s2->begin_label = e->false_label = labeln++;
			if (t->next_label<=0)
				t->next_label = labeln++;	 
			s1->next_label = s2->next_label = t->next_label;
			if (t->sibling)
				t->sibling->begin_label = t->next_label;  
			get_label(e);		
			get_label(s1);
			get_label(s2);
		}
		break;
    }
    case WhileK:
    {
		e = t->child[0];	
		s = t->child[1];
		if (t->begin_label <= 0)
			t->begin_label = labeln++;
		s->next_label = t->begin_label;	
		s->begin_label = e->true_label = labeln++; 
		if (t->next_label <=0)
			t->next_label = labeln++;		
		e->false_label = t->next_label;	
		if (t->sibling)
			t->sibling->begin_label = t->next_label;  
		get_label(e);		
		get_label(s);
		break;
    }
    case ForK:
    {
		e = t->child[1];	
		s = t->child[3];
		
		if (t->begin_label<=0)
			t->begin_label = labeln++;
		if (t->true_label<=0)
			t->true_label = labeln++;
		if(e->true_label<=0)
			e->true_label = labeln++;				
		s->next_label = t->true_label;	
		s->begin_label = e->true_label;  
	
		if (t->next_label <= 0)
			t->next_label = labeln++;		
		e->false_label = t->next_label;	
		if (t->sibling)
			t->sibling->begin_label = t->next_label;  
		get_label(e);		
		get_label(s);
		break;
    }
    
  }
}


int main(void)
{
	int i;
	struct TreeNode *r = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	
	yyin = fopen("test6.txt","r");
	fp = fopen("output.txt","w+");
	
	yyparse();
	
	r = root;	
	gen_asm(r);
	
	printf("\n---------symbol table------------\n");
	for(i = 0; i < 1000; i++)
	{
		if(table[i].id_type != NULL)
		{
			//printf("****************************\n");
			printf("id:%s\t", table[i].id);
			printf("\ttype:%c\n", table[i].id_type);
		}
	}
	
	
	return 0;
	
}
