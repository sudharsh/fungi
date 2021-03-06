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
    int exit_code;
    
    char **funge;
        
    FILE *file_ptr = fopen(source, "r");

    if (!file_ptr) {
	    fprintf(stderr, "Error: No such file %s\n", source);
	    return FALSE;
    }

    /* We don't support concurrent IPs yet */
    ip.delta.row = 0;
    ip.delta.col = 0;
    ip.direction = MOVE_EAST;
    ip.iteration_count = 1;
    ip.stack = NULL;

    /* Get the funge size in first pass and initialise the data structures accordingly */
    funge = get_funge(file_ptr, &ip);
    fclose(file_ptr);

    /* The main Intrepreter loop */
    while (interpret_funge(&ip, funge))
        ;

    /* Done interpreting. Cleanup */
    __debug("Cleaning up..\n");
    exit_code = cleanup(&ip, funge, FALSE);

    return exit_code;
}

		 
int main(int argc, char **argv) 
{
    /* Use getopts? */
    if (argc > 1)
        load_source(argv[1]);
	return 0;
}
