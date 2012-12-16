/* 
 * utils.c
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


#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "fungi.h"

/* Just a lazy helper function */
void print_current_coordinates(InstructionPointer *ip_ptr) {
    __debug("%d %d\n", ip_ptr->delta.row, ip_ptr->delta.col);
}

/* Taken from Linux code */
static char *strstrip(char *s)
{
        size_t size;
        char *end;
        size = strlen(s);
        
        if (!size)
                return s;
        end = s + size - 1;
        
        while (end >= s && isspace(*end))
                end--;
        *(end + 1) = '\0';

        /* Strip only trailing whitespaces
          while (*s && isspace(*s))
                s++;
        */

        return s;
}


char** get_funge(FILE *fptr, InstructionPointer *ip_ptr)
{
    int height = 0;
    int width = 0;
    
    int curr_width = 0; /* Width of the current active line */    
    char curr_c; /* current character */
    char **funge;
    char command;

    int i;

    while( (curr_c = getc(fptr)) != EOF) {
        if (curr_c == '\n') {
            if (width < curr_width)
                width = curr_width - 1;
            curr_width = 0;
            height++;
        }
        curr_width++;
    }
    rewind(fptr); /* Is there any way to avoid this pass */

    __debug("height: %d, width %d\n", height, width);
    ip_ptr->funge_height = height;
    ip_ptr->funge_width = width;
    
    funge = (char **) malloc(height * sizeof(char *));
    for(i = 0; i < height; i++) {
        funge[i] = (char *) malloc (width * sizeof(char *));
        fgets(strstrip(funge[i]), width + 2, fptr);
        __debug("Line %d: %s\n", i, strstrip(funge[i]));
    }
    
    return funge;
}


int __get_random_direction()
{
    int val;
    int inverse = 1;
    struct timeval tm;

    gettimeofday(&tm, NULL);
    srand(tm.tv_usec);

    /* Get a random number 0,1 and add 1 to it */
    val = (int)(2.0 * rand() / ( RAND_MAX + 1.0 ) ) + 1;
    
    __debug("%d\n", val);

    gettimeofday(&tm, NULL);
    srand(tm.tv_usec);

    if ((int)(2.0 * rand() / ( RAND_MAX + 1.0 ) ) == 0)
        inverse = -1;
    
    __debug("%d\n", val * inverse);
    return val * inverse;
}
        


int cleanup(InstructionPointer *ip, char **funge, int exit_code_from_stack) {
    int exit_code;
    int height, width = 0;
    if (exit_code_from_stack)
        exit_code = stack_pop(ip->stack);
    else
        exit_code = EXIT_SUCCESS;
    
    while (INSTRUCTION_POP(ip) != NULL)
        ;

    __debug("Clearing Funge\n");
    for (height = 0; height < ip->funge_height; height++) {
        free(funge[height]);
    }
    free(funge);
    __debug("Cleaning up done. Exiting with code %d\n", exit_code);
    return exit_code;
}
