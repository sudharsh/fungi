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


int interpret_funge(InstructionPointer *ip, char **funge)
{
    char instruction = tolower(funge[ip->delta.row][ip->delta.col]);

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
            __debug("Processing %c %d times\n", instruction, ip->iteration_count);
        
            /* Execute the current iteration n times. Mostly its only 1,
               unless k instruction is reached */

            for (curr_instruction_iter_count = 0;
                 curr_instruction_iter_count < ip->iteration_count;
                 curr_instruction_iter_count++)
                {
                    switch(instruction) {
                        /* 
                           Direction instructions
                        */
                    case '>': /* Move east */
                        ip->direction = MOVE_EAST;
                        break;
                    case '<': /* Move west */
                        ip->direction = MOVE_WEST;
                        break;
                    case '^': /* Move north */
                        ip->direction = MOVE_NORTH;
                        break;
                    case 'v': /* Move south */
                        ip->direction = MOVE_SOUTH;
                        break;
                    case 'r': /* Reflect */
                        ip->delta.row = (ip->delta.row) * -1;
                        ip->delta.col = (ip->delta.col) * -1;
                        break;
                    case '#': /* Trampoline. Skip the next cell */
                        move_ip(ip, ip->direction);
                        break;
                        
                    turn_right: /* Hehe :D */
                    case ']': /* Turn right */
                        switch(ip->direction) {
                        case MOVE_EAST:
                            ip->direction = MOVE_SOUTH;
                            break;
                        case MOVE_WEST:
                            ip->direction = MOVE_NORTH;
                            break;
                        case MOVE_SOUTH:
                            ip->direction = MOVE_WEST;
                            break;
                        case MOVE_NORTH:
                            ip->direction = MOVE_EAST;
                            break;
                        }
                        break;
                    turn_left: /* I ain't afraid of no steenking velociraptor */
                    case '[': /* Turn Left */
                        switch(ip->direction) {
                        case MOVE_EAST:
                            ip->direction = MOVE_NORTH;
                            break;
                        case MOVE_WEST:
                            ip->direction = MOVE_SOUTH;
                            break;
                        case MOVE_SOUTH:
                            ip->direction = MOVE_EAST;
                            break;
                        case MOVE_NORTH:
                            ip->direction = MOVE_WEST;
                            break;
                        }
                        break;
                    case 'j':
                        popped = INSTRUCTION_POP(ip);
                        if (popped < 0) /* If negative value, then reverse direction of jump */
                            ip->direction = ip->direction * -1;
                        popped = abs(popped);
                        for (iter = 0; iter < popped; popped++)
                            move_ip(ip, ip->direction);
                        /* Restore the opposite direction */
                        ip->direction = ip->direction * -1;
                        break;
                    case 'k':
                        popped = INSTRUCTION_POP(ip);
                        __debug("Next instruction will be executed %d times\n", popped);
                        next_instruction_iter_count = popped;
                        break;
                    case '?':
                        ip->direction = __get_random_direction();
                        break;
                    case 'x': /* Absolute vector */
                        update_ip_by_offset(ip, INSTRUCTION_POP(ip),
                                            INSTRUCTION_POP(ip));
                        break;
        
                        /*
                          Instructions to print stuff on screen
                        */
                    case '.': /* Print integer */
                        printf("%d", INSTRUCTION_POP(ip));
                        break;
                    case ',': /* Print ASCII */
                        printf("%c", INSTRUCTION_POP(ip));
                        break;

                        /*
                          Input instructions
                        */
                    case '&':
                        scanf("%d", &input);
                        INSTRUCTION_PUSH(ip, input);
                        break;
                    case '~':
                        scanf("%c", &input);
                        INSTRUCTION_PUSH(ip, input);
                        break;
                
                        /*
                          Stack Manipulation
                        */
                    case ':': /* Duplicate top value in the stack. Pop once and push twice */
                        popped = INSTRUCTION_POP(ip);
                        INSTRUCTION_PUSH(ip, popped);
                        INSTRUCTION_PUSH(ip, popped);
                        break;	    
                    case '$': /* Pop and discard */
                        INSTRUCTION_POP(ip);
                        break;
                    case '\\': /* Swap the top 2 elements */
                        a = INSTRUCTION_POP(ip);
                        b = INSTRUCTION_POP(ip);
                        INSTRUCTION_PUSH(ip, a);   
                        INSTRUCTION_PUSH(ip, b);
                        break;
                    case 'n': /* Clear Stack */
                        while (INSTRUCTION_POP(ip) != NULL)
                            ;
                        break;

                        /*
                          Conditional Instructions
                        */
                    case '_': /* Horizontal If-else */
                        popped = INSTRUCTION_POP(ip);
                        if (popped)
                            ip->direction = MOVE_WEST;
                        else
                            ip->direction = MOVE_EAST;
                        break;
                    case '|':
                        popped = INSTRUCTION_POP(ip);
                        if (popped)
                            ip->direction = MOVE_NORTH;
                        else
                            ip->direction = MOVE_SOUTH;
                        break;
                   
                        /*
                          Logical instructions
                        */
                    case '!': /* Pop the element of the stack and negate it */
                        popped = INSTRUCTION_POP(ip);
                        if (popped) {
                            INSTRUCTION_PUSH(ip, 0);
                            break;
                        }
                        INSTRUCTION_PUSH(ip, 1);
                        break;
                    case '`': /* check if b > a. if yes push 1, else 0 */
                        a = INSTRUCTION_POP(ip);
                        b = INSTRUCTION_POP(ip);
                        if (b > a)
                            INSTRUCTION_PUSH(ip, 1);
                        else
                            INSTRUCTION_PUSH(ip, 0);
                        break;
                    case 'w':
                        a = INSTRUCTION_POP(ip);
                        b = INSTRUCTION_POP(ip);
                        if (b > a)
                            goto turn_right;
                        else
                            if (b < a)
                                goto turn_left;
                        break; /* Don't change the delta */                        

                        /*
                          fungi process controller
                        */
                    case '@': /* End current IP */
                        return FALSE;
                    case 'q': /* Exit after cleaning up. No concurrent IPs yet.
                                 so is similar to '@' */
                        printf( "FSSFSFS\n");                        exit(cleanup(ip, funge, TRUE));

                        /*
                          String Mode
                        */
                    case '"':
                        __debug("Entering string mode\n");

                        /* Keep moving and pushing the character to the stack till we reach the matching '"' at the other end */
                        while((move_ip(ip, ip->direction)) && (c = funge[ip->delta.row][ip->delta.col]) != '"') {
                            __debug("%p\n", ip->stack);
                            INSTRUCTION_PUSH(ip, c);
                        }

                        __debug("Leaving string mode %c\n", instruction);
                        break;
            
        
                    default:
                        /* instruction is *either* a digit or is in abcde.. or in other words a valid hex */
                        if(isdigit(instruction) || (instruction >= 0x61 && instruction <= 0x66) ) {
                            if (instruction >= 0x61 && instruction <= 0x66)
                                instruction = 10 + (instruction - 'a'); /* Convert hex to decimal */
                            INSTRUCTION_PUSH(ip, instruction - 48); /* convert ascii -> decimal and push it to the stack */
                            __debug("Digit found. Pushing %d to the number stack\n", instruction - 48);
                        }
                        else {
                            if (instruction == '/' || instruction ==  '*' || \
                                instruction == '+' || instruction == '-' ||  \
                                instruction == '%') {
                                a = INSTRUCTION_POP(ip);
                                b = INSTRUCTION_POP(ip);
                                __debug("Popped %d and %d\n", a, b);

                                /* Push the results back to the stack */
                                switch(instruction) {
                                case '/':
                                    INSTRUCTION_PUSH(ip, b/a);
                                    break;
                                case '*':
                                    INSTRUCTION_PUSH(ip, b*a);
                                    break;
                                case '+':
                                    INSTRUCTION_PUSH(ip, a+b);
                                    break;
                                case '-':
                                    INSTRUCTION_PUSH(ip, b-a);
                                    break;
                                case '%':
                                    INSTRUCTION_PUSH(ip, b%a);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                } /* end iter loop */

            /* The next iteration will be repeated 'next_instruction_iter_count' times
               If its 0. the next iteration will be skipped */
            ip->iteration_count = next_instruction_iter_count;
            
        } /* end if */
    
    /* Move along in the same direction */
    if (move_along)
        move_ip(ip, ip->direction);

    __debug("Finished processing '%c' instruction\n", instruction);
    __debug("-------------------------------\n");
    return TRUE;
}
