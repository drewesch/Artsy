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
char currentScope[50]; // global or the name of the function

#line 91 "parser.tab.c"

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
  YYSYMBOL_FLOAT = 5,                      /* FLOAT  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_LOGICALOPERATOR = 7,            /* LOGICALOPERATOR  */
  YYSYMBOL_COMPARSIONOPERATOR = 8,         /* COMPARSIONOPERATOR  */
  YYSYMBOL_CHAR = 9,                       /* CHAR  */
  YYSYMBOL_COMMA = 10,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 11,                 /* SEMICOLON  */
  YYSYMBOL_EQ = 12,                        /* EQ  */
  YYSYMBOL_LEFTBRACKET = 13,               /* LEFTBRACKET  */
  YYSYMBOL_RIGHTBRACKET = 14,              /* RIGHTBRACKET  */
  YYSYMBOL_LEFTPAREN = 15,                 /* LEFTPAREN  */
  YYSYMBOL_RIGHTPAREN = 16,                /* RIGHTPAREN  */
  YYSYMBOL_LEFTSQUARE = 17,                /* LEFTSQUARE  */
  YYSYMBOL_RIGHTSQUARE = 18,               /* RIGHTSQUARE  */
  YYSYMBOL_NUMBER = 19,                    /* NUMBER  */
  YYSYMBOL_WRITE = 20,                     /* WRITE  */
  YYSYMBOL_WRITELN = 21,                   /* WRITELN  */
  YYSYMBOL_READ = 22,                      /* READ  */
  YYSYMBOL_RETURN = 23,                    /* RETURN  */
  YYSYMBOL_IF = 24,                        /* IF  */
  YYSYMBOL_ELIF = 25,                      /* ELIF  */
  YYSYMBOL_ELSE = 26,                      /* ELSE  */
  YYSYMBOL_WHILE = 27,                     /* WHILE  */
  YYSYMBOL_BREAK = 28,                     /* BREAK  */
  YYSYMBOL_FOR = 29,                       /* FOR  */
  YYSYMBOL_TRUEZ = 30,                     /* TRUEZ  */
  YYSYMBOL_FALSEZ = 31,                    /* FALSEZ  */
  YYSYMBOL_FUNCTION = 32,                  /* FUNCTION  */
  YYSYMBOL_PLUS = 33,                      /* PLUS  */
  YYSYMBOL_MINUS = 34,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 35,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 36,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 37,                    /* MODULO  */
  YYSYMBOL_EXPONENT = 38,                  /* EXPONENT  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_Program = 40,                   /* Program  */
  YYSYMBOL_DeclList = 41,                  /* DeclList  */
  YYSYMBOL_Decl = 42,                      /* Decl  */
  YYSYMBOL_VarDecl = 43,                   /* VarDecl  */
  YYSYMBOL_FunDeclList = 44,               /* FunDeclList  */
  YYSYMBOL_FunDeclListTail = 45,           /* FunDeclListTail  */
  YYSYMBOL_FunDecl = 46,                   /* FunDecl  */
  YYSYMBOL_ParamDeclList = 47,             /* ParamDeclList  */
  YYSYMBOL_ParamDeclListTail = 48,         /* ParamDeclListTail  */
  YYSYMBOL_ParamDecl = 49,                 /* ParamDecl  */
  YYSYMBOL_StmtList = 50,                  /* StmtList  */
  YYSYMBOL_Stmt = 51,                      /* Stmt  */
  YYSYMBOL_Loop = 52,                      /* Loop  */
  YYSYMBOL_If = 53,                        /* If  */
  YYSYMBOL_Primary = 54,                   /* Primary  */
  YYSYMBOL_ExprListTail = 55,              /* ExprListTail  */
  YYSYMBOL_ExprList = 56,                  /* ExprList  */
  YYSYMBOL_Block = 57,                     /* Block  */
  YYSYMBOL_Expr = 58,                      /* Expr  */
  YYSYMBOL_FunctionCall = 59               /* FunctionCall  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   199

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  104

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    82,    82,    93,    94,    96,    99,   103,   110,   134,
     152,   153,   154,   157,   158,   161,   186,   187,   190,   191,
     194,   195,   200,   201,   207,   208,   212,   217,   218,   219,
     220,   221,   228,   231,   235,   236,   237,   238,   239,   246,
     247,   252,   253,   258,   259,   266,   270,   303,   312,   320,
     328,   336,   344,   345,   346,   347,   348,   349,   353
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
  "\"end of file\"", "error", "\"invalid token\"", "TYPE", "ID", "FLOAT",
  "STRING", "LOGICALOPERATOR", "COMPARSIONOPERATOR", "CHAR", "COMMA",
  "SEMICOLON", "EQ", "LEFTBRACKET", "RIGHTBRACKET", "LEFTPAREN",
  "RIGHTPAREN", "LEFTSQUARE", "RIGHTSQUARE", "NUMBER", "WRITE", "WRITELN",
  "READ", "RETURN", "IF", "ELIF", "ELSE", "WHILE", "BREAK", "FOR", "TRUEZ",
  "FALSEZ", "FUNCTION", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO",
  "EXPONENT", "$accept", "Program", "DeclList", "Decl", "VarDecl",
  "FunDeclList", "FunDeclListTail", "FunDecl", "ParamDeclList",
  "ParamDeclListTail", "ParamDecl", "StmtList", "Stmt", "Loop", "If",
  "Primary", "ExprListTail", "ExprList", "Block", "Expr", "FunctionCall", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-80)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     112,     5,    36,   -80,   -80,   -80,   112,   168,   -80,    -3,
       6,     3,     2,    12,   -80,   -80,    20,   -11,   -80,   112,
     -80,   140,   -80,   -80,   -80,   -80,     0,   -80,     1,   168,
     168,   168,   140,    21,    13,    47,    51,   -80,   168,   168,
     -80,    39,   140,   -80,   -11,   -80,   -80,   168,   168,   -80,
     168,   168,   168,   168,   168,   -80,    44,    86,   -80,    52,
      42,    53,    56,   -80,   -80,   -80,    65,    76,    75,   -80,
     -80,   -11,    31,   114,    69,    69,    57,    57,   -80,    64,
     -80,   168,   -80,   -80,    72,    72,    81,    79,   -80,   -80,
     -80,    94,   -80,    98,    90,   -80,   103,    91,    72,    94,
     108,   -80,   -80,   -80
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,    35,    37,    36,    24,     3,     0,    34,     0,
       0,     0,     0,     0,    56,    57,     0,    10,     5,     3,
       7,    22,    30,    31,    45,    29,     0,    55,     0,     0,
      41,     0,    43,     0,    35,     0,     0,    27,     0,     0,
       1,     0,    43,    12,    11,     4,    23,     0,     0,    25,
       0,     0,     0,     0,     0,     8,     0,    46,    42,     0,
      39,     0,     0,    54,    26,    28,     0,     0,     0,     2,
      14,    13,    53,    52,    47,    48,    49,    50,    51,     0,
      58,     0,    38,    44,    43,    43,     0,     0,    40,    33,
      32,    16,     9,     0,     0,    17,    18,    20,    43,     0,
       0,    15,    19,    21
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -80,   -80,     7,   -80,   -80,   -80,   111,   113,   -80,    30,
     -80,   -17,   -80,   -80,   -80,   124,    59,   -80,   -79,    -7,
     -80
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    16,    17,    18,    19,    42,    70,    71,    94,    95,
      96,    20,    21,    22,    23,    24,    58,    59,    25,    26,
      27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      33,    34,     3,     4,    46,    89,    90,    47,    48,    28,
      36,    49,    55,    32,    37,    62,     8,    38,    56,   101,
      40,    41,    57,    60,    61,    69,    45,    39,    47,    48,
      31,    66,    67,    50,    51,    52,    53,    63,    54,    48,
      72,    73,    68,    74,    75,    76,    77,    78,    29,    47,
      48,    30,    81,    31,    50,    51,    52,    53,    64,    54,
      47,    48,    65,    79,    50,    51,    52,    53,    80,    54,
      83,    82,    47,    48,    60,    50,    51,    52,    53,    86,
      54,    84,    87,    47,    48,     6,    50,    51,    52,    53,
      92,    54,    85,    47,    48,    54,    91,    93,    50,    51,
      52,    53,    97,    54,    52,    53,    98,    54,   100,    50,
      51,    52,    53,    99,    54,     1,     2,     3,     4,    50,
      51,    52,    53,     5,    54,     6,   103,     7,    43,   102,
      44,     8,     9,    35,    10,    11,    12,     0,     0,    13,
      88,     0,    14,    15,     2,     3,     4,    50,    51,    52,
      53,     5,    54,     6,     0,     7,     0,     0,     0,     8,
       9,     0,    10,    11,    12,     0,     0,    13,     0,     0,
      14,    15,     2,     3,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     0,     0,     0,     8,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,    15
};

static const yytype_int8 yycheck[] =
{
       7,     4,     5,     6,    21,    84,    85,     7,     8,     4,
       4,    11,    11,     6,    11,    32,    19,    15,    17,    98,
       0,    32,    29,    30,    31,    42,    19,    15,     7,     8,
      17,    38,    39,    33,    34,    35,    36,    16,    38,     8,
      47,    48,     3,    50,    51,    52,    53,    54,    12,     7,
       8,    15,    10,    17,    33,    34,    35,    36,    11,    38,
       7,     8,    11,    19,    33,    34,    35,    36,    16,    38,
      14,    18,     7,     8,    81,    33,    34,    35,    36,     4,
      38,    16,    18,     7,     8,    13,    33,    34,    35,    36,
      11,    38,    16,     7,     8,    38,    15,     3,    33,    34,
      35,    36,     4,    38,    35,    36,    16,    38,    17,    33,
      34,    35,    36,    10,    38,     3,     4,     5,     6,    33,
      34,    35,    36,    11,    38,    13,    18,    15,    17,    99,
      17,    19,    20,     9,    22,    23,    24,    -1,    -1,    27,
      81,    -1,    30,    31,     4,     5,     6,    33,    34,    35,
      36,    11,    38,    13,    -1,    15,    -1,    -1,    -1,    19,
      20,    -1,    22,    23,    24,    -1,    -1,    27,    -1,    -1,
      30,    31,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    11,    13,    15,    19,    20,
      22,    23,    24,    27,    30,    31,    40,    41,    42,    43,
      50,    51,    52,    53,    54,    57,    58,    59,     4,    12,
      15,    17,    41,    58,     4,    54,     4,    11,    15,    15,
       0,    32,    44,    45,    46,    41,    50,     7,     8,    11,
      33,    34,    35,    36,    38,    11,    17,    58,    55,    56,
      58,    58,    50,    16,    11,    11,    58,    58,     3,    50,
      45,    46,    58,    58,    58,    58,    58,    58,    58,    19,
      16,    10,    18,    14,    16,    16,     4,    18,    55,    57,
      57,    15,    11,     3,    47,    48,    49,     4,    16,    10,
      17,    57,    48,    18
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    41,    42,    42,    43,    43,
      44,    44,    44,    45,    45,    46,    47,    47,    48,    48,
      49,    49,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    51,    52,    53,    54,    54,    54,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    59
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     0,     2,     1,     1,     1,     3,     6,
       0,     1,     1,     1,     2,     7,     0,     1,     1,     3,
       2,     4,     1,     2,     1,     2,     3,     2,     3,     1,
       1,     1,     5,     5,     1,     1,     1,     1,     4,     1,
       3,     0,     1,     0,     4,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     4
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
  case 2: /* Program: DeclList FunDeclList StmtList  */
#line 82 "parser.y"
                                       {
	// Main program parser rule, generates the whole AST for the program
	(yyval.ast) = AST_SingleChildNode("program",(yyvsp[-2].ast), (yyvsp[-2].ast));

	printf("\n\n\n\n\n--------------------Parser End------------------------\n\n\n");

	ast = (yyval.ast);

}
#line 1230 "parser.tab.c"
    break;

  case 4: /* DeclList: VarDecl DeclList  */
#line 94 "parser.y"
                                { (yyval.ast) = AST_DoublyChildNodes("vardec", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
							}
#line 1237 "parser.tab.c"
    break;

  case 5: /* DeclList: Decl  */
#line 96 "parser.y"
                { (yyval.ast) = (yyvsp[0].ast); }
#line 1243 "parser.tab.c"
    break;

  case 6: /* Decl: VarDecl  */
#line 99 "parser.y"
                {
	// Basic Var Declaration Rule, generates AST for all variable declarations
	(yyval.ast) = (yyvsp[0].ast);
	}
#line 1252 "parser.tab.c"
    break;

  case 7: /* Decl: StmtList  */
#line 103 "parser.y"
                   {
		// Basic Statement list declaration rule, generates AST for all statement declarations
		(yyval.ast) = (yyvsp[0].ast);
		}
#line 1261 "parser.tab.c"
    break;

  case 8: /* VarDecl: TYPE ID SEMICOLON  */
#line 110 "parser.y"
                                        { printf("\n RECOGNIZED RULE: Variable declaration %s\n", (yyvsp[-1].string));
									// Variable declaration rule
									// Symbol Table
									symTabAccess();
									int inSymTab = found((yyvsp[-1].string), currentScope);
									//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
									
									// Check if the variable has been declared
									// If it has, throw an error
									if (inSymTab == 0) 
										addItem((yyvsp[-1].string), "Var", (yyvsp[-2].string),0, currentScope);
									else {
										printf("SEMANTIC ERROR: Var %s is already in the symbol table", (yyvsp[-1].string));
										exit(1);
									}
									// If the variable has not been declared 
									showSymTable();
									

								  // Generate AST node as a doubly node
								  (yyval.ast) = AST_DoublyChildNodes("type",(yyvsp[-2].string),(yyvsp[-1].string),(yyvsp[-2].string), (yyvsp[-1].string));

								}
#line 1289 "parser.tab.c"
    break;

  case 9: /* VarDecl: TYPE ID LEFTSQUARE NUMBER RIGHTSQUARE SEMICOLON  */
#line 134 "parser.y"
                                                                                                                  {printf("Found Array declaration"); 
									symTabAccess(); 
									int inSymTab = found((yyvsp[-4].string), currentScope);
									//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
														
									// Check if the variable has been declared
									// If it has, throw an error
									if (inSymTab == 0) 
										addItem((yyvsp[-4].string), "Array", (yyvsp[-5].string),atoi((yyvsp[-2].number)), currentScope);
									else {
										printf("SEMANTIC ERROR: Var %s is already in the symbol table", (yyvsp[-4].string));
										exit(1);
									}
									// If the variable has not been declared 
									showSymTable();
								}
#line 1310 "parser.tab.c"
    break;

  case 10: /* FunDeclList: %empty  */
#line 152 "parser.y"
             {}
#line 1316 "parser.tab.c"
    break;

  case 11: /* FunDeclList: FunDecl  */
#line 153 "parser.y"
                  {(yyval.ast) = (yyvsp[0].ast);}
#line 1322 "parser.tab.c"
    break;

  case 12: /* FunDeclList: FunDeclListTail  */
#line 154 "parser.y"
                          {(yyval.ast) = (yyvsp[0].ast);}
#line 1328 "parser.tab.c"
    break;

  case 13: /* FunDeclListTail: FunDecl  */
#line 157 "parser.y"
                         {(yyval.ast) = (yyvsp[0].ast);}
#line 1334 "parser.tab.c"
    break;

  case 14: /* FunDeclListTail: FunDecl FunDeclListTail  */
#line 158 "parser.y"
                                  {(yyval.ast) = AST_DoublyChildNodes("FunDecl FunDeclListTail",(yyvsp[-1].ast),(yyvsp[0].ast),(yyvsp[-1].ast), (yyvsp[0].ast));}
#line 1340 "parser.tab.c"
    break;

  case 15: /* FunDecl: FUNCTION TYPE ID LEFTPAREN ParamDeclList RIGHTPAREN Block  */
#line 161 "parser.y"
                                                                   {
	symTabAccess();
	int inSymTab = found((yyvsp[-4].string), currentScope);
	//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);

	// Check if the variable has been declared
	// If it has, throw an error
	//printf("0 Function okkkkkkkkkkkkkkkkkkkkkkkkkkkkk-----------------------\n");
	if (inSymTab == 0){
		//printf("Function okkkkkkkkkkkkkkkkkkkkkkkkkkkkk-----------------------\n");
		addFunction((yyvsp[-5].string), (yyvsp[-4].string), (yyvsp[-2].ast)); //id
	}
	else {
		printf("SEMANTIC ERROR: Function %s is already in the symbol table", (yyvsp[-4].string));
		exit(1);
	}
	//printf("2 Function okkkkkkkkkkkkkkkkkkkkkkkkkkkkk-----------------------\n");
	// If the variable has not been declared 
	showSymTable();

	// Generate AST node as a doubly node
	(yyval.ast) = AST_DoublyChildNodes("Function",(yyvsp[-4].string),(yyvsp[-2].ast),(yyvsp[-4].string), (yyvsp[-2].ast));
	}
#line 1368 "parser.tab.c"
    break;

  case 16: /* ParamDeclList: %empty  */
#line 186 "parser.y"
               {}
#line 1374 "parser.tab.c"
    break;

  case 17: /* ParamDeclList: ParamDeclListTail  */
#line 187 "parser.y"
                            {(yyval.ast) = (yyvsp[0].ast);}
#line 1380 "parser.tab.c"
    break;

  case 18: /* ParamDeclListTail: ParamDecl  */
#line 190 "parser.y"
                             {(yyval.ast) = (yyvsp[0].ast);}
#line 1386 "parser.tab.c"
    break;

  case 19: /* ParamDeclListTail: ParamDecl COMMA ParamDeclListTail  */
#line 191 "parser.y"
                                            {(yyval.ast) = AST_DoublyChildNodes("ParaDecl comma ParaDeclListTail",(yyvsp[-2].ast),(yyvsp[0].ast),(yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1392 "parser.tab.c"
    break;

  case 20: /* ParamDecl: TYPE ID  */
#line 194 "parser.y"
                   {(yyval.ast) = AST_DoublyChildNodes("Variable parm",(yyvsp[-1].string),(yyvsp[0].string),(yyvsp[-1].string), (yyvsp[0].string));}
#line 1398 "parser.tab.c"
    break;

  case 21: /* ParamDecl: TYPE ID LEFTSQUARE RIGHTSQUARE  */
#line 195 "parser.y"
                                         {(yyval.ast) = AST_DoublyChildNodes("array parm",(yyvsp[-3].string),(yyvsp[-2].string),(yyvsp[-3].string), (yyvsp[-2].string));}
#line 1404 "parser.tab.c"
    break;

  case 23: /* StmtList: Stmt StmtList  */
#line 201 "parser.y"
                        {
		// Generate a list of all statement declarations below vardecl
		(yyval.ast) = AST_DoublyChildNodes("statements", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
		}
#line 1413 "parser.tab.c"
    break;

  case 24: /* Stmt: SEMICOLON  */
#line 207 "parser.y"
                        {}
#line 1419 "parser.tab.c"
    break;

  case 25: /* Stmt: Expr SEMICOLON  */
#line 208 "parser.y"
                                {
		// Simplest expr statement in grammar
		(yyval.ast) = (yyvsp[-1].ast);
		}
#line 1428 "parser.tab.c"
    break;

  case 26: /* Stmt: WRITE Primary SEMICOLON  */
#line 212 "parser.y"
                                        { printf("\n RECOGNIZED RULE: WRITE statement\n");
					// Generate write declarations as a statement in the parser
					(yyval.ast) = AST_SingleChildNode("write", (yyvsp[-1].ast), (yyvsp[-1].ast));
					printf("Write AST generated!");
				}
#line 1438 "parser.tab.c"
    break;

  case 27: /* Stmt: RETURN SEMICOLON  */
#line 217 "parser.y"
                           {(yyval.ast) = AST_SingleChildNode("RETURN", 0,0);}
#line 1444 "parser.tab.c"
    break;

  case 28: /* Stmt: READ ID SEMICOLON  */
#line 218 "parser.y"
                            {(yyval.ast) = AST_SingleChildNode("READ", (yyvsp[-1].string), 0);}
#line 1450 "parser.tab.c"
    break;

  case 29: /* Stmt: Block  */
#line 219 "parser.y"
                {(yyval.ast) = (yyvsp[0].ast);}
#line 1456 "parser.tab.c"
    break;

  case 30: /* Stmt: Loop  */
#line 220 "parser.y"
               {(yyval.ast)=(yyvsp[0].ast);}
#line 1462 "parser.tab.c"
    break;

  case 31: /* Stmt: If  */
#line 221 "parser.y"
             {(yyval.ast)=(yyvsp[0].ast);}
#line 1468 "parser.tab.c"
    break;

  case 32: /* Loop: WHILE LEFTPAREN Expr RIGHTPAREN Block  */
#line 228 "parser.y"
                                            {}
#line 1474 "parser.tab.c"
    break;

  case 33: /* If: IF LEFTPAREN Expr RIGHTPAREN Block  */
#line 231 "parser.y"
                                       {}
#line 1480 "parser.tab.c"
    break;

  case 34: /* Primary: NUMBER  */
#line 235 "parser.y"
                        {(yyval.ast) = AST_SingleChildNode("int", (yyvsp[0].number), (yyvsp[0].number)); }
#line 1486 "parser.tab.c"
    break;

  case 35: /* Primary: ID  */
#line 236 "parser.y"
              {(yyval.ast) = AST_SingleChildNode((yyvsp[0].string), (yyvsp[0].string), (yyvsp[0].string));}
#line 1492 "parser.tab.c"
    break;

  case 36: /* Primary: STRING  */
#line 237 "parser.y"
                  {(yyval.ast) = AST_SingleChildNode( "string", (yyvsp[0].string), (yyvsp[0].string));}
#line 1498 "parser.tab.c"
    break;

  case 37: /* Primary: FLOAT  */
#line 238 "parser.y"
                {(yyval.ast) = AST_SingleChildNode( "float", (yyvsp[0].string), (yyvsp[0].string));}
#line 1504 "parser.tab.c"
    break;

  case 38: /* Primary: ID LEFTSQUARE Expr RIGHTSQUARE  */
#line 239 "parser.y"
                                         {(yyval.ast) = AST_SingleChildNode((yyvsp[-3].string), (yyvsp[-3].string), (yyvsp[-1].ast));}
#line 1510 "parser.tab.c"
    break;

  case 39: /* ExprListTail: Expr  */
#line 246 "parser.y"
                        { (yyval.ast) = (yyvsp[0].ast); }
#line 1516 "parser.tab.c"
    break;

  case 40: /* ExprListTail: Expr COMMA ExprListTail  */
#line 247 "parser.y"
                                        { (yyvsp[-2].ast)->left = (yyvsp[0].ast);
							  (yyval.ast) = (yyvsp[-2].ast);
							}
#line 1524 "parser.tab.c"
    break;

  case 41: /* ExprList: %empty  */
#line 252 "parser.y"
          {}
#line 1530 "parser.tab.c"
    break;

  case 43: /* Block: %empty  */
#line 258 "parser.y"
       {}
#line 1536 "parser.tab.c"
    break;

  case 44: /* Block: LEFTBRACKET DeclList StmtList RIGHTBRACKET  */
#line 259 "parser.y"
                                                     { printf("\n RECOGNIZED RULE: Block statement\n");
		(yyval.ast) = AST_DoublyChildNodes("BLOCK",(yyvsp[-2].ast),(yyvsp[-1].ast), (yyvsp[-2].ast), (yyvsp[-1].ast));
		}
#line 1544 "parser.tab.c"
    break;

  case 45: /* Expr: Primary  */
#line 266 "parser.y"
                { printf("\n RECOGNIZED RULE: Simplest expression\n");
				(yyval.ast) = (yyvsp[0].ast);
				strcpy((yyval.ast)->nodeType, CheckPrimaryType((yyvsp[0].ast), currentScope));
				}
#line 1553 "parser.tab.c"
    break;

  case 46: /* Expr: ID EQ Expr  */
#line 270 "parser.y"
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
					printf("ID Declare check\n");
					CheckAssignmentType((yyvsp[-2].string),(yyvsp[0].ast), currentScope);
					// printf("RHS LHS Check\n");
					// if (compareTypes($1,$3, currentScope) != 0) {
					// 	exit(1);
					// }

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					(yyval.ast) = AST_DoublyChildNodes("=",(yyvsp[-2].string),(yyvsp[0].ast), (yyvsp[-2].string), (yyvsp[0].ast));
					// Generate IRcode
					// printf("Generate IR Code\n");
					// emitConstantIntAssignment($1, $3);

					// Generate MIPS code
					// printf("Generate MIPS\n");
					// emitMIPSConstantIntAssignment($1, $3);

					}
#line 1591 "parser.tab.c"
    break;

  case 47: /* Expr: Expr PLUS Expr  */
#line 303 "parser.y"
                         { printf("\n RECOGNIZED RULE: PLUS statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("+",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
					printf("EXPR PLUS EXPR: %s \n------------------------------------------------------------------\n", (yyvsp[0].ast) ->nodeType);
				}
#line 1605 "parser.tab.c"
    break;

  case 48: /* Expr: Expr MINUS Expr  */
#line 312 "parser.y"
                          { printf("\n RECOGNIZED RULE: MINUS statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("-",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				}
#line 1618 "parser.tab.c"
    break;

  case 49: /* Expr: Expr MULTIPLY Expr  */
#line 320 "parser.y"
                             { printf("\n RECOGNIZED RULE: MULTIPLY statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("*",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				}
#line 1631 "parser.tab.c"
    break;

  case 50: /* Expr: Expr DIVIDE Expr  */
#line 328 "parser.y"
                           { printf("\n RECOGNIZED RULE: DIVIDE statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("/",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				}
#line 1644 "parser.tab.c"
    break;

  case 51: /* Expr: Expr EXPONENT Expr  */
#line 336 "parser.y"
                             { printf("\n RECOGNIZED RULE: BinOp statement\n");
				// Semantic checks
				
				// Check if both exprs exist
				
				// Generate AST Nodes (doubly linked)
				(yyval.ast) = AST_DoublyChildNodes("EXP ",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
			}
#line 1657 "parser.tab.c"
    break;

  case 52: /* Expr: Expr COMPARSIONOPERATOR Expr  */
#line 344 "parser.y"
                                       {(yyval.ast) = AST_DoublyChildNodes("Comparsion",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1663 "parser.tab.c"
    break;

  case 53: /* Expr: Expr LOGICALOPERATOR Expr  */
#line 345 "parser.y"
                                    {(yyval.ast) = AST_DoublyChildNodes("Logical",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1669 "parser.tab.c"
    break;

  case 54: /* Expr: LEFTPAREN Expr RIGHTPAREN  */
#line 346 "parser.y"
                                    {(yyval.ast) = (yyvsp[-1].ast);}
#line 1675 "parser.tab.c"
    break;

  case 55: /* Expr: FunctionCall  */
#line 347 "parser.y"
                       {(yyval.ast) = (yyvsp[0].ast);}
#line 1681 "parser.tab.c"
    break;

  case 56: /* Expr: TRUEZ  */
#line 348 "parser.y"
                {(yyval.ast) = AST_SingleChildNode("TRUE", (yyvsp[0].string), (yyvsp[0].string));}
#line 1687 "parser.tab.c"
    break;

  case 57: /* Expr: FALSEZ  */
#line 349 "parser.y"
                 {(yyval.ast) = AST_SingleChildNode("FALSE",(yyvsp[0].string), (yyvsp[0].string));}
#line 1693 "parser.tab.c"
    break;

  case 58: /* FunctionCall: ID LEFTPAREN ExprList RIGHTPAREN  */
#line 353 "parser.y"
                                               {}
#line 1699 "parser.tab.c"
    break;


#line 1703 "parser.tab.c"

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

#line 356 "parser.y"




/* [EType]  */




/* 
EType = CheckPrimaryType($1); */
/* EType = CheckAssignmentType($1, $3);
EType = CheckBinOpType($1, $3); */


// int main(int argc, char**argv)
// {
// /* 
// 	#ifdef YYDEBUG
// 		yydebug = 1;
// 	#endif */

// 	printf("\n \n \n \n \n \n--------------------Parser Start------------------------\n\n\n");
	
// 	if (argc > 1){
// 	  if(!(yyin = fopen(argv[1], "r")))
//           {
// 		perror(argv[1]);
// 		return(1);
// 	  }
// 	}
// 	yyparse();
// }

int parser_main(FILE*inputfile)
{
/* 
	#ifdef YYDEBUG
		yydebug = 1;
	#endif */

	printf("\n \n \n \n \n \n--------------------Parser Start------------------------\n\n\n");
	strcpy(currentScope, "global");
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
