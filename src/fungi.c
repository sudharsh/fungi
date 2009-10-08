/* 
 *  main.c
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


int load_source(const char *source)
{
    InstructionPointer ip; /* Instruction Pointer */
    char **funge;
        
    
    FILE *file_ptr = fopen(source, "r");

    if (!file_ptr) {
	    fprintf(stderr, "Error: No such file %s\n", source);
	    return FALSE;
    }

    ip.row = 0;
    ip.col = 0;
    ip.direction = MOVE_EAST;
    ip.iteration_count = 1;
    ip.stack = __get_node();

    /* Get the funge size in first pass and initialise the data structures accordingly */
    funge = get_funge(file_ptr, &ip);

    while (interpret_funge(&ip, funge))
        ;
                
    /* Clean up stuff */        
	fclose(file_ptr);
    free(funge);
    return TRUE;
}

		 
int main(int argc, char **argv) 
{
    /* Use getopts? */
	if (argc > 1)
		load_source(argv[1]);
	return 0;
}
