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
  YYSYMBOL_WRITE = 21,                     /* WRITE  */
  YYSYMBOL_WRITELN = 22,                   /* WRITELN  */
  YYSYMBOL_READ = 23,                      /* READ  */
  YYSYMBOL_RETURN = 24,                    /* RETURN  */
  YYSYMBOL_IF = 25,                        /* IF  */
  YYSYMBOL_ELIF = 26,                      /* ELIF  */
  YYSYMBOL_ELSE = 27,                      /* ELSE  */
  YYSYMBOL_WHILE = 28,                     /* WHILE  */
  YYSYMBOL_BREAK = 29,                     /* BREAK  */
  YYSYMBOL_FOR = 30,                       /* FOR  */
  YYSYMBOL_TRUEZ = 31,                     /* TRUEZ  */
  YYSYMBOL_FALSEZ = 32,                    /* FALSEZ  */
  YYSYMBOL_FUNCTION = 33,                  /* FUNCTION  */
  YYSYMBOL_PLUS = 34,                      /* PLUS  */
  YYSYMBOL_MINUS = 35,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 36,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 37,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 38,                    /* MODULO  */
  YYSYMBOL_EXPONENT = 39,                  /* EXPONENT  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Program = 41,                   /* Program  */
  YYSYMBOL_DeclList = 42,                  /* DeclList  */
  YYSYMBOL_Decl = 43,                      /* Decl  */
  YYSYMBOL_VarDecl = 44,                   /* VarDecl  */
  YYSYMBOL_FunDeclList = 45,               /* FunDeclList  */
  YYSYMBOL_FunDeclListTail = 46,           /* FunDeclListTail  */
  YYSYMBOL_FuncHeader = 47,                /* FuncHeader  */
  YYSYMBOL_FunDecl = 48,                   /* FunDecl  */
  YYSYMBOL_ParamDeclList = 49,             /* ParamDeclList  */
  YYSYMBOL_ParamDeclListTail = 50,         /* ParamDeclListTail  */
  YYSYMBOL_ParamDecl = 51,                 /* ParamDecl  */
  YYSYMBOL_StmtList = 52,                  /* StmtList  */
  YYSYMBOL_Stmt = 53,                      /* Stmt  */
  YYSYMBOL_Loop = 54,                      /* Loop  */
  YYSYMBOL_If = 55,                        /* If  */
  YYSYMBOL_Elif = 56,                      /* Elif  */
  YYSYMBOL_Else = 57,                      /* Else  */
  YYSYMBOL_Primary = 58,                   /* Primary  */
  YYSYMBOL_ExprListTail = 59,              /* ExprListTail  */
  YYSYMBOL_ExprList = 60,                  /* ExprList  */
  YYSYMBOL_Block = 61,                     /* Block  */
  YYSYMBOL_Expr = 62,                      /* Expr  */
  YYSYMBOL_FunctionCall = 63               /* FunctionCall  */
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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   182

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    84,    84,   101,   103,   106,   107,   114,   138,   160,
     161,   162,   165,   166,   169,   192,   199,   200,   203,   204,
     207,   208,   211,   214,   221,   222,   226,   231,   235,   236,
     237,   238,   239,   240,   241,   245,   248,   251,   254,   258,
     259,   260,   261,   262,   263,   272,   273,   278,   279,   286,
     291,   296,   329,   365,   374,   382,   390,   427,   435,   436,
     437,   438,   439,   440,   444
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
  "LEFTPAREN", "RIGHTPAREN", "LEFTSQUARE", "RIGHTSQUARE", "NUMBER",
  "WRITE", "WRITELN", "READ", "RETURN", "IF", "ELIF", "ELSE", "WHILE",
  "BREAK", "FOR", "TRUEZ", "FALSEZ", "FUNCTION", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "MODULO", "EXPONENT", "$accept", "Program",
  "DeclList", "Decl", "VarDecl", "FunDeclList", "FunDeclListTail",
  "FuncHeader", "FunDecl", "ParamDeclList", "ParamDeclListTail",
  "ParamDecl", "StmtList", "Stmt", "Loop", "If", "Elif", "Else", "Primary",
  "ExprListTail", "ExprList", "Block", "Expr", "FunctionCall", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-31)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -1,    11,    21,   -30,   -31,    -1,     6,   -31,    14,   150,
     -31,    22,   -30,   -31,   -31,    32,    41,   118,   -31,   -31,
     -31,   -31,    -1,     3,   -31,     7,    30,    51,     3,    45,
      53,    22,    54,   -31,   -31,   -31,   150,   -31,   -31,   -31,
     -31,   -31,   -31,    17,   -31,   -31,   -31,   -30,    48,    55,
       3,     7,    61,   150,    23,    65,    74,   -31,    77,    64,
       3,     3,   -31,     3,   -31,     3,     3,   -31,     3,     3,
       3,     3,     3,    78,    79,   114,    81,   -31,    71,    75,
      99,   -31,    88,   -31,   -31,   -31,    70,    76,   108,    93,
      29,    38,    38,    80,    80,   -31,   -31,   116,   101,   -31,
     110,     7,   -31,   111,   -31,   107,    22,    22,    22,   115,
     -31,    79,   -31,     3,   -31,   -31,   -31,   -31,   119,   -31,
     114,   -31
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     9,     4,     5,     0,     1,     0,     0,
      11,     0,    10,     3,     7,     0,     0,    41,    39,    43,
      42,    24,     5,     0,    40,     0,     0,     0,     0,     0,
       0,     0,     0,    62,    63,     2,    22,    31,    32,    33,
      34,    50,    30,     0,    61,    15,    13,    12,     0,     0,
       0,    47,     0,     0,     0,    41,     0,    27,     0,     0,
       0,     0,    38,     0,    23,     0,     0,    25,     0,     0,
       0,     0,     0,     0,    16,    51,    45,    48,     0,     0,
       0,    60,     0,    26,    29,    28,     0,     0,     0,    59,
      58,    53,    54,    55,    56,    57,     8,     0,     0,    17,
      18,     0,    64,    44,    49,     0,     0,     0,     0,    20,
      14,     0,    46,     0,    44,    36,    37,    35,     0,    19,
      52,    21
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -31,   -31,     0,   -31,   -31,   -31,   132,   -31,   134,   -31,
      28,   -31,   -20,   -31,   -31,   -31,   -31,   -31,   -21,    39,
     -31,   -11,   -22,   -31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,     5,     9,    46,    11,    47,    98,
      99,   100,    35,    36,    37,    38,    39,    40,    41,    77,
      78,    42,    43,    44
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      45,    54,     1,     8,    56,    13,    59,    17,    18,    19,
      20,    55,    18,    19,    20,     6,    64,    16,    14,    23,
      62,     7,    53,    24,    15,    65,    66,    24,    75,    67,
      76,    65,    66,    80,    33,    34,    22,    48,    86,    87,
      81,    88,    57,    89,    90,    49,    91,    92,    93,    94,
      95,    68,    69,    70,    71,    58,    72,    68,    69,    70,
      71,    60,    72,    68,    69,    70,    71,    73,    72,    61,
      63,    74,    65,    66,    70,    71,    85,    72,    65,    66,
      76,    79,    97,    82,    65,    66,    83,   106,   102,    84,
      96,   120,   101,   107,   103,   115,   116,   117,    68,    69,
      70,    71,    66,    72,    68,    69,    70,    71,   105,    72,
      68,    69,    70,    71,   104,    72,    65,    66,   110,    72,
     109,   111,    65,    66,   113,   108,   114,    68,    69,    70,
      71,    50,    72,   118,    51,    10,    52,    12,   121,   119,
     112,     0,    68,    69,    70,    71,     0,    72,    68,    69,
      70,    71,     0,    72,    17,    18,    19,    20,     0,     0,
       0,     0,    21,     0,    22,     0,    23,     0,     0,     0,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     0,
       0,    33,    34
};

static const yytype_int8 yycheck[] =
{
      11,    23,     3,    33,    25,     5,    28,     4,     5,     6,
       7,     4,     5,     6,     7,     4,    36,     3,    12,    16,
      31,     0,    22,    20,    18,     8,     9,    20,    50,    12,
      51,     8,     9,    53,    31,    32,    14,     5,    60,    61,
      17,    63,    12,    65,    66,     4,    68,    69,    70,    71,
      72,    34,    35,    36,    37,     4,    39,    34,    35,    36,
      37,    16,    39,    34,    35,    36,    37,    19,    39,    16,
      16,    16,     8,     9,    36,    37,    12,    39,     8,     9,
     101,    20,     3,    18,     8,     9,    12,    17,    17,    12,
      12,   113,    11,    17,    19,   106,   107,   108,    34,    35,
      36,    37,     9,    39,    34,    35,    36,    37,    20,    39,
      34,    35,    36,    37,    15,    39,     8,     9,    17,    39,
       4,    11,     8,     9,    13,    17,    19,    34,    35,    36,
      37,    13,    39,    18,    16,     3,    18,     3,    19,   111,
     101,    -1,    34,    35,    36,    37,    -1,    39,    34,    35,
      36,    37,    -1,    39,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    12,    -1,    14,    -1,    16,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    31,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    41,    42,    43,    44,     4,     0,    33,    45,
      46,    47,    48,    42,    12,    18,     3,     4,     5,     6,
       7,    12,    14,    16,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    31,    32,    52,    53,    54,    55,    56,
      57,    58,    61,    62,    63,    61,    46,    48,     5,     4,
      13,    16,    18,    42,    62,     4,    58,    12,     4,    62,
      16,    16,    61,    16,    52,     8,     9,    12,    34,    35,
      36,    37,    39,    19,    16,    62,    58,    59,    60,    20,
      52,    17,    18,    12,    12,    12,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    12,     3,    49,    50,
      51,    11,    17,    19,    15,    20,    17,    17,    17,     4,
      17,    11,    59,    13,    19,    61,    61,    61,    18,    50,
      62,    19
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    44,    44,    45,
      45,    45,    46,    46,    47,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    55,    56,    57,    58,
      58,    58,    58,    58,    58,    59,    59,    60,    60,    61,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     1,     0,     1,     3,     6,     0,
       1,     1,     1,     2,     6,     2,     0,     1,     1,     3,
       2,     4,     1,     2,     1,     2,     3,     2,     3,     3,
       1,     1,     1,     1,     1,     5,     5,     5,     2,     1,
       1,     1,     1,     1,     4,     1,     3,     0,     1,     4,
       1,     3,     6,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     4
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
#line 84 "parser.y"
                                       {
	// Main program parser rule, generates the whole AST for the program
	struct AST * funcChildNode = AST_DoublyChildNodes("program", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
	(yyval.ast) = AST_DoublyChildNodes("program",(yyvsp[-2].ast), funcChildNode, (yyvsp[-2].ast), funcChildNode);

	printf("\n\n\n\n\n--------------------Parser End------------------------\n\n\n");

	ast = (yyval.ast);

}
#line 1244 "parser.tab.c"
    break;

  case 3: /* DeclList: VarDecl DeclList  */
#line 101 "parser.y"
                                { (yyval.ast) = AST_DoublyChildNodes("vardec", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
							}
#line 1251 "parser.tab.c"
    break;

  case 4: /* DeclList: Decl  */
#line 103 "parser.y"
                { (yyval.ast) = (yyvsp[0].ast); }
#line 1257 "parser.tab.c"
    break;

  case 5: /* Decl: %empty  */
#line 106 "parser.y"
      { (yyval.ast) = AST_SingleChildNode("empty", "empty", "empty");}
#line 1263 "parser.tab.c"
    break;

  case 6: /* Decl: VarDecl  */
#line 107 "parser.y"
                  {
	// Basic Var Declaration Rule, generates AST for all variable declarations
	(yyval.ast) = (yyvsp[0].ast);
	}
#line 1272 "parser.tab.c"
    break;

  case 7: /* VarDecl: TYPE ID SEMICOLON  */
#line 114 "parser.y"
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
#line 1300 "parser.tab.c"
    break;

  case 8: /* VarDecl: TYPE ID LEFTSQUARE INTEGER RIGHTSQUARE SEMICOLON  */
#line 138 "parser.y"
                                                                                                                   {printf("Found Array declaration"); 
									symTabAccess(); 
									int inSymTab = found((yyvsp[-4].string), currentScope);
									//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
														
									// Check if the variable has been declared
									// If it has, throw an error
									if (inSymTab == 0) 
										addItem((yyvsp[-4].string), "Array", (yyvsp[-5].string),atoi((yyvsp[-2].string)), currentScope);
									else {
										printf("SEMANTIC ERROR: Var %s is already in the symbol table", (yyvsp[-4].string));
										exit(1);
									}
									// If the variable has not been declared 
									showSymTable();

									struct AST* arraySize = AST_SingleChildNode("size", (yyvsp[-2].string), (yyvsp[-2].string)); 
									struct AST* array = AST_DoublyChildNodes((yyvsp[-4].string), "array", arraySize, "array", arraySize);
									(yyval.ast) = AST_DoublyChildNodes("type",(yyvsp[-5].string), array, (yyvsp[-5].string), array);
								}
#line 1325 "parser.tab.c"
    break;

  case 9: /* FunDeclList: %empty  */
#line 160 "parser.y"
             {}
#line 1331 "parser.tab.c"
    break;

  case 10: /* FunDeclList: FunDecl  */
#line 161 "parser.y"
                  {(yyval.ast) = (yyvsp[0].ast);}
#line 1337 "parser.tab.c"
    break;

  case 11: /* FunDeclList: FunDeclListTail  */
#line 162 "parser.y"
                          {(yyval.ast) = (yyvsp[0].ast);}
#line 1343 "parser.tab.c"
    break;

  case 12: /* FunDeclListTail: FunDecl  */
#line 165 "parser.y"
                         {(yyval.ast) = (yyvsp[0].ast);}
#line 1349 "parser.tab.c"
    break;

  case 13: /* FunDeclListTail: FunDecl FunDeclListTail  */
#line 166 "parser.y"
                                  {(yyval.ast) = AST_DoublyChildNodes("FunDecl FunDeclListTail",(yyvsp[-1].ast),(yyvsp[0].ast),(yyvsp[-1].ast), (yyvsp[0].ast));}
#line 1355 "parser.tab.c"
    break;

  case 14: /* FuncHeader: FUNCTION TYPE ID LEFTPAREN ParamDeclList RIGHTPAREN  */
#line 169 "parser.y"
                                                                {
	symTabAccess();
	int inSymTab = found((yyvsp[-3].string), currentScope);

	// Check if the function variable has already been declared
	// If it has, throw an error
	if (inSymTab == 0){
		addFunction((yyvsp[-4].string), (yyvsp[-3].string), (yyvsp[-1].ast)); //id
	}
	else {
		printf("SEMANTIC ERROR: Function %s is already in the symbol table", (yyvsp[-3].string));
		exit(1);
	}

	// If the variable has not been declared 
	showSymTable();
	(yyval.ast) = AST_DoublyChildNodes("function context", (yyvsp[-3].string), (yyvsp[-1].ast), (yyvsp[-3].string), (yyvsp[-1].ast));

	strcpy(tempScopeStore, currentScope);
	strcpy(currentScope, (yyvsp[-3].string));
}
#line 1381 "parser.tab.c"
    break;

  case 15: /* FunDecl: FuncHeader Block  */
#line 192 "parser.y"
                          {
	// Generate AST node as a doubly node
	(yyval.ast) = AST_DoublyChildNodes("function",(yyvsp[-1].ast),(yyvsp[0].ast),(yyvsp[-1].ast), (yyvsp[0].ast));
	strcpy(currentScope, tempScopeStore);
}
#line 1391 "parser.tab.c"
    break;

  case 16: /* ParamDeclList: %empty  */
#line 199 "parser.y"
               {}
#line 1397 "parser.tab.c"
    break;

  case 17: /* ParamDeclList: ParamDeclListTail  */
#line 200 "parser.y"
                            {(yyval.ast) = (yyvsp[0].ast);}
#line 1403 "parser.tab.c"
    break;

  case 18: /* ParamDeclListTail: ParamDecl  */
#line 203 "parser.y"
                             {(yyval.ast) = (yyvsp[0].ast);}
#line 1409 "parser.tab.c"
    break;

  case 19: /* ParamDeclListTail: ParamDecl COMMA ParamDeclListTail  */
#line 204 "parser.y"
                                            {(yyval.ast) = AST_DoublyChildNodes("ParaDecl comma ParaDeclListTail",(yyvsp[-2].ast),(yyvsp[0].ast),(yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1415 "parser.tab.c"
    break;

  case 20: /* ParamDecl: TYPE ID  */
#line 207 "parser.y"
                   {(yyval.ast) = AST_DoublyChildNodes("variable parm",(yyvsp[-1].string),(yyvsp[0].string),(yyvsp[-1].string), (yyvsp[0].string));}
#line 1421 "parser.tab.c"
    break;

  case 21: /* ParamDecl: TYPE ID LEFTSQUARE RIGHTSQUARE  */
#line 208 "parser.y"
                                         {(yyval.ast) = AST_DoublyChildNodes("array parm",(yyvsp[-3].string),(yyvsp[-2].string),(yyvsp[-3].string), (yyvsp[-2].string));}
#line 1427 "parser.tab.c"
    break;

  case 22: /* StmtList: Stmt  */
#line 211 "parser.y"
               {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1435 "parser.tab.c"
    break;

  case 23: /* StmtList: Stmt StmtList  */
#line 214 "parser.y"
                        {
		printf("\n RECOGNIZED RULE: StmtList statement\n");
		// Generate a list of all statement declarations below vardecl
		(yyval.ast) = AST_DoublyChildNodes("statements", (yyvsp[-1].ast), (yyvsp[0].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
		}
#line 1445 "parser.tab.c"
    break;

  case 24: /* Stmt: SEMICOLON  */
#line 221 "parser.y"
                        {}
#line 1451 "parser.tab.c"
    break;

  case 25: /* Stmt: Expr SEMICOLON  */
#line 222 "parser.y"
                                {
		// Simplest expr statement in grammar
		(yyval.ast) = (yyvsp[-1].ast);
		}
#line 1460 "parser.tab.c"
    break;

  case 26: /* Stmt: WRITE Primary SEMICOLON  */
#line 226 "parser.y"
                                        { printf("\n RECOGNIZED RULE: WRITE statement\n");
					// Generate write declarations as a statement in the parser
					(yyval.ast) = AST_SingleChildNode("write", (yyvsp[-1].ast), (yyvsp[-1].ast));
					printf("Write AST generated!\n");
				}
#line 1470 "parser.tab.c"
    break;

  case 27: /* Stmt: WRITELN SEMICOLON  */
#line 231 "parser.y"
                            {
		printf("\n RECOGNIZED RULE: WRITEIN statement\n");
		(yyval.ast) = AST_SingleChildNode("writeln", "\n", 0);
	}
#line 1479 "parser.tab.c"
    break;

  case 28: /* Stmt: RETURN Expr SEMICOLON  */
#line 235 "parser.y"
                                { (yyval.ast) = AST_SingleChildNode("return", (yyvsp[-1].ast),(yyvsp[-1].ast)); }
#line 1485 "parser.tab.c"
    break;

  case 29: /* Stmt: READ ID SEMICOLON  */
#line 236 "parser.y"
                            {(yyval.ast) = AST_SingleChildNode("read", (yyvsp[-1].string), 0);}
#line 1491 "parser.tab.c"
    break;

  case 30: /* Stmt: Block  */
#line 237 "parser.y"
                {(yyval.ast) = (yyvsp[0].ast);}
#line 1497 "parser.tab.c"
    break;

  case 31: /* Stmt: Loop  */
#line 238 "parser.y"
               {(yyval.ast)=(yyvsp[0].ast);}
#line 1503 "parser.tab.c"
    break;

  case 32: /* Stmt: If  */
#line 239 "parser.y"
             {(yyval.ast)=(yyvsp[0].ast);}
#line 1509 "parser.tab.c"
    break;

  case 33: /* Stmt: Elif  */
#line 240 "parser.y"
               {(yyval.ast)=(yyvsp[0].ast);}
#line 1515 "parser.tab.c"
    break;

  case 34: /* Stmt: Else  */
#line 241 "parser.y"
               {(yyval.ast)=(yyvsp[0].ast);}
#line 1521 "parser.tab.c"
    break;

  case 35: /* Loop: WHILE LEFTPAREN Expr RIGHTPAREN Block  */
#line 245 "parser.y"
                                            { }
#line 1527 "parser.tab.c"
    break;

  case 36: /* If: IF LEFTPAREN Expr RIGHTPAREN Block  */
#line 248 "parser.y"
                                       {}
#line 1533 "parser.tab.c"
    break;

  case 37: /* Elif: ELIF LEFTPAREN Expr RIGHTPAREN Block  */
#line 251 "parser.y"
                                            {}
#line 1539 "parser.tab.c"
    break;

  case 38: /* Else: ELSE Block  */
#line 254 "parser.y"
                  {}
#line 1545 "parser.tab.c"
    break;

  case 39: /* Primary: INTEGER  */
#line 258 "parser.y"
                                {(yyval.ast) = AST_SingleChildNode("int", (yyvsp[0].string), (yyvsp[0].string)); }
#line 1551 "parser.tab.c"
    break;

  case 40: /* Primary: NUMBER  */
#line 259 "parser.y"
                        {(yyval.ast) = AST_SingleChildNode("float", (yyvsp[0].number), (yyvsp[0].number)); }
#line 1557 "parser.tab.c"
    break;

  case 41: /* Primary: ID  */
#line 260 "parser.y"
              {(yyval.ast) = AST_SingleChildNode((yyvsp[0].string), (yyvsp[0].string), (yyvsp[0].string));}
#line 1563 "parser.tab.c"
    break;

  case 42: /* Primary: STRING  */
#line 261 "parser.y"
                  {(yyval.ast) = AST_SingleChildNode( "string", (yyvsp[0].string), (yyvsp[0].string));}
#line 1569 "parser.tab.c"
    break;

  case 43: /* Primary: FLOAT  */
#line 262 "parser.y"
                {(yyval.ast) = AST_SingleChildNode( "float", (yyvsp[0].string), (yyvsp[0].string));}
#line 1575 "parser.tab.c"
    break;

  case 44: /* Primary: ID LEFTSQUARE NUMBER RIGHTSQUARE  */
#line 263 "parser.y"
                                           {
		(yyval.ast) = AST_DoublyChildNodes((yyvsp[-3].string), "array", (yyvsp[-1].number), "array", (yyvsp[-1].number));
	}
#line 1583 "parser.tab.c"
    break;

  case 45: /* ExprListTail: Primary  */
#line 272 "parser.y"
                        { (yyval.ast) = AST_SingleChildNode("exprlist end", (yyvsp[0].ast), (yyvsp[0].ast)); }
#line 1589 "parser.tab.c"
    break;

  case 46: /* ExprListTail: Primary COMMA ExprListTail  */
#line 273 "parser.y"
                                        {
			(yyval.ast) = AST_DoublyChildNodes("exprlist exprtail", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
		}
#line 1597 "parser.tab.c"
    break;

  case 47: /* ExprList: %empty  */
#line 278 "parser.y"
          {}
#line 1603 "parser.tab.c"
    break;

  case 48: /* ExprList: ExprListTail  */
#line 279 "parser.y"
                       {
		(yyval.ast) = (yyvsp[0].ast);
	}
#line 1611 "parser.tab.c"
    break;

  case 49: /* Block: LEFTBRACKET DeclList StmtList RIGHTBRACKET  */
#line 286 "parser.y"
                                                   { printf("\n RECOGNIZED RULE: Block statement\n");
		(yyval.ast) = AST_DoublyChildNodes("block",(yyvsp[-2].ast),(yyvsp[-1].ast), (yyvsp[-2].ast), (yyvsp[-1].ast));
		}
#line 1619 "parser.tab.c"
    break;

  case 50: /* Expr: Primary  */
#line 291 "parser.y"
                { printf("\n RECOGNIZED RULE: Simplest expression\n");
				(yyval.ast) = (yyvsp[0].ast);
				printf("%s\n", (yyvsp[0].ast));
				strcpy((yyval.ast)->nodeType, CheckPrimaryType((yyvsp[0].ast), currentScope));
				}
#line 1629 "parser.tab.c"
    break;

  case 51: /* Expr: ID EQ Expr  */
#line 296 "parser.y"
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
#line 1667 "parser.tab.c"
    break;

  case 52: /* Expr: ID LEFTSQUARE NUMBER RIGHTSQUARE EQ Expr  */
#line 329 "parser.y"
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
					struct AST* arrayElement = AST_DoublyChildNodes("element assignment", (yyvsp[-3].number), (yyvsp[0].ast), (yyvsp[-3].number), (yyvsp[0].ast)); 

					(yyval.ast) = AST_DoublyChildNodes("=",(yyvsp[-5].string),arrayElement, (yyvsp[-5].string), arrayElement);
					// Generate IRcode
					// printf("Generate IR Code\n");
					// emitConstantIntAssignment($1, $3);

					// Generate MIPS code
					// printf("Generate MIPS\n");
					// emitMIPSConstantIntAssignment($1, $3);

					}
#line 1707 "parser.tab.c"
    break;

  case 53: /* Expr: Expr PLUS Expr  */
#line 365 "parser.y"
                         { printf("\n RECOGNIZED RULE: PLUS statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("+",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
					printf("EXPR PLUS EXPR: %s \n------------------------------------------------------------------\n", (yyvsp[0].ast) ->nodeType);
				}
#line 1721 "parser.tab.c"
    break;

  case 54: /* Expr: Expr MINUS Expr  */
#line 374 "parser.y"
                          { printf("\n RECOGNIZED RULE: MINUS statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("-",(yyvsp[-2].ast),(yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				}
#line 1734 "parser.tab.c"
    break;

  case 55: /* Expr: Expr MULTIPLY Expr  */
#line 382 "parser.y"
                             { printf("\n RECOGNIZED RULE: MULTIPLY statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("*", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
				}
#line 1747 "parser.tab.c"
    break;

  case 56: /* Expr: Expr DIVIDE Expr  */
#line 390 "parser.y"
                           { printf("\n RECOGNIZED RULE: DIVIDE statement\n");
					// Semantic checks
					
					// Check if both exprs exist
					
					// Generate AST Nodes (doubly linked)
					(yyval.ast) = AST_DoublyChildNodes("/", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));

					// If the RHS is an int, check for integer division error
					if (strncmp((yyvsp[0].ast), "int", 3) == 0) {
						int numerator = 1;
						int denominator = 1;

						// Assign expression values if it's not just a sequence of vars
						if (containsNonVars((yyvsp[-2].ast))) {
							numerator = evaluateIntExpr((yyvsp[-2].ast));
						}
						if (containsNonVars((yyvsp[0].ast))) {
							denominator = evaluateIntExpr((yyvsp[0].ast));
						}
						checkIntDivisionError(numerator, denominator);
					} else if (strncmp((yyvsp[0].ast), "float", 5) == 0) {
						// float numerator = evaluateFloatExpr($1);
						float numerator = 1.0;
						float denominator = 1.0;

						// Assign expression values if it's not just a sequence of vars
						if (containsNonVars((yyvsp[-2].ast))) {
							numerator = evaluateFloatExpr((yyvsp[-2].ast));
						}
						if (containsNonVars((yyvsp[0].ast))) {
							denominator = evaluateFloatExpr((yyvsp[0].ast));
						}
						checkFloatDivisionError(numerator, denominator);
					}

				}
#line 1789 "parser.tab.c"
    break;

  case 57: /* Expr: Expr EXPONENT Expr  */
#line 427 "parser.y"
                             { printf("\n RECOGNIZED RULE: BinOp statement\n");
				// Semantic checks
				
				// Check if both exprs exist
				
				// Generate AST Nodes (doubly linked)
				(yyval.ast) = AST_DoublyChildNodes("EXP ", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
			}
#line 1802 "parser.tab.c"
    break;

  case 58: /* Expr: Expr COMPARSIONOPERATOR Expr  */
#line 435 "parser.y"
                                       {(yyval.ast) = AST_DoublyChildNodes("Comparsion", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1808 "parser.tab.c"
    break;

  case 59: /* Expr: Expr LOGICALOPERATOR Expr  */
#line 436 "parser.y"
                                    {(yyval.ast) = AST_DoublyChildNodes("Logical", (yyvsp[-2].ast), (yyvsp[0].ast), (yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1814 "parser.tab.c"
    break;

  case 60: /* Expr: LEFTPAREN Expr RIGHTPAREN  */
#line 437 "parser.y"
                                    {(yyval.ast) = (yyvsp[-1].ast);}
#line 1820 "parser.tab.c"
    break;

  case 61: /* Expr: FunctionCall  */
#line 438 "parser.y"
                       {(yyval.ast) = (yyvsp[0].ast);}
#line 1826 "parser.tab.c"
    break;

  case 62: /* Expr: TRUEZ  */
#line 439 "parser.y"
                {(yyval.ast) = AST_SingleChildNode("TRUE", (yyvsp[0].string), (yyvsp[0].string));}
#line 1832 "parser.tab.c"
    break;

  case 63: /* Expr: FALSEZ  */
#line 440 "parser.y"
                 {(yyval.ast) = AST_SingleChildNode("FALSE",(yyvsp[0].string), (yyvsp[0].string));}
#line 1838 "parser.tab.c"
    break;

  case 64: /* FunctionCall: ID LEFTPAREN ExprList RIGHTPAREN  */
#line 444 "parser.y"
                                               {
	struct AST* funcCallParamList = AST_SingleChildNode("function call param list", (yyvsp[-1].ast), (yyvsp[-1].ast));
	(yyval.ast) = AST_DoublyChildNodes("function call", (yyvsp[-3].string), funcCallParamList, (yyvsp[-3].string), funcCallParamList);

	int funcParams = getNumFuncParams((yyvsp[-3].string));
	// printf("Num Func Params: %d\n", funcParams);
	// printf("Call Params\n");
	int callParams = getNumExprs(funcCallParamList);
	// printf("End Call Params\n");
	// printf("Num Call Params: %d\n", callParams);

	if (funcParams != callParams) {
		printf("\nSEMANTIC ERROR: The total number of call parameters for \"%s\" (%d) does not match function declaration (%d).\n", (yyvsp[-3].string), callParams, funcParams);
		exit(1);
	}

}
#line 1860 "parser.tab.c"
    break;


#line 1864 "parser.tab.c"

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

#line 463 "parser.y"




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
