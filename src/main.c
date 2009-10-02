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
#include <ctype.h>
#include <config.h>

#include "main.h"


int interpret_funge(InstructionPointer *ip_ptr, char **funge)
{

    char command = funge[ip_ptr->row][ip_ptr->col];
    printf("%c ", command);

    if (command == ' ' || !isascii(command)) {
        printf( "Whitespace/Non ascii command. Processing last seen valid command %c", ip_ptr->last_command);
        command = ip_ptr->last_command;
    }
        
	switch(command) {
    case '>': /* Move east */
        update_ip(ip_ptr, 0, 1);
        break;
    case '<': /* Move west */
        update_ip(ip_ptr, 0, -1);
        break;
    case '^': /* Move north */
        update_ip(ip_ptr, -1, 0);
        break;
    case 'v': /* Move south */
        update_ip(ip_ptr, 1, 0);
        break;
    case 'r': /* Reflect */
        ip_ptr->row = (ip_ptr->row) * -1;
        ip_ptr->col = (ip_ptr->col) * -1;
        break;
    case '@': /* End program */
        exit(1);
        break;
    }
    if (command != ' ')
        ip_ptr->last_command = command;    
}


int load_source(const char *source)
{
    InstructionPointer ip; /* Instruction Pointer */
    char **funge;
        
    ip.row = 0;
    ip.col = 0;
    
    FILE *file_ptr = fopen(source, "r");

	if (!file_ptr) {
		fprintf(stderr, "Error: No such file %s\n", source);
		return FALSE;
	}

    /* Get the funge size in first pass and initialise the data structures accordingly */
    funge = get_funge(file_ptr, &ip);

    while (TRUE)
        interpret_funge(&ip, funge);
    
            
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
