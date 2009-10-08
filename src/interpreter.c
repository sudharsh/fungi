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
#include <math.h>

int interpret_funge(InstructionPointer *ip_ptr, char **funge)
{
    char instruction = tolower(funge[ip_ptr->delta.row][ip_ptr->delta.col]);

    int a, b; /* For mathematical operations */
    int popped; /* popped right from the stack */
    int input;
    int move_along = TRUE;
    int invert_direction = FALSE;
    int iter, rand;
    int curr_instruction_iter_count;
    int next_instruction_iter_count = 1;
    char c; /* when we enter string mode */
    
    /* Do not consume any ticks if the current instruction is a <space> or ';' */        
    if (instruction != ';' && instruction != ' ')
        {        
            __debug("Processing %c %d times\n", instruction, ip_ptr->iteration_count);
        
            /* Execute the current iteration n times. Mostly its only 1,
               unless k instruction is reached */

            for (curr_instruction_iter_count = 0;
                 curr_instruction_iter_count < ip_ptr->iteration_count;
                 curr_instruction_iter_count++)
                {
                    switch(instruction) {
                        /* 
                           Direction instructions
                        */
                    case '>': /* Move east */
                        ip_ptr->direction = MOVE_EAST;
                        break;
                    case '<': /* Move west */
                        ip_ptr->direction = MOVE_WEST;
                        break;
                    case '^': /* Move north */
                        ip_ptr->direction = MOVE_NORTH;
                        break;
                    case 'v': /* Move south */
                        ip_ptr->direction = MOVE_SOUTH;
                        break;
                    case 'r': /* Reflect */
                        ip_ptr->delta.row = (ip_ptr->delta.row) * -1;
                        ip_ptr->delta.col = (ip_ptr->delta.col) * -1;
                        break;
                    case '#': /* Trampoline. Skip the next cell */
                        move_ip(ip_ptr, ip_ptr->direction);
                        break;
                    case ']': /* Turn right */
                        switch(ip_ptr->direction) {
                        case MOVE_EAST:
                            ip_ptr->direction = MOVE_SOUTH;
                            break;
                        case MOVE_WEST:
                            ip_ptr->direction = MOVE_NORTH;
                            break;
                        case MOVE_SOUTH:
                            ip_ptr->direction = MOVE_WEST;
                            break;
                        case MOVE_NORTH:
                            ip_ptr->direction = MOVE_EAST;
                            break;
                        }
                        break;
                    case '[': /* Turn Left */
                        switch(ip_ptr->direction) {
                        case MOVE_EAST:
                            ip_ptr->direction = MOVE_NORTH;
                            break;
                        case MOVE_WEST:
                            ip_ptr->direction = MOVE_SOUTH;
                            break;
                        case MOVE_SOUTH:
                            ip_ptr->direction = MOVE_EAST;
                            break;
                        case MOVE_NORTH:
                            ip_ptr->direction = MOVE_WEST;
                            break;
                        }
                        break;
                    case 'j':
                        popped = stack_pop(&(ip_ptr)->stack);
                        if (popped < 0) /* If negative value, then reverse direction of jump */
                            ip_ptr->direction = ip_ptr->direction * -1;
                        popped = abs(popped);
                        for (iter = 0; iter < popped; popped++)
                            move_ip(ip_ptr, ip_ptr->direction);
                        /* Restore the opposite direction */
                        ip_ptr->direction = ip_ptr->direction * -1;
                        break;
                    case 'k':
                        popped = stack_pop(&(ip_ptr)->stack);
                        __debug("Next instruction will be executed %d times\n", popped);
                        next_instruction_iter_count = popped;
                        break;
        
                        /*
                          Instructions to print stuff on screen
                        */
                    case '.': /* Print integer */
                        printf("%d", stack_pop(&(ip_ptr)->stack));
                        break;
                    case ',': /* Print ASCII */
                        printf("%c", stack_pop(&(ip_ptr)->stack));
                        break;

                        /*
                          Input instructions
                        */
                    case '&':
                        scanf("%d", &input);
                        stack_push(&(ip_ptr)->stack, input);
                        break;
                    case '~':
                        scanf("%c", &input);
                        stack_push(&(ip_ptr)->stack, input);
                        break;
                
                        /*
                          Stack Manipulation
                        */
                    case ':': /* Duplicate top value in the stack. Pop once and push twice */
                        popped = stack_pop(&(ip_ptr)->stack);
                        stack_push(&(ip_ptr)->stack, popped);
                        stack_push(&(ip_ptr)->stack, popped);
                        break;	    
                    case '$': /* Pop and discard */
                        stack_pop(&(ip_ptr)->stack);
                        break;
                    case '\\': /* Swap the top 2 elements */
                        a = stack_pop(&(ip_ptr)->stack);
                        b = stack_pop(&(ip_ptr)->stack);
                        stack_push(&(ip_ptr)->stack, b);   
                        stack_push(&(ip_ptr)->stack, a);
                        break;

                        /*
                          Conditional Instructions
                        */
                    case '_': /* Horizontal If-else */
                        popped = stack_pop(&(ip_ptr)->stack);
                        if (popped)
                            ip_ptr->direction = MOVE_WEST;
                        else
                            ip_ptr->direction = MOVE_EAST;
                        break;
                    case '|':
                        popped = stack_pop(&(ip_ptr)->stack);
                        if (popped)
                            ip_ptr->direction = MOVE_NORTH;
                        else
                            ip_ptr->direction = MOVE_SOUTH;
                        break;

                        /*
                          Logical instructions
                        */
                    case '!': /* Pop the element of the stack and negate it */
                        popped = stack_pop(&(ip_ptr)->stack);
                        if (popped) {
                            stack_push(&(ip_ptr)->stack, 0);
                            break;
                        }
                        stack_push(&(ip_ptr)->stack, 1);
                        break;
                    case '`': /* check if b > a. if yes push 1, else 0 */
                        a = stack_pop(&(ip_ptr)->stack);
                        b = stack_pop(&(ip_ptr)->stack);
                        if (b > a)
                            stack_push(&(ip_ptr)->stack, 1);
                        else
                            stack_push(&(ip_ptr)->stack, 0);
                        break;

                        /*
                          fungi process controller
                        */
                    case '@': /* End current IP */
                        return FALSE;
                    case 'q':
                        exit(stack_pop(&(ip_ptr)->stack));

                        /*
                          String Mode
                        */
                    case '"':
                        __debug("Entering string mode\n");

                        /* Keep moving and pushing the character to the stack till we reach the matching '"' at the other end */
                        while((move_ip(ip_ptr, ip_ptr->direction)) && (c = funge[ip_ptr->delta.row][ip_ptr->delta.col]) != '"')
                            stack_push(&(ip_ptr)->stack, c);

                        __debug("Leaving string mode %c\n", instruction);
                        break;
            
        
                    default:
                        /* instruction is *either* a digit or is in abcde.. or in other words a valid hex */
                        if(isdigit(instruction) || (instruction >= 0x61 && instruction <= 0x66) ) {
                            if (instruction >= 0x61 && instruction <= 0x66)
                                instruction = 10 + (instruction - 'a'); /* Convert hex to decimal */
                            stack_push(&(ip_ptr)->stack, instruction - 48); /* convert ascii -> decimal and push it to the stack */
                            __debug("Digit found. Pushing %d to the number stack\n", instruction - 48);
                        }
                        else {
                            if (instruction == '/' || instruction ==  '*' || \
                                instruction == '+' || instruction == '-' ||  \
                                instruction == '%') {
                                a = stack_pop(&(ip_ptr)->stack);
                                b = stack_pop(&(ip_ptr)->stack);
                                __debug("Popped %d and %d\n", a, b);

                                /* Push the results back to the stack */
                                switch(instruction) {
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
                        break;
                    }
                } /* end iter loop */

            /* The next iteration will be repeated 'next_instruction_iter_count' times
               If its 0. the next iteration will be skipped */
            ip_ptr->iteration_count = next_instruction_iter_count;
            
        } /* end if */
    
    /* Move along in the same direction */
    if (move_along)
        move_ip(ip_ptr, ip_ptr->direction);

    __debug("Finished processing '%s' instruction", instruction);
    __debug("-------------------------------\n");
    return TRUE;
}
