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
#include <assert.h>

static FStackNode *__get_node()
{
    FStackNode *node = NULL;
    node = (FStackNode *) malloc(sizeof(FStackNode));
    return node;
}


FStack *stack_push(FStack *ns, int nw)
{
    __debug("Pushing to %p\n", ns);
    int index;
    FStackNode *new_node;
    new_node = __get_node();
    new_node->value = nw;
    if (!ns) {
        new_node->prev = NULL;
        ns = malloc(sizeof(FStack));
        ns->size = 0;
    }
    else
        new_node->prev = ns->top;
    ns->top = new_node;
    ns->size++;
    __debug("PUSH: Stack %p --> Size:%d Top:%p\n", ns, ns->size, ns->top);
    return ns;
}


int stack_pop(FStack *ns) {
    FStackNode *top;
    int topval;
    if (!ns) {
        __debug("Null stack\n");
        return NULL;
    }
    if (ns->size == 0 && !ns->top) {
        __debug("Empty stack\n");
        return NULL;
    }
    top = ns->top;
    topval = top->value;
    ns->top = ns->top->prev;
    free(top);
    ns->size--;
    __debug("POP: Stack %p --> Size:%d Stack top:%p\n", ns, ns->size, ns->top);
    return topval;
}
    
    
int test_stack() {
    FStack *ns = __get_node();
    stack_push(ns, 5);
    stack_push(ns, 4);
    __debug("Popped : %d\n", stack_pop(ns));
    __debug("Popped : %d\n", stack_pop(ns));
    __debug("Popped : %d\n", stack_pop(ns));
    __debug("Popped : %d\n", stack_pop(ns));
    stack_push(ns, 6);
    __debug("Popped : %d\n", stack_pop(ns));
}
    
