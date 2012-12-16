/* 
 * main.h
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

//#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <config.h>
#include <stdarg.h>

#include "stack.h"

#define DEBUG TRUE
#undef DEBUG

enum ip_direction {
    MOVE_WEST = 1,
    MOVE_EAST = -1,
    MOVE_NORTH = 2,
    MOVE_SOUTH = -2,
    FLY = 3
};

/* The InstructionPointer */
typedef struct _InstructionPointer {
    struct {
        int row;
        int col;
    } delta;
    int funge_height;
    int funge_width;
    int iteration_count; /* Number of Iterations for the next count */
    char last_instruction;
    enum ip_direction direction;
    FStack *stack;    
} InstructionPointer;


int __debug(const char *message, ...);

int interpret_funge(InstructionPointer *ip_ptr, char **funge);

/* A helper function */
void print_current_coordinates(InstructionPointer *ip);

/* Update the given instruction pointer given a delta */
int update_ip_by_offset(InstructionPointer *ip_ptr, int dr, int dc);

/* Read the source file and initialise funge space */
char** get_funge(FILE *fptr, InstructionPointer *ip);

/* Cleanup routines */
int cleanup(InstructionPointer *ip_ptr, char **funge, int exit_code_from_stack);


#define INSTRUCTION_PUSH(IP, VAL) IP->stack = stack_push(IP->stack, VAL)
#define INSTRUCTION_POP(IP)  stack_pop(IP->stack)
