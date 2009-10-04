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
    
    node->value = nw;                          
    node->next = NULL;
        
    node->next = *ns;
    *ns = node;
    (*ns)->index = node->index + 1;
    return;
}



int stack_pop(NumberStack **ns) {
    int value;
    NumberStack *dummy;
    
    if((*ns)->index == -1) {
        printf("Stack is empty");
        return (*ns)->value;
        
    } else {                 
        value = (*ns)->value;
        dummy = *ns;
        *ns = (*ns)->next;
        (*ns)->index = dummy->index - 1;
        free(dummy);
    }
    
    return value;
}

    
    
int test_stack() {
    NumberStack *ns = __get_node();
    stack_push(&ns, 5);
    stack_push(&ns, 4);
    printf("Popped : %d\n", stack_pop(&ns));
    printf("Popped : %d\n", stack_pop(&ns));
    printf("Popped : %d\n", stack_pop(&ns));
    printf("Popped : %d\n", stack_pop(&ns));
    stack_push(&ns, 6);
    printf("Popped : %d\n", stack_pop(&ns));
}
    