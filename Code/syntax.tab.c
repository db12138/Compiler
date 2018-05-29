/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     ID = 260,
     PLUS = 261,
     MINUS = 262,
     STAR = 263,
     DIV = 264,
     AND = 265,
     OR = 266,
     NOT = 267,
     DOT = 268,
     RELOP = 269,
     SEMI = 270,
     COMMA = 271,
     ASSIGNOP = 272,
     LP = 273,
     RP = 274,
     LB = 275,
     RB = 276,
     LC = 277,
     RC = 278,
     TYPE = 279,
     STRUCT = 280,
     RETURN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     LOWER_THAN_ELSE = 285
   };
#endif
/* Tokens.  */
#define INT 258
#define FLOAT 259
#define ID 260
#define PLUS 261
#define MINUS 262
#define STAR 263
#define DIV 264
#define AND 265
#define OR 266
#define NOT 267
#define DOT 268
#define RELOP 269
#define SEMI 270
#define COMMA 271
#define ASSIGNOP 272
#define LP 273
#define RP 274
#define LB 275
#define RB 276
#define LC 277
#define RC 278
#define TYPE 279
#define STRUCT 280
#define RETURN 281
#define IF 282
#define ELSE 283
#define WHILE 284
#define LOWER_THAN_ELSE 285




/* Copy the first part of user declarations.  */
#line 1 ".//syntax.y"

#include<stdio.h>
#include "common.h"
#include <stdlib.h>
/*typedef struct Node
{
	int intval;
	float floatval;
	char strval[50];
	struct Node * node;
}Node;*/

#define ERR_COMMA "\",\""
#define ERR_LP   "Missing \"(\""
#define ERR_RP   "Missing \")\""
#define ERR_LB   "Missing \"[\""
#define ERR_RB   "Missing \"]\""
#define ERR_RC   "Missing \"}\""
#define ERR_LC   "Missing \"{\""
#define ERR_SEMI "Missing \";\""

extern BOOL hasError;
extern int errorCount;

Node *Root;
Node *NewNodeSyn(char *,int);
Node *MergeNode1(Node*,Node*);
Node *MergeNode2(Node*,Node*,Node*);
Node *MergeNode3(Node*,Node*,Node*,Node*);
Node *MergeNode4(Node*, Node*,Node*,Node*,Node*);
Node *MergeNode5(Node*, Node*,Node*,Node*,Node*,Node*);
Node *MergeNode7(Node*, Node*,Node*,Node*,Node*,Node*,Node* ,Node*);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 ".//syntax.y"
{
	Node *type_node;
}
/* Line 193 of yacc.c.  */
#line 195 ".//syntax.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 220 ".//syntax.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   343

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNRULES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    13,    18,    23,    26,
      29,    33,    37,    41,    46,    51,    53,    57,    59,    61,
      67,    70,    76,    78,    79,    81,    83,    88,    93,    97,
     102,   106,   108,   111,   114,   119,   123,   126,   127,   130,
     133,   135,   139,   144,   150,   158,   166,   172,   177,   180,
     183,   184,   188,   193,   198,   200,   204,   207,   209,   213,
     217,   222,   226,   231,   235,   239,   243,   247,   251,   255,
     259,   263,   266,   269,   274,   278,   283,   288,   292,   294,
     296,   298,   303,   308,   312
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    33,    -1,    34,    33,    -1,    -1,    36,
      35,    15,    -1,    36,    35,     1,    15,    -1,    36,    35,
       1,    36,    -1,    36,    15,    -1,     1,    15,    -1,    36,
       1,    15,    -1,    36,    41,    44,    -1,    36,    41,    15,
      -1,    36,    41,     1,    22,    -1,    36,    41,     1,    23,
      -1,    40,    -1,    40,    16,    35,    -1,    24,    -1,    37,
      -1,    25,    38,    22,    47,    23,    -1,    25,    39,    -1,
      25,    38,    22,     1,    23,    -1,     5,    -1,    -1,     5,
      -1,     5,    -1,    40,    20,     3,    21,    -1,     5,    18,
      42,    19,    -1,     5,    18,    19,    -1,     5,    18,     1,
      19,    -1,    43,    16,    42,    -1,    43,    -1,     1,    19,
      -1,    36,    40,    -1,    22,    47,    45,    23,    -1,    22,
      44,     1,    -1,    46,    45,    -1,    -1,    51,    15,    -1,
       1,    23,    -1,    44,    -1,    26,    51,    15,    -1,    26,
      51,     1,    15,    -1,    27,    18,    51,    19,    46,    -1,
      27,    18,    51,    19,    46,    28,    46,    -1,    27,    18,
      51,     1,    46,    28,    46,    -1,    29,    18,    51,    19,
      46,    -1,    29,    18,     1,    19,    -1,     1,    15,    -1,
      48,    47,    -1,    -1,    36,    49,    15,    -1,    36,     1,
      49,    15,    -1,    36,    49,     1,    15,    -1,    50,    -1,
      50,    16,    49,    -1,     1,    15,    -1,    40,    -1,    40,
      17,    51,    -1,    20,     1,    17,    -1,    40,    17,     1,
      15,    -1,    51,    17,    51,    -1,    51,    17,     1,    15,
      -1,    51,    10,    51,    -1,    51,    11,    51,    -1,    51,
      14,    51,    -1,    51,     6,    51,    -1,    51,     7,    51,
      -1,    51,     8,    51,    -1,    51,     9,    51,    -1,    18,
      51,    19,    -1,     7,    51,    -1,    12,    51,    -1,     5,
      18,    52,    19,    -1,     5,    18,    19,    -1,     5,    18,
       1,    15,    -1,    51,    20,    51,    21,    -1,    51,    13,
       5,    -1,     5,    -1,     3,    -1,     4,    -1,    51,    20,
       1,    21,    -1,     5,    18,     1,    19,    -1,    51,    16,
      52,    -1,    51,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    67,    67,    69,    70,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    83,    84,    88,    89,    91,
      92,    93,    95,    96,    98,   101,   102,   104,   105,   106,
     108,   109,   110,   112,   115,   116,   118,   119,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   134,
     135,   137,   138,   139,   141,   142,   143,   145,   146,   147,
     148,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   174,   175
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "PLUS", "MINUS",
  "STAR", "DIV", "AND", "OR", "NOT", "DOT", "RELOP", "SEMI", "COMMA",
  "ASSIGNOP", "LP", "RP", "LB", "RB", "LC", "RC", "TYPE", "STRUCT",
  "RETURN", "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    34,
      34,    34,    34,    34,    34,    35,    35,    36,    36,    37,
      37,    37,    38,    38,    39,    40,    40,    41,    41,    41,
      42,    42,    42,    43,    44,    44,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    47,
      47,    48,    48,    48,    49,    49,    49,    50,    50,    50,
      50,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    52,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     4,     4,     2,     2,
       3,     3,     3,     4,     4,     1,     3,     1,     1,     5,
       2,     5,     1,     0,     1,     1,     4,     4,     3,     4,
       3,     1,     2,     2,     4,     3,     2,     0,     2,     2,
       1,     3,     4,     5,     7,     7,     5,     4,     2,     2,
       0,     3,     4,     4,     1,     3,     2,     1,     3,     3,
       4,     3,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     3,     4,     4,     3,     1,     1,
       1,     4,     4,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    17,    23,     0,     2,     0,     0,    18,     9,
      24,     0,    20,     1,     3,     0,    25,     8,     0,    15,
       0,     0,    10,     0,     0,     5,     0,     0,     0,    12,
      50,    11,     0,     0,     0,    50,     0,    28,     0,     0,
      31,     6,     7,    25,    16,     0,    13,    14,     0,     0,
      21,     0,     0,    57,     0,    54,    19,    49,    29,    33,
      27,     0,    26,    35,     0,    79,    80,    78,     0,     0,
       0,     0,     0,     0,    40,     0,     0,     0,     0,    56,
       0,     0,     0,     0,    51,     0,     0,    30,    48,    39,
       0,    71,    72,     0,     0,     0,     0,    34,    36,     0,
       0,     0,     0,     0,     0,     0,     0,    38,     0,     0,
      52,    59,     0,    58,    53,    55,    32,     0,    74,    84,
       0,    70,     0,    41,     0,     0,     0,    66,    67,    68,
      69,    63,    64,    77,    65,     0,    61,     0,     0,    60,
      75,    82,     0,    73,    42,     0,     0,    47,     0,    62,
      81,    76,    83,     0,    43,    46,     0,     0,    45,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    18,    33,     8,    11,    12,    53,
      20,    39,    40,    74,    75,    76,    34,    35,    54,    55,
      77,   120
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -69
static const yytype_int16 yypact[] =
{
      56,    -6,   -69,    15,    26,   -69,    56,    10,   -69,   -69,
      49,    67,   -69,   -69,   -69,    45,    60,   -69,     9,    48,
      82,    62,   -69,    81,    -8,   -69,    90,   110,    31,   -69,
     139,   -69,   108,     3,   121,    95,   131,   -69,    90,   132,
     141,   -69,   -69,   -69,   -69,   125,   -69,   -69,   151,    43,
     -69,   127,   164,   154,    44,   159,   -69,   -69,   162,   171,
     -69,    18,   -69,   -69,    -2,   -69,   -69,   166,   217,   217,
     217,   217,   167,   176,   -69,   172,    43,   230,   181,   -69,
     183,   182,   155,   186,   -69,   133,   191,   -69,   -69,   -69,
     136,    83,    38,   245,   101,   217,   165,   -69,   -69,   217,
     217,   217,   217,   217,   217,   195,   217,   -69,   175,   185,
     -69,   -69,   187,   290,   -69,   -69,   -69,   130,   -69,   260,
     194,   -69,   199,   -69,   116,   197,   275,    83,    83,    38,
      38,   314,   305,   -69,   323,   202,   290,   204,   198,   -69,
     -69,   -69,   217,   -69,   -69,    72,    72,   -69,    72,   -69,
     -69,   -69,   -69,   200,   203,   -69,    72,    72,   -69,   -69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -69,   -69,   220,   -69,   201,     6,   -69,   -69,   -69,    11,
     -69,   169,   -69,    32,   147,   160,    58,   -69,   -46,   -69,
     -68,    91
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -51
static const yytype_int16 yytable[] =
{
      91,    92,    93,    94,    51,    80,     7,    41,    43,     9,
      24,    15,     7,    88,   113,    16,     2,     3,    19,    86,
      10,    89,   119,    52,    25,    17,    13,   124,   126,    38,
      42,   127,   128,   129,   130,   131,   132,    19,   134,   115,
     136,   138,     2,     3,    64,    83,    65,    66,    67,    59,
      68,   105,    31,    46,    47,    69,    -4,     1,   109,    84,
      22,    70,    48,    32,    26,    30,   -37,    38,    27,    71,
      72,   -22,    73,    64,   119,    65,    66,    67,    23,    68,
       2,     3,    36,    28,    69,   -50,     2,     3,    49,    21,
      70,   101,   102,    57,    30,    43,   105,    29,    71,    72,
      37,    73,   122,   109,    30,     2,     3,    99,   100,   101,
     102,   103,   104,    45,   105,   106,   123,   145,   108,     2,
       3,   109,    99,   100,   101,   102,   103,   104,    78,   105,
     106,    50,    43,   108,    78,   146,   109,   117,    43,    65,
      66,    67,    79,    68,    56,   140,    62,    52,    69,   141,
      58,    60,    63,    52,    70,   118,   112,    61,    65,    66,
      67,    30,    68,     2,     3,    81,   125,    69,    65,    66,
      67,    82,    68,    70,    27,    85,   135,    69,    65,    66,
      67,   -32,    68,    70,    90,    95,   137,    69,    65,    66,
      67,    27,    68,    70,    96,    97,    79,    69,   110,   111,
     133,   114,   139,    70,    99,   100,   101,   102,   103,   104,
     116,   105,   106,   143,   144,   108,   147,   149,   109,   151,
      65,    66,    67,    98,    68,   150,    14,    44,   156,    69,
      87,   157,     0,   152,     0,    70,    99,   100,   101,   102,
     103,   104,     0,   105,   106,   107,     0,   108,     0,     0,
     109,    99,   100,   101,   102,   103,   104,     0,   105,   106,
       0,     0,   108,     0,   121,   109,    99,   100,   101,   102,
     103,   104,     0,   105,   106,     0,   142,   108,     0,     0,
     109,    99,   100,   101,   102,   103,   104,     0,   105,   106,
       0,     0,   108,     0,   148,   109,    99,   100,   101,   102,
     103,   104,     0,   105,   106,   153,   154,   108,   155,     0,
     109,    99,   100,   101,   102,   103,   158,   159,   105,   106,
      99,   100,   101,   102,     0,   109,     0,   105,   106,    99,
     100,   101,   102,     0,   109,     0,   105,     0,     0,     0,
       0,     0,     0,   109
};

static const yytype_int16 yycheck[] =
{
      68,    69,    70,    71,     1,    51,     0,    15,     5,    15,
       1,     1,     6,    15,    82,     5,    24,    25,     7,     1,
       5,    23,    90,    20,    15,    15,     0,    95,    96,    23,
      24,    99,   100,   101,   102,   103,   104,    26,   106,    85,
     108,   109,    24,    25,     1,     1,     3,     4,     5,    38,
       7,    13,    20,    22,    23,    12,     0,     1,    20,    15,
      15,    18,    30,     1,    16,    22,    23,    61,    20,    26,
      27,    22,    29,     1,   142,     3,     4,     5,    18,     7,
      24,    25,     1,     1,    12,    23,    24,    25,    30,    22,
      18,     8,     9,    35,    22,     5,    13,    15,    26,    27,
      19,    29,     1,    20,    22,    24,    25,     6,     7,     8,
       9,    10,    11,     3,    13,    14,    15,     1,    17,    24,
      25,    20,     6,     7,     8,     9,    10,    11,     1,    13,
      14,    23,     5,    17,     1,    19,    20,     1,     5,     3,
       4,     5,    15,     7,    23,    15,    21,    20,    12,    19,
      19,    19,     1,    20,    18,    19,     1,    16,     3,     4,
       5,    22,     7,    24,    25,     1,     1,    12,     3,     4,
       5,    17,     7,    18,    20,    16,     1,    12,     3,     4,
       5,    19,     7,    18,    18,    18,     1,    12,     3,     4,
       5,    20,     7,    18,    18,    23,    15,    12,    15,    17,
       5,    15,    15,    18,     6,     7,     8,     9,    10,    11,
      19,    13,    14,    19,    15,    17,    19,    15,    20,    21,
       3,     4,     5,    76,     7,    21,     6,    26,    28,    12,
      61,    28,    -1,   142,    -1,    18,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,    15,    -1,    17,    -1,    -1,
      20,     6,     7,     8,     9,    10,    11,    -1,    13,    14,
      -1,    -1,    17,    -1,    19,    20,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,    -1,    16,    17,    -1,    -1,
      20,     6,     7,     8,     9,    10,    11,    -1,    13,    14,
      -1,    -1,    17,    -1,    19,    20,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,   145,   146,    17,   148,    -1,
      20,     6,     7,     8,     9,    10,   156,   157,    13,    14,
       6,     7,     8,     9,    -1,    20,    -1,    13,    14,     6,
       7,     8,     9,    -1,    20,    -1,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    24,    25,    32,    33,    34,    36,    37,    15,
       5,    38,    39,     0,    33,     1,     5,    15,    35,    40,
      41,    22,    15,    18,     1,    15,    16,    20,     1,    15,
      22,    44,     1,    36,    47,    48,     1,    19,    36,    42,
      43,    15,    36,     5,    35,     3,    22,    23,    44,    47,
      23,     1,    20,    40,    49,    50,    23,    47,    19,    40,
      19,    16,    21,     1,     1,     3,     4,     5,     7,    12,
      18,    26,    27,    29,    44,    45,    46,    51,     1,    15,
      49,     1,    17,     1,    15,    16,     1,    42,    15,    23,
      18,    51,    51,    51,    51,    18,    18,    23,    45,     6,
       7,     8,     9,    10,    11,    13,    14,    15,    17,    20,
      15,    17,     1,    51,    15,    49,    19,     1,    19,    51,
      52,    19,     1,    15,    51,     1,    51,    51,    51,    51,
      51,    51,    51,     5,    51,     1,    51,     1,    51,    15,
      15,    19,    16,    19,    15,     1,    19,    19,    19,    15,
      21,    21,    52,    46,    46,    46,    28,    28,    46,    46
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 67 ".//syntax.y"
    {Node* p=NewNodeSyn("Program",(yyloc).first_line);(yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));Root=(yyval.type_node);;}
    break;

  case 3:
#line 69 ".//syntax.y"
    {Node *p=NewNodeSyn("ExtDefList",(yyloc).first_line); (yyval.type_node)=MergeNode2(p,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));;}
    break;

  case 4:
#line 70 ".//syntax.y"
    {(yyval.type_node)=NULL;;}
    break;

  case 5:
#line 72 ".//syntax.y"
    {Node* p=NewNodeSyn("ExtDef",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 6:
#line 73 ".//syntax.y"
    { yyerror("wrong global def."); yyclearin; yyerrok; ;}
    break;

  case 7:
#line 74 ".//syntax.y"
    { yyerror(ERR_SEMI);yyerrok; ;}
    break;

  case 8:
#line 75 ".//syntax.y"
    {Node *p=NewNodeSyn("ExtDef",(yyloc).first_line); (yyval.type_node)=MergeNode2(p,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));;}
    break;

  case 9:
#line 76 ".//syntax.y"
    {(yyval.type_node) = NewNodeSyn("error",(yyloc).first_line); yyerror("some error in this defination.");yyerrok; yyclearin; ;}
    break;

  case 10:
#line 77 ".//syntax.y"
    {yyerror("syntax error, wrong expression."); yyerrok; ;}
    break;

  case 11:
#line 78 ".//syntax.y"
    {Node *p=NewNodeSyn("ExtDef",(yyloc).first_line); (yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 12:
#line 79 ".//syntax.y"
    {Node *p = NewNodeSyn("ExtDef",(yyloc).first_line); (yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 13:
#line 80 ".//syntax.y"
    { yyerror(ERR_RP); yyerrok; ;}
    break;

  case 14:
#line 81 ".//syntax.y"
    { yyerror(ERR_RP" or \"{\"."); yyerrok; ;}
    break;

  case 15:
#line 83 ".//syntax.y"
    {Node *p=NewNodeSyn("ExtDecList",(yyloc).first_line); (yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 16:
#line 84 ".//syntax.y"
    {Node *p=NewNodeSyn("ExtDecList",(yyloc).first_line); (yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 17:
#line 88 ".//syntax.y"
    {Node* p=NewNodeSyn("Specifier",(yyloc).first_line);(yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 18:
#line 89 ".//syntax.y"
    {Node *p=NewNodeSyn("Specifier",(yyloc).first_line); (yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 19:
#line 91 ".//syntax.y"
    {Node *p=NewNodeSyn("StructSpecifier",(yyloc).first_line); (yyval.type_node)=MergeNode5(p,(yyvsp[(1) - (5)].type_node),(yyvsp[(2) - (5)].type_node),(yyvsp[(3) - (5)].type_node),(yyvsp[(4) - (5)].type_node),(yyvsp[(5) - (5)].type_node));;}
    break;

  case 20:
#line 92 ".//syntax.y"
    {Node *p=NewNodeSyn("StructSpecifier",(yyloc).first_line); (yyval.type_node)=MergeNode2(p,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));;}
    break;

  case 21:
#line 93 ".//syntax.y"
    { yyerror("Wrong defination in struct."); yyerrok; ;}
    break;

  case 22:
#line 95 ".//syntax.y"
    {Node *p=NewNodeSyn("OptTag",(yyloc).first_line); (yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 23:
#line 96 ".//syntax.y"
    {(yyval.type_node)=NULL;;}
    break;

  case 24:
#line 98 ".//syntax.y"
    {Node *p=NewNodeSyn("Tag",(yyloc).first_line); (yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 25:
#line 101 ".//syntax.y"
    {Node *p=NewNodeSyn("VarDec",(yyloc).first_line); (yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 26:
#line 102 ".//syntax.y"
    {Node *p=NewNodeSyn("VarDec",(yyloc).first_line); (yyval.type_node)=MergeNode4(p,(yyvsp[(1) - (4)].type_node),(yyvsp[(2) - (4)].type_node),(yyvsp[(3) - (4)].type_node),(yyvsp[(4) - (4)].type_node));;}
    break;

  case 27:
#line 104 ".//syntax.y"
    {Node *p=NewNodeSyn("FunDec",(yyloc).first_line);(yyval.type_node)=MergeNode4(p,(yyvsp[(1) - (4)].type_node),(yyvsp[(2) - (4)].type_node),(yyvsp[(3) - (4)].type_node),(yyvsp[(4) - (4)].type_node));;}
    break;

  case 28:
#line 105 ".//syntax.y"
    {Node *p=NewNodeSyn("FunDec",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 29:
#line 106 ".//syntax.y"
    { yyerror(ERR_RP); yyerrok; ;}
    break;

  case 30:
#line 108 ".//syntax.y"
    {Node *p=NewNodeSyn("VarList",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 31:
#line 109 ".//syntax.y"
    {Node *p=NewNodeSyn("VarList",(yyloc).first_line);(yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 32:
#line 110 ".//syntax.y"
    {yyerror("Wrong defination!");;}
    break;

  case 33:
#line 112 ".//syntax.y"
    {Node *p=NewNodeSyn("ParamDec",(yyloc).first_line);(yyval.type_node)=MergeNode2(p,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));;}
    break;

  case 34:
#line 115 ".//syntax.y"
    {Node *p=NewNodeSyn("CompSt",(yyloc).first_line);(yyval.type_node)=MergeNode4(p,(yyvsp[(1) - (4)].type_node),(yyvsp[(2) - (4)].type_node),(yyvsp[(3) - (4)].type_node),(yyvsp[(4) - (4)].type_node));;}
    break;

  case 35:
#line 116 ".//syntax.y"
    { yyerror("Wrong end here."); ;}
    break;

  case 36:
#line 118 ".//syntax.y"
    {Node *p=NewNodeSyn("StmtList",(yyloc).first_line);(yyval.type_node)=MergeNode2(p,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));;}
    break;

  case 37:
#line 119 ".//syntax.y"
    {(yyval.type_node)=NULL;;}
    break;

  case 38:
#line 121 ".//syntax.y"
    {Node *p=NewNodeSyn("Stmt",(yyloc).first_line);(yyval.type_node)=MergeNode2(p,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));;}
    break;

  case 39:
#line 122 ".//syntax.y"
    { yyerror(ERR_LC); yyclearin; yyerrok; ;}
    break;

  case 40:
#line 123 ".//syntax.y"
    {Node *p=NewNodeSyn("Stmt",(yyloc).first_line);(yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 41:
#line 124 ".//syntax.y"
    {Node *p=NewNodeSyn("Stmt",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 42:
#line 125 ".//syntax.y"
    { yyerror(ERR_SEMI); yyerrok;;}
    break;

  case 43:
#line 126 ".//syntax.y"
    {Node *p=NewNodeSyn("Stmt",(yyloc).first_line);(yyval.type_node)=MergeNode5(p,(yyvsp[(1) - (5)].type_node),(yyvsp[(2) - (5)].type_node),(yyvsp[(3) - (5)].type_node),(yyvsp[(4) - (5)].type_node),(yyvsp[(5) - (5)].type_node));;}
    break;

  case 44:
#line 127 ".//syntax.y"
    {Node *p=NewNodeSyn("Stmt",(yyloc).first_line);(yyval.type_node)=MergeNode7(p,(yyvsp[(1) - (7)].type_node),(yyvsp[(2) - (7)].type_node),(yyvsp[(3) - (7)].type_node),(yyvsp[(4) - (7)].type_node),(yyvsp[(5) - (7)].type_node),(yyvsp[(6) - (7)].type_node),(yyvsp[(7) - (7)].type_node));;}
    break;

  case 45:
#line 128 ".//syntax.y"
    { yyerror(ERR_RP); yyerrok;;}
    break;

  case 46:
#line 129 ".//syntax.y"
    {Node *p=NewNodeSyn("Stmt",(yyloc).first_line);(yyval.type_node)=MergeNode5(p,(yyvsp[(1) - (5)].type_node),(yyvsp[(2) - (5)].type_node),(yyvsp[(3) - (5)].type_node),(yyvsp[(4) - (5)].type_node),(yyvsp[(5) - (5)].type_node));;}
    break;

  case 47:
#line 130 ".//syntax.y"
    { yyerror("while syntax error."); yyerrok; ;}
    break;

  case 48:
#line 131 ".//syntax.y"
    { yyerror(ERR_SEMI); yyclearin; ;}
    break;

  case 49:
#line 134 ".//syntax.y"
    {Node *p=NewNodeSyn("DefList",(yyloc).first_line);(yyval.type_node)=MergeNode2(p,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));;}
    break;

  case 50:
#line 135 ".//syntax.y"
    {(yyval.type_node)=NULL;;}
    break;

  case 51:
#line 137 ".//syntax.y"
    {Node *p=NewNodeSyn("Def",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 52:
#line 138 ".//syntax.y"
    { yyerrok; ;}
    break;

  case 53:
#line 139 ".//syntax.y"
    { yyclearin; yyerrok; ;}
    break;

  case 54:
#line 141 ".//syntax.y"
    {Node *p=NewNodeSyn("DecList",(yyloc).first_line);(yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 55:
#line 142 ".//syntax.y"
    {Node *p=NewNodeSyn("DecList",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 56:
#line 143 ".//syntax.y"
    { yyerror("Wrong defination."); yyclearin; ;}
    break;

  case 57:
#line 145 ".//syntax.y"
    {Node *p=NewNodeSyn("Dec",(yyloc).first_line);(yyval.type_node) =MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 58:
#line 146 ".//syntax.y"
    {Node *p=NewNodeSyn("Dec",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 59:
#line 147 ".//syntax.y"
    {yyerror(ERR_RB); yyclearin; yyerrok; ;}
    break;

  case 60:
#line 148 ".//syntax.y"
    { yyerror("Missing operation numbers."); yyclearin; yyerrok; ;}
    break;

  case 61:
#line 151 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 62:
#line 152 ".//syntax.y"
    { yyerror("wrong assign expression."); ;}
    break;

  case 63:
#line 153 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 64:
#line 154 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 65:
#line 155 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 66:
#line 156 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 67:
#line 157 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 68:
#line 158 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 69:
#line 159 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 70:
#line 160 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 71:
#line 161 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode2(p,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));;}
    break;

  case 72:
#line 162 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode2(p,(yyvsp[(1) - (2)].type_node),(yyvsp[(2) - (2)].type_node));;}
    break;

  case 73:
#line 163 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode4(p,(yyvsp[(1) - (4)].type_node),(yyvsp[(2) - (4)].type_node),(yyvsp[(3) - (4)].type_node),(yyvsp[(4) - (4)].type_node));;}
    break;

  case 74:
#line 164 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 75:
#line 165 ".//syntax.y"
    { yyerror(ERR_RP); yyclearin; ;}
    break;

  case 76:
#line 166 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode4(p,(yyvsp[(1) - (4)].type_node),(yyvsp[(2) - (4)].type_node),(yyvsp[(3) - (4)].type_node),(yyvsp[(4) - (4)].type_node));;}
    break;

  case 77:
#line 167 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 78:
#line 168 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 79:
#line 169 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 80:
#line 170 ".//syntax.y"
    {Node *p=NewNodeSyn("Exp",(yyloc).first_line);(yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;

  case 81:
#line 171 ".//syntax.y"
    { yyerror("Wrong VarDec."); yyerrok; ;}
    break;

  case 82:
#line 172 ".//syntax.y"
    { yyerror("check LP and RP."); yyerrok; ;}
    break;

  case 83:
#line 174 ".//syntax.y"
    {Node *p=NewNodeSyn("Args",(yyloc).first_line);(yyval.type_node)=MergeNode3(p,(yyvsp[(1) - (3)].type_node),(yyvsp[(2) - (3)].type_node),(yyvsp[(3) - (3)].type_node));;}
    break;

  case 84:
#line 175 ".//syntax.y"
    {Node *p=NewNodeSyn("Args",(yyloc).first_line);(yyval.type_node)=MergeNode1(p,(yyvsp[(1) - (1)].type_node));;}
    break;


/* Line 1267 of yacc.c.  */
#line 2029 ".//syntax.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 177 ".//syntax.y"


