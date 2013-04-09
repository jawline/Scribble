/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 4 "./src/Parser/Parser.yy"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <Statement/BoolStatement.hpp>
#include <Statement/IntStatement.hpp>
#include <Statement/OperateStatement.hpp>
#include <Statement/StringStatement.hpp>
#include <Statement/AssignVariable.hpp>
#include <Statement/GetVariableStatement.hpp>
#include <Statement/FunctionStatement.hpp>
#include <Statement/ForStatement.hpp>
#include <Statement/TestStatement.hpp>
#include <Statement/IfStatement.hpp>
#include <Statement/OperateStatement.hpp>
#include <Statement/ReturnStatement.hpp>
#include <Statement/WhileStatement.hpp>
#include <Statement/IncrementStatement.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Function/Function.hpp>
#include <Function/ScriptedFunction.hpp>
#include <Function/WriteFunction.hpp>
#include <Value/Util.hpp>
#include <Parser/Parser.hpp>

#include <Value/Variable.hpp>
#include <Value/String.hpp>

int yylex();
void yyerror(const char* s);

bool ParsingError;
std::vector<std::string> ImportList;
std::map<std::string, Variable*> Variables;

std::map<std::string, NamespaceType> Namespace;
NamespaceType Functions;

std::vector<SmartPointer<FunctionReference>> References;

extern int yylineno;	// defined and maintained in lex.c
extern char *yytext;	// defined and maintained in lex.c



/* Line 268 of yacc.c  */
#line 120 "./gen/Parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     WORD = 258,
     STRING = 259,
     REAL = 260,
     INT = 261,
     PLUS = 262,
     MINUS = 263,
     TIMES = 264,
     DIVIDE = 265,
     POWER = 266,
     EQUALS = 267,
     ASSIGN = 268,
     IF = 269,
     ELSE = 270,
     GREATER = 271,
     LESSER = 272,
     FOR = 273,
     TYPE_VOID = 274,
     RETURN = 275,
     WHILE = 276,
     NOT = 277,
     IMPORT = 278,
     LINK = 279,
     LPAREN = 280,
     RPAREN = 281,
     LBRACKET = 282,
     RBRACKET = 283,
     COMMA = 284,
     TWOMINUS = 285,
     TWOPLUS = 286,
     TYPE_BOOL = 287,
     TRUE = 288,
     FALSE = 289,
     FUNCTION = 290,
     VARIABLE = 291,
     CONST = 292,
     STRUCT = 293,
     TYPE_INT = 294,
     TYPE_STRING = 295,
     COLON = 296,
     END = 297,
     NEG = 298
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 52 "./src/Parser/Parser.yy"

	std::string* string;
	std::vector<SmartPointer<Statement>>* statements;
	std::vector<SmartPointer<Variable>>* variables;
	Statement* statement;
	Function* function;
	Variable* variable;
	float real;
	int integer;
	ValueType type;



/* Line 293 of yacc.c  */
#line 213 "./gen/Parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
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


/* Line 343 of yacc.c  */
#line 238 "./gen/Parser.cpp"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   379

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  10
/* YYNRULES -- Number of rules.  */
#define YYNRULES  47
/* YYNRULES -- Number of states.  */
#define YYNSTATES  109

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,    10,    13,    15,    17,    19,    21,
      26,    28,    32,    43,    53,    55,    59,    60,    63,    67,
      72,    76,    83,    89,    91,    93,    95,    97,    99,   103,
     105,   107,   113,   123,   127,   131,   135,   145,   151,   155,
     160,   164,   168,   172,   176,   179,   182,   185
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    -1,    45,    23,    25,     4,    26,    -1,
      45,    49,    -1,    39,    -1,    40,    -1,    32,    -1,    19,
      -1,    36,     3,    41,    46,    -1,    47,    -1,    48,    29,
      47,    -1,    35,     3,    25,    48,    26,    41,    46,    27,
      51,    28,    -1,    35,     3,    25,    26,    41,    46,    27,
      51,    28,    -1,    53,    -1,    50,    29,    53,    -1,    -1,
      51,    53,    -1,    51,    20,    53,    -1,     3,    25,    50,
      26,    -1,     3,    25,    26,    -1,     3,    24,     3,    25,
      50,    26,    -1,     3,    24,     3,    25,    26,    -1,    33,
      -1,    34,    -1,     6,    -1,     4,    -1,    47,    -1,    47,
      13,    53,    -1,     3,    -1,    52,    -1,    14,    53,    27,
      51,    28,    -1,    14,    53,    27,    51,    28,    15,    27,
      51,    28,    -1,    53,     7,    53,    -1,    53,     8,    53,
      -1,    53,     9,    53,    -1,    18,    53,    42,    53,    42,
      53,    27,    51,    28,    -1,    21,    53,    27,    51,    28,
      -1,    53,    12,    53,    -1,    53,    22,    12,    53,    -1,
      53,    16,    53,    -1,    53,    17,    53,    -1,    25,    53,
      26,    -1,     3,    13,    53,    -1,     3,    31,    -1,    31,
       3,    -1,     3,    30,    -1,    30,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    91,    91,    94,    98,   103,   105,   107,   109,   114,
     135,   138,   144,   180,   220,   223,   229,   231,   234,   240,
     257,   265,   284,   297,   299,   301,   303,   310,   312,   314,
     328,   330,   332,   334,   336,   338,   340,   342,   344,   346,
     348,   350,   352,   354,   367,   379,   390,   401
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WORD", "STRING", "REAL", "INT", "PLUS",
  "MINUS", "TIMES", "DIVIDE", "POWER", "EQUALS", "ASSIGN", "IF", "ELSE",
  "GREATER", "LESSER", "FOR", "TYPE_VOID", "RETURN", "WHILE", "NOT",
  "IMPORT", "LINK", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "COMMA",
  "TWOMINUS", "TWOPLUS", "TYPE_BOOL", "TRUE", "FALSE", "FUNCTION",
  "VARIABLE", "CONST", "STRUCT", "TYPE_INT", "TYPE_STRING", "COLON", "END",
  "NEG", "$accept", "Program", "Type", "Variable", "Variables", "Function",
  "Arguments", "Statements", "FunctionCall", "Statement", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    45,    46,    46,    46,    46,    47,
      48,    48,    49,    49,    50,    50,    51,    51,    51,    52,
      52,    52,    52,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     5,     2,     1,     1,     1,     1,     4,
       1,     3,    10,     9,     1,     3,     0,     2,     3,     4,
       3,     6,     5,     1,     1,     1,     1,     1,     3,     1,
       1,     5,     9,     3,     3,     3,     9,     5,     3,     4,
       3,     3,     3,     3,     2,     2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     4,     0,     0,     0,     0,
       3,     0,     0,    10,     0,     0,     0,     0,     0,     8,
       7,     5,     6,     0,     0,     0,    11,    16,     9,     0,
       0,    16,    29,    26,    25,     0,     0,     0,     0,     0,
      13,     0,     0,    23,    24,    27,    30,    17,     0,     0,
       0,     0,    46,    44,     0,     0,    18,     0,     0,    47,
      45,     0,     0,     0,     0,     0,     0,     0,     0,    12,
      43,     0,    20,     0,    14,    16,     0,    16,    42,    28,
      33,    34,    35,    38,    40,    41,     0,     0,    19,     0,
       0,     0,     0,    39,    22,     0,    15,    31,     0,    37,
      21,     0,     0,    16,    16,     0,     0,    32,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    23,    45,    14,     5,    73,    30,    46,    47
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -35
static const yytype_int16 yypact[] =
{
     -35,    12,   -35,   -15,    19,   -35,    32,    13,    15,    14,
     -35,    -2,    40,   -35,   -20,    30,     7,    10,     9,   -35,
     -35,   -35,   -35,    27,    30,    30,   -35,   -35,   -35,    36,
      74,   -35,    -6,   -35,   -35,   280,   280,   280,   280,   280,
     -35,    64,    65,   -35,   -35,    68,   -35,   357,    97,   280,
      79,   212,   -35,   -35,   310,    49,   357,   322,   346,   -35,
     -35,   280,   280,   280,   280,   280,   280,   280,    73,   -35,
     357,    61,   -35,   -18,   357,   -35,   280,   -35,   -35,   357,
       4,     4,   219,   357,   357,   357,   280,   246,   -35,   280,
     120,    67,   143,   357,   -35,     8,   357,    72,   280,   -35,
     -35,    63,   334,   -35,   -35,   166,   189,   -35,   -35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,    35,     5,   -35,   -35,     6,   -31,   -35,   -34
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      48,    54,    55,    56,    57,    58,    17,    49,    88,    18,
       6,    89,     2,    64,    13,    70,    65,    74,    50,    51,
      66,    67,     7,    26,    52,    53,    68,    79,    80,    81,
      82,    83,    84,    85,   100,     3,     8,    89,     9,    15,
      11,    10,    91,    16,    90,    12,    92,     4,    24,    19,
      12,    25,    93,    74,    27,    96,    62,    63,    64,    28,
      29,    65,    20,    31,   102,    66,    67,    59,    60,    21,
      22,    68,   105,   106,    62,    63,    64,    32,    33,    65,
      34,    61,    71,    66,    67,    86,    87,   101,    35,    68,
     103,    76,    36,    95,    37,    38,     0,     0,     0,    39,
      32,    33,    40,    34,    41,    42,     0,    43,    44,    98,
      12,    35,     0,     0,     0,    36,     0,    37,    38,     0,
       0,     0,    39,    32,    33,    69,    34,    41,    42,     0,
      43,    44,     0,    12,    35,     0,     0,     0,    36,     0,
      37,    38,     0,     0,     0,    39,    32,    33,    97,    34,
      41,    42,     0,    43,    44,     0,    12,    35,     0,     0,
       0,    36,     0,    37,    38,     0,     0,     0,    39,    32,
      33,    99,    34,    41,    42,     0,    43,    44,     0,    12,
      35,     0,     0,     0,    36,     0,    37,    38,     0,     0,
       0,    39,    32,    33,   107,    34,    41,    42,     0,    43,
      44,     0,    12,    35,     0,     0,     0,    36,     0,    37,
      38,     0,     0,     0,    39,    32,    33,   108,    34,    41,
      42,     0,    43,    44,     0,    12,    35,     0,     0,     0,
      36,    65,     0,    38,     0,    66,    67,    39,    72,     0,
       0,    68,    41,    42,     0,    43,    44,     0,    12,    32,
      33,     0,    34,     0,     0,     0,     0,     0,     0,     0,
      35,     0,     0,     0,    36,     0,     0,    38,     0,     0,
       0,    39,    94,     0,     0,     0,    41,    42,     0,    43,
      44,     0,    12,    32,    33,     0,    34,     0,     0,     0,
       0,     0,     0,     0,    35,     0,     0,     0,    36,     0,
       0,    38,     0,     0,     0,    39,     0,     0,     0,     0,
      41,    42,     0,    43,    44,     0,    12,    62,    63,    64,
       0,     0,    65,     0,     0,     0,    66,    67,     0,    62,
      63,    64,    68,     0,    65,     0,     0,    75,    66,    67,
       0,    62,    63,    64,    68,     0,    65,     0,     0,    77,
      66,    67,     0,    62,    63,    64,    68,     0,    65,     0,
       0,   104,    66,    67,    62,    63,    64,     0,    68,    65,
       0,     0,    78,    66,    67,     0,     0,     0,     0,    68
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-35))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      31,    35,    36,    37,    38,    39,    26,    13,    26,    29,
      25,    29,     0,     9,     9,    49,    12,    51,    24,    25,
      16,    17,     3,    18,    30,    31,    22,    61,    62,    63,
      64,    65,    66,    67,    26,    23,     4,    29,    25,    41,
      26,    26,    76,     3,    75,    36,    77,    35,    41,    19,
      36,    41,    86,    87,    27,    89,     7,     8,     9,    24,
      25,    12,    32,    27,    98,    16,    17,     3,     3,    39,
      40,    22,   103,   104,     7,     8,     9,     3,     4,    12,
       6,    13,     3,    16,    17,    12,    25,    15,    14,    22,
      27,    42,    18,    87,    20,    21,    -1,    -1,    -1,    25,
       3,     4,    28,     6,    30,    31,    -1,    33,    34,    42,
      36,    14,    -1,    -1,    -1,    18,    -1,    20,    21,    -1,
      -1,    -1,    25,     3,     4,    28,     6,    30,    31,    -1,
      33,    34,    -1,    36,    14,    -1,    -1,    -1,    18,    -1,
      20,    21,    -1,    -1,    -1,    25,     3,     4,    28,     6,
      30,    31,    -1,    33,    34,    -1,    36,    14,    -1,    -1,
      -1,    18,    -1,    20,    21,    -1,    -1,    -1,    25,     3,
       4,    28,     6,    30,    31,    -1,    33,    34,    -1,    36,
      14,    -1,    -1,    -1,    18,    -1,    20,    21,    -1,    -1,
      -1,    25,     3,     4,    28,     6,    30,    31,    -1,    33,
      34,    -1,    36,    14,    -1,    -1,    -1,    18,    -1,    20,
      21,    -1,    -1,    -1,    25,     3,     4,    28,     6,    30,
      31,    -1,    33,    34,    -1,    36,    14,    -1,    -1,    -1,
      18,    12,    -1,    21,    -1,    16,    17,    25,    26,    -1,
      -1,    22,    30,    31,    -1,    33,    34,    -1,    36,     3,
       4,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,    -1,
      -1,    25,    26,    -1,    -1,    -1,    30,    31,    -1,    33,
      34,    -1,    36,     3,     4,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    14,    -1,    -1,    -1,    18,    -1,
      -1,    21,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      30,    31,    -1,    33,    34,    -1,    36,     7,     8,     9,
      -1,    -1,    12,    -1,    -1,    -1,    16,    17,    -1,     7,
       8,     9,    22,    -1,    12,    -1,    -1,    27,    16,    17,
      -1,     7,     8,     9,    22,    -1,    12,    -1,    -1,    27,
      16,    17,    -1,     7,     8,     9,    22,    -1,    12,    -1,
      -1,    27,    16,    17,     7,     8,     9,    -1,    22,    12,
      -1,    -1,    26,    16,    17,    -1,    -1,    -1,    -1,    22
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,     0,    23,    35,    49,    25,     3,     4,    25,
      26,    26,    36,    47,    48,    41,     3,    26,    29,    19,
      32,    39,    40,    46,    41,    41,    47,    27,    46,    46,
      51,    27,     3,     4,     6,    14,    18,    20,    21,    25,
      28,    30,    31,    33,    34,    47,    52,    53,    51,    13,
      24,    25,    30,    31,    53,    53,    53,    53,    53,     3,
       3,    13,     7,     8,     9,    12,    16,    17,    22,    28,
      53,     3,    26,    50,    53,    27,    42,    27,    26,    53,
      53,    53,    53,    53,    53,    53,    12,    25,    26,    29,
      51,    53,    51,    53,    26,    50,    53,    28,    42,    28,
      26,    15,    53,    27,    27,    51,    51,    28,    28
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  yylloc.first_column = yylloc.last_column = 1;
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1806 of yacc.c  */
#line 91 "./src/Parser/Parser.yy"
    {
		Variables.clear();
		(yyval.statements) = 0;
	}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 94 "./src/Parser/Parser.yy"
    {
		ImportList.push_back(*(yyvsp[(4) - (5)].string));
		delete (yyvsp[(4) - (5)].string);
		(yyval.statements) = 0;
	}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 98 "./src/Parser/Parser.yy"
    {
		(yyval.statements) = 0;
	}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 103 "./src/Parser/Parser.yy"
    {
		(yyval.type) = Int;
	}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 105 "./src/Parser/Parser.yy"
    {
		(yyval.type) = String;
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 107 "./src/Parser/Parser.yy"
    {
		(yyval.type) = Boolean;
	}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 109 "./src/Parser/Parser.yy"
    {
		(yyval.type) = Void;
	}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 114 "./src/Parser/Parser.yy"
    {

		if (((ValueType)(yyvsp[(4) - (4)].type)) == TYPE_VOID) {
			yyerror("Cannot declare a variable as a void.");
			return -1;
		}

		auto it = Variables.find(*(yyvsp[(2) - (4)].string));
			
		if (it != Variables.end()) {
			yyerror("Variable already defined.");
			return -1;
		} else {
			Variable* nVar = new Variable((yyvsp[(4) - (4)].type), 0, ValueUtil::generateValue((yyvsp[(4) - (4)].type)));
			Variables[*(yyvsp[(2) - (4)].string)] = nVar;
			(yyval.variable) = nVar;
		}
		
	}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 135 "./src/Parser/Parser.yy"
    {
		(yyval.variables) = new std::vector<SP<Variable>>();
		(yyval.variables)->push_back((yyvsp[(1) - (1)].variable));
	}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 138 "./src/Parser/Parser.yy"
    {
		(yyval.variables) = (yyvsp[(1) - (3)].variables);
		(yyval.variables)->push_back((yyvsp[(3) - (3)].variable));
	}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 144 "./src/Parser/Parser.yy"
    {
		std::vector<SP<Variable>> values;

		int pos = 0;
		for (auto it = Variables.begin(); it != Variables.end(); it++) {
			it->second->setPosition(pos);
			values.push_back(it->second);
			pos++;
		}

		SP<Function> fn = new ScriptedFunction((yyvsp[(7) - (10)].type), ValueUtil::generateValue((yyvsp[(7) - (10)].type)), *(yyvsp[(9) - (10)].statements), values, *(yyvsp[(4) - (10)].variables));
		
		if ( Functions[*(yyvsp[(2) - (10)].string)].size() > 0) {
		
			if (Parser::functionSetType(Functions[*(yyvsp[(2) - (10)].string)]) != (yyvsp[(7) - (10)].type)) {
				yyerror("Function differs from predefined function type");
				return -1;
			}
			
			if (Parser::functionSetNumArguments(Functions[*(yyvsp[(2) - (10)].string)]) != values.size()) {
				yyerror("Due to previous definition function is expected to have a specific number of arguments");
				return -1;
			}
			
			if (Parser::functionSetAlreadyContainsEquivilent(fn, Functions[*(yyvsp[(2) - (10)].string)]) == true) {
				yyerror("Identical function already defined");
				return -1;
			}
		}
		
		Functions[*(yyvsp[(2) - (10)].string)].push_back(fn);
		
		Variables.clear();
		
		delete (yyvsp[(2) - (10)].string);

	}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 180 "./src/Parser/Parser.yy"
    {
		
		std::vector<SP<Variable>> values;

		int pos = 0;
		for (auto it = Variables.begin(); it != Variables.end(); it++) {
			it->second->setPosition(pos);
			values.push_back(it->second);
			pos++;
		}
	
		SP<Function> fn = SP<Function>(new ScriptedFunction((yyvsp[(6) - (9)].type), ValueUtil::generateValue((yyvsp[(6) - (9)].type)), *(yyvsp[(8) - (9)].statements), values, std::vector<SP<Variable>>()));

		if ( Functions[*(yyvsp[(2) - (9)].string)].size() > 0) {

			if (Parser::functionSetType(Functions[*(yyvsp[(2) - (9)].string)]) != (yyvsp[(6) - (9)].type)) {
				yyerror("Function differs from predefined function type");
				return -1;
			}

			if (Parser::functionSetNumArguments(Functions[*(yyvsp[(2) - (9)].string)]) != values.size()) {
				yyerror("Due to previous definition function is expected to have a specific number of arguments");
				return -1;
			}

			if (Parser::functionSetAlreadyContainsEquivilent(fn, Functions[*(yyvsp[(2) - (9)].string)]) == true) {
				yyerror("Identical function already defined");
				return -1;
			}

		}
		
		Functions[*(yyvsp[(2) - (9)].string)].push_back(fn);
	
		Variables.clear();

		delete (yyvsp[(2) - (9)].string);
	}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 220 "./src/Parser/Parser.yy"
    {
		(yyval.statements) = new std::vector<SmartPointer<Statement>>();
		(yyval.statements)->push_back((yyvsp[(1) - (1)].statement));
	}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 223 "./src/Parser/Parser.yy"
    {
		(yyval.statements) = (yyvsp[(1) - (3)].statements);
		(yyval.statements)->push_back((yyvsp[(3) - (3)].statement));
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 229 "./src/Parser/Parser.yy"
    {
		(yyval.statements) = new std::vector<SmartPointer<Statement>>();
	}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 231 "./src/Parser/Parser.yy"
    {
		(yyval.statements) = (yyvsp[(1) - (2)].statements);
		(yyval.statements)->push_back((yyvsp[(2) - (2)].statement));
	}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 234 "./src/Parser/Parser.yy"
    {
		(yyval.statements) = (yyvsp[(1) - (3)].statements);
		(yyval.statements)->push_back(new ReturnStatement(yylineno, yytext, (yyvsp[(3) - (3)].statement)));
	}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 240 "./src/Parser/Parser.yy"
    {
	
		std::vector<SmartPointer<Statement>> args;
	
		for (unsigned int i = 0; i < (yyvsp[(3) - (4)].statements)->size(); ++i) {
			args.push_back((yyvsp[(3) - (4)].statements)->at(i));
		}
	
		delete (yyvsp[(3) - (4)].statements);
		
		SmartPointer<FunctionReference> reference = SmartPointer<FunctionReference>(new FunctionReference("", *(yyvsp[(1) - (4)].string), args, 0));
		References.push_back(reference);
		(yyval.statement) = new FunctionStatement(yylineno, yytext, reference);
		
		//Free the name pointer
		delete (yyvsp[(1) - (4)].string);
		
	}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 257 "./src/Parser/Parser.yy"
    {
		std::vector<SmartPointer<Statement>> args;
		SmartPointer<FunctionReference> reference = SmartPointer<FunctionReference>(new FunctionReference("", *(yyvsp[(1) - (3)].string), args, 0));
		References.push_back(reference);
		(yyval.statement) = new FunctionStatement(yylineno, yytext, reference);
		
		//Free the name pointer
		delete (yyvsp[(1) - (3)].string);
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 265 "./src/Parser/Parser.yy"
    {
	
		std::vector<SmartPointer<Statement>> args;
	
		for (unsigned int i = 0; i < (yyvsp[(5) - (6)].statements)->size(); ++i) {
			args.push_back((yyvsp[(5) - (6)].statements)->at(i));
		}
	
		delete (yyvsp[(5) - (6)].statements);
	
		SmartPointer<FunctionReference> reference = SmartPointer<FunctionReference>(new FunctionReference(*(yyvsp[(1) - (6)].string), *(yyvsp[(3) - (6)].string), args, 0));
		References.push_back(reference);
	
		(yyval.statement) = new FunctionStatement(yylineno, yytext, reference);
	
		//Free the name pointers
		delete (yyvsp[(1) - (6)].string);
		delete (yyvsp[(3) - (6)].string);
		
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 284 "./src/Parser/Parser.yy"
    {
		std::vector<SmartPointer<Statement>> args;
		SmartPointer<FunctionReference> reference = SmartPointer<FunctionReference>(new FunctionReference(*(yyvsp[(1) - (5)].string), *(yyvsp[(3) - (5)].string), args, 0));
		References.push_back(reference);
		(yyval.statement) = new FunctionStatement(yylineno, yytext, reference);
		
		//Free the name pointers
		delete (yyvsp[(1) - (5)].string);
		delete (yyvsp[(3) - (5)].string);

	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 297 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new BoolStatement(yylineno, yytext, true);
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 299 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new BoolStatement(yylineno, yytext, false);
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 301 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new IntStatement(yylineno, yytext, (yyvsp[(1) - (1)].integer));
	}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 303 "./src/Parser/Parser.yy"
    {
		
		(yyval.statement) = new StringStatement(yylineno, yytext, *(yyvsp[(1) - (1)].string));
		
		//Free string pointer
		delete (yyvsp[(1) - (1)].string);
		
	}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 310 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new GetVariableStatement(yylineno, yytext, (yyvsp[(1) - (1)].variable));
	}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 312 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new AssignVariableStatement(yylineno, yytext, (yyvsp[(1) - (3)].variable), (yyvsp[(3) - (3)].statement));
	}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 314 "./src/Parser/Parser.yy"
    {

		auto it = Variables.find(*(yyvsp[(1) - (1)].string));

		if (it == Variables.end()) {
			yyerror("Variable not defined");
			return -1;
		} else {
			(yyval.statement) = new GetVariableStatement(yylineno, yytext, it->second);
		}

		//Free name pointer
		delete (yyvsp[(1) - (1)].string);
		
	}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 328 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = (yyvsp[(1) - (1)].statement);
	}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 330 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new IfStatement(yylineno, yytext, (yyvsp[(2) - (5)].statement), *(yyvsp[(4) - (5)].statements), std::vector<SP<Statement>>());
	}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 332 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new IfStatement(yylineno, yytext, (yyvsp[(2) - (9)].statement), *(yyvsp[(4) - (9)].statements), *(yyvsp[(8) - (9)].statements));
	}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 334 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new OperateStatement(yylineno, yytext, Add, (yyvsp[(1) - (3)].statement), (yyvsp[(3) - (3)].statement));
	}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 336 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new OperateStatement(yylineno, yytext, Subtract, (yyvsp[(1) - (3)].statement), (yyvsp[(3) - (3)].statement));
	}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 338 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new OperateStatement(yylineno, yytext, Multiply, (yyvsp[(1) - (3)].statement), (yyvsp[(3) - (3)].statement));
	}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 340 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new ForStatement(yylineno, yytext, (yyvsp[(2) - (9)].statement), (yyvsp[(4) - (9)].statement), (yyvsp[(6) - (9)].statement), *(yyvsp[(8) - (9)].statements));
	}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 342 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new WhileStatement(yylineno, yytext, (yyvsp[(2) - (5)].statement), *(yyvsp[(4) - (5)].statements));
	}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 344 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new TestStatement(yylineno, yytext, TestEquals, (yyvsp[(1) - (3)].statement), (yyvsp[(3) - (3)].statement));
	}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 346 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new TestStatement(yylineno, yytext, TestNotEquals, (yyvsp[(1) - (4)].statement), (yyvsp[(4) - (4)].statement));
	}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 348 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new TestStatement(yylineno, yytext, TestGreater, (yyvsp[(1) - (3)].statement), (yyvsp[(3) - (3)].statement));
	}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 350 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = new TestStatement(yylineno, yytext, TestLess, (yyvsp[(1) - (3)].statement), (yyvsp[(3) - (3)].statement));
	}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 352 "./src/Parser/Parser.yy"
    {
		(yyval.statement) = (yyvsp[(2) - (3)].statement);
	}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 354 "./src/Parser/Parser.yy"
    {
		
		auto it = Variables.find(*(yyvsp[(1) - (3)].string));

		if (it == Variables.end()) {
			yyerror("Variable not defined");
		} else {
			(yyval.statement) = new AssignVariableStatement(yylineno, yytext, it->second, (yyvsp[(3) - (3)].statement));
		}
		
		//Free up string pointer.
		delete (yyvsp[(1) - (3)].string);
		
	}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 367 "./src/Parser/Parser.yy"
    {
	
		auto it = Variables.find(*(yyvsp[(1) - (2)].string));
		if (it == Variables.end()) {
			yyerror("Variable not defined");
		} else {
			(yyval.statement) = new IncrementStatement(yylineno, yytext, it->second, Increment, false);
		}
		
		//Free name pointer
		delete (yyvsp[(1) - (2)].string);
		
	}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 379 "./src/Parser/Parser.yy"
    {
		auto it = Variables.find(*(yyvsp[(2) - (2)].string));
		if (it == Variables.end()) {
			yyerror("Variable not defined");
		} else {
			(yyval.statement) = new IncrementStatement(yylineno, yytext, it->second, Increment, true);
		}
		
		//Free name pointer
		delete (yyvsp[(2) - (2)].string);
		
	}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 390 "./src/Parser/Parser.yy"
    {
		auto it = Variables.find(*(yyvsp[(1) - (2)].string));
		if (it == Variables.end()) {
			yyerror("Variable not defined");
		} else {
			(yyval.statement) = new IncrementStatement(yylineno, yytext, it->second, Decrement, false);
		}
		
		//Free name pointer
		delete (yyvsp[(1) - (2)].string);
		
	}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 401 "./src/Parser/Parser.yy"
    {
		auto it = Variables.find(*(yyvsp[(2) - (2)].string));
		if (it == Variables.end()) {
			yyerror("Variable not defined");
		} else {
			(yyval.statement) = new IncrementStatement(yylineno, yytext, it->second, Decrement, true);
		}
		
		//Free name pointer
		delete (yyvsp[(2) - (2)].string);
	}
    break;



/* Line 1806 of yacc.c  */
#line 2263 "./gen/Parser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  yyerror_range[1] = yylsp[1-yylen];
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
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
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



/* Line 2067 of yacc.c  */
#line 414 "./src/Parser/Parser.yy"


void yyerror(std::string s)
{

  printf("ERROR: %s at symbol %s on line %i\n", s.c_str(), yytext, yylineno);
  ParsingError = true;
}

void yyerror(const char* s)
{
  yyerror(std::string(s));
}

