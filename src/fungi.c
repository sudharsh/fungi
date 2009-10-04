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


int interpret_funge(InstructionPointer *ip_ptr, char **funge)
{
    char command = tolower(funge[ip_ptr->row][ip_ptr->col]);
    
    if (command == ' ' || !isascii(command) || !command) {
        printf("Whitespace/Non character command. Processing last seen valid command %c\n", ip_ptr->last_command);
        command = ip_ptr->last_command;
    }

    printf("Processing %c\n", command);

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
    case '@': /* End program */
        return FALSE;
    default:
        /* command is *either* a digit or is in abcde.. or in other words a valid hex */
        if(isdigit(command) ^ (command >= 0x61 && command <= 0x66) ) {
            if (command >= 0x61 && command <= 0x66)
                command = 10 + (command - 'a'); /* Convert hex to decimal */
            stack_push(&(ip_ptr)->stack, command);
            printf("Digit found. Pushing %d to the number stack\n", command);
            move_ip(ip_ptr, ip_ptr->direction);
        }
        break;
            
    }
    if (command != ' ' || !isdigit(command))
        ip_ptr->last_command = command;
    printf("-----------------\n");
    return TRUE;
}



int load_source(const char *source)
{
    InstructionPointer ip; /* Instruction Pointer */
    char **funge;
        
    ip.row = 0;
    ip.col = 0;
    ip.direction = MOVE_EAST;
    ip.stack = __get_node();
    
    FILE *file_ptr = fopen(source, "r");

	if (!file_ptr) {
		fprintf(stderr, "Error: No such file %s\n", source);
		return FALSE;
	}

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
