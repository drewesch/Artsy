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
char tempScopeStore[50];

#line 92 "parser.tab.c"

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
  YYSYMBOL_FuncHeader = 46,                /* FuncHeader  */
  YYSYMBOL_FunDecl = 47,                   /* FunDecl  */
  YYSYMBOL_ParamDeclList = 48,             /* ParamDeclList  */
  YYSYMBOL_ParamDeclListTail = 49,         /* ParamDeclListTail  */
  YYSYMBOL_ParamDecl = 50,                 /* ParamDecl  */
  YYSYMBOL_StmtList = 51,                  /* StmtList  */
  YYSYMBOL_Stmt = 52,                      /* Stmt  */
  YYSYMBOL_Loop = 53,                      /* Loop  */
  YYSYMBOL_If = 54,                        /* If  */
  YYSYMBOL_Primary = 55,                   /* Primary  */
  YYSYMBOL_ExprListTail = 56,              /* ExprListTail  */
  YYSYMBOL_ExprList = 57,                  /* ExprList  */
  YYSYMBOL_Block = 58,                     /* Block  */
  YYSYMBOL_Expr = 59,                      /* Expr  */
  YYSYMBOL_FunctionCall = 60               /* FunctionCall  */
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
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   213

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  113

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
       0,    83,    83,    98,    99,   101,   104,   108,   115,   139,
     157,   158,   159,   162,   163,   166,   192,   199,   200,   203,
     204,   207,   208,   213,   214,   220,   221,   225,   230,   234,
     235,   236,   237,   238,   245,   248,   252,   253,   254,   255,
     256,   263,   264,   269,   270,   275,   276,   283,   288,   321,
     356,   365,   373,   381,   389,   397,   398,   399,   400,   401,
     402,   406
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
  "FunDeclList", "FunDeclListTail", "FuncHeader", "FunDecl",
  "ParamDeclList", "ParamDeclListTail", "ParamDecl", "StmtList", "Stmt",
  "Loop", "If", "Primary", "ExprListTail", "ExprList", "Block", "Expr",
  "FunctionCall", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-41)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     154,     4,    67,   -41,   -41,   -41,   154,    -3,   -41,    13,
       0,    18,    -3,    14,    38,   -41,   -41,    54,    30,   -41,
     154,   -41,   182,   -41,   -41,   -41,   -41,     2,   -41,     3,
      -3,    -3,    -3,   182,    23,    46,    44,   -41,    55,    34,
      -3,    -3,   -41,    68,   182,   -41,    64,    30,   -41,   -41,
      -3,    -3,   -41,    -3,    -3,    -3,    -3,    -3,   -41,    59,
     111,   -41,    65,    66,    57,    69,   -41,    -3,   -41,   -41,
     -41,    78,    89,    83,   -41,   -41,   -41,    30,   118,   105,
      93,    93,    50,    50,   -41,    80,   -41,    -3,    91,   -41,
      99,    64,    64,    94,    97,   -41,    -3,   -41,   -41,   -41,
     107,   -41,   111,   116,   114,   -41,   126,    98,   -41,   107,
     103,   -41,   -41
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,    37,    39,    38,    25,     3,     0,    36,     0,
       0,     0,     0,     0,     0,    59,    60,     0,    10,     5,
       3,     7,    23,    32,    33,    47,    31,     0,    58,     0,
       0,    43,     0,    45,     0,    37,     0,    28,     0,     0,
       0,     0,     1,     0,    45,    12,    45,    11,     4,    24,
       0,     0,    26,     0,     0,     0,     0,     0,     8,     0,
      48,    44,     0,    41,     0,     0,    57,     0,    27,    30,
      29,     0,     0,     0,     2,    16,    14,    13,    56,    55,
      50,    51,    52,    53,    54,     0,    61,     0,    40,    46,
       0,    45,    45,     0,     0,    42,     0,    40,    35,    34,
      17,     9,    49,     0,     0,    18,    19,    21,    15,     0,
       0,    20,    22
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -41,   -41,     1,   -41,   -41,   -41,   124,   -41,   130,   -41,
      41,   -41,   -18,   -41,   -41,   -41,   146,    74,   -41,   -40,
      -7,   -41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    17,    18,    19,    20,    44,    76,    46,    77,   104,
     105,   106,    21,    22,    23,    24,    25,    61,    62,    26,
      27,    28
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      34,     2,     3,     4,    49,    39,    75,    33,    29,    50,
      51,    37,     7,    52,    58,    65,     8,    35,     3,     4,
      59,    48,    38,    60,    63,    64,    74,    15,    16,    40,
      50,    51,     8,    71,    72,    53,    54,    55,    56,    66,
      57,    50,    51,    78,    79,    70,    80,    81,    82,    83,
      84,    98,    99,    41,    42,    68,    53,    54,    55,    56,
      90,    57,    43,    67,    50,    51,    69,    53,    54,    55,
      56,    73,    57,    50,    51,    88,    87,     6,    85,    30,
      63,    86,    31,    89,    32,    50,    51,    93,    57,   102,
      53,    54,    55,    56,    91,    57,    50,    51,    94,    53,
      54,    55,    56,    96,    57,    92,    50,    51,   101,   100,
     103,    53,    54,    55,    56,   110,    57,    97,    50,    51,
     107,   112,    53,    54,    55,    56,    51,    57,    55,    56,
     108,    57,    53,    54,    55,    56,   109,    57,    53,    54,
      55,    56,    45,    57,    53,    54,    55,    56,    47,    57,
     111,    53,    54,    55,    56,    36,    57,     1,     2,     3,
       4,    95,     0,     0,     0,     5,     0,     6,     0,     7,
       0,     0,     0,     8,     9,    10,    11,    12,    13,     0,
       0,    14,     0,     0,    15,    16,     2,     3,     4,     0,
       0,     0,     0,     5,     0,     6,     0,     7,     0,     0,
       0,     8,     9,    10,    11,    12,    13,     0,     0,    14,
       0,     0,    15,    16
};

static const yytype_int8 yycheck[] =
{
       7,     4,     5,     6,    22,    12,    46,     6,     4,     7,
       8,    11,    15,    11,    11,    33,    19,     4,     5,     6,
      17,    20,     4,    30,    31,    32,    44,    30,    31,    15,
       7,     8,    19,    40,    41,    33,    34,    35,    36,    16,
      38,     7,     8,    50,    51,    11,    53,    54,    55,    56,
      57,    91,    92,    15,     0,    11,    33,    34,    35,    36,
      67,    38,    32,    17,     7,     8,    11,    33,    34,    35,
      36,     3,    38,     7,     8,    18,    10,    13,    19,    12,
      87,    16,    15,    14,    17,     7,     8,     4,    38,    96,
      33,    34,    35,    36,    16,    38,     7,     8,    18,    33,
      34,    35,    36,    12,    38,    16,     7,     8,    11,    15,
       3,    33,    34,    35,    36,    17,    38,    18,     7,     8,
       4,    18,    33,    34,    35,    36,     8,    38,    35,    36,
      16,    38,    33,    34,    35,    36,    10,    38,    33,    34,
      35,    36,    18,    38,    33,    34,    35,    36,    18,    38,
     109,    33,    34,    35,    36,     9,    38,     3,     4,     5,
       6,    87,    -1,    -1,    -1,    11,    -1,    13,    -1,    15,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    -1,
      -1,    27,    -1,    -1,    30,    31,     4,     5,     6,    -1,
      -1,    -1,    -1,    11,    -1,    13,    -1,    15,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    -1,    -1,    27,
      -1,    -1,    30,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    11,    13,    15,    19,    20,
      21,    22,    23,    24,    27,    30,    31,    40,    41,    42,
      43,    51,    52,    53,    54,    55,    58,    59,    60,     4,
      12,    15,    17,    41,    59,     4,    55,    11,     4,    59,
      15,    15,     0,    32,    44,    45,    46,    47,    41,    51,
       7,     8,    11,    33,    34,    35,    36,    38,    11,    17,
      59,    56,    57,    59,    59,    51,    16,    17,    11,    11,
      11,    59,    59,     3,    51,    58,    45,    47,    59,    59,
      59,    59,    59,    59,    59,    19,    16,    10,    18,    14,
      59,    16,    16,     4,    18,    56,    12,    18,    58,    58,
      15,    11,    59,     3,    48,    49,    50,     4,    16,    10,
      17,    49,    18
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    41,    42,    42,    43,    43,
      44,    44,    44,    45,    45,    46,    47,    48,    48,    49,
      49,    50,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    53,    54,    55,    55,    55,    55,
      55,    56,    56,    57,    57,    58,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    60
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     0,     2,     1,     1,     1,     3,     6,
       0,     1,     1,     1,     2,     6,     2,     0,     1,     1,
       3,     2,     4,     1,     2,     1,     2,     3,     2,     3,
       3,     1,     1,     1,     5,     5,     1,     1,     1,     1,
       4,     1,     3,     0,     1,     0,     4,     1,     3,     6,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     4
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
#line 83 "parser.y"
                                       {
	// Main program parser rule, generates the whole AST for the program
	(yyval.ast) = AST_SingleChildNode("program",(yyvsp[-2].ast), (yyvsp[-2].ast));

	printf("\n\n\n\n\n--------------------Parser End------------------------\n\n\n");

	ast = (yyval.ast);

}
#line 1243 "parser.tab.c"
    break;

  case 4: /* DeclList: VarDecl DeclList  */
#line 99 "parser.y"
                                { (yyval.ast) = AST_DoublyChildNodes("vardec", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
							}
#line 1250 "parser.tab.c"
    break;

  case 5: /* DeclList: Decl  */
#line 101 "parser.y"
                { (yyval.ast) = (yyvsp[0].ast); }
#line 1256 "parser.tab.c"
    break;

  case 6: /* Decl: VarDecl  */
#line 104 "parser.y"
                {
	// Basic Var Declaration Rule, generates AST for all variable declarations
	(yyval.ast) = (yyvsp[0].ast);
	}
#line 1265 "parser.tab.c"
    break;

  case 7: /* Decl: StmtList  */
#line 108 "parser.y"
                   {
		// Basic Statement list declaration rule, generates AST for all statement declarations
		(yyval.ast) = (yyvsp[0].ast);
		}
#line 1274 "parser.tab.c"
    break;

  case 8: /* VarDecl: TYPE ID SEMICOLON  */
#line 115 "parser.y"
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
#line 1302 "parser.tab.c"
    break;

  case 9: /* VarDecl: TYPE ID LEFTSQUARE NUMBER RIGHTSQUARE SEMICOLON  */
#line 139 "parser.y"
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
#line 1323 "parser.tab.c"
    break;

  case 10: /* FunDeclList: %empty  */
#line 157 "parser.y"
             {}
#line 1329 "parser.tab.c"
    break;

  case 11: /* FunDeclList: FunDecl  */
#line 158 "parser.y"
                  {(yyval.ast) = (yyvsp[0].ast);}
#line 1335 "parser.tab.c"
    break;

  case 12: /* FunDeclList: FunDeclListTail  */
#line 159 "parser.y"
                          {(yyval.ast) = (yyvsp[0].ast);}
#line 1341 "parser.tab.c"
    break;

  case 13: /* FunDeclListTail: FunDecl  */
#line 162 "parser.y"
                         {(yyval.ast) = (yyvsp[0].ast);}
#line 1347 "parser.tab.c"
    break;

  case 14: /* FunDeclListTail: FunDecl FunDeclListTail  */
#line 163 "parser.y"
                                  {(yyval.ast) = AST_DoublyChildNodes("FunDecl FunDeclListTail",(yyvsp[-1].ast),(yyvsp[0].ast),(yyvsp[-1].ast), (yyvsp[0].ast));}
#line 1353 "parser.tab.c"
    break;

  case 15: /* FuncHeader: FUNCTION TYPE ID LEFTPAREN ParamDeclList RIGHTPAREN  */
#line 166 "parser.y"
                                                                {
	symTabAccess();
	int inSymTab = found((yyvsp[-3].string), currentScope);
	//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);

	// Check if the variable has been declared
	// If it has, throw an error
	//printf("0 Function okkkkkkkkkkkkkkkkkkkkkkkkkkkkk-----------------------\n");
	if (inSymTab == 0){
		//printf("Function okkkkkkkkkkkkkkkkkkkkkkkkkkkkk-----------------------\n");
		addFunction((yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-1].ast)); //id
	}
	else {
		printf("SEMANTIC ERROR: Function %s is already in the symbol table", (yyvsp[-3].string));
		exit(1);
	}
	//printf("2 Function okkkkkkkkkkkkkkkkkkkkkkkkkkkkk-----------------------\n");
	// If the variable has not been declared 
	showSymTable();
	(yyval.ast) = AST_DoublyChildNodes("Function Context", (yyvsp[-3].string), (yyvsp[-1].ast), (yyvsp[-3].string), (yyvsp[-1].ast));

	strcpy(tempScopeStore, currentScope);
	strcpy(currentScope, (yyvsp[-3].string));
}
#line 1382 "parser.tab.c"
    break;

  case 16: /* FunDecl: FuncHeader Block  */
#line 192 "parser.y"
                          {
	// Generate AST node as a doubly node
	(yyval.ast) = AST_DoublyChildNodes("Function",(yyvsp[-1].ast),(yyvsp[0].ast),(yyvsp[-1].ast), (yyvsp[0].ast));
	strcpy(currentScope, tempScopeStore);
}
#line 1392 "parser.tab.c"
    break;

  case 17: /* ParamDeclList: %empty  */
#line 199 "parser.y"
               {}
#line 1398 "parser.tab.c"
    break;

  case 18: /* ParamDeclList: ParamDeclListTail  */
#line 200 "parser.y"
                            {(yyval.ast) = (yyvsp[0].ast);}
#line 1404 "parser.tab.c"
    break;

  case 19: /* ParamDeclListTail: ParamDecl  */
#line 203 "parser.y"
                             {(yyval.ast) = (yyvsp[0].ast);}
#line 1410 "parser.tab.c"
    break;

  case 20: /* ParamDeclListTail: ParamDecl COMMA ParamDeclListTail  */
#line 204 "parser.y"
                                            {(yyval.ast) = AST_DoublyChildNodes("ParaDecl comma ParaDeclListTail",(yyvsp[-2].ast),(yyvsp[0].ast),(yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1416 "parser.tab.c"
    break;

  case 21: /* ParamDecl: TYPE ID  */
#line 207 "parser.y"
                   {(yyval.ast) = AST_DoublyChildNodes("Variable parm",(yyvsp[-1].string),(yyvsp[0].string),(yyvsp[-1].string), (yyvsp[0].string));}
#line 1422 "parser.tab.c"
    break;

  case 22: /* ParamDecl: TYPE ID LEFTSQUARE RIGHTSQUARE  */
#line 208 "parser.y"
                                         {(yyval.ast) = AST_DoublyChildNodes("array parm",(yyvsp[-3].string),(yyvsp[-2].string),(yyvsp[-3].string), (yyvsp[-2].string));}
#line 1428 "parser.tab.c"
    break;

  case 24: /* StmtList: Stmt StmtList  */
#line 214 "parser.y"
                        {
		// Generate a list of all statement declarations below vardecl
		(yyval.ast) = AST_DoublyChildNodes("statements", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
		}
#line 1437 "parser.tab.c"
    break;

  case 25: /* Stmt: SEMICOLON  */
#line 220 "parser.y"
                        {}
#line 1443 "parser.tab.c"
    break;

  case 26: /* Stmt: Expr SEMICOLON  */
#line 221 "parser.y"
                                {
		// Simplest expr statement in grammar
		(yyval.ast) = (yyvsp[-1].ast);
		}
#line 1452 "parser.tab.c"
    break;

  case 27: /* Stmt: WRITE Primary SEMICOLON  */
#line 225 "parser.y"
                                        { printf("\n RECOGNIZED RULE: WRITE statement\n");
					// Generate write declarations as a statement in the parser
					(yyval.ast) = AST_SingleChildNode("write", (yyvsp[-1].ast), (yyvsp[-1].ast));
					printf("Write AST generated!");
				}
#line 1462 "parser.tab.c"
    break;

  case 28: /* Stmt: WRITELN SEMICOLON  */
#line 230 "parser.y"
                            {
		printf("\n RECOGNIZED RULE: WRITEIN statement\n");
		(yyval.ast) = AST_SingleChildNode("writeln", "\n", 0);
	}
#line 1471 "parser.tab.c"
    break;

  case 29: /* Stmt: RETURN Expr SEMICOLON  */
#line 234 "parser.y"
                                { (yyval.ast) = AST_SingleChildNode("return", (yyvsp[-1].ast),0); }
#line 1477 "parser.tab.c"
    break;

  case 30: /* Stmt: READ ID SEMICOLON  */
#line 235 "parser.y"
                            {(yyval.ast) = AST_SingleChildNode("read", (yyvsp[-1].string), 0);}
#line 1483 "parser.tab.c"
    break;

  case 31: /* Stmt: Block  */
#line 236 "parser.y"
                {(yyval.ast) = (yyvsp[0].ast);}
#line 1489 "parser.tab.c"
    break;

  case 32: /* Stmt: Loop  */
#line 237 "parser.y"
               {(yyval.ast)=(yyvsp[0].ast);}
#line 1495 "parser.tab.c"
    break;

  case 33: /* Stmt: If  */
#line 238 "parser.y"
             {(yyval.ast)=(yyvsp[0].ast);}
#line 1501 "parser.tab.c"
    break;

  case 34: /* Loop: WHILE LEFTPAREN Expr RIGHTPAREN Block  */
#line 245 "parser.y"
                                            {}
#line 1507 "parser.tab.c"
    break;

  case 35: /* If: IF LEFTPAREN Expr RIGHTPAREN Block  */
#line 248 "parser.y"
                                       {}
#line 1513 "parser.tab.c"
    break;

  case 36: /* Primary: NUMBER  */
#line 252 "parser.y"
                        {(yyval.ast) = AST_SingleChildNode("int", (yyvsp[0].number), (yyvsp[0].number)); }
#line 1519 "parser.tab.c"
    break;

  case 37: /* Primary: ID  */
#line 253 "parser.y"
              {(yyval.ast) = AST_SingleChildNode((yyvsp[0].string), (yyvsp[0].string), (yyvsp[0].string));}
#line 1525 "parser.tab.c"
    break;

  case 38: /* Primary: STRING  */
#line 254 "parser.y"
                  {(yyval.ast) = AST_SingleChildNode( "string", (yyvsp[0].string), (yyvsp[0].string));}
#line 1531 "parser.tab.c"
    break;

  case 39: /* Primary: FLOAT  */
#line 255 "parser.y"
                {(yyval.ast) = AST_SingleChildNode( "float", (yyvsp[0].string), (yyvsp[0].string));}
#line 1537 "parser.tab.c"
    break;

  case 40: /* Primary: ID LEFTSQUARE Expr RIGHTSQUARE  */
#line 256 "parser.y"
                                         {(yyval.ast) = AST_SingleChildNode((yyvsp[-3].string), (yyvsp[-3].string), (yyvsp[-1].ast));}
#line 1543 "parser.tab.c"
    break;

  case 41: /* ExprListTail: Expr  */
#line 263 "parser.y"
                        { (yyval.ast) = (yyvsp[0].ast); }
#line 1549 "parser.tab.c"
    break;

  case 42: /* ExprListTail: Expr COMMA ExprListTail  */
#line 264 "parser.y"
                                        { (yyvsp[-2].ast)->left = (yyvsp[0].ast);
							  (yyval.ast) = (yyvsp[-2].ast);
							}
#line 1557 "parser.tab.c"
    break;

  case 43: /* ExprList: %empty  */
#line 269 "parser.y"
          {}
#line 1563 "parser.tab.c"
    break;

  case 45: /* Block: %empty  */
#line 275 "parser.y"
       {}
#line 1569 "parser.tab.c"
    break;

  case 46: /* Block: LEFTBRACKET DeclList StmtList RIGHTBRACKET  */
#line 276 "parser.y"
                                                     { printf("\n RECOGNIZED RULE: Block statement\n");
		(yyval.ast) = AST_DoublyChildNodes("BLOCK",(yyvsp[-2].ast),(yyvsp[-1].ast), (yyvsp[-2].ast), (yyvsp[-1].ast));
		}
#line 1577 "parser.tab.c"
    break;

  case 47: /* Expr: Primary  */
#line 283 "parser.y"
                { printf("\n RECOGNIZED RULE: Simplest expression\n");
				(yyval.ast) = (yyvsp[0].ast);
				printf("%s\n", (yyvsp[0].ast));
				strcpy((yyval.ast)->nodeType, CheckPrimaryType((yyvsp[0].ast), currentScope));
				}
#line 1587 "parser.tab.c"
    break;

  case 48: /* Expr: ID EQ Expr  */
#line 288 "parser.y"
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
#line 1625 "parser.tab.c"
    break;

  case 49: /* Expr: ID LEFTSQUARE Expr RIGHTSQUARE EQ Expr  */
#line 321 "parser.y"
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
					printf("ID Declare check\n");
					CheckAssignmentType((yyvsp[-5].string),(yyvsp[0].ast), currentScope);
					// printf("RHS LHS Check\n");
					// if (compareTypes($1,$3, currentScope) != 0) {
					// 	exit(1);
					// }

					// Generate AST tree nodes
					printf("DEBUG -- GENERATE AST\n");
					struct AST* arrElementNode = AST_DoublyChildNodes("element",(yyvsp[-5].string),(yyvsp[-3].ast), (yyvsp[-5].string), (yyvsp[-3].ast));
					(yyval.ast) = AST_DoublyChildNodes("=",arrElementNode,(yyvsp[0].ast), arrElementNode, (yyvsp[0].ast));
					// Generate IRcode
					// printf("Generate IR Code\n");
					// emitConstantIntAssignment($1, $3);

					// Generate MIPS code
					// printf("Generate MIPS\n");
					// emitMIPSConstantIntAssignment($1, $3);

					}
#line 1664 "parser.tab.c"
    break;

  case 50: /* Expr: Expr PLUS Expr  */
#line 356 "parser.y"
                         { printf("\n RECOGNIZED RULE: PLUS statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("+",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
					printf("EXPR PLUS EXPR: %s \n------------------------------------------------------------------\n", (yyvsp[0].ast) ->nodeType);
				}
#line 1678 "parser.tab.c"
    break;

  case 51: /* Expr: Expr MINUS Expr  */
#line 365 "parser.y"
                          { printf("\n RECOGNIZED RULE: MINUS statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("-",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				}
#line 1691 "parser.tab.c"
    break;

  case 52: /* Expr: Expr MULTIPLY Expr  */
#line 373 "parser.y"
                             { printf("\n RECOGNIZED RULE: MULTIPLY statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("*",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				}
#line 1704 "parser.tab.c"
    break;

  case 53: /* Expr: Expr DIVIDE Expr  */
#line 381 "parser.y"
                           { printf("\n RECOGNIZED RULE: DIVIDE statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("/",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				}
#line 1717 "parser.tab.c"
    break;

  case 54: /* Expr: Expr EXPONENT Expr  */
#line 389 "parser.y"
                             { printf("\n RECOGNIZED RULE: BinOp statement\n");
				// Semantic checks
				
				// Check if both exprs exist
				
				// Generate AST Nodes (doubly linked)
				(yyval.ast) = AST_DoublyChildNodes("EXP ",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
			}
#line 1730 "parser.tab.c"
    break;

  case 55: /* Expr: Expr COMPARSIONOPERATOR Expr  */
#line 397 "parser.y"
                                       {(yyval.ast) = AST_DoublyChildNodes("Comparsion",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1736 "parser.tab.c"
    break;

  case 56: /* Expr: Expr LOGICALOPERATOR Expr  */
#line 398 "parser.y"
                                    {(yyval.ast) = AST_DoublyChildNodes("Logical",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1742 "parser.tab.c"
    break;

  case 57: /* Expr: LEFTPAREN Expr RIGHTPAREN  */
#line 399 "parser.y"
                                    {(yyval.ast) = (yyvsp[-1].ast);}
#line 1748 "parser.tab.c"
    break;

  case 58: /* Expr: FunctionCall  */
#line 400 "parser.y"
                       {(yyval.ast) = (yyvsp[0].ast);}
#line 1754 "parser.tab.c"
    break;

  case 59: /* Expr: TRUEZ  */
#line 401 "parser.y"
                {(yyval.ast) = AST_SingleChildNode("TRUE", (yyvsp[0].string), (yyvsp[0].string));}
#line 1760 "parser.tab.c"
    break;

  case 60: /* Expr: FALSEZ  */
#line 402 "parser.y"
                 {(yyval.ast) = AST_SingleChildNode("FALSE",(yyvsp[0].string), (yyvsp[0].string));}
#line 1766 "parser.tab.c"
    break;

  case 61: /* FunctionCall: ID LEFTPAREN ExprList RIGHTPAREN  */
#line 406 "parser.y"
                                               {}
#line 1772 "parser.tab.c"
    break;


#line 1776 "parser.tab.c"

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

#line 409 "parser.y"




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

	// #ifdef YYDEBUG
	// 	yydebug = 1;
	// #endif

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
