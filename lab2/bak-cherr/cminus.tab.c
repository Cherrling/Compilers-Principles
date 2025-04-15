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
#line 2 "cminus.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;

ast_node* root = NULL;
int Err = 0;


void yyerror(const char *s);





#line 93 "cminus.tab.c"

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

#include "cminus.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_TYPE = 6,                       /* TYPE  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_VOID = 10,                      /* VOID  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_STRUCT = 12,                    /* STRUCT  */
  YYSYMBOL_PLUS = 13,                      /* PLUS  */
  YYSYMBOL_MINUS = 14,                     /* MINUS  */
  YYSYMBOL_TIMES = 15,                     /* TIMES  */
  YYSYMBOL_DIVIDE = 16,                    /* DIVIDE  */
  YYSYMBOL_LT = 17,                        /* LT  */
  YYSYMBOL_LTE = 18,                       /* LTE  */
  YYSYMBOL_GT = 19,                        /* GT  */
  YYSYMBOL_GTE = 20,                       /* GTE  */
  YYSYMBOL_EQ = 21,                        /* EQ  */
  YYSYMBOL_NEQ = 22,                       /* NEQ  */
  YYSYMBOL_ASSIGN = 23,                    /* ASSIGN  */
  YYSYMBOL_SEMI = 24,                      /* SEMI  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_LPAREN = 26,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 27,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 28,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 29,                  /* RBRACKET  */
  YYSYMBOL_LBRACE = 30,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 31,                    /* RBRACE  */
  YYSYMBOL_OR = 32,                        /* OR  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_DOT = 34,                       /* DOT  */
  YYSYMBOL_NOT = 35,                       /* NOT  */
  YYSYMBOL_RELOP = 36,                     /* RELOP  */
  YYSYMBOL_THEN = 37,                      /* THEN  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_ExtDefList = 40,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 41,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 42,                /* ExtDecList  */
  YYSYMBOL_Specifier = 43,                 /* Specifier  */
  YYSYMBOL_VarDec = 44,                    /* VarDec  */
  YYSYMBOL_FunDec = 45,                    /* FunDec  */
  YYSYMBOL_VarList = 46,                   /* VarList  */
  YYSYMBOL_ParamDec = 47,                  /* ParamDec  */
  YYSYMBOL_CompSt = 48,                    /* CompSt  */
  YYSYMBOL_StmtList = 49,                  /* StmtList  */
  YYSYMBOL_Stmt = 50,                      /* Stmt  */
  YYSYMBOL_StructSpecifier = 51,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 52,                    /* OptTag  */
  YYSYMBOL_Tag = 53,                       /* Tag  */
  YYSYMBOL_DefList = 54,                   /* DefList  */
  YYSYMBOL_Def = 55,                       /* Def  */
  YYSYMBOL_DecList = 56,                   /* DecList  */
  YYSYMBOL_Dec = 57,                       /* Dec  */
  YYSYMBOL_Exp = 58,                       /* Exp  */
  YYSYMBOL_arg_list = 59                   /* arg_list  */
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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   328

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  128

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


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
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    70,    70,    83,    86,    97,   102,   107,   110,   113,
     118,   121,   125,   130,   136,   144,   149,   156,   163,   170,
     178,   184,   187,   192,   197,   205,   208,   215,   220,   223,
     226,   229,   232,   237,   243,   251,   255,   263,   272,   276,
     282,   286,   291,   298,   301,   307,   310,   320,   325,   331,
     336,   341,   345,   351,   354,   357,   360,   363,   366,   369,
     372,   379,   386,   391,   396,   399,   402,   411,   414
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "ID",
  "TYPE", "ELSE", "IF", "RETURN", "VOID", "WHILE", "STRUCT", "PLUS",
  "MINUS", "TIMES", "DIVIDE", "LT", "LTE", "GT", "GTE", "EQ", "NEQ",
  "ASSIGN", "SEMI", "COMMA", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET",
  "LBRACE", "RBRACE", "OR", "AND", "DOT", "NOT", "RELOP", "THEN",
  "$accept", "program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "VarDec", "FunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt",
  "StructSpecifier", "OptTag", "Tag", "DefList", "Def", "DecList", "Dec",
  "Exp", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-99)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-37)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      58,   -99,    48,    83,   -99,    58,    37,   -99,    64,    77,
     -99,   -99,   -99,   -99,    79,   -99,    84,    15,    60,    58,
       6,   -99,   104,   104,    43,   -99,    58,   -99,    61,    80,
      58,    89,   -99,   104,    90,    93,   -99,   -99,   -99,    91,
      97,    95,   100,   -15,    21,    94,   -99,   -99,   -99,   106,
     -99,    58,   -99,   -99,   -99,   -99,   102,   114,    51,   115,
      51,    51,   -99,   111,    95,    35,   -99,    51,   -99,   -99,
     104,   -99,    75,    51,    99,    51,   123,     7,   -99,   -99,
     -99,    51,    51,    51,    51,    51,   -99,    51,   142,    51,
      51,   139,    51,   219,   -99,   118,   -99,   147,   120,   171,
     -99,   195,   -99,   294,   294,     7,     7,   -19,    59,   117,
     243,   267,   -99,   291,   -99,    51,   -99,    95,    95,   125,
     -99,   -99,   -99,   145,   -99,   -99,    95,   -99
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    13,    35,     0,     2,     3,     0,    14,    37,     0,
      34,     1,     4,     9,    15,     6,     0,     0,     0,    38,
       0,     5,     0,     0,     0,     8,    38,     7,     0,     0,
      38,     0,    19,     0,     0,    22,    15,    12,    11,     0,
       0,    25,     0,    45,     0,    43,    33,    39,    20,    23,
      18,     0,    17,    16,    49,    50,    47,     0,     0,     0,
       0,     0,    28,     0,    25,     0,    41,     0,    42,    40,
       0,    21,     0,     0,     0,     0,     0,    59,    24,    26,
      32,     0,     0,     0,     0,     0,    27,     0,     0,     0,
       0,     0,     0,    46,    44,     0,    60,    68,     0,     0,
      29,     0,    63,    52,    53,    54,    55,    51,     0,     0,
      58,    57,    48,    56,    66,     0,    61,     0,     0,     0,
      62,    65,    67,     0,    31,    64,     0,    30
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -99,   -99,   144,   -99,    74,     1,   -23,   -99,   107,   -99,
     146,   101,   -98,   -99,   -99,   -99,    55,   -99,    96,   -99,
     -58,    52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,    16,    28,    17,    18,    34,    35,
      62,    63,    64,     7,     9,    10,    29,    30,    44,    45,
      65,    98
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      74,     6,    76,    77,    85,    43,     6,    31,    67,    93,
      49,    88,     1,    24,    97,    99,    22,   101,     2,   123,
     124,    33,    68,   103,   104,   105,   106,   107,   127,   108,
      85,   110,   111,    32,   113,    87,    80,    88,    13,   -10,
      23,    91,    14,    24,    39,    69,    40,    43,    81,    82,
      83,    84,    33,     8,    54,    55,    56,    97,    85,    86,
     119,    15,    42,    87,     1,    88,    36,    89,    90,    91,
       2,    92,    81,    82,    83,    84,    95,    60,    54,    55,
      56,    41,    85,    11,    25,    47,    61,    87,   120,    88,
      26,    89,    90,    91,   -36,    92,    37,    38,    54,    55,
      56,    60,    96,    57,    58,    20,    59,    19,    21,    36,
      61,    46,    81,    82,    83,    84,    48,    50,    51,    70,
      52,    60,    85,   100,    66,    26,    53,    87,    72,    88,
      61,    89,    90,    91,    24,    92,    81,    82,    83,    84,
      73,    75,    78,   109,   112,   114,    85,   116,   121,    12,
     102,    87,   126,    88,   125,    89,    90,    91,    71,    92,
      81,    82,    83,    84,    27,    79,    94,   122,     0,     0,
      85,     0,   115,     0,     0,    87,     0,    88,     0,    89,
      90,    91,     0,    92,    81,    82,    83,    84,     0,     0,
       0,     0,     0,     0,    85,     0,     0,     0,   117,    87,
       0,    88,     0,    89,    90,    91,     0,    92,    81,    82,
      83,    84,     0,     0,     0,     0,     0,     0,    85,     0,
       0,     0,   118,    87,     0,    88,     0,    89,    90,    91,
       0,    92,    81,    82,    83,    84,     0,     0,     0,     0,
       0,     0,    85,     0,     0,     0,     0,    87,     0,    88,
       0,    89,    90,    91,     0,    92,    81,    82,    83,    84,
       0,     0,     0,     0,     0,     0,    85,     0,     0,     0,
       0,    87,     0,    88,     0,     0,    90,    91,     0,    92,
      81,    82,    83,    84,     0,     0,     0,     0,     0,     0,
      85,     0,     0,     0,     0,    87,     0,    88,     0,     0,
       0,    91,     0,    92,    81,    82,    83,    84,     0,    83,
      84,     0,     0,     0,    85,     0,     0,    85,     0,    87,
       0,    88,    87,     0,    88,    91,     0,     0,    91
};

static const yytype_int8 yycheck[] =
{
      58,     0,    60,    61,    23,    28,     5,     1,    23,    67,
      33,    30,     6,    28,    72,    73,     1,    75,    12,   117,
     118,    20,     1,    81,    82,    83,    84,    85,   126,    87,
      23,    89,    90,    27,    92,    28,     1,    30,     1,    24,
      25,    34,     5,    28,     1,    24,     3,    70,    13,    14,
      15,    16,    51,     5,     3,     4,     5,   115,    23,    24,
       1,    24,     1,    28,     6,    30,     5,    32,    33,    34,
      12,    36,    13,    14,    15,    16,     1,    26,     3,     4,
       5,    26,    23,     0,    24,    30,    35,    28,    29,    30,
      30,    32,    33,    34,    30,    36,    22,    23,     3,     4,
       5,    26,    27,     8,     9,    26,    11,    30,    24,     5,
      35,    31,    13,    14,    15,    16,    27,    27,    25,    25,
      29,    26,    23,    24,    24,    30,    29,    28,    26,    30,
      35,    32,    33,    34,    28,    36,    13,    14,    15,    16,
      26,    26,    31,     1,     5,    27,    23,    27,    31,     5,
      27,    28,     7,    30,    29,    32,    33,    34,    51,    36,
      13,    14,    15,    16,    18,    64,    70,   115,    -1,    -1,
      23,    -1,    25,    -1,    -1,    28,    -1,    30,    -1,    32,
      33,    34,    -1,    36,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    27,    28,
      -1,    30,    -1,    32,    33,    34,    -1,    36,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    27,    28,    -1,    30,    -1,    32,    33,    34,
      -1,    36,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    30,
      -1,    32,    33,    34,    -1,    36,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    28,    -1,    30,    -1,    -1,    33,    34,    -1,    36,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    28,    -1,    30,    -1,    -1,
      -1,    34,    -1,    36,    13,    14,    15,    16,    -1,    15,
      16,    -1,    -1,    -1,    23,    -1,    -1,    23,    -1,    28,
      -1,    30,    28,    -1,    30,    34,    -1,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    12,    39,    40,    41,    43,    51,     5,    52,
      53,     0,    40,     1,     5,    24,    42,    44,    45,    30,
      26,    24,     1,    25,    28,    24,    30,    48,    43,    54,
      55,     1,    27,    43,    46,    47,     5,    42,    42,     1,
       3,    54,     1,    44,    56,    57,    31,    54,    27,    44,
      27,    25,    29,    29,     3,     4,     5,     8,     9,    11,
      26,    35,    48,    49,    50,    58,    24,    23,     1,    24,
      25,    46,    26,    26,    58,    26,    58,    58,    31,    49,
       1,    13,    14,    15,    16,    23,    24,    28,    30,    32,
      33,    34,    36,    58,    56,     1,    27,    58,    59,    58,
      24,    58,    27,    58,    58,    58,    58,    58,    58,     1,
      58,    58,     5,    58,    27,    25,    27,    27,    27,     1,
      29,    31,    59,    50,    50,    29,     7,    50
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      42,    42,    42,    43,    43,    44,    44,    44,    45,    45,
      45,    46,    46,    47,    48,    49,    49,    50,    50,    50,
      50,    50,    50,    51,    51,    52,    52,    53,    54,    54,
      55,    55,    55,    56,    56,    57,    57,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    59,    59
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     3,     2,
       1,     3,     3,     1,     1,     1,     4,     4,     4,     3,
       4,     3,     1,     2,     4,     0,     2,     2,     1,     3,
       7,     5,     2,     5,     2,     0,     1,     1,     0,     2,
       3,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     4,     4,     3,     5,     4,     4,     3,     1
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
#line 70 "cminus.y"
                 { 
        if ((yyvsp[0].node) == NULL) {
            (yyval.node) = create_node("Program", 0, (yylsp[0]).first_line);
        } else if ((yyvsp[0].node)->child_count == 1) {
            (yyval.node) = create_node("Program", 1, (yyvsp[0].node)->linenumber, (yyvsp[0].node));
        } else {
            (yyval.node) = create_node("Program", 1, (yylsp[0]).first_line, (yyvsp[0].node));
        }
        root = (yyval.node);
    }
#line 1383 "cminus.tab.c"
    break;

  case 3: /* ExtDefList: %empty  */
#line 83 "cminus.y"
                  { 
        (yyval.node) = NULL;  // 空规则直接返回 NULL，不创建节点
    }
#line 1391 "cminus.tab.c"
    break;

  case 4: /* ExtDefList: ExtDef ExtDefList  */
#line 86 "cminus.y"
                        { 
        if ((yyvsp[0].node) == NULL) {
            (yyval.node) = create_node("ExtDefList", 1, (yylsp[-1]).first_line, (yyvsp[-1].node));
        } else {
            (yyval.node) = create_node("ExtDefList", 2, (yylsp[-1]).first_line, (yyvsp[-1].node), (yyvsp[0].node)); 
            (yyval.node) -> val.int_value = 2;
        }
    }
#line 1404 "cminus.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 97 "cminus.y"
                               {
        ast_node* semi_node = create_node("SEMI", 0, (yylsp[0]).first_line);
        (yyval.node)=create_node("ExtDef", 3, (yylsp[-2]).first_line, (yyvsp[-2].node), (yyvsp[-1].node), semi_node);
    
    }
#line 1414 "cminus.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 102 "cminus.y"
                    {
        ast_node* semi_node = create_node("SEMI", 0, (yylsp[0]).first_line);
        (yyval.node)=create_node("ExtDef", 2, (yylsp[-1]).first_line, (yyvsp[-1].node), semi_node);
    
    }
#line 1424 "cminus.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 107 "cminus.y"
                             {
        (yyval.node)=create_node("ExtDef", 3, (yylsp[-2]).first_line, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1432 "cminus.tab.c"
    break;

  case 8: /* ExtDef: Specifier FunDec SEMI  */
#line 110 "cminus.y"
                           {
        (yyval.node)=create_node("ExtDef", 2, (yylsp[-2]).first_line, (yyvsp[-2].node), (yyvsp[-1].node));
    }
#line 1440 "cminus.tab.c"
    break;

  case 9: /* ExtDef: Specifier error  */
#line 113 "cminus.y"
                      {
        printError('B', "Missing \";\""); // 打印错误消息
    }
#line 1448 "cminus.tab.c"
    break;

  case 10: /* ExtDecList: VarDec  */
#line 118 "cminus.y"
            {
        (yyval.node)=create_node("ExtDecList", 1, (yylsp[0]).first_line, (yyvsp[0].node));
    }
#line 1456 "cminus.tab.c"
    break;

  case 11: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 121 "cminus.y"
                             {
        (yyval.node)=create_node("ExtDecList", 2, (yylsp[-2]).first_line, (yyvsp[-2].node),  (yyvsp[0].node));

    }
#line 1465 "cminus.tab.c"
    break;

  case 12: /* ExtDecList: VarDec error ExtDecList  */
#line 125 "cminus.y"
                             {
        printError('B', "text"); // 打印错误消息
    }
#line 1473 "cminus.tab.c"
    break;

  case 13: /* Specifier: TYPE  */
#line 130 "cminus.y"
           { 
        ast_node* type_node = create_node("TYPE", 0, (yylsp[0]).first_line);
        type_node->val.str_value = strdup((yyvsp[0].string));  // 保存类型字符串
        // 创建Specifier节点
        (yyval.node) = create_node("Specifier", 1, (yylsp[0]).first_line, type_node);
    }
#line 1484 "cminus.tab.c"
    break;

  case 14: /* Specifier: StructSpecifier  */
#line 136 "cminus.y"
                      { 
        (yyval.node) = create_node("Specifier", 1, (yylsp[0]).first_line, (yyvsp[0].node)); 
    }
#line 1492 "cminus.tab.c"
    break;

  case 15: /* VarDec: ID  */
#line 144 "cminus.y"
         { 
        ast_node* id_node = create_node("ID", 0, (yylsp[0]).first_line);
        id_node->val.str_value = strdup((yyvsp[0].string));  // 保存变量名
        (yyval.node) = create_node("VarDec", 1, (yylsp[0]).first_line, id_node); 
    }
#line 1502 "cminus.tab.c"
    break;

  case 16: /* VarDec: VarDec LBRACKET INT RBRACKET  */
#line 149 "cminus.y"
                                   {
        ast_node* lb_node = create_node("LB", 0, (yylsp[-2]).first_line);
        ast_node* int_node = create_node("INT", 0, (yylsp[-1]).first_line);
        int_node->val.int_value = (yyvsp[-1].int_number);
        ast_node* rb_node = create_node("RB", 0, (yylsp[0]).first_line);
        (yyval.node) = create_node("VarDec", 4, (yylsp[-3]).first_line, (yyvsp[-3].node), lb_node, int_node, rb_node); 
    }
#line 1514 "cminus.tab.c"
    break;

  case 17: /* VarDec: VarDec LBRACKET error RBRACKET  */
#line 156 "cminus.y"
                                     {
        char msg[32]; // 定义错误信息缓冲区
        sprintf(msg, "Syntax error, near \'%c\'", yytext[0]); // 格式化错误消息
        printError('B', msg); // 打印错误消息
    }
#line 1524 "cminus.tab.c"
    break;

  case 18: /* FunDec: ID LPAREN VarList RPAREN  */
#line 163 "cminus.y"
                             {
        ast_node* id_node = create_node("ID", 0, (yylsp[-3]).first_line);
        id_node->val.str_value = strdup((yyvsp[-3].string));  // 保存函数名
        ast_node* lp_node = create_node("LP", 0, (yylsp[-2]).first_line);
        ast_node* rp_node = create_node("RP", 0, (yylsp[0]).first_line);
        (yyval.node) = create_node("FunDec", 4, (yylsp[-3]).first_line, id_node, lp_node, (yyvsp[-1].node), rp_node); 
    }
#line 1536 "cminus.tab.c"
    break;

  case 19: /* FunDec: ID LPAREN RPAREN  */
#line 170 "cminus.y"
                      {
        ast_node* id_node = create_node("ID", 0, (yylsp[-2]).first_line);
        id_node->val.str_value = strdup((yyvsp[-2].string));  // 保存函数名
        ast_node* lp_node = create_node("LP", 0, (yylsp[-1]).first_line);
        ast_node* rp_node = create_node("RP", 0, (yylsp[0]).first_line);
        (yyval.node) = create_node("FunDec", 3, (yylsp[-2]).first_line, id_node, lp_node, rp_node); 
    
    }
#line 1549 "cminus.tab.c"
    break;

  case 20: /* FunDec: ID LPAREN error RPAREN  */
#line 178 "cminus.y"
                             {
        printError('B', "Syntax error between ()"); // 打印错误消息
    }
#line 1557 "cminus.tab.c"
    break;

  case 21: /* VarList: ParamDec COMMA VarList  */
#line 184 "cminus.y"
                             {
        (yyval.node) = create_node("VarList", 2, (yylsp[-2]).first_line, (yyvsp[-2].node),  (yyvsp[0].node)); 
    }
#line 1565 "cminus.tab.c"
    break;

  case 22: /* VarList: ParamDec  */
#line 187 "cminus.y"
               {
        (yyval.node) = create_node("VarList", 1, (yylsp[0]).first_line, (yyvsp[0].node)); 
    }
#line 1573 "cminus.tab.c"
    break;

  case 23: /* ParamDec: Specifier VarDec  */
#line 192 "cminus.y"
                       {
        (yyval.node) = create_node("ParamDec", 2, (yylsp[-1]).first_line, (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 1581 "cminus.tab.c"
    break;

  case 24: /* CompSt: LBRACE DefList StmtList RBRACE  */
#line 197 "cminus.y"
                                   {
        ast_node* lc_node = create_node("LC", 0, (yylsp[-3]).first_line);
        ast_node* rc_node = create_node("RC", 0, (yylsp[0]).first_line);
        (yyval.node) = create_node("CompSt", 4, (yylsp[-3]).first_line, lc_node, (yyvsp[-2].node), (yyvsp[-1].node), rc_node); 
    }
#line 1591 "cminus.tab.c"
    break;

  case 25: /* StmtList: %empty  */
#line 205 "cminus.y"
      {
        (yyval.node) = NULL;
    }
#line 1599 "cminus.tab.c"
    break;

  case 26: /* StmtList: Stmt StmtList  */
#line 208 "cminus.y"
                   {
        (yyval.node) = create_node("StmtList", 2, (yylsp[-1]).first_line, (yyvsp[-1].node), (yyvsp[0].node)); 
    }
#line 1607 "cminus.tab.c"
    break;

  case 27: /* Stmt: Exp SEMI  */
#line 215 "cminus.y"
               {
        ast_node* semi_node = create_node("SEMI", 0, (yylsp[0]).first_line);
        (yyval.node) = create_node("Stmt", 2, (yylsp[-1]).first_line, (yyvsp[-1].node), semi_node); 
    
    }
#line 1617 "cminus.tab.c"
    break;

  case 28: /* Stmt: CompSt  */
#line 220 "cminus.y"
             {
        (yyval.node) = create_node("Stmt", 1, (yylsp[0]).first_line, (yyvsp[0].node)); 
    }
#line 1625 "cminus.tab.c"
    break;

  case 29: /* Stmt: RETURN Exp SEMI  */
#line 223 "cminus.y"
                      {
        (yyval.node) = create_node("Stmt", 1, (yylsp[-2]).first_line, (yyvsp[-1].node)); 
    }
#line 1633 "cminus.tab.c"
    break;

  case 30: /* Stmt: IF LPAREN Exp RPAREN Stmt ELSE Stmt  */
#line 226 "cminus.y"
                                          {
        (yyval.node) = create_node("Stmt", 3, (yylsp[-6]).first_line,  (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); 
    }
#line 1641 "cminus.tab.c"
    break;

  case 31: /* Stmt: WHILE LPAREN Exp RPAREN Stmt  */
#line 229 "cminus.y"
                                   {
        (yyval.node) = create_node("Stmt", 2, (yylsp[-4]).first_line, (yyvsp[-2].node), (yyvsp[0].node)); 
    }
#line 1649 "cminus.tab.c"
    break;

  case 32: /* Stmt: Exp error  */
#line 232 "cminus.y"
                {
        printError('B', "Missing \";\""); // 打印错误消息
    }
#line 1657 "cminus.tab.c"
    break;

  case 33: /* StructSpecifier: STRUCT OptTag LBRACE DefList RBRACE  */
#line 237 "cminus.y"
                                          {
        ast_node* struct_node = create_node("STRUCT", 0, (yylsp[-4]).first_line);
        ast_node* lb_node = create_node("LC", 0, (yylsp[-2]).first_line);
        ast_node* rb_node = create_node("RC", 0, (yylsp[0]).first_line);
        (yyval.node) = create_node("StructSpecifier", 5, (yylsp[-4]).first_line, struct_node, (yyvsp[-3].node), lb_node, (yyvsp[-1].node), rb_node); 
    }
#line 1668 "cminus.tab.c"
    break;

  case 34: /* StructSpecifier: STRUCT Tag  */
#line 243 "cminus.y"
                 {
        ast_node* struct_node = create_node("STRUCT", 0, (yylsp[-1]).first_line);
        (yyval.node) = create_node("StructSpecifier", 2, (yylsp[-1]).first_line, struct_node, (yyvsp[0].node)); 
    }
#line 1677 "cminus.tab.c"
    break;

  case 35: /* OptTag: %empty  */
#line 251 "cminus.y"
                  {
        (yyval.node) = create_node("OptTag", 0, 0);
        (yyval.node) -> val.int_value = 0; 
    }
#line 1686 "cminus.tab.c"
    break;

  case 36: /* OptTag: ID  */
#line 255 "cminus.y"
         {
        ast_node* id_node = create_node("ID", 0, (yylsp[0]).first_line);
        id_node->val.str_value = strdup((yyvsp[0].string));  // 保存ID值
        (yyval.node) = create_node("OptTag", 1, (yylsp[0]).first_line, id_node); 
    }
#line 1696 "cminus.tab.c"
    break;

  case 37: /* Tag: ID  */
#line 263 "cminus.y"
         {
        ast_node* id_node = create_node("ID", 0, (yylsp[0]).first_line);
        id_node->val.str_value = strdup((yyvsp[0].string));  // 保存ID值
        (yyval.node) = create_node("Tag", 1, (yylsp[0]).first_line, id_node); 

    }
#line 1707 "cminus.tab.c"
    break;

  case 38: /* DefList: %empty  */
#line 272 "cminus.y"
                  { 
        (yyval.node) = NULL;

    }
#line 1716 "cminus.tab.c"
    break;

  case 39: /* DefList: Def DefList  */
#line 276 "cminus.y"
                  {
        (yyval.node) = create_node("DefList", 2, (yylsp[-1]).first_line, (yyvsp[-1].node), (yyvsp[0].node));
    }
#line 1724 "cminus.tab.c"
    break;

  case 40: /* Def: Specifier DecList SEMI  */
#line 282 "cminus.y"
                             {
        ast_node* semi_node = create_node("SEMI", 0, (yylsp[0]).first_line);
        (yyval.node) = create_node("Def", 3, (yylsp[-2]).first_line, (yyvsp[-2].node), (yyvsp[-1].node), semi_node); 
    }
#line 1733 "cminus.tab.c"
    break;

  case 41: /* Def: Specifier error SEMI  */
#line 286 "cminus.y"
                           {
        char msg[32]; // 定义错误信息缓冲区
        sprintf(msg, "Syntax error, near \'%c\'", yytext[0]); // 格式化错误消息
        printError('B', msg); // 打印错误消息
    }
#line 1743 "cminus.tab.c"
    break;

  case 42: /* Def: Specifier DecList error  */
#line 291 "cminus.y"
                              {
        printError('B',"Missing \";\""); // 打印错误消息
    }
#line 1751 "cminus.tab.c"
    break;

  case 43: /* DecList: Dec  */
#line 298 "cminus.y"
          {
        (yyval.node) = create_node("DecList", 1, (yylsp[0]).first_line, (yyvsp[0].node)); 
    }
#line 1759 "cminus.tab.c"
    break;

  case 44: /* DecList: Dec COMMA DecList  */
#line 301 "cminus.y"
                        {
        ast_node* comma_node = create_node("COMMA", 0, (yylsp[-1]).first_line);
        (yyval.node) = create_node("DecList", 3, (yylsp[-2]).first_line, (yyvsp[-2].node), comma_node, (yyvsp[0].node));
    }
#line 1768 "cminus.tab.c"
    break;

  case 45: /* Dec: VarDec  */
#line 307 "cminus.y"
             {
        (yyval.node) = create_node("Dec", 1, (yylsp[0]).first_line, (yyvsp[0].node)); // 将 VarDec 作为 Dec 的子节点
    }
#line 1776 "cminus.tab.c"
    break;

  case 46: /* Dec: VarDec ASSIGN Exp  */
#line 310 "cminus.y"
                        {
        ast_node* assign_node = create_node("ASSIGN", 0, (yylsp[-1]).first_line);
        assign_node->val.str_value = "=";
        (yyval.node) = create_node("Dec", 3, (yylsp[-2]).first_line, (yyvsp[-2].node), assign_node, (yyvsp[0].node)); 
    }
#line 1786 "cminus.tab.c"
    break;

  case 47: /* Exp: ID  */
#line 320 "cminus.y"
         { 
        ast_node* id_node = create_node("ID", 0, (yylsp[0]).first_line);
        id_node->val.str_value = strdup((yyvsp[0].string));  // 保存ID的值
        (yyval.node) = create_node("Exp", 1, (yylsp[0]).first_line, id_node);  // 将ID作为Exp的子节点
    }
#line 1796 "cminus.tab.c"
    break;

  case 48: /* Exp: Exp DOT ID  */
#line 325 "cminus.y"
                 {
        ast_node* dot_node = create_node("DOT", 0, (yylsp[-1]).first_line);
        ast_node* id_node = create_node("ID", 0, (yylsp[0]).first_line);
        id_node->val.str_value = strdup((yyvsp[0].string));  // 保存ID值
        (yyval.node) = create_node("Exp", 3, (yylsp[-2]).first_line, (yyvsp[-2].node), dot_node, id_node);
    }
#line 1807 "cminus.tab.c"
    break;

  case 49: /* Exp: INT  */
#line 331 "cminus.y"
          { 
        ast_node* int_node = create_node("INT", 0, (yylsp[0]).first_line);
        int_node->val.int_value = (yyvsp[0].int_number);  // 保存整数值
        (yyval.node) = create_node("Exp", 1, (yylsp[0]).first_line, int_node);
    }
#line 1817 "cminus.tab.c"
    break;

  case 50: /* Exp: FLOAT  */
#line 336 "cminus.y"
            {
        ast_node* float_node = create_node("FLOAT", 0, (yylsp[0]).first_line);
        float_node->val.float_value = (yyvsp[0].float_number);  // 保存整数值
        (yyval.node) = create_node("Exp", 1, (yylsp[0]).first_line, float_node);
    }
#line 1827 "cminus.tab.c"
    break;

  case 51: /* Exp: Exp ASSIGN Exp  */
#line 341 "cminus.y"
                     {
        ast_node* assign_node = create_node("ASSIGN", 0, (yylsp[-1]).first_line);
        (yyval.node) = create_node("Exp", 3, (yylsp[-2]).first_line, (yyvsp[-2].node), assign_node, (yyvsp[0].node));
    }
#line 1836 "cminus.tab.c"
    break;

  case 52: /* Exp: Exp PLUS Exp  */
#line 345 "cminus.y"
                   {
        ast_node* plus_node = create_node("PLUS", 0, (yylsp[-1]).first_line);
        ast_node* left_exp = create_node("Exp", 1, (yylsp[-2]).first_line, (yyvsp[-2].node));
        ast_node* right_exp = create_node("Exp", 1, (yylsp[0]).first_line, (yyvsp[0].node));
        (yyval.node) = create_node("Exp", 3, (yylsp[-2]).first_line, (yyvsp[-2].node), plus_node, (yyvsp[0].node));
    }
#line 1847 "cminus.tab.c"
    break;

  case 53: /* Exp: Exp MINUS Exp  */
#line 351 "cminus.y"
                    {
        (yyval.node) = create_node("minus",2 , (yylsp[-2]).first_line, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1855 "cminus.tab.c"
    break;

  case 54: /* Exp: Exp TIMES Exp  */
#line 354 "cminus.y"
                    {
        (yyval.node) = create_node("mul",2 , (yylsp[-2]).first_line, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1863 "cminus.tab.c"
    break;

  case 55: /* Exp: Exp DIVIDE Exp  */
#line 357 "cminus.y"
                     {
        (yyval.node) = create_node("div",2 , (yylsp[-2]).first_line, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1871 "cminus.tab.c"
    break;

  case 56: /* Exp: Exp RELOP Exp  */
#line 360 "cminus.y"
                    {
        (yyval.node) = create_node("RELOP",2 , (yylsp[-2]).first_line, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1879 "cminus.tab.c"
    break;

  case 57: /* Exp: Exp AND Exp  */
#line 363 "cminus.y"
                  {
        (yyval.node) = create_node("AND",2 , (yylsp[-2]).first_line, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1887 "cminus.tab.c"
    break;

  case 58: /* Exp: Exp OR Exp  */
#line 366 "cminus.y"
                 {
        (yyval.node) = create_node("OR",2 , (yylsp[-2]).first_line, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1895 "cminus.tab.c"
    break;

  case 59: /* Exp: NOT Exp  */
#line 369 "cminus.y"
             {
        (yyval.node) = create_node("NOT",1 , (yylsp[-1]).first_line, (yyvsp[0].node));
    }
#line 1903 "cminus.tab.c"
    break;

  case 60: /* Exp: ID LPAREN RPAREN  */
#line 372 "cminus.y"
                       {
        ast_node* id_node = create_node("ID", 0, (yylsp[-2]).first_line);
        id_node->val.str_value = strdup((yyvsp[-2].string));
        ast_node* lp_node = create_node("LP", 0, (yylsp[-1]).first_line);
        ast_node* rp_node = create_node("RP", 0, (yylsp[0]).first_line);
        (yyval.node) = create_node("CALL", 3, (yylsp[-2]).first_line, id_node, lp_node, rp_node);
    }
#line 1915 "cminus.tab.c"
    break;

  case 61: /* Exp: ID LPAREN arg_list RPAREN  */
#line 379 "cminus.y"
                               {
        ast_node* id_node = create_node("ID", 0, (yylsp[-3]).first_line);
        id_node->val.str_value = strdup((yyvsp[-3].string));
        ast_node* lp_node = create_node("LP", 0, (yylsp[-2]).first_line);
        ast_node* rp_node = create_node("RP", 0, (yylsp[0]).first_line);
        (yyval.node) = create_node("CALL", 4, (yylsp[-3]).first_line, id_node, lp_node, (yyvsp[-1].node), rp_node);
    }
#line 1927 "cminus.tab.c"
    break;

  case 62: /* Exp: Exp LBRACKET Exp RBRACKET  */
#line 386 "cminus.y"
                                {
        ast_node* lb_node = create_node("LB", 0, (yylsp[-2]).first_line);
        ast_node* rb_node = create_node("RB", 0, (yylsp[0]).first_line);
        (yyval.node) = create_node("array_access", 4, (yylsp[-3]).first_line, (yyvsp[-3].node), lb_node, (yyvsp[-1].node), rb_node);
    }
#line 1937 "cminus.tab.c"
    break;

  case 63: /* Exp: LPAREN Exp RPAREN  */
#line 391 "cminus.y"
                        {
        ast_node* lp_node = create_node("LP", 0, (yylsp[-2]).first_line);
        ast_node* rp_node = create_node("RP", 0, (yylsp[0]).first_line);
        (yyval.node) = create_node("Exp", 3, (yylsp[-2]).first_line, lp_node, (yyvsp[-1].node), rp_node);
    }
#line 1947 "cminus.tab.c"
    break;

  case 64: /* Exp: Exp LBRACKET Exp error RBRACKET  */
#line 396 "cminus.y"
                                      {
        printError('B', "Missing \"]\"");
    }
#line 1955 "cminus.tab.c"
    break;

  case 65: /* Exp: Exp LBRACE error RBRACE  */
#line 399 "cminus.y"
                              {
        printError('B', "Syntax error between \"[]\""); // 打印错误消息
    }
#line 1963 "cminus.tab.c"
    break;

  case 66: /* Exp: ID LPAREN error RPAREN  */
#line 402 "cminus.y"
                             {
        printError('B', "Syntax error in Exp"); // 打印错误消息
    }
#line 1971 "cminus.tab.c"
    break;

  case 67: /* arg_list: Exp COMMA arg_list  */
#line 411 "cminus.y"
                         {
        (yyval.node) = create_node("arg_list", 2, (yylsp[-2]).first_line, (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1979 "cminus.tab.c"
    break;

  case 68: /* arg_list: Exp  */
#line 414 "cminus.y"
          { 
        (yyval.node) = create_node("arg_list", 1, (yylsp[0]).first_line, (yyvsp[0].node)); 
    }
#line 1987 "cminus.tab.c"
    break;


#line 1991 "cminus.tab.c"

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

#line 420 "cminus.y"

