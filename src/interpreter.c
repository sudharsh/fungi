/* 
 *  interpreter.c
 *  Author: Sudharshan "Sup3rkiddo" sudharsh@gmail.com>
 *  All Rights Reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

#include "fungi.h"


int interpret_funge(InstructionPointer *ip_ptr, char **funge)
{
    char command = tolower(funge[ip_ptr->row][ip_ptr->col]);

    int a, b; /* For mathematical operations */
    int popped;
    char c; /* when we enter string mode */
    
    __debug("Processing %c\n", command);

    switch(command) {
    case '>': /* Move east */
        move_ip(ip_ptr, MOVE_EAST);
        break;
    case '<': /* Move west */
        move_ip(ip_ptr, MOVE_WEST);
        break;
    case '^': /* Move north */
        move_ip(ip_ptr, MOVE_NORTH);
        break;
    case 'v': /* Move south */
        move_ip(ip_ptr, MOVE_SOUTH);
        break;
    case 'r': /* Reflect */
        ip_ptr->row = (ip_ptr->row) * -1;
        ip_ptr->col = (ip_ptr->col) * -1;
        break;

    case '.': /* Print integer */
	printf("%d", stack_pop(&(ip_ptr)->stack));
        move_ip(ip_ptr, ip_ptr->direction);
        break;

    case ',': /* Print ASCII */
        printf("%c", stack_pop(&(ip_ptr)->stack));
        move_ip(ip_ptr, ip_ptr->direction);
        break;

    case ':': /* Duplicate top value in the stack. Pop once and push twice */
        popped = stack_pop(&(ip_ptr)->stack);
	stack_push(&(ip_ptr)->stack, popped);
	stack_push(&(ip_ptr)->stack, popped);
	break;	    
        
    case '@': /* End program */
        return FALSE;

    case '"':
        __debug("Entering string mode\n");

        /* Keep moving pushing the character to the stack till we reach the matching '"' at the other end */
        while((move_ip(ip_ptr, ip_ptr->direction)) && (c = funge[ip_ptr->row][ip_ptr->col]) != '"')
	{
	    if (c == '"')
	        break;
            stack_push(&(ip_ptr)->stack, c);
                
	}
	__debug("Leaving string mode %c\n", command);
        move_ip(ip_ptr, ip_ptr->direction);
	
        break;
            
        
    default:
        /* command is *either* a digit or is in abcde.. or in other words a valid hex */
        if(isdigit(command) || (command >= 0x61 && command <= 0x66) ) {
            if (command >= 0x61 && command <= 0x66)
                command = 10 + (command - 'a'); /* Convert hex to decimal */
            stack_push(&(ip_ptr)->stack, command - 48); /* convert ascii -> decimal and push it to the stack */
            __debug("Digit found. Pushing %d to the number stack\n", command - 48);
        }
        else {
            if (command == '/' || command ==  '*' || \
                command == '+' || command == '-' ||  \
                command == '%') {
                a = stack_pop(&(ip_ptr)->stack);
                b = stack_pop(&(ip_ptr)->stack);
                __debug("Popped %d and %d\n", a, b);

                /* Push the results back to the stack */
                switch(command) {
                case '/':
                    stack_push(&(ip_ptr)->stack, b/a);
                    break;
                case '*':
                    stack_push(&(ip_ptr)->stack, b*a);
                    break;
                case '+':
                    stack_push(&(ip_ptr)->stack, a+b);
                    break;
                case '_':
                    stack_push(&(ip_ptr)->stack, b-a);
                    break;
                case '%':
                    stack_push(&(ip_ptr)->stack, b%a);
                    break;
                }
            }
        }

	/* Move along the same direction */
        move_ip(ip_ptr, ip_ptr->direction);
        break;
            
    }
    if (command != ' ' || !isdigit(command))
        ip_ptr->last_command = command;
    __debug("-----------------\n");
    return TRUE;
}
