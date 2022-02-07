/* stack data structure to store multiple formulae */

#include <stdlib.h>
#include "s_tree.h"

typedef struct stack_node
{
    tree_nd *formula;
    struct stack_node *next;
} stk_nd;

stk_nd *new_nd_stk(tree_nd *formula)
{
    stk_nd *new_node = (stk_nd *) malloc(sizeof(stk_nd));
    
    if(!new_node)
        return NULL;

    new_node->next = NULL;
    new_node->formula = formula;

    return new_node;
}

void stk_push(stk_nd **head, tree_nd *formula)
{
    stk_nd* new_node = new_nd_stk(formula);
    
    new_node->next = *head;
    *head = new_node;
}

// pops from the stack and returns the popped formula
tree_nd *stk_pop(stk_nd **head)
{
    if(head)
    {
        tree_nd *popped_val = (*head)->formula; 
        stk_nd *garbage = *head;
        *head = (*head)->next;
        free(garbage);
        
        return popped_val;
    }
    return NULL;
}

void stk_pop_all(stk_nd **head)
{
    if(!head)
        return;

    while(*head)
        stk_pop(head);
}