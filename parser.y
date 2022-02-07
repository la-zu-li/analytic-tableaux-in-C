%{
    #include <stdio.h>

    #include "include/s_tree.h"

    int yylex();
    int yyerror();
    // int yydebug = 1; // debugger session is active
%}

/* below are the declaration of the types that will be present in the symbols. */

%union
{
    char *s;
    struct tree_node *n;
}

/* declaration of tokens below. The terminal symbols (tokens) are considered strings. */
%token <s> EOL
%token <s> ATOM
%token <s> LP RP
%token <s> AND OR IMP NOT
%token <s> OTHER

/* below are the nonterminal symbols, represented by nodes (subtrees) of a syntax tree. */

%type <n> proposition implication disjunction conjunction term

%%

/* the routines below are executed at the same time a syntax tree is built. */

proposition: /*nothing*/ {}
|   proposition implication EOL{
        node *formula = $2;
        return 0;
    }
;

/* an implication can be either a single disjunction or
   two or more disjunctions on an implication or several implications (IMP).
   note the recursion in this second case.
   also note how the order of the operands is different from
   the other binary operators. That's what causes the associativity
   directed to the right of the implication operator. */

implication: disjunction {$$ = $1;}
|    disjunction IMP implication {$$ = new_node(">", $1, $3);}
;

/* a disjunction can be either a single conjunction or 
   two or more conjunctions in a disjunction or several disjunctions (OR).
   note the recursion in this second case. */

disjunction: conjunction {$$ = $1;}
|   disjunction OR conjunction {$$ = new_node("#", $1, $3);}
;

/* a conjunction can be either a single term or
   two or more terms in a conjunction or several conjunctions (AND).
   note the recursion in this second case. */

conjunction: term {$$ = $1;}
|   conjunction AND term {$$ = new_node("&", $1, $3);}
;

/* a term can be either an ATOM, or an parenthesised expression, 
or one of the above negated one or more times. (note the recursion in this last case) */

term: ATOM {$$ = new_node($1, NULL, NULL);}
|   LP implication RP {$$ = $2;}
|   NOT term {$$ = new_node("-", $2, NULL);}
;

%%

void fancy_welcome()
{
    printf("=-=-=-=-=-= CONVERT FORMULA TO CNF =-=-=-=-=-=\n\n");
    printf("enter expression, hit ENTER, and a equivalent CNF will be prompted.\n");
    printf("> ");
}

int main (int argc, char *argv[])
{
    tree_nd *formula = NULL;
    fancy_welcome();
    yyparse();

    
}

int yyerror(char *s)
{
    fprintf(stderr, "error: %s\n", s);
}