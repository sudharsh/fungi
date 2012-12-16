/* 
 * stack.h
 * Written by Sudharshan S <sudharsh@gmail.com>
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


#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


typedef struct _FStackNode {
    int index;
    int value;
    struct _FStackNode *prev;
} FStackNode;


typedef struct _FStack {
    FStackNode *top;
    size_t size;
} FStack;


FStack* stack_push(FStack *ns, int nw);
int stack_pop(FStack *ns);

#endif
