/****************************************************************************
* myparser.c
* C source file generated from myparser.y.
* 
* Date: 12/19/19
* Time: 00:00:22
* 
* AYACC Version: 2.07
****************************************************************************/

#include <yypars.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTPARSER

#line 1 ".\\myparser.y"

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

#line 196 "myparser.c"
/* repeated because of possible precompiled header */
#include <yypars.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTPARSER

#include ".\myparser.h"

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYSTACK_SIZE
#define YYSTACK_SIZE 100
#endif
#ifndef YYSTACK_MAX
#define YYSTACK_MAX 0
#endif

/* (state) stack */
#if (YYSTACK_SIZE) != 0
static yystack_t YYNEAR yystack[(YYSTACK_SIZE)];
yystack_t YYFAR *YYNEAR YYDCDECL yysstackptr = yystack;
yystack_t YYFAR *YYNEAR YYDCDECL yystackptr = yystack;
#else
yystack_t YYFAR *YYNEAR YYDCDECL yysstackptr = NULL;
yystack_t YYFAR *YYNEAR YYDCDECL yystackptr = NULL;
#endif

/* attribute stack */
#if (YYSTACK_SIZE) != 0
static YYSTYPE YYNEAR yyattributestack[(YYSTACK_SIZE)];
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yysattributestackptr = yyattributestack;
void YYFAR *YYNEAR YYDCDECL yyattributestackptr = yyattributestack;
#else
char YYFAR *YYNEAR YYDCDECL yysattributestackptr = (char YYFAR *) yyattributestack;
char YYFAR *YYNEAR YYDCDECL yyattributestackptr = (char YYFAR *) yyattributestack;
#endif
#else
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yysattributestackptr = NULL;
void YYFAR *YYNEAR YYDCDECL yyattributestackptr = NULL;
#else
char YYFAR *YYNEAR YYDCDECL yysattributestackptr = NULL;
char YYFAR *YYNEAR YYDCDECL yyattributestackptr = NULL;
#endif
#endif

int YYNEAR YYDCDECL yysstack_size = (YYSTACK_SIZE);
int YYNEAR YYDCDECL yystack_size = (YYSTACK_SIZE);
int YYNEAR YYDCDECL yystack_max = (YYSTACK_MAX);

/* attributes */
YYSTYPE YYNEAR yyval;
YYSTYPE YYNEAR yylval;
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yyvalptr = &yyval;
void YYFAR *YYNEAR YYDCDECL yylvalptr = &yylval;
#else
char YYFAR *YYNEAR YYDCDECL yyvalptr = (char *) &yyval;
char YYFAR *YYNEAR YYDCDECL yylvalptr = (char *) &yylval;
#endif

size_t YYNEAR YYDCDECL yyattribute_size = sizeof(YYSTYPE);

/* yyattribute */
#ifdef YYDEBUG
#ifdef YYPROTOTYPE
static YYSTYPE YYFAR *yyattribute1(int index)
#else
static YYSTYPE YYFAR *yyattribute1(index)
int index;
#endif
{
	YYSTYPE YYFAR *p = &((YYSTYPE YYFAR *) yyattributestackptr)[yytop + index];
	return p;
}
#define yyattribute(index) (*yyattribute1(index))
#else
#define yyattribute(index) (((YYSTYPE YYFAR *) yyattributestackptr)[yytop + (index)])
#endif

#ifdef YYDEBUG
#ifdef YYPROTOTYPE
static void yyinitdebug(YYSTYPE YYFAR **p, int count)
#else
static void yyinitdebug(p, count)
YYSTYPE YYFAR **p;
int count;
#endif
{
	int i;
	yyassert(p != NULL);
	yyassert(count >= 1);

	for (i = 0; i < count; i++) {
		p[i] = &((YYSTYPE YYFAR *) yyattributestackptr)[yytop + i - (count - 1)];
	}
}
#endif

#ifdef YYPROTOTYPE
void YYCDECL yyparseraction(int action)
#else
void YYCDECL yyparseraction(action)
int action;
#endif
{
	switch (action) {
	case 0:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 202 ".\\myparser.y"

				yyval = yyattribute(4 - 4);
				Display(yyattribute(4 - 4));
				root  = yyattribute(4 - 4);
			
#line 326 "myparser.c"
			}
		}
		break;
	case 1:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 209 ".\\myparser.y"

				yyval = newStmtNode(CompK);
				yyval->child[0] = yyattribute(2 - 3);
				yyval->type = Void;
			
#line 343 "myparser.c"
			}
		}
		break;
	case 2:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 216 ".\\myparser.y"

				yyval->sibling = yyattribute(2 - 2);
				yyval = yyattribute(1 - 2);
			
#line 359 "myparser.c"
			}
		}
		break;
	case 3:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 221 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 374 "myparser.c"
			}
		}
		break;
	case 4:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 226 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 389 "myparser.c"
			}
		}
		break;
	case 5:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 230 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 404 "myparser.c"
			}
		}
		break;
	case 6:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 234 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 419 "myparser.c"
			}
		}
		break;
	case 7:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 238 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 434 "myparser.c"
			}
		}
		break;
	case 8:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 242 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 449 "myparser.c"
			}
		}
		break;
	case 9:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 246 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 464 "myparser.c"
			}
		}
		break;
	case 10:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 250 ".\\myparser.y"

				yyval = yyattribute(1 - 2);
			
#line 479 "myparser.c"
			}
		}
		break;
	case 11:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 254 ".\\myparser.y"

				yyval = yyattribute(1 - 2);
			
#line 494 "myparser.c"
			}
		}
		break;
	case 12:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 258 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 509 "myparser.c"
			}
		}
		break;
	case 13:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 263 ".\\myparser.y"

				yyval = newStmtNode(NullK);
				yyval->type = Void;
			
#line 525 "myparser.c"
			}
		}
		break;
	case 14:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 269 ".\\myparser.y"

				yyval = newExpNode(TypeK);
				yyval->type = Integer;
			
#line 541 "myparser.c"
			}
		}
		break;
	case 15:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 274 ".\\myparser.y"

				yyval = newExpNode(TypeK);
				yyval->type = Char;
			
#line 557 "myparser.c"
			}
		}
		break;
	case 16:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 280 ".\\myparser.y"

				yyval = yyattribute(1 - 3);
				yyval->sibling = yyattribute(3 - 3);
			
#line 573 "myparser.c"
			}
		}
		break;
	case 17:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 285 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 588 "myparser.c"
			}
		}
		break;
	case 18:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 290 ".\\myparser.y"

				char *type1[3] = {"Integer", "Char", "Void"};
				struct TreeNode * temp = (struct TreeNode*) malloc(sizeof(struct TreeNode));
				struct symbol * sym = (struct symbol*) malloc(sizeof(struct symbol));
				char typeDec;
				yyval = newDeclNode(VarK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[2] = yyattribute(2 - 3);
				yyval->child[2]->type = yyattribute(1 - 3)->type;
				temp = yyval->child[2]->sibling;
				if(type1[yyattribute(1 - 3)->type] == "Integer")
					typeDec = 'I';
				else if(type1[yyattribute(1 - 3)->type] == "Char")
					typeDec = 'C';
				while(temp != NULL)
				{
					temp->type = yyattribute(1 - 3)->type;
					sym = newSymbolItem(temp->attr.name, typeDec);
					table[temp->index] = *sym;
					temp = temp->sibling;
				}
				sym = newSymbolItem(yyval->child[2]->attr.name, typeDec);
				table[yyval->child[2]->index] = *sym;
				yyval->type = Void;
			
#line 625 "myparser.c"
			}
		}
		break;
	case 19:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 317 ".\\myparser.y"

				yyval = newStmtNode(InputK);
				yyval->child[0] = yyattribute(3 - 4);
				yyval->type = Void;
			
#line 642 "myparser.c"
			}
		}
		break;
	case 20:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 324 ".\\myparser.y"

				yyval = newStmtNode(OutputK);
				yyval->child[0] = yyattribute(3 - 4);
				yyval->type = Void;
			
#line 659 "myparser.c"
			}
		}
		break;
	case 21:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[6];
			yyinitdebug(yya, 6);
#endif
			{
#line 331 ".\\myparser.y"

				yyval = newStmtNode(IfK);
				yyval->child[0] = yyattribute(3 - 5);
				yyval->child[1] = yyattribute(5 - 5);
				yyval->type = Void;
			
#line 677 "myparser.c"
			}
		}
		break;
	case 22:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[8];
			yyinitdebug(yya, 8);
#endif
			{
#line 338 ".\\myparser.y"

				yyval = newStmtNode(IfK);
				yyval->child[0] = yyattribute(3 - 7);
				yyval->child[1] = yyattribute(5 - 7);
				yyval->child[2] = yyattribute(7 - 7);
				yyval->type = Void;
			
#line 696 "myparser.c"
			}
		}
		break;
	case 23:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[10];
			yyinitdebug(yya, 10);
#endif
			{
#line 347 ".\\myparser.y"

				yyval = newStmtNode(ForK);
				yyval->child[0] = yyattribute(3 - 9);
				yyval->child[1] = yyattribute(5 - 9);
				yyval->child[2] = yyattribute(7 - 9);
				yyval->child[3] = yyattribute(9 - 9);
				yyval->type = Void;
			
#line 716 "myparser.c"
			}
		}
		break;
	case 24:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[9];
			yyinitdebug(yya, 9);
#endif
			{
#line 356 ".\\myparser.y"

				yyval = newStmtNode(ForK);
				yyval->child[0] = NULL;
				yyval->child[1] = yyattribute(4 - 8);
                yyval->child[2] = yyattribute(6 - 8);
                yyval->child[3] = yyattribute(8 - 8);
                yyval->type = Void;
			
#line 736 "myparser.c"
			}
		}
		break;
	case 25:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[9];
			yyinitdebug(yya, 9);
#endif
			{
#line 365 ".\\myparser.y"

				yyval = newStmtNode(ForK);
				yyval->child[0] = yyattribute(3 - 8);
				yyval->child[1] = NULL;
                yyval->child[2] = yyattribute(6 - 8);
                yyval->child[3] = yyattribute(8 - 8);
                yyval->type = Void;
			
#line 756 "myparser.c"
			}
		}
		break;
	case 26:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[9];
			yyinitdebug(yya, 9);
#endif
			{
#line 374 ".\\myparser.y"

				yyval = newStmtNode(ForK);
				yyval->child[0] = yyattribute(3 - 8);
				yyval->child[1] = yyattribute(5 - 8);
                yyval->child[2] = NULL;
                yyval->child[3] = yyattribute(8 - 8);
                yyval->type = Void;
			
#line 776 "myparser.c"
			}
		}
		break;
	case 27:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[8];
			yyinitdebug(yya, 8);
#endif
			{
#line 383 ".\\myparser.y"

				yyval = newStmtNode(ForK);
				yyval->child[0] = NULL;
				yyval->child[1] = NULL;
                yyval->child[2] = yyattribute(5 - 7);
                yyval->child[3] = yyattribute(7 - 7);
                yyval->type = Void;
			
#line 796 "myparser.c"
			}
		}
		break;
	case 28:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[8];
			yyinitdebug(yya, 8);
#endif
			{
#line 392 ".\\myparser.y"

				yyval = newStmtNode(ForK);
				yyval->child[0] = NULL;
				yyval->child[1] = yyattribute(4 - 7);
                yyval->child[2] = NULL;
                yyval->child[3] = yyattribute(7 - 7);
                yyval->type = Void;
			
#line 816 "myparser.c"
			}
		}
		break;
	case 29:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[8];
			yyinitdebug(yya, 8);
#endif
			{
#line 401 ".\\myparser.y"

				yyval = newStmtNode(ForK);
				yyval->child[0] = yyattribute(3 - 7);
				yyval->child[1] = NULL;
                yyval->child[2] = NULL;
                yyval->child[3] = yyattribute(7 - 7);
                yyval->type = Void;
			
#line 836 "myparser.c"
			}
		}
		break;
	case 30:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[7];
			yyinitdebug(yya, 7);
#endif
			{
#line 410 ".\\myparser.y"

				yyval = newStmtNode(ForK);
				yyval->child[0] = NULL;
				yyval->child[1] = NULL;
                yyval->child[2] = NULL;
                yyval->child[3] = yyattribute(6 - 6);
                yyval->type = Void;
			
#line 856 "myparser.c"
			}
		}
		break;
	case 31:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[6];
			yyinitdebug(yya, 6);
#endif
			{
#line 420 ".\\myparser.y"

				yyval = newStmtNode(WhileK);
				yyval->child[0] = yyattribute(3 - 5);
				yyval->child[1] = yyattribute(5 - 5);
				yyval->type = Void;
			
#line 874 "myparser.c"
			}
		}
		break;
	case 32:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 428 ".\\myparser.y"

				yyval = yyattribute(1 - 2);
			
#line 889 "myparser.c"
			}
		}
		break;
	case 33:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 433 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = ASSIGN;
				yyval->type = Void;
			
#line 908 "myparser.c"
			}
		}
		break;
	case 34:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 441 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 923 "myparser.c"
			}
		}
		break;
	case 35:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 446 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = OR;
				yyval->type = Void;
				get_temp_var(yyval);
			
#line 943 "myparser.c"
			}
		}
		break;
	case 36:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 455 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 958 "myparser.c"
			}
		}
		break;
	case 37:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 460 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = AND;
				yyval->type = Void;
				get_temp_var(yyval);
			
#line 978 "myparser.c"
			}
		}
		break;
	case 38:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 469 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 993 "myparser.c"
			}
		}
		break;
	case 39:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 474 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = EQ;
				yyval->type = Void;
				get_temp_var(yyval);
			
#line 1013 "myparser.c"
			}
		}
		break;
	case 40:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 483 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = GREATER;
				yyval->type = Void;
				get_temp_var(yyval);
			
#line 1033 "myparser.c"
			}
		}
		break;
	case 41:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 492 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = LESS;
				yyval->type = Void;
				get_temp_var(yyval);
			
#line 1053 "myparser.c"
			}
		}
		break;
	case 42:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 501 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = G_EQ;
				yyval->type = Void;
				get_temp_var(yyval);
			
#line 1073 "myparser.c"
			}
		}
		break;
	case 43:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 510 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = L_EQ;
				yyval->type = Void;
				get_temp_var(yyval);
			
#line 1093 "myparser.c"
			}
		}
		break;
	case 44:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 519 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = NEQ;
				yyval->type = Void;
				get_temp_var(yyval);
			
#line 1113 "myparser.c"
			}
		}
		break;
	case 45:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 528 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 1128 "myparser.c"
			}
		}
		break;
	case 46:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 533 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = PLUS;
				yyval->type = Void;
				get_temp_var(yyval);
			
#line 1148 "myparser.c"
			}
		}
		break;
	case 47:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 542 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = SUB;
				yyval->type = Void;
				get_temp_var(yyval);
			
#line 1168 "myparser.c"
			}
		}
		break;
	case 48:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 551 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 1183 "myparser.c"
			}
		}
		break;
	case 49:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 556 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = MUL;
				yyval->type = Integer;
				get_temp_var(yyval);
			
#line 1203 "myparser.c"
			}
		}
		break;
	case 50:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 565 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = DIV;
				yyval->type = Integer;
				get_temp_var(yyval);
			
#line 1223 "myparser.c"
			}
		}
		break;
	case 51:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 574 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = MOD;
				yyval->type = Integer;
				get_temp_var(yyval);
			
#line 1243 "myparser.c"
			}
		}
		break;
	case 52:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 583 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = B_AND;
				yyval->type = Integer;
				get_temp_var(yyval);
			
#line 1263 "myparser.c"
			}
		}
		break;
	case 53:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 592 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = B_OR;
				yyval->type = Integer;
				get_temp_var(yyval);
			
#line 1283 "myparser.c"
			}
		}
		break;
	case 54:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 601 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = B_XOR;
				yyval->type = Integer;
				get_temp_var(yyval);
			
#line 1303 "myparser.c"
			}
		}
		break;
	case 55:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 610 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 2);
				yyval->attr.op = INC;
				yyval->type = Integer;
			
#line 1321 "myparser.c"
			}
		}
		break;
	case 56:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 617 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 2);
				yyval->attr.op = DEC;
				yyval->type = Integer;
			
#line 1339 "myparser.c"
			}
		}
		break;
	case 57:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 624 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = SHIFT_L;
				yyval->type = Integer;
				get_temp_var(yyval);
			
#line 1359 "myparser.c"
			}
		}
		break;
	case 58:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 633 ".\\myparser.y"

				yyval = newExpNode(OpK);
				yyval->child[0] = yyattribute(1 - 3);
				yyval->child[1] = yyattribute(3 - 3);
				yyval->attr.op = SHIFT_R;
				yyval->type = Integer;
				get_temp_var(yyval);
			
#line 1379 "myparser.c"
			}
		}
		break;
	case 59:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 642 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 1394 "myparser.c"
			}
		}
		break;
	case 60:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 647 ".\\myparser.y"

				yyval = yyattribute(2 - 3);
			
#line 1409 "myparser.c"
			}
		}
		break;
	case 61:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 651 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 1424 "myparser.c"
			}
		}
		break;
	case 62:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 655 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 1439 "myparser.c"
			}
		}
		break;
	case 63:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 659 ".\\myparser.y"

			   yyval = newExpNode(OpK);
			   yyval -> attr.op = NOT;
			   yyval -> child[0] =yyattribute(2 - 2);
			   yyval->type = Void;
			
#line 1457 "myparser.c"
			}
		}
		break;
	case 64:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 666 ".\\myparser.y"

			   yyval = newExpNode(OpK);
			   yyval -> attr.op = B_NOT;
			   yyval -> child[0] =yyattribute(2 - 2);
			   yyval->type = Void;
			
#line 1475 "myparser.c"
			}
		}
		break;
	case 65:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 673 ".\\myparser.y"

				yyval = yyattribute(1 - 1);
			
#line 1490 "myparser.c"
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}
#ifdef YYDEBUG
YYCONST yysymbol_t YYNEARFAR YYBASED_CODE YYDCDECL yysymbol[] = {
	{ "$end", 0 },
	{ "error", 256 },
	{ "MAIN", 257 },
	{ "IF", 258 },
	{ "WHILE", 259 },
	{ "FOR", 260 },
	{ "INPUT", 262 },
	{ "OUTPUT", 263 },
	{ "INT", 264 },
	{ "CHAR", 265 },
	{ "ASSIGN", 266 },
	{ "ID", 267 },
	{ "NUMBER", 268 },
	{ "CHARACTER", 269 },
	{ "PLUS", 270 },
	{ "SUB", 271 },
	{ "MUL", 272 },
	{ "DIV", 273 },
	{ "MOD", 274 },
	{ "INC", 275 },
	{ "DEC", 276 },
	{ "B_AND", 277 },
	{ "B_OR", 278 },
	{ "B_NOT", 279 },
	{ "B_XOR", 280 },
	{ "SHIFT_L", 281 },
	{ "SHIFT_R", 282 },
	{ "AND", 283 },
	{ "OR", 284 },
	{ "NOT", 285 },
	{ "EQ", 286 },
	{ "GREATER", 287 },
	{ "LESS", 288 },
	{ "G_EQ", 289 },
	{ "L_EQ", 290 },
	{ "NEQ", 291 },
	{ "SEMICOLON", 292 },
	{ "LPAREN", 293 },
	{ "RPAREN", 294 },
	{ "LBRACE", 295 },
	{ "RBRACE", 296 },
	{ "COMMA", 297 },
	{ "ELSE", 298 },
	{ NULL, 0 }
};

YYCONST char *YYCONST YYNEARFAR YYBASED_CODE YYDCDECL yyrule[] = {
	"$accept: start",
	"start: MAIN LPAREN RPAREN compStmt",
	"compStmt: LBRACE stmtList RBRACE",
	"stmtList: stmt stmtList",
	"stmtList: stmt",
	"stmt: decStmt",
	"stmt: exprStmt",
	"stmt: ifStmt",
	"stmt: whileStmt",
	"stmt: forStmt",
	"stmt: compStmt",
	"stmt: inputStmt SEMICOLON",
	"stmt: outputStmt SEMICOLON",
	"stmt: nullStmt",
	"nullStmt: SEMICOLON",
	"typeDecp: INT",
	"typeDecp: CHAR",
	"idList: expr COMMA idList",
	"idList: expr",
	"decStmt: typeDecp idList SEMICOLON",
	"inputStmt: INPUT LPAREN expr RPAREN",
	"outputStmt: OUTPUT LPAREN expr RPAREN",
	"ifStmt: IF LPAREN expr RPAREN stmt",
	"ifStmt: IF LPAREN expr RPAREN stmt ELSE stmt",
	"forStmt: FOR LPAREN expr SEMICOLON expr SEMICOLON expr RPAREN stmt",
	"forStmt: FOR LPAREN SEMICOLON expr SEMICOLON expr RPAREN stmt",
	"forStmt: FOR LPAREN expr SEMICOLON SEMICOLON expr RPAREN stmt",
	"forStmt: FOR LPAREN expr SEMICOLON expr SEMICOLON RPAREN stmt",
	"forStmt: FOR LPAREN SEMICOLON SEMICOLON expr RPAREN stmt",
	"forStmt: FOR LPAREN SEMICOLON expr SEMICOLON RPAREN stmt",
	"forStmt: FOR LPAREN expr SEMICOLON SEMICOLON RPAREN stmt",
	"forStmt: FOR LPAREN SEMICOLON SEMICOLON RPAREN stmt",
	"whileStmt: WHILE LPAREN expr RPAREN stmt",
	"exprStmt: expr SEMICOLON",
	"expr: expr ASSIGN expr",
	"expr: orExpr",
	"orExpr: orExpr OR andExpr",
	"orExpr: andExpr",
	"andExpr: andExpr AND eqExpr",
	"andExpr: eqExpr",
	"eqExpr: eqExpr EQ simpleExpr",
	"eqExpr: eqExpr GREATER simpleExpr",
	"eqExpr: eqExpr LESS simpleExpr",
	"eqExpr: eqExpr G_EQ simpleExpr",
	"eqExpr: eqExpr L_EQ simpleExpr",
	"eqExpr: eqExpr NEQ simpleExpr",
	"eqExpr: simpleExpr",
	"simpleExpr: simpleExpr PLUS factor",
	"simpleExpr: simpleExpr SUB factor",
	"simpleExpr: factor",
	"factor: factor MUL term",
	"factor: factor DIV term",
	"factor: factor MOD term",
	"factor: factor B_AND term",
	"factor: factor B_OR term",
	"factor: factor B_XOR term",
	"factor: factor INC",
	"factor: factor DEC",
	"factor: factor SHIFT_L term",
	"factor: factor SHIFT_R term",
	"factor: term",
	"term: LPAREN expr RPAREN",
	"term: ID",
	"term: NUMBER",
	"term: NOT term",
	"term: B_NOT term",
	"term: CHARACTER"
};
#endif

YYCONST yyreduction_t YYNEARFAR YYBASED_CODE YYDCDECL yyreduction[] = {
	{ 0, 1, -1 },
	{ 1, 4, 0 },
	{ 2, 3, 1 },
	{ 3, 2, 2 },
	{ 3, 1, 3 },
	{ 4, 1, 4 },
	{ 4, 1, 5 },
	{ 4, 1, 6 },
	{ 4, 1, 7 },
	{ 4, 1, 8 },
	{ 4, 1, 9 },
	{ 4, 2, 10 },
	{ 4, 2, 11 },
	{ 4, 1, 12 },
	{ 5, 1, 13 },
	{ 6, 1, 14 },
	{ 6, 1, 15 },
	{ 7, 3, 16 },
	{ 7, 1, 17 },
	{ 8, 3, 18 },
	{ 9, 4, 19 },
	{ 10, 4, 20 },
	{ 11, 5, 21 },
	{ 11, 7, 22 },
	{ 12, 9, 23 },
	{ 12, 8, 24 },
	{ 12, 8, 25 },
	{ 12, 8, 26 },
	{ 12, 7, 27 },
	{ 12, 7, 28 },
	{ 12, 7, 29 },
	{ 12, 6, 30 },
	{ 13, 5, 31 },
	{ 14, 2, 32 },
	{ 15, 3, 33 },
	{ 15, 1, 34 },
	{ 16, 3, 35 },
	{ 16, 1, 36 },
	{ 17, 3, 37 },
	{ 17, 1, 38 },
	{ 18, 3, 39 },
	{ 18, 3, 40 },
	{ 18, 3, 41 },
	{ 18, 3, 42 },
	{ 18, 3, 43 },
	{ 18, 3, 44 },
	{ 18, 1, 45 },
	{ 19, 3, 46 },
	{ 19, 3, 47 },
	{ 19, 1, 48 },
	{ 20, 3, 49 },
	{ 20, 3, 50 },
	{ 20, 3, 51 },
	{ 20, 3, 52 },
	{ 20, 3, 53 },
	{ 20, 3, 54 },
	{ 20, 2, 55 },
	{ 20, 2, 56 },
	{ 20, 3, 57 },
	{ 20, 3, 58 },
	{ 20, 1, 59 },
	{ 21, 3, 60 },
	{ 21, 1, 61 },
	{ 21, 1, 62 },
	{ 21, 2, 63 },
	{ 21, 2, 64 },
	{ 21, 1, 65 }
};

int YYNEAR YYDCDECL yytokenaction_size = 130;
YYCONST yytokenaction_t YYNEARFAR YYBASED_CODE YYDCDECL yytokenaction[] = {
	{ 29, YYAT_SHIFT, 7 },
	{ 29, YYAT_SHIFT, 8 },
	{ 29, YYAT_SHIFT, 9 },
	{ 134, YYAT_SHIFT, 74 },
	{ 29, YYAT_SHIFT, 10 },
	{ 29, YYAT_SHIFT, 11 },
	{ 29, YYAT_SHIFT, 12 },
	{ 29, YYAT_SHIFT, 13 },
	{ 63, YYAT_SHIFT, 74 },
	{ 29, YYAT_SHIFT, 14 },
	{ 29, YYAT_SHIFT, 15 },
	{ 29, YYAT_SHIFT, 16 },
	{ 138, YYAT_SHIFT, 7 },
	{ 138, YYAT_SHIFT, 8 },
	{ 138, YYAT_SHIFT, 9 },
	{ 118, YYAT_SHIFT, 74 },
	{ 138, YYAT_SHIFT, 10 },
	{ 138, YYAT_SHIFT, 11 },
	{ 138, YYAT_SHIFT, 12 },
	{ 138, YYAT_SHIFT, 13 },
	{ 125, YYAT_SHIFT, 132 },
	{ 29, YYAT_SHIFT, 17 },
	{ 101, YYAT_SHIFT, 65 },
	{ 101, YYAT_SHIFT, 66 },
	{ 100, YYAT_SHIFT, 65 },
	{ 100, YYAT_SHIFT, 66 },
	{ 123, YYAT_SHIFT, 130 },
	{ 29, YYAT_SHIFT, 18 },
	{ 99, YYAT_SHIFT, 65 },
	{ 99, YYAT_SHIFT, 66 },
	{ 117, YYAT_SHIFT, 124 },
	{ 134, YYAT_SHIFT, 138 },
	{ 98, YYAT_SHIFT, 65 },
	{ 98, YYAT_SHIFT, 66 },
	{ 29, YYAT_SHIFT, 19 },
	{ 29, YYAT_SHIFT, 20 },
	{ 116, YYAT_SHIFT, 122 },
	{ 29, YYAT_SHIFT, 5 },
	{ 115, YYAT_SHIFT, 121 },
	{ 63, YYAT_SHIFT, 92 },
	{ 112, YYAT_SHIFT, 119 },
	{ 118, YYAT_SHIFT, 126 },
	{ 97, YYAT_SHIFT, 65 },
	{ 97, YYAT_SHIFT, 66 },
	{ 96, YYAT_SHIFT, 65 },
	{ 96, YYAT_SHIFT, 66 },
	{ 138, YYAT_SHIFT, 19 },
	{ 36, YYAT_SHIFT, 65 },
	{ 36, YYAT_SHIFT, 66 },
	{ 138, YYAT_SHIFT, 5 },
	{ 95, YYAT_SHIFT, 52 },
	{ 95, YYAT_SHIFT, 53 },
	{ 95, YYAT_SHIFT, 54 },
	{ 95, YYAT_SHIFT, 55 },
	{ 95, YYAT_SHIFT, 56 },
	{ 95, YYAT_SHIFT, 57 },
	{ 95, YYAT_SHIFT, 58 },
	{ 108, YYAT_SHIFT, 117 },
	{ 95, YYAT_SHIFT, 59 },
	{ 95, YYAT_SHIFT, 60 },
	{ 95, YYAT_SHIFT, 61 },
	{ 94, YYAT_SHIFT, 52 },
	{ 94, YYAT_SHIFT, 53 },
	{ 94, YYAT_SHIFT, 54 },
	{ 94, YYAT_SHIFT, 55 },
	{ 94, YYAT_SHIFT, 56 },
	{ 94, YYAT_SHIFT, 57 },
	{ 94, YYAT_SHIFT, 58 },
	{ 107, YYAT_SHIFT, 116 },
	{ 94, YYAT_SHIFT, 59 },
	{ 94, YYAT_SHIFT, 60 },
	{ 94, YYAT_SHIFT, 61 },
	{ 33, YYAT_SHIFT, 52 },
	{ 33, YYAT_SHIFT, 53 },
	{ 33, YYAT_SHIFT, 54 },
	{ 33, YYAT_SHIFT, 55 },
	{ 33, YYAT_SHIFT, 56 },
	{ 33, YYAT_SHIFT, 57 },
	{ 33, YYAT_SHIFT, 58 },
	{ 106, YYAT_SHIFT, 114 },
	{ 33, YYAT_SHIFT, 59 },
	{ 33, YYAT_SHIFT, 60 },
	{ 33, YYAT_SHIFT, 61 },
	{ 126, YYAT_SHIFT, 14 },
	{ 126, YYAT_SHIFT, 15 },
	{ 126, YYAT_SHIFT, 16 },
	{ 93, YYAT_SHIFT, 67 },
	{ 93, YYAT_SHIFT, 68 },
	{ 93, YYAT_SHIFT, 69 },
	{ 93, YYAT_SHIFT, 70 },
	{ 93, YYAT_SHIFT, 71 },
	{ 93, YYAT_SHIFT, 72 },
	{ 103, YYAT_SHIFT, 74 },
	{ 102, YYAT_SHIFT, 64 },
	{ 92, YYAT_ERROR, 0 },
	{ 126, YYAT_SHIFT, 17 },
	{ 81, YYAT_SHIFT, 110 },
	{ 80, YYAT_SHIFT, 109 },
	{ 79, YYAT_SHIFT, 108 },
	{ 78, YYAT_SHIFT, 106 },
	{ 77, YYAT_SHIFT, 105 },
	{ 126, YYAT_SHIFT, 18 },
	{ 37, YYAT_SHIFT, 67 },
	{ 37, YYAT_SHIFT, 68 },
	{ 37, YYAT_SHIFT, 69 },
	{ 37, YYAT_SHIFT, 70 },
	{ 37, YYAT_SHIFT, 71 },
	{ 37, YYAT_SHIFT, 72 },
	{ 76, YYAT_SHIFT, 104 },
	{ 126, YYAT_SHIFT, 20 },
	{ 126, YYAT_SHIFT, 133 },
	{ 62, YYAT_SHIFT, 91 },
	{ 47, YYAT_SHIFT, 82 },
	{ 42, YYAT_SHIFT, 78 },
	{ 39, YYAT_SHIFT, 75 },
	{ 38, YYAT_SHIFT, 73 },
	{ 35, YYAT_SHIFT, 64 },
	{ 27, YYAT_SHIFT, 50 },
	{ 26, YYAT_SHIFT, 49 },
	{ 23, YYAT_SHIFT, 48 },
	{ 11, YYAT_SHIFT, 44 },
	{ 10, YYAT_SHIFT, 43 },
	{ 9, YYAT_SHIFT, 42 },
	{ 8, YYAT_SHIFT, 41 },
	{ 7, YYAT_SHIFT, 40 },
	{ 4, YYAT_SHIFT, 5 },
	{ 3, YYAT_SHIFT, 4 },
	{ 2, YYAT_ACCEPT, 0 },
	{ 1, YYAT_SHIFT, 3 },
	{ 0, YYAT_SHIFT, 1 }
};

YYCONST yystateaction_t YYNEARFAR YYBASED_CODE YYDCDECL yystateaction[] = {
	{ -128, 1, YYAT_ERROR, 0 },
	{ -165, 1, YYAT_ERROR, 0 },
	{ 127, 1, YYAT_ERROR, 0 },
	{ -168, 1, YYAT_ERROR, 0 },
	{ -170, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_DEFAULT, 138 },
	{ 0, 0, YYAT_REDUCE, 1 },
	{ -169, 1, YYAT_ERROR, 0 },
	{ -170, 1, YYAT_ERROR, 0 },
	{ -171, 1, YYAT_ERROR, 0 },
	{ -172, 1, YYAT_ERROR, 0 },
	{ -173, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 15 },
	{ 0, 0, YYAT_REDUCE, 16 },
	{ 0, 0, YYAT_REDUCE, 62 },
	{ 0, 0, YYAT_REDUCE, 63 },
	{ 0, 0, YYAT_REDUCE, 66 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_REDUCE, 14 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_REDUCE, 6 },
	{ 0, 0, YYAT_REDUCE, 7 },
	{ -177, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 8 },
	{ 0, 0, YYAT_REDUCE, 9 },
	{ -174, 1, YYAT_ERROR, 0 },
	{ -175, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 13 },
	{ -258, 1, YYAT_REDUCE, 4 },
	{ 0, 0, YYAT_REDUCE, 5 },
	{ 0, 0, YYAT_REDUCE, 10 },
	{ 0, 0, YYAT_REDUCE, 60 },
	{ -200, 1, YYAT_REDUCE, 49 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ -167, 1, YYAT_REDUCE, 37 },
	{ -223, 1, YYAT_REDUCE, 46 },
	{ -184, 1, YYAT_REDUCE, 39 },
	{ -169, 1, YYAT_REDUCE, 35 },
	{ -178, 1, YYAT_DEFAULT, 118 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ -179, 1, YYAT_DEFAULT, 108 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_REDUCE, 65 },
	{ 0, 0, YYAT_REDUCE, 64 },
	{ -182, 1, YYAT_DEFAULT, 134 },
	{ 0, 0, YYAT_REDUCE, 2 },
	{ 0, 0, YYAT_REDUCE, 11 },
	{ 0, 0, YYAT_REDUCE, 12 },
	{ 0, 0, YYAT_REDUCE, 3 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_REDUCE, 56 },
	{ 0, 0, YYAT_REDUCE, 57 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ -181, 1, YYAT_ERROR, 0 },
	{ -258, 1, YYAT_REDUCE, 18 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_REDUCE, 33 },
	{ -186, 1, YYAT_DEFAULT, 134 },
	{ -194, 1, YYAT_DEFAULT, 134 },
	{ -193, 1, YYAT_DEFAULT, 108 },
	{ -194, 1, YYAT_DEFAULT, 118 },
	{ -197, 1, YYAT_DEFAULT, 134 },
	{ -198, 1, YYAT_DEFAULT, 134 },
	{ 0, 0, YYAT_REDUCE, 61 },
	{ 0, 0, YYAT_REDUCE, 50 },
	{ 0, 0, YYAT_REDUCE, 51 },
	{ 0, 0, YYAT_REDUCE, 52 },
	{ 0, 0, YYAT_REDUCE, 53 },
	{ 0, 0, YYAT_REDUCE, 54 },
	{ 0, 0, YYAT_REDUCE, 55 },
	{ 0, 0, YYAT_REDUCE, 58 },
	{ 0, 0, YYAT_REDUCE, 59 },
	{ 0, 0, YYAT_REDUCE, 19 },
	{ -200, 1, YYAT_DEFAULT, 126 },
	{ -200, 1, YYAT_REDUCE, 38 },
	{ -211, 1, YYAT_REDUCE, 47 },
	{ -222, 1, YYAT_REDUCE, 48 },
	{ -226, 1, YYAT_REDUCE, 40 },
	{ -228, 1, YYAT_REDUCE, 41 },
	{ -238, 1, YYAT_REDUCE, 42 },
	{ -242, 1, YYAT_REDUCE, 43 },
	{ -246, 1, YYAT_REDUCE, 44 },
	{ -248, 1, YYAT_REDUCE, 45 },
	{ -190, 1, YYAT_REDUCE, 36 },
	{ -174, 1, YYAT_REDUCE, 34 },
	{ 0, 0, YYAT_DEFAULT, 138 },
	{ 0, 0, YYAT_DEFAULT, 138 },
	{ -215, 1, YYAT_DEFAULT, 126 },
	{ -224, 1, YYAT_DEFAULT, 118 },
	{ -235, 1, YYAT_DEFAULT, 92 },
	{ 0, 0, YYAT_REDUCE, 20 },
	{ 0, 0, YYAT_REDUCE, 21 },
	{ 0, 0, YYAT_REDUCE, 17 },
	{ -258, 1, YYAT_REDUCE, 22 },
	{ 0, 0, YYAT_REDUCE, 32 },
	{ 0, 0, YYAT_DEFAULT, 138 },
	{ -256, 1, YYAT_DEFAULT, 134 },
	{ -258, 1, YYAT_DEFAULT, 126 },
	{ -264, 1, YYAT_DEFAULT, 126 },
	{ -251, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_DEFAULT, 138 },
	{ 0, 0, YYAT_REDUCE, 31 },
	{ 0, 0, YYAT_DEFAULT, 138 },
	{ 0, 0, YYAT_DEFAULT, 138 },
	{ -268, 1, YYAT_DEFAULT, 134 },
	{ 0, 0, YYAT_DEFAULT, 138 },
	{ -274, 1, YYAT_DEFAULT, 134 },
	{ -184, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 23 },
	{ 0, 0, YYAT_REDUCE, 28 },
	{ 0, 0, YYAT_REDUCE, 29 },
	{ 0, 0, YYAT_DEFAULT, 138 },
	{ 0, 0, YYAT_REDUCE, 30 },
	{ 0, 0, YYAT_DEFAULT, 138 },
	{ 0, 0, YYAT_DEFAULT, 138 },
	{ -263, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 25 },
	{ 0, 0, YYAT_REDUCE, 26 },
	{ 0, 0, YYAT_REDUCE, 27 },
	{ -246, 1, YYAT_DEFAULT, 108 },
	{ 0, 0, YYAT_REDUCE, 24 }
};

int YYNEAR YYDCDECL yynontermgoto_size = 72;

YYCONST yynontermgoto_t YYNEARFAR YYBASED_CODE YYDCDECL yynontermgoto[] = {
	{ 138, 31 },
	{ 133, 137 },
	{ 138, 139 },
	{ 138, 28 },
	{ 138, 34 },
	{ 132, 136 },
	{ 138, 30 },
	{ 138, 26 },
	{ 138, 27 },
	{ 138, 22 },
	{ 138, 25 },
	{ 138, 24 },
	{ 138, 21 },
	{ 138, 39 },
	{ 126, 134 },
	{ 126, 38 },
	{ 126, 35 },
	{ 126, 37 },
	{ 126, 36 },
	{ 92, 111 },
	{ 73, -1 },
	{ 73, -1 },
	{ 73, 102 },
	{ 72, 101 },
	{ 72, 33 },
	{ 66, 95 },
	{ 66, 32 },
	{ 92, 63 },
	{ 64, -1 },
	{ 64, 93 },
	{ 29, 51 },
	{ 29, 29 },
	{ 130, 135 },
	{ 124, 131 },
	{ 122, 129 },
	{ 121, 128 },
	{ 119, 127 },
	{ 117, 125 },
	{ 116, 123 },
	{ 114, 120 },
	{ 108, 118 },
	{ 106, 115 },
	{ 105, 113 },
	{ 104, 112 },
	{ 78, 107 },
	{ 74, 103 },
	{ 71, 100 },
	{ 70, 99 },
	{ 69, 98 },
	{ 68, 97 },
	{ 67, 96 },
	{ 65, 94 },
	{ 61, 90 },
	{ 60, 89 },
	{ 59, 88 },
	{ 58, 87 },
	{ 57, 86 },
	{ 54, 85 },
	{ 53, 84 },
	{ 52, 83 },
	{ 44, 81 },
	{ 43, 80 },
	{ 42, 79 },
	{ 41, 77 },
	{ 40, 76 },
	{ 34, 62 },
	{ 20, 47 },
	{ 18, 46 },
	{ 17, 45 },
	{ 5, 23 },
	{ 4, 6 },
	{ 0, 2 }
};

YYCONST yystategoto_t YYNEARFAR YYBASED_CODE YYDCDECL yystategoto[] = {
	{ 70, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 68, -1 },
	{ 66, 29 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 47, -1 },
	{ 46, -1 },
	{ 0, -1 },
	{ 51, 126 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 27, 138 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 58, 92 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 49, 126 },
	{ 48, 126 },
	{ 47, 126 },
	{ 46, 126 },
	{ 45, 126 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 38, -1 },
	{ 37, -1 },
	{ 36, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 35, -1 },
	{ 34, -1 },
	{ 33, -1 },
	{ 32, -1 },
	{ 31, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 11, 73 },
	{ 31, 66 },
	{ 5, -1 },
	{ 31, 72 },
	{ 30, 72 },
	{ 29, 72 },
	{ 28, 72 },
	{ 27, 72 },
	{ 4, 66 },
	{ 5, 126 },
	{ 30, 126 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 29, 126 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 12, 126 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 39, 138 },
	{ 38, 138 },
	{ 26, 126 },
	{ 0, -1 },
	{ 25, 126 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 35, 138 },
	{ 0, -1 },
	{ 23, 126 },
	{ 22, 126 },
	{ 0, -1 },
	{ 32, 138 },
	{ 0, -1 },
	{ 31, 138 },
	{ 30, 138 },
	{ 0, -1 },
	{ 29, 138 },
	{ 0, -1 },
	{ -1, 72 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 28, 138 },
	{ 0, -1 },
	{ 1, 138 },
	{ -3, 138 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ -2, 126 },
	{ 0, -1 }
};

YYCONST yydestructor_t YYNEARFAR *YYNEAR YYDCDECL yydestructorptr = NULL;

YYCONST yytokendest_t YYNEARFAR *YYNEAR YYDCDECL yytokendestptr = NULL;
int YYNEAR YYDCDECL yytokendest_size = 0;

YYCONST yytokendestbase_t YYNEARFAR *YYNEAR YYDCDECL yytokendestbaseptr = NULL;
int YYNEAR YYDCDECL yytokendestbase_size = 0;
#line 677 ".\\myparser.y"


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
		else if(temp->type == Char)
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
			if(t->child[0]->kind == ConstK)
			{
				fprintf(fp, "\tinvoke crt_printf, addr type1, %d\n", t->child[0]->attr.val);
				fprintf(fp, "\tinvoke crt_printf, OFFSET newline\n");
			}
			else if(r->child[0]->kind == IdK)
			{
				fprintf(fp, "\tinvoke crt_printf, addr type1, _%s\n", t->child[0]->attr.name);
				fprintf(fp, "\tinvoke crt_printf, OFFSET newline\n");
			}
			else if(r->child[0]->kind == OpK)
			{
				gen_code(t->child[0]);
				fprintf(fp, "\tinvoke crt_printf, addr type1, t%d\n", t->child[0]->tid);
				fprintf(fp, "\tinvoke crt_printf, OFFSET newline\n");
			}
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
					break;
				}
				case OR:
				{
					break;
				}
				case NOT:
				{
					break;
				}
				case EQ:
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
					fprintf(fp, "\tje label%d\n", r->true_label);
					fprintf(fp, "\tjmp label%d\n", r->false_label);
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
					break;
				}
				case LESS:
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
					fprintf(fp, "\tjl label%d\n", r->true_label);
					fprintf(fp, "\tjmp label%d\n", r->false_label);
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
					break;
				}
				case NEQ:
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
					fprintf(fp, "\tjne label%d\n", r->true_label);
					fprintf(fp, "\tjmp label%d\n", r->false_label);
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
			break;
		}
		case IdK:
		{
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
		if(t->child[2] == NULL)//without else
		{
			e = t->child[0];	
			s = t->child[1];
			if (t->begin_label <= 0)
				t->begin_label = labeln++;
			s->begin_label = e->true_label = labeln++;  		
			if (t->next_label <= 0)
				t->next_label = labeln++;	
			s->next_label = e->false_label = t->next_label;
			if (t->sibling)
				t->sibling->begin_label = t->next_label;  
			get_label(e);		
			get_label(s);
		}
		else if(t->child[2] != NULL)//with else
		{
			e = t->child[0];	
			s1 = t->child[1];
			s2 = t->child[2];
			if (t->begin_label <= 0)
				t->begin_label = labeln++;
			s1->begin_label = e->true_label = labeln++; 
			s2->begin_label = e->false_label = labeln++;
			if (t->next_label <= 0)
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
		if (t->next_label <= 0)
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
		
		if (t->begin_label <=0)
			t->begin_label = labeln++;
		if (t->true_label <= 0)
			t->true_label = labeln++;
		if(e->true_label <= 0)
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

