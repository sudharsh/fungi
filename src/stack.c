/* 
 * stack.c
 * Written by Sudharshan "Sup3rkiddo" S <sudharsh@gmail.com>
 * All Rights Reserved
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */ 

#include "fungi.h"


NumberStack *__get_node()
{
    NumberStack *node;
    node = (NumberStack *) malloc(sizeof(NumberStack));
    return node;
}


void stack_push(NumberStack **ns, int nw)
{
    NumberStack *node = __get_node();
    int prev_idx = 0;

    
    if (*ns)
        prev_idx = (*ns)->index;
    else
        prev_idx = -1;
    node->value = nw;                          
    node->next = NULL;
        
    node->next = *ns;
    *ns = node;
    (*ns)->index = prev_idx + 1;
    __debug("Pushed %d. Size is now", nw, (*ns)->index + 1);
    return;
}



int stack_pop(NumberStack **ns) {
    int value;
    NumberStack *dummy;

    if(*ns)
        if((*ns)->index < 0) {
            __debug("Stack is empty\n");
            return;
        
        } else {                 
            value = (*ns)->value;
            dummy = *ns;
            *ns = (*ns)->next;
            if (*ns) {
                (*ns)->index = dummy->index - 1;
                free(dummy);
            }
        }
    
    return value;
}

    
    
int test_stack() {
    NumberStack *ns = __get_node();
    stack_push(&ns, 5);
    stack_push(&ns, 4);
    __debug("Popped : %d\n", stack_pop(&ns));
    __debug("Popped : %d\n", stack_pop(&ns));
    __debug("Popped : %d\n", stack_pop(&ns));
    __debug("Popped : %d\n", stack_pop(&ns));
    stack_push(&ns, 6);
    __debug("Popped : %d\n", stack_pop(&ns));
}
    
