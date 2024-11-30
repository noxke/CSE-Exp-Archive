/* A Bison parser, made by GNU Bison 3.8.2.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 4 "parser.y"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "def.h"

#include <bits/stdc++.h>
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
char myerror[255];
extern NProgram *p;
extern int allerror;
void myyyerror();

extern "C"{
void yyerror(const char* fmt, ...);
extern int yylex(void);
}

#line 92 "parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_RELOP = 5,                      /* RELOP  */
  YYSYMBOL_TYPE = 6,                       /* TYPE  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_CHAR = 8,                       /* CHAR  */
  YYSYMBOL_STRUCT = 9,                     /* STRUCT  */
  YYSYMBOL_LP = 10,                        /* LP  */
  YYSYMBOL_RP = 11,                        /* RP  */
  YYSYMBOL_LC = 12,                        /* LC  */
  YYSYMBOL_RC = 13,                        /* RC  */
  YYSYMBOL_LB = 14,                        /* LB  */
  YYSYMBOL_RB = 15,                        /* RB  */
  YYSYMBOL_SEMI = 16,                      /* SEMI  */
  YYSYMBOL_COMMA = 17,                     /* COMMA  */
  YYSYMBOL_DOT = 18,                       /* DOT  */
  YYSYMBOL_PLUS = 19,                      /* PLUS  */
  YYSYMBOL_MINUS = 20,                     /* MINUS  */
  YYSYMBOL_STAR = 21,                      /* STAR  */
  YYSYMBOL_DIV = 22,                       /* DIV  */
  YYSYMBOL_MOD = 23,                       /* MOD  */
  YYSYMBOL_ASSIGNOP = 24,                  /* ASSIGNOP  */
  YYSYMBOL_AND = 25,                       /* AND  */
  YYSYMBOL_OR = 26,                        /* OR  */
  YYSYMBOL_NOT = 27,                       /* NOT  */
  YYSYMBOL_IF = 28,                        /* IF  */
  YYSYMBOL_BREAK = 29,                     /* BREAK  */
  YYSYMBOL_ELSE = 30,                      /* ELSE  */
  YYSYMBOL_WHILE = 31,                     /* WHILE  */
  YYSYMBOL_RETURN = 32,                    /* RETURN  */
  YYSYMBOL_PLUSASS = 33,                   /* PLUSASS  */
  YYSYMBOL_MINUSASS = 34,                  /* MINUSASS  */
  YYSYMBOL_STARASS = 35,                   /* STARASS  */
  YYSYMBOL_DIVASS = 36,                    /* DIVASS  */
  YYSYMBOL_MODASS = 37,                    /* MODASS  */
  YYSYMBOL_PLUSPLUS = 38,                  /* PLUSPLUS  */
  YYSYMBOL_MINUSMINUS = 39,                /* MINUSMINUS  */
  YYSYMBOL_UMINUS = 40,                    /* UMINUS  */
  YYSYMBOL_UPLUSPLUS = 41,                 /* UPLUSPLUS  */
  YYSYMBOL_UMINUSMINUS = 42,               /* UMINUSMINUS  */
  YYSYMBOL_LOWER_THEN_ELSE = 43,           /* LOWER_THEN_ELSE  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_ExtDefList = 46,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 47,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 48,                /* ExtDecList  */
  YYSYMBOL_Specifier = 49,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 50,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 51,                    /* OptTag  */
  YYSYMBOL_Tag = 52,                       /* Tag  */
  YYSYMBOL_VarDec = 53,                    /* VarDec  */
  YYSYMBOL_FunDec = 54,                    /* FunDec  */
  YYSYMBOL_VarList = 55,                   /* VarList  */
  YYSYMBOL_ParamDec = 56,                  /* ParamDec  */
  YYSYMBOL_CompSt = 57,                    /* CompSt  */
  YYSYMBOL_StmtList = 58,                  /* StmtList  */
  YYSYMBOL_Stmt = 59,                      /* Stmt  */
  YYSYMBOL_DefList = 60,                   /* DefList  */
  YYSYMBOL_Def = 61,                       /* Def  */
  YYSYMBOL_DecList = 62,                   /* DecList  */
  YYSYMBOL_Dec = 63,                       /* Dec  */
  YYSYMBOL_Exp = 64,                       /* Exp  */
  YYSYMBOL_Args = 65                       /* Args  */
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   429

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  150

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   106,   106,   108,   109,   110,   112,   113,   114,   116,
     117,   121,   122,   125,   126,   129,   130,   133,   137,   138,
     140,   141,   143,   144,   146,   150,   151,   153,   154,   156,
     157,   158,   159,   160,   161,   162,   164,   165,   166,   170,
     171,   173,   176,   177,   178,   179,   181,   182,   186,   188,
     189,   190,   191,   193,   194,   195,   196,   198,   199,   200,
     201,   202,   203,   204,   206,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   221,   222
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "ID", "RELOP",
  "TYPE", "FLOAT", "CHAR", "STRUCT", "LP", "RP", "LC", "RC", "LB", "RB",
  "SEMI", "COMMA", "DOT", "PLUS", "MINUS", "STAR", "DIV", "MOD",
  "ASSIGNOP", "AND", "OR", "NOT", "IF", "BREAK", "ELSE", "WHILE", "RETURN",
  "PLUSASS", "MINUSASS", "STARASS", "DIVASS", "MODASS", "PLUSPLUS",
  "MINUSMINUS", "UMINUS", "UPLUSPLUS", "UMINUSMINUS", "LOWER_THEN_ELSE",
  "$accept", "program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-120)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-28)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      50,    -3,  -120,     8,    28,  -120,    50,     7,  -120,    50,
      17,    41,  -120,  -120,  -120,    48,  -120,    61,    62,     5,
    -120,   121,    51,  -120,    85,    60,    76,   121,  -120,     1,
      77,   121,  -120,    60,    91,    86,   100,  -120,  -120,  -120,
     138,     1,    -4,    98,   111,  -120,  -120,   102,  -120,   121,
    -120,    76,  -120,   119,  -120,  -120,   199,   199,   199,   126,
     128,   137,   199,   199,   199,  -120,   139,   138,   225,  -120,
     199,  -120,     1,  -120,   185,  -120,   251,    16,    16,   199,
    -120,   199,    47,    16,    16,  -120,  -120,   199,   199,  -120,
     150,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,  -120,  -120,   323,  -120,  -120,   274,   157,
    -120,    73,    99,   145,  -120,   356,   300,  -120,   390,   390,
      16,    16,    16,   346,   378,   368,   346,   346,   346,   346,
     199,  -120,   158,   152,   162,   152,  -120,  -120,  -120,   147,
     144,   159,  -120,  -120,   152,     5,  -120,   177,   166,  -120
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    11,    16,     0,     2,     0,     0,    12,     0,
      17,     0,    14,     1,     4,    18,     7,     0,     9,     0,
       5,    39,     0,     6,     0,     0,     0,    39,     8,     0,
       0,    39,    21,     0,     0,    22,     0,    18,    10,    26,
       0,    45,    46,     0,    42,    13,    40,    24,    20,     0,
      19,    76,    73,    72,    74,    75,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,     0,     0,     0,    44,
       0,    41,     0,    23,     0,    76,     0,    66,    67,     0,
      35,     0,     0,    53,    54,    25,    28,     0,     0,    29,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    55,    56,    47,    43,    69,    78,     0,
      65,     0,     0,     0,    31,    59,     0,    71,    60,    61,
      62,    63,    64,    48,    57,    58,    49,    50,    51,    52,
       0,    68,     0,     0,     0,     0,    36,    70,    77,     0,
      32,     0,    34,    37,     0,     0,    33,     0,     0,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -120,  -120,   134,  -120,   160,     0,  -120,  -120,  -120,   124,
    -120,   148,  -120,   -19,   120,  -119,    74,  -120,   -37,  -120,
     -55,    64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    17,     7,     8,    11,    12,    42,
      19,    34,    35,    65,    66,    67,    30,    31,    43,    44,
      68,   109
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    76,    77,    78,    69,    37,    26,    82,    83,    84,
      24,    15,    10,     9,   140,   105,   142,    27,    41,   108,
      70,    29,    33,    16,   111,   146,   112,    29,    13,   -15,
      88,    29,   115,   116,    90,   106,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   113,    33,
      -3,     1,    87,    21,   103,   104,     2,     2,    22,     3,
       3,    88,    32,   114,    37,    90,    91,    92,    93,    94,
      95,    96,    97,    98,   132,   108,    24,    23,    87,    25,
      99,   100,   101,   102,   133,   103,   104,    88,    36,    39,
      45,    90,    91,    92,    93,    94,    95,    96,    97,    98,
     134,    40,    48,    49,    87,    46,    99,   100,   101,   102,
     135,   103,   104,    88,    71,    50,    24,    90,    91,    92,
      93,    94,    95,    96,    97,    98,   147,     2,    72,    74,
       3,    18,    99,   100,   101,   102,    79,   103,   104,    51,
      14,    52,    53,    20,    80,    54,    55,    81,    56,    18,
      27,   -27,    85,    51,   117,    52,    53,    47,    57,    54,
      55,   136,    56,   143,    27,    58,    59,    60,   131,    61,
      62,   139,    57,   141,   144,   145,    63,    64,   148,    58,
      59,    60,   149,    61,    62,    38,    75,    86,    52,    53,
      63,    64,    54,    55,   138,    56,   107,    73,     0,     0,
      75,     0,    52,    53,     0,    57,    54,    55,     0,    56,
       0,     0,    58,     0,     0,     0,     0,     0,     0,    57,
       0,     0,     0,    63,    64,     0,    58,     0,     0,     0,
      87,     0,     0,     0,     0,     0,     0,    63,    64,    88,
       0,    89,     0,    90,    91,    92,    93,    94,    95,    96,
      97,    98,     0,     0,     0,     0,    87,     0,    99,   100,
     101,   102,   110,   103,   104,    88,     0,     0,     0,    90,
      91,    92,    93,    94,    95,    96,    97,    98,     0,    87,
       0,     0,     0,     0,    99,   100,   101,   102,    88,   103,
     104,   130,    90,    91,    92,    93,    94,    95,    96,    97,
      98,     0,     0,     0,     0,    87,     0,    99,   100,   101,
     102,     0,   103,   104,    88,   137,     0,     0,    90,    91,
      92,    93,    94,    95,    96,    97,    98,     0,    87,     0,
       0,     0,     0,    99,   100,   101,   102,    88,   103,   104,
       0,    90,    91,    92,    93,    94,    95,    96,    97,    98,
       0,    87,     0,     0,     0,     0,    99,   100,   101,   102,
      88,   103,   104,     0,    90,    91,    92,    93,    94,    95,
      88,    97,    98,    87,    90,    91,    92,    93,    94,    95,
       0,     0,    88,    87,   103,   104,    90,    91,    92,    93,
      94,    95,    88,    97,   103,   104,    90,    91,    92,    93,
      94,    95,     0,     0,    88,     0,   103,   104,    90,     0,
       0,    93,    94,    95,     0,     0,   103,   104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   103,   104
};

static const yytype_int16 yycheck[] =
{
      19,    56,    57,    58,    41,     4,     1,    62,    63,    64,
      14,     4,     4,    16,   133,    70,   135,    12,    17,    74,
      24,    21,    22,    16,    79,   144,    81,    27,     0,    12,
      14,    31,    87,    88,    18,    72,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,     1,    49,
       0,     1,     5,    12,    38,    39,     6,     6,    10,     9,
       9,    14,    11,    16,     4,    18,    19,    20,    21,    22,
      23,    24,    25,    26,     1,   130,    14,    16,     5,    17,
      33,    34,    35,    36,    11,    38,    39,    14,     3,    13,
      13,    18,    19,    20,    21,    22,    23,    24,    25,    26,
       1,    27,    11,    17,     5,    31,    33,    34,    35,    36,
      11,    38,    39,    14,    16,    15,    14,    18,    19,    20,
      21,    22,    23,    24,    25,    26,   145,     6,    17,    10,
       9,     7,    33,    34,    35,    36,    10,    38,    39,     1,
       6,     3,     4,     9,    16,     7,     8,    10,    10,    25,
      12,    13,    13,     1,     4,     3,     4,    33,    20,     7,
       8,    16,    10,    16,    12,    27,    28,    29,    11,    31,
      32,    13,    20,    11,    30,    16,    38,    39,     1,    27,
      28,    29,    16,    31,    32,    25,     1,    67,     3,     4,
      38,    39,     7,     8,   130,    10,    11,    49,    -1,    -1,
       1,    -1,     3,     4,    -1,    20,     7,     8,    -1,    10,
      -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    38,    39,    -1,    27,    -1,    -1,    -1,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    14,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    -1,     5,    -1,    33,    34,
      35,    36,    11,    38,    39,    14,    -1,    -1,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,     5,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    14,    38,
      39,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    -1,     5,    -1,    33,    34,    35,
      36,    -1,    38,    39,    14,    15,    -1,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,     5,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    14,    38,    39,
      -1,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,     5,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      14,    38,    39,    -1,    18,    19,    20,    21,    22,    23,
      14,    25,    26,     5,    18,    19,    20,    21,    22,    23,
      -1,    -1,    14,     5,    38,    39,    18,    19,    20,    21,
      22,    23,    14,    25,    38,    39,    18,    19,    20,    21,
      22,    23,    -1,    -1,    14,    -1,    38,    39,    18,    -1,
      -1,    21,    22,    23,    -1,    -1,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     6,     9,    45,    46,    47,    49,    50,    16,
       4,    51,    52,     0,    46,     4,    16,    48,    53,    54,
      46,    12,    10,    16,    14,    17,     1,    12,    57,    49,
      60,    61,    11,    49,    55,    56,     3,     4,    48,    13,
      60,    17,    53,    62,    63,    13,    60,    53,    11,    17,
      15,     1,     3,     4,     7,     8,    10,    20,    27,    28,
      29,    31,    32,    38,    39,    57,    58,    59,    64,    62,
      24,    16,    17,    55,    10,     1,    64,    64,    64,    10,
      16,    10,    64,    64,    64,    13,    58,     5,    14,    16,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    33,
      34,    35,    36,    38,    39,    64,    62,    11,    64,    65,
      11,    64,    64,     1,    16,    64,    64,     4,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      17,    11,     1,    11,     1,    11,    16,    15,    65,    13,
      59,    11,    59,    16,    30,    16,    59,    57,     1,    16
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    46,    47,    47,    47,    48,
      48,    49,    49,    50,    50,    51,    51,    52,    53,    53,
      54,    54,    55,    55,    56,    57,    57,    58,    58,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    60,
      60,    61,    62,    62,    62,    62,    63,    63,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    65,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     3,     2,     3,     1,
       3,     1,     1,     5,     2,     1,     0,     1,     1,     4,
       4,     3,     1,     3,     2,     4,     2,     0,     2,     2,
       1,     3,     5,     7,     5,     2,     4,     6,     9,     0,
       2,     3,     1,     3,     2,     1,     1,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     4,     3,
       4,     3,     1,     1,     1,     1,     1,     3,     1
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: ExtDefList  */
#line 106 "parser.y"
                    {p=new NProgram((yyvsp[0].nExtDefList));if((yyvsp[0].nExtDefList)) p->line=(yyvsp[0].nExtDefList)->line;}
#line 1409 "parser.cpp"
    break;

  case 3: /* ExtDefList: %empty  */
#line 108 "parser.y"
            {  (yyval.nExtDefList)=nullptr;}
#line 1415 "parser.cpp"
    break;

  case 4: /* ExtDefList: ExtDef ExtDefList  */
#line 109 "parser.y"
                            {(yyval.nExtDefList)=new NExtDefList(*(yyvsp[-1].nExtDef),(yyvsp[0].nExtDefList)); (yyval.nExtDefList)->line=(yyvsp[-1].nExtDef)->line;}
#line 1421 "parser.cpp"
    break;

  case 5: /* ExtDefList: error SEMI ExtDefList  */
#line 110 "parser.y"
                                {allerror=1;sprintf(myerror," Error : wrong ");(yyval.nExtDefList)=(yyvsp[0].nExtDefList);myyyerror();}
#line 1427 "parser.cpp"
    break;

  case 6: /* ExtDef: Specifier ExtDecList SEMI  */
#line 112 "parser.y"
                                  {(yyval.nExtDef)=new NExtDefVarDec(*(yyvsp[-2].nSpecifier),(yyvsp[-1].nExtDecList));(yyval.nExtDef)->line=(yyvsp[-2].nSpecifier)->line;}
#line 1433 "parser.cpp"
    break;

  case 7: /* ExtDef: Specifier SEMI  */
#line 113 "parser.y"
                         {(yyval.nExtDef)=new NExtDefVarDec(*(yyvsp[-1].nSpecifier),nullptr);(yyval.nExtDef)->line=(yyvsp[-1].nSpecifier)->line;}
#line 1439 "parser.cpp"
    break;

  case 8: /* ExtDef: Specifier FunDec CompSt  */
#line 114 "parser.y"
                                  {(yyval.nExtDef)=new NExtDefFunDec(*(yyvsp[-2].nSpecifier),(yyvsp[-1].nFunDec),(yyvsp[0].nCompSt));(yyval.nExtDef)->line=(yyvsp[-2].nSpecifier)->line;}
#line 1445 "parser.cpp"
    break;

  case 9: /* ExtDecList: VarDec  */
#line 116 "parser.y"
                   {(yyval.nExtDecList)=new NExtDecList(*(yyvsp[0].nVarDec),nullptr);(yyval.nExtDecList)->line=(yyvsp[0].nVarDec)->line;}
#line 1451 "parser.cpp"
    break;

  case 10: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 117 "parser.y"
                                  {(yyval.nExtDecList)=new NExtDecList(*(yyvsp[-2].nVarDec),(yyvsp[0].nExtDecList));(yyval.nExtDecList)->line=(yyvsp[-2].nVarDec)->line;}
#line 1457 "parser.cpp"
    break;

  case 11: /* Specifier: TYPE  */
#line 121 "parser.y"
                {(yyval.nSpecifier)=new NSpecifier(*(new std::string((yyvsp[0].type_id))));(yyval.nSpecifier)->line=yylineno;}
#line 1463 "parser.cpp"
    break;

  case 12: /* Specifier: StructSpecifier  */
#line 122 "parser.y"
                          {(yyval.nSpecifier)=(yyvsp[0].nStructSpecifier);/*$$->line=yylineno;*/}
#line 1469 "parser.cpp"
    break;

  case 13: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 125 "parser.y"
                                             {(yyval.nStructSpecifier)=new NStructSpecifier((yyvsp[-3].nIdentifier),(yyvsp[-1].nDefList));(yyval.nStructSpecifier)->line=(yyvsp[-4].line);}
#line 1475 "parser.cpp"
    break;

  case 14: /* StructSpecifier: STRUCT Tag  */
#line 126 "parser.y"
                     {(yyval.nStructSpecifier)=new NStructSpecifier((yyvsp[0].nIdentifier));(yyval.nStructSpecifier)->line=(yyvsp[-1].line);}
#line 1481 "parser.cpp"
    break;

  case 15: /* OptTag: ID  */
#line 129 "parser.y"
           {(yyval.nIdentifier)=new NIdentifier(*(new std::string((yyvsp[0].type_id))));(yyval.nIdentifier)->line=yylineno;}
#line 1487 "parser.cpp"
    break;

  case 16: /* OptTag: %empty  */
#line 130 "parser.y"
          {(yyval.nIdentifier)=nullptr;}
#line 1493 "parser.cpp"
    break;

  case 17: /* Tag: ID  */
#line 133 "parser.y"
        {(yyval.nIdentifier)=new NIdentifier(*(new std::string((yyvsp[0].type_id))));(yyval.nIdentifier)->line=yylineno;}
#line 1499 "parser.cpp"
    break;

  case 18: /* VarDec: ID  */
#line 137 "parser.y"
            {NIdentifier *nIdentifier = new NIdentifier(*(new std::string((yyvsp[0].type_id))));(yyval.nVarDec)=new NVarDec(*nIdentifier);(yyval.nVarDec)->line=yylineno;}
#line 1505 "parser.cpp"
    break;

  case 19: /* VarDec: VarDec LB INT RB  */
#line 138 "parser.y"
                           {(yyval.nVarDec)=(yyvsp[-3].nVarDec);(yyval.nVarDec)->v.push_back((yyvsp[-1].type_int));}
#line 1511 "parser.cpp"
    break;

  case 20: /* FunDec: ID LP VarList RP  */
#line 140 "parser.y"
                         {(yyval.nFunDec)=new NFunDec(*(new NIdentifier(*(new std::string((yyvsp[-3].type_id))))),(yyvsp[-1].nVarList));(yyval.nFunDec)->line=yylineno;}
#line 1517 "parser.cpp"
    break;

  case 21: /* FunDec: ID LP RP  */
#line 141 "parser.y"
                   {(yyval.nFunDec)=new NFunDec(*(new NIdentifier(*(new std::string((yyvsp[-2].type_id))))),nullptr);(yyval.nFunDec)->line=yylineno;}
#line 1523 "parser.cpp"
    break;

  case 22: /* VarList: ParamDec  */
#line 143 "parser.y"
                  {(yyval.nVarList)=new NVarList(*(yyvsp[0].nParamDec),nullptr);(yyval.nVarList)->line=(yyvsp[0].nParamDec)->line;}
#line 1529 "parser.cpp"
    break;

  case 23: /* VarList: ParamDec COMMA VarList  */
#line 144 "parser.y"
                                 {(yyval.nVarList)=new NVarList(*(yyvsp[-2].nParamDec),(yyvsp[0].nVarList));(yyval.nVarList)->line=(yyvsp[-2].nParamDec)->line;}
#line 1535 "parser.cpp"
    break;

  case 24: /* ParamDec: Specifier VarDec  */
#line 146 "parser.y"
                           {(yyval.nParamDec)=new NParamDec(*(yyvsp[-1].nSpecifier),*(yyvsp[0].nVarDec));(yyval.nParamDec)->line=(yyvsp[-1].nSpecifier)->line;}
#line 1541 "parser.cpp"
    break;

  case 25: /* CompSt: LC DefList StmtList RC  */
#line 150 "parser.y"
                                 {(yyval.nCompSt)=new NCompSt((yyvsp[-2].nDefList),(yyvsp[-1].nStmtList));(yyval.nCompSt)->line=(yyvsp[-3].line);}
#line 1547 "parser.cpp"
    break;

  case 26: /* CompSt: error RC  */
#line 151 "parser.y"
                   {allerror=1;sprintf(myerror," big error in Conmpst");(yyval.nCompSt)=NULL;}
#line 1553 "parser.cpp"
    break;

  case 27: /* StmtList: %empty  */
#line 153 "parser.y"
          {(yyval.nStmtList)=nullptr;}
#line 1559 "parser.cpp"
    break;

  case 28: /* StmtList: Stmt StmtList  */
#line 154 "parser.y"
                         {(yyval.nStmtList)=new NStmtList(*(yyvsp[-1].nStmt),(yyvsp[0].nStmtList));(yyval.nStmtList)->line=(yyvsp[-1].nStmt)->line;}
#line 1565 "parser.cpp"
    break;

  case 29: /* Stmt: Exp SEMI  */
#line 156 "parser.y"
                   {(yyval.nStmt)=new NExpStmt(*(yyvsp[-1].nExpression));(yyval.nStmt)->line=(yyvsp[-1].nExpression)->line;}
#line 1571 "parser.cpp"
    break;

  case 30: /* Stmt: CompSt  */
#line 157 "parser.y"
                 {(yyval.nStmt)=new NCompStStmt(*(yyvsp[0].nCompSt)); (yyval.nStmt)->line=(yyvsp[0].nCompSt)->line;}
#line 1577 "parser.cpp"
    break;

  case 31: /* Stmt: RETURN Exp SEMI  */
#line 158 "parser.y"
                          {(yyval.nStmt)=new NRetutnStmt(*(yyvsp[-1].nExpression)); (yyval.nStmt)->line=yylineno;}
#line 1583 "parser.cpp"
    break;

  case 32: /* Stmt: IF LP Exp RP Stmt  */
#line 159 "parser.y"
                                                    {(yyval.nStmt)=new NIfStmt(*(yyvsp[-2].nExpression),*(yyvsp[0].nStmt));(yyval.nStmt)->line=(yyvsp[-4].line);}
#line 1589 "parser.cpp"
    break;

  case 33: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 160 "parser.y"
                                      {(yyval.nStmt)=new NIfElseStmt(*(yyvsp[-4].nExpression),*(yyvsp[-2].nStmt),*(yyvsp[0].nStmt));(yyval.nStmt)->line=(yyvsp[-6].line);}
#line 1595 "parser.cpp"
    break;

  case 34: /* Stmt: WHILE LP Exp RP Stmt  */
#line 161 "parser.y"
                               {(yyval.nStmt)= new NWhileStmt(*(yyvsp[-2].nExpression),*(yyvsp[0].nStmt));(yyval.nStmt)->line=(yyvsp[-4].line);}
#line 1601 "parser.cpp"
    break;

  case 35: /* Stmt: BREAK SEMI  */
#line 162 "parser.y"
                     {(yyval.nStmt)= new NBreakStmt();(yyval.nStmt)->line=yylineno;}
#line 1607 "parser.cpp"
    break;

  case 36: /* Stmt: RETURN Exp error SEMI  */
#line 164 "parser.y"
                                {allerror=1;}
#line 1613 "parser.cpp"
    break;

  case 37: /* Stmt: IF LP Exp error RC SEMI  */
#line 165 "parser.y"
                                                          {allerror=1;sprintf(myerror," IF wrong");myyyerror();(yyval.nStmt)=NULL;}
#line 1619 "parser.cpp"
    break;

  case 38: /* Stmt: WHILE LP Exp error RP SEMI CompSt error SEMI  */
#line 166 "parser.y"
                                                       {allerror=1;sprintf(myerror," WHILE wrong");}
#line 1625 "parser.cpp"
    break;

  case 39: /* DefList: %empty  */
#line 170 "parser.y"
         {(yyval.nDefList)=nullptr; }
#line 1631 "parser.cpp"
    break;

  case 40: /* DefList: Def DefList  */
#line 171 "parser.y"
                      {(yyval.nDefList)=new NDefList(*(yyvsp[-1].nDef),(yyvsp[0].nDefList));(yyval.nDefList)->line=(yyvsp[-1].nDef)->line;}
#line 1637 "parser.cpp"
    break;

  case 41: /* Def: Specifier DecList SEMI  */
#line 173 "parser.y"
                            {(yyval.nDef)=new NDef(*(yyvsp[-2].nSpecifier),(yyvsp[-1].nDecList));(yyval.nDef)->line=(yyvsp[-2].nSpecifier)->line;}
#line 1643 "parser.cpp"
    break;

  case 42: /* DecList: Dec  */
#line 176 "parser.y"
               {(yyval.nDecList)=new NDecList(*(yyvsp[0].nDec),nullptr);(yyval.nDecList)->line=(yyvsp[0].nDec)->line;}
#line 1649 "parser.cpp"
    break;

  case 43: /* DecList: Dec COMMA DecList  */
#line 177 "parser.y"
                             {(yyval.nDecList)=new NDecList(*(yyvsp[-2].nDec),(yyvsp[0].nDecList));(yyval.nDecList)->line=(yyvsp[-2].nDec)->line;}
#line 1655 "parser.cpp"
    break;

  case 44: /* DecList: COMMA DecList  */
#line 178 "parser.y"
                         {allerror=1;sprintf(myerror," too more ','");(yyval.nDecList)=(yyvsp[0].nDecList);myyyerror();}
#line 1661 "parser.cpp"
    break;

  case 45: /* DecList: COMMA  */
#line 179 "parser.y"
                 {allerror=1;sprintf(myerror," too more ','");(yyval.nDecList)=NULL;myyyerror();}
#line 1667 "parser.cpp"
    break;

  case 46: /* Dec: VarDec  */
#line 181 "parser.y"
                  {(yyval.nDec)=new NDec(*(yyvsp[0].nVarDec));(yyval.nDec)->line=(yyvsp[0].nVarDec)->line;}
#line 1673 "parser.cpp"
    break;

  case 47: /* Dec: VarDec ASSIGNOP Exp  */
#line 182 "parser.y"
                               {(yyval.nDec)=new NDec(*(yyvsp[-2].nVarDec),(yyvsp[0].nExpression));(yyval.nDec)->line=(yyvsp[-2].nVarDec)->line;}
#line 1679 "parser.cpp"
    break;

  case 48: /* Exp: Exp ASSIGNOP Exp  */
#line 186 "parser.y"
                           {(yyval.nExpression)=new NAssignment(*(new std::string("ASSIGNOP")),*(yyvsp[-2].nExpression),ASSIGNOP,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1685 "parser.cpp"
    break;

  case 49: /* Exp: Exp PLUSASS Exp  */
#line 188 "parser.y"
                            {(yyval.nExpression)=new NAssignment(*(new std::string("PLUSASS")),*(yyvsp[-2].nExpression),PLUSASS,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1691 "parser.cpp"
    break;

  case 50: /* Exp: Exp MINUSASS Exp  */
#line 189 "parser.y"
                             {(yyval.nExpression)=new NAssignment(*(new std::string("MINUSASS")),*(yyvsp[-2].nExpression),MINUSASS,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1697 "parser.cpp"
    break;

  case 51: /* Exp: Exp STARASS Exp  */
#line 190 "parser.y"
                            {(yyval.nExpression)=new NAssignment(*(new std::string("STARASS")),*(yyvsp[-2].nExpression),STARASS,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1703 "parser.cpp"
    break;

  case 52: /* Exp: Exp DIVASS Exp  */
#line 191 "parser.y"
                           {(yyval.nExpression)=new NAssignment(*(new std::string("DIVASS")),*(yyvsp[-2].nExpression),DIVASS,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1709 "parser.cpp"
    break;

  case 53: /* Exp: PLUSPLUS Exp  */
#line 193 "parser.y"
                                         {(yyval.nExpression)=new NSingleOperator(*(new std::string("PLUSPLUS-")),PLUSPLUS,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1715 "parser.cpp"
    break;

  case 54: /* Exp: MINUSMINUS Exp  */
#line 194 "parser.y"
                                             {(yyval.nExpression)=new NSingleOperator(*(new std::string("MINUSMINUS-")),MINUSMINUS,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1721 "parser.cpp"
    break;

  case 55: /* Exp: Exp PLUSPLUS  */
#line 195 "parser.y"
                         {(yyval.nExpression)=new NSingleOperator(*(new std::string("-PLUSPLUS")),PLUSPLUS,*(yyvsp[-1].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1727 "parser.cpp"
    break;

  case 56: /* Exp: Exp MINUSMINUS  */
#line 196 "parser.y"
                          {(yyval.nExpression)=new NSingleOperator(*(new std::string("-MINUSMINUS")),MINUSMINUS,*(yyvsp[-1].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1733 "parser.cpp"
    break;

  case 57: /* Exp: Exp AND Exp  */
#line 198 "parser.y"
                        {(yyval.nExpression)=new NBinaryOperator(*(new std::string("AND")),*(yyvsp[-2].nExpression),AND,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1739 "parser.cpp"
    break;

  case 58: /* Exp: Exp OR Exp  */
#line 199 "parser.y"
                        {(yyval.nExpression)=new NBinaryOperator(*(new std::string("OR")),*(yyvsp[-2].nExpression),OR,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1745 "parser.cpp"
    break;

  case 59: /* Exp: Exp RELOP Exp  */
#line 200 "parser.y"
                        {(yyval.nExpression)=new NBinaryOperator(*(new std::string("RELOP"))+(yyvsp[-1].type_id),*(yyvsp[-2].nExpression),RELOP,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1751 "parser.cpp"
    break;

  case 60: /* Exp: Exp PLUS Exp  */
#line 201 "parser.y"
                        {(yyval.nExpression)=new NBinaryOperator(*(new std::string("PLUS")),*(yyvsp[-2].nExpression),PLUS,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1757 "parser.cpp"
    break;

  case 61: /* Exp: Exp MINUS Exp  */
#line 202 "parser.y"
                        {(yyval.nExpression)=new NBinaryOperator(*(new std::string("MINUS")),*(yyvsp[-2].nExpression),MINUS,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1763 "parser.cpp"
    break;

  case 62: /* Exp: Exp STAR Exp  */
#line 203 "parser.y"
                        {(yyval.nExpression)=new NBinaryOperator(*(new std::string("STAR")),*(yyvsp[-2].nExpression),STAR,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1769 "parser.cpp"
    break;

  case 63: /* Exp: Exp DIV Exp  */
#line 204 "parser.y"
                        {(yyval.nExpression)=new NBinaryOperator(*(new std::string("DIV")),*(yyvsp[-2].nExpression),DIV,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1775 "parser.cpp"
    break;

  case 64: /* Exp: Exp MOD Exp  */
#line 206 "parser.y"
                        {(yyval.nExpression)=new NBinaryOperator(*(new std::string("MOD")),*(yyvsp[-2].nExpression),MOD,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1781 "parser.cpp"
    break;

  case 65: /* Exp: LP Exp RP  */
#line 208 "parser.y"
                        {(yyval.nExpression)=new NParenOperator(*(yyvsp[-1].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1787 "parser.cpp"
    break;

  case 66: /* Exp: MINUS Exp  */
#line 209 "parser.y"
                                   {(yyval.nExpression)=new NSingleOperator(*(new std::string("MINUS-")),MINUS,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1793 "parser.cpp"
    break;

  case 67: /* Exp: NOT Exp  */
#line 210 "parser.y"
                        {(yyval.nExpression)=new NSingleOperator(*(new std::string("NOT-")),NOT,*(yyvsp[0].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1799 "parser.cpp"
    break;

  case 68: /* Exp: ID LP Args RP  */
#line 211 "parser.y"
                        {(yyval.nExpression)=new NMethodCall(*(new NIdentifier(*(new std::string((yyvsp[-3].type_id))))),(yyvsp[-1].nArgs));(yyval.nExpression)->line=yylineno;}
#line 1805 "parser.cpp"
    break;

  case 69: /* Exp: ID LP RP  */
#line 212 "parser.y"
                        {(yyval.nExpression)=new NMethodCall(*(new NIdentifier(*(new std::string((yyvsp[-2].type_id))))));(yyval.nExpression)->line=yylineno;}
#line 1811 "parser.cpp"
    break;

  case 70: /* Exp: Exp LB Exp RB  */
#line 213 "parser.y"
                        {(yyval.nExpression)=new NListOperator(*(yyvsp[-3].nExpression),*(yyvsp[-1].nExpression));(yyval.nExpression)->line=yylineno;}
#line 1817 "parser.cpp"
    break;

  case 71: /* Exp: Exp DOT ID  */
#line 214 "parser.y"
                        {(yyval.nExpression)=new NDotOperator(*(yyvsp[-2].nExpression),*(new NIdentifier(*(new std::string((yyvsp[0].type_id))))));(yyval.nExpression)->line=yylineno;}
#line 1823 "parser.cpp"
    break;

  case 72: /* Exp: ID  */
#line 215 "parser.y"
                        {(yyval.nExpression)=new NIdentifier(*(new std::string((yyvsp[0].type_id))));(yyval.nExpression)->line=yylineno;}
#line 1829 "parser.cpp"
    break;

  case 73: /* Exp: INT  */
#line 216 "parser.y"
                        {(yyval.nExpression)=new NInteger((yyvsp[0].type_int));(yyval.nExpression)->line=yylineno;}
#line 1835 "parser.cpp"
    break;

  case 74: /* Exp: FLOAT  */
#line 217 "parser.y"
                        {(yyval.nExpression)=new NFloat((yyvsp[0].type_float));(yyval.nExpression)->line=yylineno;}
#line 1841 "parser.cpp"
    break;

  case 75: /* Exp: CHAR  */
#line 218 "parser.y"
                        {(yyval.nExpression)=new NChar((yyvsp[0].type_char));(yyval.nExpression)->line=yylineno;}
#line 1847 "parser.cpp"
    break;

  case 76: /* Exp: error  */
#line 219 "parser.y"
                   {allerror=1;sprintf(myerror," error in Exp");(yyval.nExpression)=NULL;myyyerror();}
#line 1853 "parser.cpp"
    break;

  case 77: /* Args: Exp COMMA Args  */
#line 221 "parser.y"
                       {(yyval.nArgs)=new NArgs(*(yyvsp[-2].nExpression),(yyvsp[0].nArgs));(yyval.nArgs)->line=yylineno;}
#line 1859 "parser.cpp"
    break;

  case 78: /* Args: Exp  */
#line 222 "parser.y"
              {(yyval.nArgs)=new NArgs(*(yyvsp[0].nExpression),nullptr);(yyval.nArgs)->line=yylineno;}
#line 1865 "parser.cpp"
    break;


#line 1869 "parser.cpp"

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
  *++yylsp = yyloc;

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 225 "parser.y"

// int main(int argc, char *argv[]){
// 	yyin=fopen(argv[1],"r");
// 	if (!yyin) return 1;
// 	yylineno=1;
//         allptr=NULL;
//         allerror=0;
// 	yyparse();
//         if(p) p->parse();
//         if(!allerror)
//         semanticanalysis(allptr,0);
//         if(!allerror){
//         //std::string temp=argv[1];
//         //temp[temp.size()-1]='l';
//         //temp+="l";
//         //FILE *tt=freopen(temp.data(),"w",stdout);
//         //codeGen(allptr,0);
//         //fclose(tt);
//         //toy_as(temp);
//         //char argvv[2][10];
//         //strcpy(argvv[0],"llc");
//         //temp[temp.size()-2]='b';
//         //temp[temp.size()-1]='c';
//         //strcpy(argvv[1],temp.data());
//         //toy_llc(2,(char **)argvv);
//         }
// 	return 0;
// }

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;//取参数对应的函数
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr,"%s",myerror);
    fprintf(stderr,"%s", ".\n");
    memset(myerror,0,sizeof(myerror));
}	
void myyyerror()
{
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    fprintf(stderr,"%s",myerror);
    fprintf(stderr, "%s",".\n");
    memset(myerror,0,sizeof(myerror));
}
