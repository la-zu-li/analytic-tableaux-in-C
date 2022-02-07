/* 
    tableau structures and methods implementation.
    
    types of conjugated (marked) formulae and it's expansions:
    _____________________    _____________________
    |    α FORMULAS     |    |    β FORMULAS     |
    |___________________|    |___________________|
    | FORM. | EXPANSION |    | FORM. | EXPANSION |
    |_______|___________|    |_______|___________|
    | T_A∧B | T_A   T_B |    | F_A∧B | F_A   F_B |
    | F_A∨B | F_A   F_B |    | T_A∨B | T_A   T_B |
    | F_A→B | T_A   F_B |    | T_A→B | F_A   T_B |
    | T_¬A  |    F_A    |    |||||||||||||||||||||
    | F_¬A  |    T_A    |    
    |||||||||||||||||||||
*/

#include <stdlib.h>
#include "s_tree.h"
#include "queue.h"
#include "utils.h"

enum mark{MARK_T, MARK_F};
enum type{ALPHA, BETA};

typedef struct marked_formula
{
    mark mk;        // "mark" of the formula, a T or a F.
    type tp;        // "type" of the formula, either Alpha (α) or Beta (β).
    tree_nd *form;  // the formula itself, passed as the root of the syntax tree.
} marked;

marked new_marked_form(mark mk, type tp, tree_nd *form)
{
    marked new_nd;
    new_nd.form = form;
    new_nd.mk = mk;
    new_nd.tp = tp;

    return new_nd;
}

typedef struct tableau_node
{
    marked mk_form;          // the marked formula.
    struct tableau_node *l;  // pointer to left.
    struct tableau_node *r;  // pointer to right.
} tab_nd;


tab_nd *new_tab_node(marked mk_form, tab_nd *left, tab_nd *right)
{
    tab_nd *new_nd = (tab_nd *) malloc(sizeof(tab_nd));
    
    if(!new_nd)
        return NULL; // returns NULL if the allocation failed

    new_nd->l = left;
    new_nd->r = right;
    new_nd->mk_form = mk_form;
}

// function that builds the initial tableau, using the entered formulae,
// which were put in a queue.
tab_nd *init_tableau(queue forms)
{
    // TODO: init tableau
}

// auxiliary function to add formulae to all the branches, 
// in a alpha expansion
void add_forms_alpha(tab_nd *root, tab_nd *add1, tab_nd *add2)
{
    if(!root || (!add1 && !add2))
        return;
    
    if(root->l)
        add_forms_alpha(root->l, add1, add2);
    
    if(root->r)
        add_forms_alpha(root->r, add1, add2);
    
    if(!root->l && !root->r)
    {
        if(add1)
        {
            root->l = add1;
            add1->l = add2;
        }

        else
            root->l = add2;
    }
}


void add_forms_beta(tab_nd *root, tab_nd *add1, tab_nd *add2)
{
    if(!root || !add1 || !add2)
        return;
    
    if(root->l)
        add_forms_beta(root->l, add1, add2);
    
    if(!root->l && !root->r)
    {
        root->l = add1;
        root->l = add2;
        return;
    }

    if(root->r)
        add_forms_beta(root->r, add1, add2);
}

// handle cases for an alpha expansion
void alpha_exp(tab_nd *root, tab_nd *form)
{

    tree_nd *formula = form->mk_form.form;
    
    // T_¬A   |->  F_A
    if(!strcmp(formula->tok, "-") && form->mk_form.mk == MARK_T)
    {
        // TODO: rest of code for this expansion
    }
    // F_¬A   |->  T_A
    else if(!strcmp(formula->tok, "-") && form->mk_form.mk == MARK_F)
    {
        // TODO: rest of code for this expansion
    }
    // T_A∧B  |->  T_A   T_B
    if(!strcmp(formula->tok, "&") && form->mk_form.mk == MARK_T)
    {
        // TODO: rest of code for this expansion
    }
    // F_A∨B  |->  F_A   F_B
    else if(!strcmp(formula->tok, "#") && form->mk_form.mk == MARK_F)
    {
        // TODO: rest of code for this expansion
    }
    // F_A→B | T_A   F_B
    else
    {
        // TODO: rest of code for this expansion
    }
}

// handle cases for a beta expansion
void beta_exp(tab_nd *root, tab_nd *form)
{
    // TODO: beta expansion cases
}

// expands a formula
void expand_form(tab_nd *root, tab_nd *form)
{
    if(!form)
        return;

    // alpha expansions
    if(form->mk_form.tp == ALPHA)
    {
        alpha_exp(root, form);        
    }
    
    // beta expansions
    else
    {
        beta_exp(root, form);
    }
}