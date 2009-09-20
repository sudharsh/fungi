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

#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include <config.h>

#include "main.h"


int process_command(char command, FILE *file_ptr, coordinates *ip_ptr)
{	
	switch(command) {
	   case '>':
           update_ip(ip_ptr, 0, 1);
           break;
	   case '<':
           update_ip(ip_ptr, 0, -1);
           break;
	   case '^':
           update_ip(ip_ptr, -1, 0);
           break;
	   case 'v':
           update_ip(ip_ptr, 1, 0);
           break;
    }
}


int interpret_source(const char *source)
{
    coordinates ip; /* Instruction Pointer */
    static char **funge;
    
    ip.x = 0;
    ip.y = 0;
    
    FILE *file_ptr = fopen(source, "r");

	if (!file_ptr) {
		fprintf(stderr, "Error: No such file %s\n", source);
		return FALSE;
	}

    /* Get the funge size in first pass and initialise the data structures accordingly */
    funge = get_funge(file_ptr);
            
    /* Clean up stuff */        
	fclose(file_ptr);
    free(funge);
    return TRUE;
}

		 
int main(int argc, char **argv) 
{
    /* Use getopts? */
	if (argc > 1)
		interpret_source(argv[1]);
	return 0;
}
