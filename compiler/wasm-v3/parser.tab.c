/* A Bison parser, made by GNU Bison 3.8.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30801

/* Bison version string.  */
#define YYBISON_VERSION "3.8.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbolTable.h"
#include "AST.h"
#include "ircode.h"
#include "semantic.h"
#include "webgen.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
char scopeStack[50][50];
char currentFunctionScope[50];
int stackPointer;
int blockNumber;

#line 94 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TYPE = 3,                       /* TYPE  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_INTEGER = 5,                    /* INTEGER  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_STRING = 7,                     /* STRING  */
  YYSYMBOL_LOGICALOPERATOR = 8,            /* LOGICALOPERATOR  */
  YYSYMBOL_COMPARSIONOPERATOR = 9,         /* COMPARSIONOPERATOR  */
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_COMMA = 11,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 12,                 /* SEMICOLON  */
  YYSYMBOL_EQ = 13,                        /* EQ  */
  YYSYMBOL_LEFTBRACKET = 14,               /* LEFTBRACKET  */
  YYSYMBOL_RIGHTBRACKET = 15,              /* RIGHTBRACKET  */
  YYSYMBOL_LEFTPAREN = 16,                 /* LEFTPAREN  */
  YYSYMBOL_RIGHTPAREN = 17,                /* RIGHTPAREN  */
  YYSYMBOL_LEFTSQUARE = 18,                /* LEFTSQUARE  */
  YYSYMBOL_RIGHTSQUARE = 19,               /* RIGHTSQUARE  */
  YYSYMBOL_NUMBER = 20,                    /* NUMBER  */
  YYSYMBOL_LET = 21,                       /* LET  */
  YYSYMBOL_DECLARE = 22,                   /* DECLARE  */
  YYSYMBOL_AS = 23,                        /* AS  */
  YYSYMBOL_WRITE = 24,                     /* WRITE  */
  YYSYMBOL_WRITELN = 25,                   /* WRITELN  */
  YYSYMBOL_READ = 26,                      /* READ  */
  YYSYMBOL_RETURN = 27,                    /* RETURN  */
  YYSYMBOL_IF = 28,                        /* IF  */
  YYSYMBOL_ELIF = 29,                      /* ELIF  */
  YYSYMBOL_ELSE = 30,                      /* ELSE  */
  YYSYMBOL_WHILE = 31,                     /* WHILE  */
  YYSYMBOL_BREAK = 32,                     /* BREAK  */
  YYSYMBOL_FOR = 33,                       /* FOR  */
  YYSYMBOL_TRUE = 34,                      /* TRUE  */
  YYSYMBOL_FALSE = 35,                     /* FALSE  */
  YYSYMBOL_FUNCTION = 36,                  /* FUNCTION  */
  YYSYMBOL_PLUS = 37,                      /* PLUS  */
  YYSYMBOL_MINUS = 38,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 39,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 40,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 41,                    /* MODULO  */
  YYSYMBOL_EXPONENT = 42,                  /* EXPONENT  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_ProgramStart = 44,              /* ProgramStart  */
  YYSYMBOL_Program = 45,                   /* Program  */
  YYSYMBOL_DeclList = 46,                  /* DeclList  */
  YYSYMBOL_Decl = 47,                      /* Decl  */
  YYSYMBOL_VarDecl = 48,                   /* VarDecl  */
  YYSYMBOL_FunDeclList = 49,               /* FunDeclList  */
  YYSYMBOL_FunDeclListTail = 50,           /* FunDeclListTail  */
  YYSYMBOL_FuncHeader = 51,                /* FuncHeader  */
  YYSYMBOL_FunDecl = 52,                   /* FunDecl  */
  YYSYMBOL_ParamDeclList = 53,             /* ParamDeclList  */
  YYSYMBOL_ParamDeclListTail = 54,         /* ParamDeclListTail  */
  YYSYMBOL_ParamDecl = 55,                 /* ParamDecl  */
  YYSYMBOL_StmtList = 56,                  /* StmtList  */
  YYSYMBOL_Stmt = 57,                      /* Stmt  */
  YYSYMBOL_IfStmt = 58,                    /* IfStmt  */
  YYSYMBOL_IfStmtTail = 59,                /* IfStmtTail  */
  YYSYMBOL_Loop = 60,                      /* Loop  */
  YYSYMBOL_ForHead = 61,                   /* ForHead  */
  YYSYMBOL_ForL = 62,                      /* ForL  */
  YYSYMBOL_WhileHead = 63,                 /* WhileHead  */
  YYSYMBOL_WhileL = 64,                    /* WhileL  */
  YYSYMBOL_IfHead = 65,                    /* IfHead  */
  YYSYMBOL_If = 66,                        /* If  */
  YYSYMBOL_ElifHead = 67,                  /* ElifHead  */
  YYSYMBOL_Elif = 68,                      /* Elif  */
  YYSYMBOL_ElseHead = 69,                  /* ElseHead  */
  YYSYMBOL_Else = 70,                      /* Else  */
  YYSYMBOL_Primary = 71,                   /* Primary  */
  YYSYMBOL_ExprListTail = 72,              /* ExprListTail  */
  YYSYMBOL_ExprList = 73,                  /* ExprList  */
  YYSYMBOL_Block = 74,                     /* Block  */
  YYSYMBOL_Expr = 75,                      /* Expr  */
  YYSYMBOL_FunctionCall = 76               /* FunctionCall  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   243

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  158

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    89,    89,    95,    98,   110,   112,   115,   117,   126,
     151,   176,   198,   221,   222,   223,   226,   227,   230,   255,
     264,   267,   270,   271,   274,   277,   282,   285,   290,   295,
     296,   300,   313,   317,   324,   325,   326,   327,   330,   336,
     337,   338,   340,   343,   348,   361,   369,   381,   389,   402,
     412,   424,   434,   445,   456,   457,   458,   459,   460,   461,
     470,   471,   474,   479,   480,   485,   490,   498,   522,   553,
     577,   604,   614,   623,   632,   669,   678,   686,   692,   693,
     694,   695,   696,   700
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TYPE", "ID",
  "INTEGER", "FLOAT", "STRING", "LOGICALOPERATOR", "COMPARSIONOPERATOR",
  "CHAR", "COMMA", "SEMICOLON", "EQ", "LEFTBRACKET", "RIGHTBRACKET",
  "LEFTPAREN", "RIGHTPAREN", "LEFTSQUARE", "RIGHTSQUARE", "NUMBER", "LET",
  "DECLARE", "AS", "WRITE", "WRITELN", "READ", "RETURN", "IF", "ELIF",
  "ELSE", "WHILE", "BREAK", "FOR", "TRUE", "FALSE", "FUNCTION", "PLUS",
  "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "EXPONENT", "$accept",
  "ProgramStart", "Program", "DeclList", "Decl", "VarDecl", "FunDeclList",
  "FunDeclListTail", "FuncHeader", "FunDecl", "ParamDeclList",
  "ParamDeclListTail", "ParamDecl", "StmtList", "Stmt", "IfStmt",
  "IfStmtTail", "Loop", "ForHead", "ForL", "WhileHead", "WhileL", "IfHead",
  "If", "ElifHead", "Elif", "ElseHead", "Else", "Primary", "ExprListTail",
  "ExprList", "Block", "Expr", "FunctionCall", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-32)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-4)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      14,     4,    12,    21,   -32,   175,   -32,    14,     0,     5,
     -32,   140,   -32,   -32,   -32,   -32,    14,   208,   -32,    28,
     137,    -8,    33,   208,     9,    40,    47,   -32,   -32,    41,
     -32,   -32,    54,    44,     7,   175,   -32,   -32,    54,   -32,
      54,   -32,    54,    46,   -32,   -32,    15,   -32,   -32,   -32,
      82,    74,   208,   137,    84,    76,    22,     2,    79,    80,
     -32,    99,    70,   208,   208,   208,    95,   -32,   -32,    44,
     -32,   -32,   -32,   -32,   -32,    97,   -32,   -32,    54,    46,
      54,   -32,   208,   208,   208,   -32,   208,   208,   208,   208,
     208,   109,    72,   112,   107,   -32,   117,   116,   -32,   -32,
     208,   131,   143,   -32,   -32,   -32,    77,    87,   122,   139,
     208,   -32,   -32,   -32,   136,    63,   112,     3,     3,     8,
       8,   152,   153,   -32,   165,   137,   -32,   159,   112,   158,
     164,   -32,   -32,   -32,   181,   129,   -32,   166,   -32,   208,
     173,   -32,   184,   176,   -32,   179,   -32,   180,   112,   208,
     186,   -32,   181,   -32,   112,   178,   -32,   -32
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       7,     0,     0,     0,     2,    13,     6,     7,     0,     0,
       1,    56,    54,    58,    57,    29,     7,     0,    55,     0,
       0,     0,     0,     0,     0,     0,     0,    81,    82,     0,
      28,    15,     0,    14,     7,    13,    37,    36,     0,    42,
       0,    43,     0,    39,    66,    35,     0,    80,     5,     9,
       0,     0,     0,    60,     0,     0,     0,     0,    56,     0,
      32,     0,     0,     0,     0,     0,     0,    19,    17,    16,
       4,    27,    45,    47,    49,     0,    52,    38,     0,    39,
       0,    40,     0,     0,     0,    30,     0,     0,     0,     0,
       0,     0,     0,    67,    61,    64,     0,     0,    65,    79,
       0,     0,     0,    31,    34,    33,     0,     0,     0,     0,
       0,    51,    41,    53,    78,    77,    76,    71,    72,    73,
      74,    75,     0,    10,     0,    60,    83,    59,    69,     0,
       0,    48,    46,    44,    20,     0,    11,     0,    62,     0,
       0,    59,     0,     0,    21,    22,    50,     0,    68,     0,
      24,    18,     0,    12,    70,     0,    23,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -32,   -32,    24,   187,   -32,   -32,   -32,   -31,   -32,   -28,
     -32,    53,   -32,   163,   -32,   -32,   128,   -32,   -32,   -32,
     -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -19,    91,
     -32,   -29,   -17,   -32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,    30,    31,    32,    33,
     143,   144,   145,    34,    35,    36,    77,    37,    38,    39,
      40,    41,    42,    43,    78,    79,    80,    81,    44,    95,
      96,    45,    46,    47
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    59,    68,    67,    60,    69,    62,    -3,     8,    72,
       1,    73,    49,    74,    84,   100,     9,     1,    50,    84,
     101,    10,    -3,    82,    83,    63,    84,    85,    51,     2,
      82,    83,    57,    84,    94,    93,     2,    61,    68,    99,
      55,    69,    88,    89,    66,    90,   106,   107,   108,   111,
      90,   113,    86,    87,    88,    89,    64,    90,    70,    86,
      87,    88,    89,    65,    90,   114,   115,   116,    16,   117,
     118,   119,   120,   121,    84,    75,    76,    92,    82,    83,
      29,    84,   105,   128,   123,    82,    83,    91,    84,    97,
     124,    98,   103,   135,   131,    82,    83,   102,    84,   109,
      86,    87,    88,    89,   132,    90,    94,    86,    87,    88,
      89,   104,    90,   110,    86,    87,    88,    89,   125,    90,
      82,    83,   148,    84,    86,    87,    88,    89,   122,    90,
      82,    83,   154,    84,   126,   127,   129,    82,    83,   133,
      84,    58,    12,    13,    14,    83,   146,    84,   130,    86,
      87,    88,    89,    52,    90,   134,    53,    18,    54,    86,
      87,    88,    89,    84,    90,   136,    86,    87,    88,    89,
     137,    90,   139,    86,    87,    88,    89,   140,    90,    11,
      12,    13,    14,   141,   142,   147,   149,    15,   150,    16,
     152,    17,   153,   151,    48,    18,    19,   157,    71,    20,
      21,    22,    23,    24,   155,   156,    25,   112,    26,    27,
      28,    29,    11,    12,    13,    14,   138,     0,     0,     0,
       0,     0,     0,     0,    17,     0,     0,     0,    18,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,    28
};

static const yytype_int16 yycheck[] =
{
      17,    20,    33,    32,    12,    33,    23,     0,     4,    38,
       3,    40,    12,    42,    11,    13,     4,     3,    18,    11,
      18,     0,    15,     8,     9,    16,    11,    12,    23,    22,
       8,     9,     4,    11,    53,    52,    22,     4,    69,    17,
      16,    69,    39,    40,     3,    42,    63,    64,    65,    78,
      42,    80,    37,    38,    39,    40,    16,    42,    34,    37,
      38,    39,    40,    16,    42,    82,    83,    84,    14,    86,
      87,    88,    89,    90,    11,    29,    30,     3,     8,     9,
      36,    11,    12,   100,    12,     8,     9,     5,    11,     5,
      18,    15,    12,   110,    17,     8,     9,    18,    11,     4,
      37,    38,    39,    40,    17,    42,   125,    37,    38,    39,
      40,    12,    42,    16,    37,    38,    39,    40,    11,    42,
       8,     9,   139,    11,    37,    38,    39,    40,    19,    42,
       8,     9,   149,    11,    17,    19,     5,     8,     9,    17,
      11,     4,     5,     6,     7,     9,    17,    11,     5,    37,
      38,    39,    40,    13,    42,    16,    16,    20,    18,    37,
      38,    39,    40,    11,    42,    12,    37,    38,    39,    40,
       5,    42,    13,    37,    38,    39,    40,    19,    42,     4,
       5,     6,     7,    19,     3,    19,    13,    12,     4,    14,
      11,    16,    12,    17,     7,    20,    21,    19,    35,    24,
      25,    26,    27,    28,    18,   152,    31,    79,    33,    34,
      35,    36,     4,     5,     6,     7,   125,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    22,    44,    45,    46,    47,    48,     4,     4,
       0,     4,     5,     6,     7,    12,    14,    16,    20,    21,
      24,    25,    26,    27,    28,    31,    33,    34,    35,    36,
      49,    50,    51,    52,    56,    57,    58,    60,    61,    62,
      63,    64,    65,    66,    71,    74,    75,    76,    46,    12,
      18,    23,    13,    16,    18,    45,    75,     4,     4,    71,
      12,     4,    75,    16,    16,    16,     3,    74,    50,    52,
      45,    56,    74,    74,    74,    29,    30,    59,    67,    68,
      69,    70,     8,     9,    11,    12,    37,    38,    39,    40,
      42,     5,     3,    75,    71,    72,    73,     5,    15,    17,
      13,    18,    18,    12,    12,    12,    75,    75,    75,     4,
      16,    74,    59,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    19,    12,    18,    11,    17,    19,    75,     5,
       5,    17,    17,    17,    16,    75,    12,     5,    72,    13,
      19,    19,     3,    53,    54,    55,    17,    19,    75,    13,
       4,    17,    11,    12,    75,    18,    54,    19
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    47,    47,    48,
      48,    48,    48,    49,    49,    49,    50,    50,    51,    52,
      53,    53,    54,    54,    55,    55,    56,    56,    56,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    58,    59,
      59,    59,    60,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    71,    71,    71,    71,    71,
      72,    72,    72,    73,    73,    74,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     3,     2,     1,     0,     1,     3,
       5,     6,     8,     0,     1,     1,     1,     2,     6,     2,
       0,     1,     1,     3,     2,     4,     1,     2,     1,     1,
       2,     3,     2,     3,     3,     1,     1,     1,     2,     0,
       1,     2,     1,     1,     4,     2,     4,     2,     4,     2,
       4,     2,     1,     2,     1,     1,     1,     1,     1,     4,
       0,     1,     3,     0,     1,     3,     1,     3,     6,     4,
       7,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* ProgramStart: Program  */
#line 89 "parser.y"
                      {
	printf("\n--------------------Parser End------------------------\n");

	ast = (yyval.ast);
}
#line 1285 "parser.tab.c"
    break;

  case 3: /* Program: DeclList StmtList  */
#line 95 "parser.y"
                           {
		(yyval.ast) = AST_DoublyChildNodes("program", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
	}
#line 1293 "parser.tab.c"
    break;

  case 4: /* Program: DeclList StmtList Program  */
#line 98 "parser.y"
                                  {
		printf("\nProgram Version: DeclList StmtList Program\n");
		struct AST * funcChildNode = AST_DoublyChildNodes("program", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
		(yyval.ast) = AST_DoublyChildNodes("program",(yyvsp[-2].ast), funcChildNode, (yyvsp[-2].ast), funcChildNode);
	}
#line 1303 "parser.tab.c"
    break;

  case 5: /* DeclList: VarDecl DeclList  */
#line 110 "parser.y"
                                { (yyval.ast) = AST_DoublyChildNodes("vardec", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
							}
#line 1310 "parser.tab.c"
    break;

  case 6: /* DeclList: Decl  */
#line 112 "parser.y"
                { (yyval.ast) = (yyvsp[0].ast); }
#line 1316 "parser.tab.c"
    break;

  case 7: /* Decl: %empty  */
#line 115 "parser.y"
      {
	(yyval.ast) = AST_SingleChildNode("empty", "empty", "empty");}
#line 1323 "parser.tab.c"
    break;

  case 8: /* Decl: VarDecl  */
#line 117 "parser.y"
                  {
	// Basic Var Declaration Rule, generates AST for all variable declarations
	(yyval.ast) = (yyvsp[0].ast);
	}
#line 1332 "parser.tab.c"
    break;

  case 9: /* VarDecl: TYPE ID SEMICOLON  */
#line 126 "parser.y"
                                {
		printf("\n RECOGNIZED RULE: Variable declaration %s\n", (yyvsp[-1].string));
		// Variable declaration rule
		// Symbol Table
		symTabAccess();
		int inSymTab = found((yyvsp[-1].string), scopeStack, stackPointer);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);

		// Check if the variable has been declared
		// If it has, throw an error
		if (inSymTab == 0) 
			addItem((yyvsp[-1].string), "Var", (yyvsp[-2].string), 0, scopeStack[stackPointer]);
		else {
			printf("SEMANTIC ERROR: Variable %s has already been declared.\n", (yyvsp[-1].string));
			exit(1);
		}
		// If the variable has not been declared 
		showSymTable();
		

		// Generate AST node as a doubly node
		(yyval.ast) = AST_DoublyChildNodes("type",(yyvsp[-2].string), (yyvsp[-1].string), (yyvsp[-2].string), (yyvsp[-1].string));

	}
#line 1361 "parser.tab.c"
    break;

  case 10: /* VarDecl: DECLARE ID AS TYPE SEMICOLON  */
#line 151 "parser.y"
                                        {
		printf("\n RECOGNIZED RULE: Variable declaration %s\n", (yyvsp[-3].string));
		// Variable declaration rule
		// Symbol Table
		symTabAccess();
		int inSymTab = found((yyvsp[-3].string), scopeStack, stackPointer);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
		
		// Check if the variable has been declared
		// If it has, throw an error
		if (inSymTab == 0) 
			addItem((yyvsp[-3].string), "Var", (yyvsp[-1].string), 0, scopeStack[stackPointer]);
		else {
			printf("SEMANTIC ERROR: Variable %s has already been declared.\n", (yyvsp[-3].string));
			exit(1);
		}
		// If the variable has not been declared 
		showSymTable();
		

		// Generate AST node as a doubly node
		(yyval.ast) = AST_DoublyChildNodes("type", (yyvsp[-1].string), (yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[-3].string));

	}
#line 1390 "parser.tab.c"
    break;

  case 11: /* VarDecl: TYPE ID LEFTSQUARE INTEGER RIGHTSQUARE SEMICOLON  */
#line 176 "parser.y"
                                                           {
		printf("RECOGNIZED RULE: Array declaration"); 
		symTabAccess(); 
		int inSymTab = found((yyvsp[-4].string), scopeStack, stackPointer);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
							
		// Check if the variable has been declared
		// If it has, throw an error
		if (inSymTab == 0) 
			addItem((yyvsp[-4].string), "Array", (yyvsp[-5].string), atoi((yyvsp[-2].string)), scopeStack[stackPointer]);
		else {
			printf("SEMANTIC ERROR: Variable %s has already been declared.\n", (yyvsp[-4].string));
			exit(1);
		}
		// If the variable has not been declared 
		showSymTable();

		struct AST* arraySize = AST_SingleChildNode("size", (yyvsp[-2].string), (yyvsp[-2].string)); 
		struct AST* array = AST_DoublyChildNodes((yyvsp[-4].string), "array", arraySize, "array", arraySize);
		(yyval.ast) = AST_DoublyChildNodes("type", (yyvsp[-5].string), array, (yyvsp[-5].string), array);
	}
#line 1416 "parser.tab.c"
    break;

  case 12: /* VarDecl: DECLARE ID AS TYPE LEFTSQUARE INTEGER RIGHTSQUARE SEMICOLON  */
#line 198 "parser.y"
                                                                      {
		printf("RECOGNIZED RULE: Array declaration"); 
		symTabAccess(); 
		int inSymTab = found((yyvsp[-6].string), scopeStack, stackPointer);
		//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
							
		// Check if the variable has been declared
		// If it has, throw an error
		if (inSymTab == 0) 
			addItem((yyvsp[-6].string), "Array", (yyvsp[-4].string), atoi((yyvsp[-2].string)), scopeStack[stackPointer]);
		else {
			printf("SEMANTIC ERROR: Variable %s has already been declared.\n", (yyvsp[-6].string));
			exit(1);
		}
		// If the variable has not been declared 
		showSymTable();

		struct AST* arraySize = AST_SingleChildNode("size", (yyvsp[-2].string), (yyvsp[-2].string)); 
		struct AST* array = AST_DoublyChildNodes((yyvsp[-6].string), "array", arraySize, "array", arraySize);
		(yyval.ast) = AST_DoublyChildNodes("type", (yyvsp[-4].string), array, (yyvsp[-4].string), array);
	}
#line 1442 "parser.tab.c"
    break;

  case 13: /* FunDeclList: %empty  */
#line 221 "parser.y"
             { 	(yyval.ast) = AST_SingleChildNode("empty", "empty", "empty");}
#line 1448 "parser.tab.c"
    break;

  case 14: /* FunDeclList: FunDecl  */
#line 222 "parser.y"
                  {(yyval.ast) = (yyvsp[0].ast);}
#line 1454 "parser.tab.c"
    break;

  case 15: /* FunDeclList: FunDeclListTail  */
#line 223 "parser.y"
                          {(yyval.ast) = (yyvsp[0].ast);}
#line 1460 "parser.tab.c"
    break;

  case 16: /* FunDeclListTail: FunDecl  */
#line 226 "parser.y"
                         {(yyval.ast) = (yyvsp[0].ast);}
#line 1466 "parser.tab.c"
    break;

  case 17: /* FunDeclListTail: FunDecl FunDeclListTail  */
#line 227 "parser.y"
                                  {(yyval.ast) = AST_DoublyChildNodes("FunDecl FunDeclListTail",(yyvsp[-1].ast),(yyvsp[0].ast),(yyvsp[-1].ast), (yyvsp[0].ast));}
#line 1472 "parser.tab.c"
    break;

  case 18: /* FuncHeader: FUNCTION TYPE ID LEFTPAREN ParamDeclList RIGHTPAREN  */
#line 230 "parser.y"
                                                                {
		symTabAccess();
		int inSymTab = found((yyvsp[-3].string), scopeStack, stackPointer);

		// Check if the function variable has already been declared
		// If it has, throw an error
		if (inSymTab == 0){
			addFunction((yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-1].ast), scopeStack, stackPointer); //id
		}
		else {
			printf("SEMANTIC ERROR: Function %s has already been declared.\n", (yyvsp[-3].string));
			exit(1);
		}

		showSymTable();
		(yyval.ast) = AST_DoublyChildNodes("function context", (yyvsp[-3].string), (yyvsp[-1].ast), (yyvsp[-3].string), (yyvsp[-1].ast));

		stackPointer += 1;
		memset(scopeStack[stackPointer], 0, 50 * sizeof(char));
		strcpy(scopeStack[stackPointer], (yyvsp[-3].string));
		memset(currentFunctionScope, 0, 50 * sizeof(char));
		strcpy(currentFunctionScope, (yyvsp[-3].string));
	}
#line 1500 "parser.tab.c"
    break;

  case 19: /* FunDecl: FuncHeader Block  */
#line 255 "parser.y"
                          {
	// Generate AST node as a doubly node
	(yyval.ast) = AST_DoublyChildNodes("function",(yyvsp[-1].ast),(yyvsp[0].ast),(yyvsp[-1].ast), (yyvsp[0].ast));
	stackPointer -= 1;
	memset(currentFunctionScope, 0, 50 * sizeof(char));
	strcpy(currentFunctionScope, scopeStack[stackPointer]);
}
#line 1512 "parser.tab.c"
    break;

  case 20: /* ParamDeclList: %empty  */
#line 264 "parser.y"
               {
		(yyval.ast) = AST_SingleChildNode("empty", "empty", "empty");
}
#line 1520 "parser.tab.c"
    break;

  case 21: /* ParamDeclList: ParamDeclListTail  */
#line 267 "parser.y"
                            {(yyval.ast) = (yyvsp[0].ast);}
#line 1526 "parser.tab.c"
    break;

  case 22: /* ParamDeclListTail: ParamDecl  */
#line 270 "parser.y"
                             {(yyval.ast) = (yyvsp[0].ast);}
#line 1532 "parser.tab.c"
    break;

  case 23: /* ParamDeclListTail: ParamDecl COMMA ParamDeclListTail  */
#line 271 "parser.y"
                                            {(yyval.ast) = AST_DoublyChildNodes("ParaDecl comma ParaDeclListTail", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1538 "parser.tab.c"
    break;

  case 24: /* ParamDecl: TYPE ID  */
#line 274 "parser.y"
                   { printf("RECOGNIZED RULE: Variable Parameter\n");
		(yyval.ast) = AST_DoublyChildNodes("variable parm", (yyvsp[-1].string), (yyvsp[0].string), (yyvsp[-1].string), (yyvsp[0].string));
	}
#line 1546 "parser.tab.c"
    break;

  case 25: /* ParamDecl: TYPE ID LEFTSQUARE RIGHTSQUARE  */
#line 277 "parser.y"
                                         { printf("RECOGNIZED RULE: Array Parameter\n");
		(yyval.ast) = AST_DoublyChildNodes("array parm", (yyvsp[-3].string), (yyvsp[-2].string), (yyvsp[-3].string), (yyvsp[-2].string));
	}
#line 1554 "parser.tab.c"
    break;

  case 26: /* StmtList: Stmt  */
#line 282 "parser.y"
               {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1562 "parser.tab.c"
    break;

  case 27: /* StmtList: Stmt StmtList  */
#line 285 "parser.y"
                        {
		printf("\n RECOGNIZED RULE: StmtList statement\n");
		// Generate a list of all statement declarations below vardecl
		(yyval.ast) = AST_DoublyChildNodes("statements", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
		}
#line 1572 "parser.tab.c"
    break;

  case 28: /* StmtList: FunDeclList  */
#line 290 "parser.y"
                      {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1580 "parser.tab.c"
    break;

  case 29: /* Stmt: SEMICOLON  */
#line 295 "parser.y"
                        { 	(yyval.ast) = AST_SingleChildNode("empty", "empty", "empty");}
#line 1586 "parser.tab.c"
    break;

  case 30: /* Stmt: Expr SEMICOLON  */
#line 296 "parser.y"
                                {
		// Simplest expr statement in grammar
		(yyval.ast) = (yyvsp[-1].ast);
		}
#line 1595 "parser.tab.c"
    break;

  case 31: /* Stmt: WRITE Primary SEMICOLON  */
#line 300 "parser.y"
                                        { printf("\n RECOGNIZED RULE: WRITE statement\n");
					// Generate write declarations as a statement in the parser
					(yyval.ast) = AST_SingleChildNode("write", (yyvsp[-1].ast), (yyvsp[-1].ast));

					printf("write: %s", (yyvsp[-1].ast) -> nodeType);

					// If the primary type is a variable, check if the variable is in the symbol table
					if (!strcmp((yyvsp[-1].ast) -> nodeType, "int") && !strcmp((yyvsp[-1].ast) -> nodeType, "float") && !strcmp((yyvsp[-1].ast) -> nodeType, "string") && strncmp(getPrimaryType((yyvsp[-1].ast)), "var", 3) == 0 && !found((yyvsp[-1].ast), scopeStack, stackPointer)) {
						printf("SEMANTIC ERROR: Variable %s does not exist.\n", (yyvsp[-1].ast));
						exit(1);
					}

				}
#line 1613 "parser.tab.c"
    break;

  case 32: /* Stmt: WRITELN SEMICOLON  */
#line 313 "parser.y"
                            {
		printf("\n RECOGNIZED RULE: WRITEIN statement\n");
		(yyval.ast) = AST_SingleChildNode("writeln", "\n", 0);
	}
#line 1622 "parser.tab.c"
    break;

  case 33: /* Stmt: RETURN Expr SEMICOLON  */
#line 317 "parser.y"
                                {
		printf("\n RECOGNIZED RULE: RETURN statement\n");
		(yyval.ast) = AST_SingleChildNode("return", (yyvsp[-1].ast),(yyvsp[-1].ast)); 

		// Check if the return type matches the function type
		CheckAssignmentType(currentFunctionScope, getExprOp((yyvsp[-1].ast)), scopeStack, stackPointer);
	}
#line 1634 "parser.tab.c"
    break;

  case 34: /* Stmt: READ ID SEMICOLON  */
#line 324 "parser.y"
                            {(yyval.ast) = AST_SingleChildNode("read", (yyvsp[-1].string), 0);}
#line 1640 "parser.tab.c"
    break;

  case 35: /* Stmt: Block  */
#line 325 "parser.y"
                {(yyval.ast) = (yyvsp[0].ast);}
#line 1646 "parser.tab.c"
    break;

  case 36: /* Stmt: Loop  */
#line 326 "parser.y"
               {(yyval.ast)=(yyvsp[0].ast);}
#line 1652 "parser.tab.c"
    break;

  case 37: /* Stmt: IfStmt  */
#line 327 "parser.y"
                 {(yyval.ast)=(yyvsp[0].ast);}
#line 1658 "parser.tab.c"
    break;

  case 38: /* IfStmt: If IfStmtTail  */
#line 330 "parser.y"
                      {
	printf("\n RECOGNIZED RULE: if statement block\n");
	(yyval.ast) = AST_DoublyChildNodes("IfStmt", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
}
#line 1667 "parser.tab.c"
    break;

  case 39: /* IfStmtTail: %empty  */
#line 336 "parser.y"
            { (yyval.ast) = AST_SingleChildNode("IfStmtTail else end", "", "");}
#line 1673 "parser.tab.c"
    break;

  case 40: /* IfStmtTail: Else  */
#line 337 "parser.y"
               { (yyval.ast) = AST_SingleChildNode("IfStmtTail else end", (yyvsp[0].ast), (yyvsp[0].ast));}
#line 1679 "parser.tab.c"
    break;

  case 41: /* IfStmtTail: Elif IfStmtTail  */
#line 338 "parser.y"
                          { (yyval.ast) = AST_DoublyChildNodes("IfStmtTail continue", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast)); }
#line 1685 "parser.tab.c"
    break;

  case 42: /* Loop: ForL  */
#line 340 "parser.y"
           {
	(yyval.ast) = (yyvsp[0].ast);
}
#line 1693 "parser.tab.c"
    break;

  case 43: /* Loop: WhileL  */
#line 343 "parser.y"
                 {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1701 "parser.tab.c"
    break;

  case 44: /* ForHead: FOR LEFTPAREN Expr RIGHTPAREN  */
#line 348 "parser.y"
                                       {
	(yyval.ast) = AST_SingleChildNode((yyvsp[-1].ast), (yyvsp[-1].ast), (yyvsp[-1].ast));
	char tempScopeName[50];
	sprintf(tempScopeName, "%s %s %d", scopeStack[stackPointer], "for", blockNumber);
	stackPointer += 1;
	blockNumber += 1;
	memset(scopeStack[stackPointer], 0, 50 * sizeof(char));
	strcpy(scopeStack[stackPointer], tempScopeName);
	memset(currentFunctionScope, 0, 50 * sizeof(char));
	strcpy(currentFunctionScope, tempScopeName);
}
#line 1717 "parser.tab.c"
    break;

  case 45: /* ForL: ForHead Block  */
#line 361 "parser.y"
                    {
	(yyval.ast) = AST_DoublyChildNodes("ForL", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
	stackPointer -= 1;
	memset(currentFunctionScope, 0, 50 * sizeof(char));
	strcpy(currentFunctionScope, scopeStack[stackPointer]);
}
#line 1728 "parser.tab.c"
    break;

  case 46: /* WhileHead: WHILE LEFTPAREN Expr RIGHTPAREN  */
#line 369 "parser.y"
                                           {
	(yyval.ast) = AST_SingleChildNode((yyvsp[-1].ast), (yyvsp[-1].ast), (yyvsp[-1].ast));
	char tempScopeName[50];
	sprintf(tempScopeName, "%s %s %d", scopeStack[stackPointer], "while", blockNumber);
	stackPointer += 1;
	blockNumber += 1;
	memset(scopeStack[stackPointer], 0, 50 * sizeof(char));
	strcpy(scopeStack[stackPointer], tempScopeName);
	memset(currentFunctionScope, 0, 50 * sizeof(char));
	strcpy(currentFunctionScope, tempScopeName);
}
#line 1744 "parser.tab.c"
    break;

  case 47: /* WhileL: WhileHead Block  */
#line 381 "parser.y"
                        {
	(yyval.ast) = AST_DoublyChildNodes("WhileL", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
	stackPointer -= 1;
	memset(currentFunctionScope, 0, 50 * sizeof(char));
	strcpy(currentFunctionScope, scopeStack[stackPointer]);
}
#line 1755 "parser.tab.c"
    break;

  case 48: /* IfHead: IF LEFTPAREN Expr RIGHTPAREN  */
#line 389 "parser.y"
                                     {
	(yyval.ast) = AST_SingleChildNode((yyvsp[-1].ast), (yyvsp[-1].ast), (yyvsp[-1].ast));
	char tempScopeName[50];
	sprintf(tempScopeName, "%s %s %d", scopeStack[stackPointer], "if", blockNumber);
	stackPointer += 1;
	blockNumber += 1;
	memset(scopeStack[stackPointer], 0, 50 * sizeof(char));
	strcpy(scopeStack[stackPointer], tempScopeName);
	memset(currentFunctionScope, 0, 50 * sizeof(char));
	strcpy(currentFunctionScope, tempScopeName);
}
#line 1771 "parser.tab.c"
    break;

  case 49: /* If: IfHead Block  */
#line 402 "parser.y"
                 {
	printf("\n RECOGNIZED RULE: if statement\n");

	(yyval.ast) = AST_DoublyChildNodes("If", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
	stackPointer -= 1;
	memset(currentFunctionScope, 0, 50 * sizeof(char));
	strcpy(currentFunctionScope, scopeStack[stackPointer]);
}
#line 1784 "parser.tab.c"
    break;

  case 50: /* ElifHead: ELIF LEFTPAREN Expr RIGHTPAREN  */
#line 412 "parser.y"
                                         {
	(yyval.ast) = AST_SingleChildNode((yyvsp[-1].ast), (yyvsp[-1].ast), (yyvsp[-1].ast));
	char tempScopeName[50];
	sprintf(tempScopeName, "%s %s %d", scopeStack[stackPointer], "elif", blockNumber);
	stackPointer += 1;
	memset(scopeStack[stackPointer], 0, 50 * sizeof(char));
	strcpy(scopeStack[stackPointer], tempScopeName);
	memset(currentFunctionScope, 0, 50 * sizeof(char));
	strcpy(currentFunctionScope, tempScopeName);
}
#line 1799 "parser.tab.c"
    break;

  case 51: /* Elif: ElifHead Block  */
#line 424 "parser.y"
                      {
	printf("\n RECOGNIZED RULE: elif statement\n");

	(yyval.ast) = AST_DoublyChildNodes("Elif", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
	stackPointer -= 1;
	memset(currentFunctionScope, 0, 50 * sizeof(char));
	strcpy(currentFunctionScope, scopeStack[stackPointer]);
}
#line 1812 "parser.tab.c"
    break;

  case 52: /* ElseHead: ELSE  */
#line 434 "parser.y"
               {
	char tempScopeName[50];
	sprintf(tempScopeName, "%s %s %d", scopeStack[stackPointer], "else", blockNumber);
	stackPointer += 1;
	memset(scopeStack[stackPointer], 0, 50 * sizeof(char));
	strcpy(scopeStack[stackPointer], tempScopeName);
	memset(currentFunctionScope, 0, 50 * sizeof(char));
	strcpy(currentFunctionScope, tempScopeName);
}
#line 1826 "parser.tab.c"
    break;

  case 53: /* Else: ElseHead Block  */
#line 445 "parser.y"
                      {
	printf("\n RECOGNIZED RULE: else statement\n");

	(yyval.ast) = AST_SingleChildNode("Else", (yyvsp[0].ast), (yyvsp[0].ast));
	stackPointer -= 1;
	memset(currentFunctionScope, 0, 50 * sizeof(char));
	strcpy(currentFunctionScope, scopeStack[stackPointer]);
}
#line 1839 "parser.tab.c"
    break;

  case 54: /* Primary: INTEGER  */
#line 456 "parser.y"
                                {(yyval.ast) = AST_SingleChildNode("int", (yyvsp[0].string), (yyvsp[0].string)); }
#line 1845 "parser.tab.c"
    break;

  case 55: /* Primary: NUMBER  */
#line 457 "parser.y"
                        {(yyval.ast) = AST_SingleChildNode("float", (yyvsp[0].number), (yyvsp[0].number)); }
#line 1851 "parser.tab.c"
    break;

  case 56: /* Primary: ID  */
#line 458 "parser.y"
              {(yyval.ast) = AST_SingleChildNode((yyvsp[0].string), (yyvsp[0].string), (yyvsp[0].string));}
#line 1857 "parser.tab.c"
    break;

  case 57: /* Primary: STRING  */
#line 459 "parser.y"
                  {(yyval.ast) = AST_SingleChildNode("string", (yyvsp[0].string), (yyvsp[0].string));}
#line 1863 "parser.tab.c"
    break;

  case 58: /* Primary: FLOAT  */
#line 460 "parser.y"
                {(yyval.ast) = AST_SingleChildNode("float", (yyvsp[0].string), (yyvsp[0].string));}
#line 1869 "parser.tab.c"
    break;

  case 59: /* Primary: ID LEFTSQUARE INTEGER RIGHTSQUARE  */
#line 461 "parser.y"
                                            {
		char * arrayPrefix = malloc(100*sizeof(char));
		strcat(arrayPrefix, "inarray_");
		strcat(arrayPrefix, getItemType((yyvsp[-3].string), scopeStack, stackPointer));
		printf("Prefix: %s\n", arrayPrefix);
		(yyval.ast) = AST_DoublyChildNodes(arrayPrefix, (yyvsp[-3].string), (yyvsp[-1].string), (yyvsp[-3].string), (yyvsp[-1].string));
	}
#line 1881 "parser.tab.c"
    break;

  case 60: /* ExprListTail: %empty  */
#line 470 "parser.y"
              {(yyval.ast) = AST_SingleChildNode("exprlist end", "\n", 0);}
#line 1887 "parser.tab.c"
    break;

  case 61: /* ExprListTail: Primary  */
#line 471 "parser.y"
                        { 
			(yyval.ast) = AST_SingleChildNode("exprlist end", (yyvsp[0].ast), (yyvsp[0].ast)); 
		}
#line 1895 "parser.tab.c"
    break;

  case 62: /* ExprListTail: Primary COMMA ExprListTail  */
#line 474 "parser.y"
                                        {
			(yyval.ast) = AST_DoublyChildNodes("exprlist exprtail", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
		}
#line 1903 "parser.tab.c"
    break;

  case 63: /* ExprList: %empty  */
#line 479 "parser.y"
          {}
#line 1909 "parser.tab.c"
    break;

  case 64: /* ExprList: ExprListTail  */
#line 480 "parser.y"
                       {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1917 "parser.tab.c"
    break;

  case 65: /* Block: LEFTBRACKET Program RIGHTBRACKET  */
#line 485 "parser.y"
                                         { printf("\n RECOGNIZED RULE: Block statement\n");
		(yyval.ast) = AST_SingleChildNode("block",(yyvsp[-1].ast), (yyvsp[-1].ast));
		}
#line 1925 "parser.tab.c"
    break;

  case 66: /* Expr: Primary  */
#line 490 "parser.y"
                { printf("\n RECOGNIZED RULE: Simplest expression\n");
		(yyval.ast) = (yyvsp[0].ast);
		
		char tempNodeType[50];
		strcpy(tempNodeType, CheckPrimaryType((yyvsp[0].ast), scopeStack, stackPointer));
		memset((yyval.ast)->nodeType, 0, 50*sizeof(char));
		strcpy((yyval.ast)->nodeType, tempNodeType);
	}
#line 1938 "parser.tab.c"
    break;

  case 67: /* Expr: ID EQ Expr  */
#line 498 "parser.y"
                        { printf("\n RECOGNIZED RULE: Assignment statement\n");
					// --- SEMANTIC CHECKS --- //
					/*
						int semanticCorrectness = FALSE;
						1. Has ID been declared? If yes, semanticCorrectness = 1

						2. Does RHS.type = LHS.type? if yes, semanticCorrectness = 1

						If all tests == 1, then
							perform SEMANTIC ACTIONS
						
					*/
					
					// Check to see if the ID exists in the symbol table
					checkID((yyvsp[-2].string), scopeStack, stackPointer);

					// Check to see if the LHS matches the RHS
					CheckAssignmentType((yyvsp[-2].string), getExprOp((yyvsp[0].ast)), scopeStack, stackPointer);

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					(yyval.ast) = AST_DoublyChildNodes("=", (yyvsp[-2].string), (yyvsp[0].ast), (yyvsp[-2].string), (yyvsp[0].ast));

					}
#line 1967 "parser.tab.c"
    break;

  case 68: /* Expr: ID LEFTSQUARE INTEGER RIGHTSQUARE EQ Expr  */
#line 522 "parser.y"
                                                        { printf("\n RECOGNIZED RULE: Assignment element statement\n");
	
					// --- SEMANTIC CHECKS --- //
					/*
						int semanticCorrectness = FALSE;
						1. Has ID been declared? If yes, semanticCorrectness = 1

						2. Does RHS.type = LHS.type? if yes, semanticCorrectness = 1

						If all tests == 1, then
							perform SEMANTIC ACTIONS
						
					*/

					// Check to see if the ID exists in the symbol table
					checkID((yyvsp[-5].string), scopeStack, stackPointer);
					

					// Check to see if the LHS matches the RHS
					char * LHS = getExprOp((yyvsp[0].ast));
					CheckAssignmentType((yyvsp[-5].string), LHS, scopeStack, stackPointer);
					CheckIndexOutOfBound((yyvsp[-5].string), (yyvsp[-3].string), scopeStack, stackPointer);

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					struct AST* arrayElement = AST_DoublyChildNodes("element assignment", (yyvsp[-3].string), (yyvsp[0].ast), (yyvsp[-3].string), (yyvsp[0].ast)); 

					(yyval.ast) = AST_DoublyChildNodes("=", (yyvsp[-5].string), arrayElement, (yyvsp[-5].string), arrayElement);

					}
#line 2002 "parser.tab.c"
    break;

  case 69: /* Expr: LET ID EQ Expr  */
#line 553 "parser.y"
                                { printf("\n RECOGNIZED RULE: Let Assignment statement \n");
					// --- SEMANTIC CHECKS --- //
					/*
						int semanticCorrectness = FALSE;
						1. Has ID been declared? If yes, semanticCorrectness = 1

						2. Does RHS.type = LHS.type? if yes, semanticCorrectness = 1

						If all tests == 1, then
							perform SEMANTIC ACTIONS
						
					*/
					
					// Check to see if the ID exists in the symbol table
					checkID((yyvsp[-2].string), scopeStack, stackPointer);

					// Check to see if the LHS matches the RHS
					CheckAssignmentType((yyvsp[-2].string), getExprOp((yyvsp[0].ast)), scopeStack, stackPointer);

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					(yyval.ast) = AST_DoublyChildNodes("=",(yyvsp[-2].string), (yyvsp[0].ast), (yyvsp[-2].string), (yyvsp[0].ast));

					}
#line 2031 "parser.tab.c"
    break;

  case 70: /* Expr: LET ID LEFTSQUARE INTEGER RIGHTSQUARE EQ Expr  */
#line 577 "parser.y"
                                                                { printf("\n RECOGNIZED RULE: Let Assignment element statement\n");
					// --- SEMANTIC CHECKS --- //
					/*
						int semanticCorrectness = FALSE;
						1. Has ID been declared? If yes, semanticCorrectness = 1

						2. Does RHS.type = LHS.type? if yes, semanticCorrectness = 1

						If all tests == 1, then
							perform SEMANTIC ACTIONS
						
					*/
					
					// Check to see if the ID exists in the symbol table
					checkID((yyvsp[-5].string), scopeStack, stackPointer);

					// Check to see if the LHS matches the RHS
					CheckAssignmentType((yyvsp[-5].string), (yyvsp[0].ast), scopeStack, stackPointer);

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					struct AST* arrayElement = AST_DoublyChildNodes("element assignment", (yyvsp[-3].string), (yyvsp[0].ast), (yyvsp[-3].string), (yyvsp[0].ast)); 

					(yyval.ast) = AST_DoublyChildNodes("=", (yyvsp[-5].string), arrayElement, (yyvsp[-5].string), arrayElement);

					}
#line 2062 "parser.tab.c"
    break;

  case 71: /* Expr: Expr PLUS Expr  */
#line 604 "parser.y"
                         { printf("\n RECOGNIZED RULE: PLUS statement\n");
					// Semantic checks

					// Check to see if the LHS matches the RHS
					CheckOperationType(getExprOp((yyvsp[-2].ast)), getExprOp((yyvsp[0].ast)));
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("+", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
					printf("EXPR PLUS EXPR: %s \n------------------------------------------------------------------\n", (yyvsp[0].ast) ->nodeType);
				}
#line 2077 "parser.tab.c"
    break;

  case 72: /* Expr: Expr MINUS Expr  */
#line 614 "parser.y"
                          { printf("\n RECOGNIZED RULE: MINUS statement\n");
					// Semantic checks
					
					// Check to see if the LHS matches the RHS
					CheckOperationType(getExprOp((yyvsp[-2].ast)), getExprOp((yyvsp[0].ast)));
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("-",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				}
#line 2091 "parser.tab.c"
    break;

  case 73: /* Expr: Expr MULTIPLY Expr  */
#line 623 "parser.y"
                             { printf("\n RECOGNIZED RULE: MULTIPLY statement\n");
					// Semantic checks
					
					// Check to see if the LHS matches the RHS
					CheckOperationType(getExprOp((yyvsp[-2].ast)), getExprOp((yyvsp[0].ast)));
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("*", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				}
#line 2105 "parser.tab.c"
    break;

  case 74: /* Expr: Expr DIVIDE Expr  */
#line 632 "parser.y"
                           { printf("\n RECOGNIZED RULE: DIVIDE statement\n");
					// Semantic checks
					
					// Check to see if the LHS matches the RHS
					CheckOperationType(getExprOp((yyvsp[-2].ast)), getExprOp((yyvsp[0].ast)));
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("/", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));

					// If the RHS is an int, check for integer division error
					if (strncmp((yyvsp[0].ast), "int", 3) == 0) {
						int numeratorInt = 1;
						int denominatorInt = 1;

						// Assign expression values if it's not just a sequence of vars
						if (containsNonVars((yyvsp[-2].ast))) {
							numeratorInt = evaluateIntExpr((yyvsp[-2].ast));
						}
						if (containsNonVars((yyvsp[0].ast))) {
							denominatorInt = evaluateIntExpr((yyvsp[0].ast));
						}
						checkIntDivisionError(numeratorInt, denominatorInt);
					} else if (strncmp((yyvsp[0].ast), "float", 5) == 0) {
						float numeratorFloat = 1.0;
						float denominatorFloat = 1.0;

						// Assign expression values if it's not just a sequence of vars
						if (containsNonVars((yyvsp[-2].ast))) {
							numeratorFloat = evaluateFloatExpr((yyvsp[-2].ast));
						}
						if (containsNonVars((yyvsp[0].ast))) {
							denominatorFloat = evaluateFloatExpr((yyvsp[0].ast));
						}
						checkFloatDivisionError(numeratorFloat, denominatorFloat);
					}

				}
#line 2147 "parser.tab.c"
    break;

  case 75: /* Expr: Expr EXPONENT Expr  */
#line 669 "parser.y"
                             { printf("\n RECOGNIZED RULE: BinOp statement\n");
				// Semantic checks
				
				// Check to see if the LHS matches the RHS
				CheckOperationType(getExprOp((yyvsp[-2].ast)), getExprOp((yyvsp[0].ast)));
				
				// Generate AST Nodes (doubly linked)
				(yyval.ast) = AST_DoublyChildNodes("^", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
			}
#line 2161 "parser.tab.c"
    break;

  case 76: /* Expr: Expr COMMA Expr  */
#line 678 "parser.y"
                          { printf("\n RECOGNIZED RULE: BinOp statement\n");
				// Semantic checks
				
				// Check if both exprs exist
				
				// Generate AST Nodes (doubly linked)
				(yyval.ast) = AST_DoublyChildNodes("EXP ", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
			}
#line 2174 "parser.tab.c"
    break;

  case 77: /* Expr: Expr COMPARSIONOPERATOR Expr  */
#line 686 "parser.y"
                                       {
		printf("\n RECOGNIZED RULE: Comparison statement\n");
		CheckComparisonType((yyvsp[-2].ast), (yyvsp[0].ast), scopeStack, stackPointer);
		struct AST * tempNode = AST_DoublyChildNodes((yyvsp[-1].string), (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
		(yyval.ast) = AST_SingleChildNode("Comparsion", tempNode, tempNode);
	}
#line 2185 "parser.tab.c"
    break;

  case 78: /* Expr: Expr LOGICALOPERATOR Expr  */
#line 692 "parser.y"
                                    {(yyval.ast) = AST_DoublyChildNodes("Logical", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));}
#line 2191 "parser.tab.c"
    break;

  case 79: /* Expr: LEFTPAREN Expr RIGHTPAREN  */
#line 693 "parser.y"
                                    {(yyval.ast) = (yyvsp[-1].ast);}
#line 2197 "parser.tab.c"
    break;

  case 80: /* Expr: FunctionCall  */
#line 694 "parser.y"
                       {(yyval.ast) = (yyvsp[0].ast);}
#line 2203 "parser.tab.c"
    break;

  case 81: /* Expr: TRUE  */
#line 695 "parser.y"
               {(yyval.ast) = AST_SingleChildNode("boolean", (yyvsp[0].string), (yyvsp[0].string));}
#line 2209 "parser.tab.c"
    break;

  case 82: /* Expr: FALSE  */
#line 696 "parser.y"
                {(yyval.ast) = AST_SingleChildNode("boolean",(yyvsp[0].string), (yyvsp[0].string));}
#line 2215 "parser.tab.c"
    break;

  case 83: /* FunctionCall: ID LEFTPAREN ExprList RIGHTPAREN  */
#line 700 "parser.y"
                                               {
	printf("\nRECOGNIZED RULE: FunctionCall\n");
	struct AST* funcCallParamList = AST_SingleChildNode("function call param list", (yyvsp[-1].ast), (yyvsp[-1].ast));
	(yyval.ast) = AST_DoublyChildNodes("function call", (yyvsp[-3].string), funcCallParamList, (yyvsp[-3].string), funcCallParamList);

	// Check if the number of call parameters matches the number of function parameters
	CheckParamLength((yyvsp[-3].string), funcCallParamList);
	
	// Find the number of parameters
    int numParams = getNumExprs(funcCallParamList);

    // Compare parameters if there's at least one parameter
    if (numParams != 0) {
        // Iterate through for each parameter in the list
        for (int i = 0; i < numParams; i++) {
            // Get the function parameter type at this index
            char * funcParamType = getFuncParamItemType((yyvsp[-3].string), numParams, i);

            // Get the expression parameter type at this index
			printf("here\n");
			char * callParamType = getCallListItemType(funcCallParamList, i, 0, scopeStack[stackPointer]);

            // Check to see if the two types do not match
            // If they don't, return a semantic error
            if (strncmp(funcParamType, callParamType, strlen(callParamType)) != 0) {
                printf("\nSEMANTIC ERROR: The call for parameter #%d (%s) does not match the type for parameter #%d (%s) in the function declaration for \"%s\".\n", i, callParamType, i, funcParamType, (yyvsp[-3].string));
                exit(1);
            }
        }
    }
}
#line 2251 "parser.tab.c"
    break;


#line 2255 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 733 "parser.y"


int parser_main(FILE*inputfile)
{
	printf("\n \n \n \n \n \n--------------------Parser Start------------------------\n\n\n");
	stackPointer = 0;
	blockNumber = 0;
	memset(scopeStack[stackPointer], 0, 50 * sizeof(char));
	strcpy(scopeStack[stackPointer], "global");
	if (2 > 1){
	  if(!(yyin = inputfile))
          {
		perror("Cannot open file");
		return(1);
	  }
	}
	
	return yyparse();
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
